#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
//#include <windows.h>

#define TAMANHO 500000000
#define LINHAS 4

int main(){
	
	srand(time(NULL));
	long int *vetor = (long int*)malloc(TAMANHO*sizeof(long int)), i, total = 0, value = 0;
	
	for(i = 0; i < TAMANHO; i++){
		vetor[i] = rand() % 2;						//infelizmente por causa da velocidade, as chances de cair 0 e 1 sao 50% cada, e maior a amostra mais visivel isso
													//printf("%d : %d\n",i,vetor[i]);
		value = value + vetor[i];
	}
	
	printf("O valor real no vetor e %d\n\n",value);
	
	double inicio = omp_get_wtime(), juncao, tempo, media, teste, paralelo, serial, final;
	#pragma omp parallel num_threads(LINHAS)
	{
		
		long int min = omp_get_thread_num()*(TAMANHO/LINHAS), max = (omp_get_thread_num()+1)*(TAMANHO/LINHAS), j, parte = 0;
		double fim, delta;
		
		//#pragma omp for private(j)
		for(j = min; j < max; j++){
			parte = parte + vetor[j];
											//if(omp_get_thread_num() == 0) printf("%d : %d : %d\n",omp_get_thread_num(),j,vetor[j]);
											//Sleep(1000);
		}
		
		fim = omp_get_wtime();
		delta = fim - inicio;
		printf("A thread %d (de %d ate %d no vetor) capturou %d em %f segundos\n",omp_get_thread_num(),min,max,parte,delta);
		total = total + parte;
		juncao = juncao + delta;
	}
	
	tempo = juncao / LINHAS;
	paralelo = tempo;
	teste = total;
	media = teste / TAMANHO;
	printf("\nO total paralelo de %d threads com o vetor de %d dividido ficou %d \nsendo a media do vetor %lf em uma media de %f segundos\n\n\n",LINHAS,TAMANHO,total,media,tempo);
	
	
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads(LINHAS)
	{
		
		long int i, k = 0, parte = 0;
		double fim, delta;
		
		//#pragma omp for private(k)
		for(k = 0; k < TAMANHO; k++){
			parte = parte + vetor[k];
			
											//printf("aa %d\n\n",k);
											//Sleep(1000);
		}
		
		fim = omp_get_wtime();
		delta = fim - inicio;
		printf("A thread %d analisou %d em %f segundos\n",omp_get_thread_num(),parte,delta);
		total = parte;
		juncao = juncao + delta;
	}
	
	tempo = juncao / LINHAS;
	teste = total;
	media = teste / TAMANHO;
	printf("\nO total paralelo de %d threads com o vetor de %d ficou %d \nsendo a media do vetor %lf em uma media de %f segundos\n\n\n",LINHAS,TAMANHO,total,media,tempo);
	
	inicio = omp_get_wtime();
	value = 0;
	for(i = 0; i < TAMANHO; i++){
		value = value + vetor[i];
	}
	final = omp_get_wtime();
	
	serial = final - inicio;
	printf("A execucao sequencial gerou o valor %d, em %f segundos\n\n",value,serial);
	printf("O speedup foi de %f, e a eficiencia foi de %f!\n",(serial/paralelo),((serial/paralelo)/LINHAS));
	
	
	
	free(vetor);
	return 0;
}
