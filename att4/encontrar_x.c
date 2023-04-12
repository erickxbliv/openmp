#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAMANHO 250000000
#define X 5
#define LIMITE 10
#define LINHAS 4

int main(){
	
	if(LIMITE > TAMANHO) return -1;
	
	long int *vetor = (long int*)malloc(TAMANHO*sizeof(long int)), i, antigo = -1, novo;
	srand(time(NULL));
	for(i = 0; i < TAMANHO; i++){
		
		novo = (rand() % LIMITE) + 1;
		if(novo == antigo) i--;
		else{
			vetor[i] = novo;
			antigo = novo;
		}
	}
	
	double quantidade = 0.0, inicio, fim, seq, delta;	
	
	inicio = omp_get_wtime();
	for(i = 0; i < TAMANHO; i++){		
		if(vetor[i] == X) quantidade++;
	}
	
	fim = omp_get_wtime();
	seq = fim - inicio;
	printf("Serialmente obtive %.0f em %f segundos\n",quantidade,seq);
	
	
	quantidade = 0.0;
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads (LINHAS)
	{
		long int j;
		#pragma omp for reduction (+:quantidade)
		for(j = 0; j < TAMANHO; j++){
			if(vetor[j] == X) quantidade++;
		}
	}
	
	fim = omp_get_wtime();
	delta = fim - inicio;
	printf("Paralelamente com %d threads obtive %.0f em %f segundos\n",LINHAS,quantidade,delta);
	
	printf("\no speedup foi de %f e a eficiencia de %f\n",(seq/delta),((seq/delta)/LINHAS));
	

	
	return 0;
}