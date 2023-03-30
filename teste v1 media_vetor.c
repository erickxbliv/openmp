#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define TAM 500000000

int main(){

    srand(time(NULL));

    #pragma omp num_threads(2)
    {

        int vetor[TAM],i,soma;
        float total;
        double inicio,fim;

        inicio = omp_get_wtime();
        #pragma omp for
        for(i = 0; i < TAM; i++){

            vetor[i] = rand() % 2;
            soma = soma + vetor[i];

        }
        total = soma/500000000.0;
        fim = omp_get_wtime();

        printf("\nem %ld a media entre todas as pos do vetor deu: %f\n",(fim-inicio),total);
    }

    return 0;
}
