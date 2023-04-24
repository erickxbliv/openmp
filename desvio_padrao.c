#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define TAMANHO 250000000			//quanto maior o valor mais parecido sera o resultado de diferentes execucoes
#define MAXIMO 1000
#define LINHAS 4

double calculo(int *vetor, int linhas, double *tempo){		//o codigo executado por uma thread alterna entre 0.07 e 0.01 segundos de diferenca do sequencial real, pra + ou pra -
	
	double media = 0.0, somatorio = 0.0, DP = 0.0, inicio, fim;
	
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads(linhas)
	{
		
		//tirar media
		#pragma omp for reduction(+:media)
		for(long int jj = 0; jj < TAMANHO; jj++){
				media += vetor[jj];
		}
		
		#pragma omp master
		{
			media = (media/TAMANHO);
															//printf("media desses numeros: %.3f\n\n",media);
		}
		
		#pragma omp barrier
		
		double desvio = 0.0;
		#pragma omp for reduction(+:somatorio)
		for(long int kk = 0; kk < TAMANHO; kk++){
				
				desvio = vetor[kk] - media;
															//printf("valor %d menos a media media %.3f = %.3f ^ 2 = %.3f\n",vetor[kk],media,desvio,desvio*desvio);
				desvio = desvio * desvio;
				somatorio += desvio;
		}
		#pragma omp barrier
		
		#pragma omp master
		{
			DP = (somatorio/TAMANHO);
															//printf("\na soma desses quadrados %.3f, e sua media: %.3f",somatorio,DP);
			DP = sqrt(DP);
															//printf(", sendo sua raiz %.3f (desvio padrao)\n",DP);
		}
		
	}
	fim = omp_get_wtime();
	
	printf("%d threads: Resultado: %f, em aprox %f segundos\n\n",linhas,DP,(fim-inicio));
	if((fim-inicio) < (*tempo)) (*tempo) = (fim-inicio);
	
	return DP;
}




int main(){
	
	int *vetor = (int*)malloc(TAMANHO*sizeof(int)), antigo = -1, novo;
	double *seq = (double*)malloc(sizeof(double)), *par = (double*)malloc(sizeof(double)), *enviar;
	(*seq) = 1000000000.0; (*par) = 1000000000.0;
	
	srand(time(NULL));
	
	//criar amostra
	for(long int ii = 0; ii < TAMANHO; ii++){
		novo = (rand() % MAXIMO) + 1;
		if(novo == antigo) ii--;
		else{
			vetor[ii] = novo;
															//printf("%d numero : %d\n",(ii+1),novo);
			antigo = novo;
		}
	}
	
	enviar = seq;
	for(int ij = 1; ij <= LINHAS; ij++){
		calculo(vetor,ij,enviar);
		enviar = par;
	}
	
	printf("O speedup foi de %f, e a eficiencia foi de %f",((*seq)/(*par)),(((*seq)/(*par))/LINHAS));
	
	free(vetor);
	free(seq);
	free(par);
	
	return 0;
}

