#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define TAMANHO 1000000000
#define LINHAS 4

/*

SEGUNDA PERGUNTA: Quais variáveis são compartilhadas entre as threads, e quais são privadas ?

Nos trechos que possuem uma regiao critica, "total" e uma variavel compartilhada, assim como "tamanho" e global e disponivel para todas
Nos trechos de reduction, total se torna uma variavel privada, assim como o contador "j" e obrigatoriamente privada, declarada assim manualmente

*/

int main(){
	
	double total = 0.0, inicio, fim, delta, seq, melhor;
	int linhas;
	
	inicio = omp_get_wtime();
	
	for(int i = 1; i <= TAMANHO; i++){
		if(TAMANHO % i == 0){
			//printf("%.0f + (%d -> %d)\n",total,i,(TAMANHO/i));
    		total += i;
		}
	}
	
	fim = omp_get_wtime();
	seq = (fim - inicio);
	melhor = seq;
	printf("sequencialmente obtive a soma %.0f dos divisores de %d, em %f segundos\n\n",total,TAMANHO,seq);
	
	
	/*
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	long int min, max, j;
    	min = omp_get_thread_num()*(TAMANHO/LINHAS);
    	max = (omp_get_thread_num()+1)*(TAMANHO/LINHAS);
    	
    	for(j = min; j < max; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    				//printf("%f + %d = %f\n",total,j,(total+j));
    				total = total + j;
    			
			}
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
    printf("com %d threads e um for manual utilizando critical, obtive %.0f em %f segundos, %f por thread\n\n",LINHAS,total,delta,(delta/LINHAS));
	*/
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	long int j;
    	#pragma omp for reduction (+: total)
    	for(j = 1; j <= TAMANHO; j++){
    		
    		if(TAMANHO % j == 0){
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
    printf("com %d threads e um omp for simples utilizando reduction, obtive %.0f em %f segundos, %f por thread\n\n",LINHAS,total,delta,(delta/LINHAS));
    
    
    
    inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("com %d threads e um omp for simples usando area critica, obtive %.0f em %f segundos, %f por thread\n\n\n\n",LINHAS,total,delta,(delta/LINHAS));
	
	
	
	
	
	
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(static)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("for estatico critico e as threads dividem igualmente as it. e trocam turnos , obtive %.0f em %f segundos\n\n",total,delta);
	
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(static, 1)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("for estatico critico iterando um por um uma de cada vez, obtive %.0f em %f segundos\n\n",total,delta);
	

	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(static) reduction(+:total)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("for estatico reduction e as threads dividem igualmente as it. e trocam turnos , obtive %.0f em %f segundos\n\n",total,delta);
	
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(static, 1) reduction(+:total)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("for estatico reduction iterando um por um uma de cada vez, obtive %.0f em %f segundos\n\n\n\n",total,delta);
   
   

   	
   	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(dynamic)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("dinamico critico com its. uma por uma onde as threads revezam aleatoriamente, obtive %.0f em %f segundos\n\n",total,delta);
	
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(dynamic,(TAMANHO/LINHAS))
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			#pragma omp critical
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("dinamico critico onde as threads trocam turnos pras its. divididas igualmente, obtive %.0f em %f segundos\n\n",total,delta);
	

	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(dynamic) reduction(+:total)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("dinamico reduction com its. uma por uma onde as threads revezam aleatoriamente, obtive %.0f em %f segundos\n\n",total,delta);
	
	
	
	inicio = omp_get_wtime();
    total = 0.0;
    #pragma omp parallel num_threads(LINHAS)
    {
    	#pragma omp for schedule(dynamic,(TAMANHO/LINHAS)) reduction(+:total)
    	for(int j = 1; j <= TAMANHO; j++){
    		if(TAMANHO % j == 0){
    			total += j;
			}	
		}
    }
    
    fim = omp_get_wtime();
    delta = (fim - inicio);
    if(delta < melhor) melhor = delta;
	printf("dinamico reduction onde as threads trocam turnos pras its. divididas igualmente, obtive %.0f em %f segundos\n\n",total,delta);

	printf("O speedup foi de %f, e a eficiencia foi de %f",(seq/melhor),((seq/melhor)/LINHAS));
	getchar();
   
    return 0;
}