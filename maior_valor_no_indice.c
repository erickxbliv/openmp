#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define TAMANHO 50000000			//quanto MAIOR for esse valor, mais a probabilidade vai tender que pelo menos uma vez apareca os top primeiros da lista dos maiores possiveis
#define MAXIMO 100000				//maior valor q o rand consegue pegar
#define LINHAS 4

//#define MAIOR_DBL 10000000000000000
//#define MAIOR_INT 100000000


/*

100 numeros entre 1 e 1000, traz a probabilidade como todas as dezenas nesse intervalo (1, 11, 21, 31... 161... 451... 761... 991)
o maximo que o rand pode trazer é 100.000 (cem mil), multiplicando temos 10 bilhoes. quanto mais proximo o TAMANHO for desse maximo,
menos diferenca gritante vai existir entre os maiores numeros encontrados, mesmo eles sendo mesmo 100% aleatorios

*/

int main(){
	
	if(TAMANHO > 50000000) exit(999);
	
	int novo_1 = -1, novo_2 = -1, ultimo_rand = -1, indice = 0;
	double *vetor = (double*)malloc(TAMANHO*sizeof(double)), resultado, t1, t2, maior = 0.0, inicio, fim;
	
	srand(time(NULL));
	
	for(long int ii = 0; ii < TAMANHO; ii++){
		
		novo_1 = (rand() % MAXIMO) + 1;
		if(novo_1 == ultimo_rand) ii--;
		else{
			t1 = novo_1;
			ultimo_rand = novo_1;
			
			while(novo_2 != ultimo_rand){
				
				novo_2 = (rand() % MAXIMO) + 1;
				if(novo_2 != ultimo_rand){
					t2 = novo_2;
					ultimo_rand = novo_2;
				}
			}
		}
		
		resultado = t1 * t2;
		vetor[ii] = resultado;
	}
	
	//for(int a = 0; a < TAMANHO; a++){printf("%f\n",vetor[a]);}
	
	inicio = omp_get_wtime();
	
	#pragma omp parallel num_threads(LINHAS) 
	{
		
		double maior_thread = 0.0;
		int indice_thread = 0;
		
		#pragma omp for
		for(long int kk = 0; kk < TAMANHO; kk++){
			
			if(maior_thread < vetor[kk]){
				indice_thread = kk;
				maior_thread = vetor[kk];
			} 
			//printf("%d - atual maior = %.0f\n",omp_get_thread_num(),maior_thread);
			
		}
		
		#pragma omp critical
		if(maior_thread > maior){
			indice = indice_thread;
			maior = maior_thread;
		} 
		
		printf("O maior que a thread %d achou foi %.0f no indice %d\n\n",omp_get_thread_num(),maior_thread,indice_thread);
		
	}
	
	fim = omp_get_wtime();
	printf("O maior valor que havia nesse vetor era %.0f no indice %d, em %f segundos!",maior,indice,(fim-inicio));
	
	return 0;
}