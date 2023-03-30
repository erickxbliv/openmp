#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAMANHO 500000000
#define LINHAS 4

int main(){

    printf("\nvalor real de PI com 50 digitos de precisao: 3.14159265358979323846264338327950288419716939937510\n");

    double tamanho, inicio, fim, serial, paralelo;
    double pi, i, pedaco = 0.0, it, total_it, lado, area;
    tamanho = TAMANHO;

    it = 1.0 / tamanho;
    inicio = omp_get_wtime();
    for(i = 0; i < TAMANHO; i++){
        lado = (i + 0.5) * it; 
        area = lado * lado;
        pedaco = pedaco + 4.0 / (1.0 + area);
    }
    
    pi = it * pedaco;
    fim = omp_get_wtime();
    serial = (fim-inicio);
    printf("execucao sequencial conseguiu\t\t     %0.53f em %f segundos\n",pi,serial);

    pedaco = 0.0;
    inicio = omp_get_wtime();
    #pragma omp parallel private(lado,area) num_threads(LINHAS)
    {
        long int j;
        #pragma omp for reduction (+:pedaco)
        for(j = 0; j < TAMANHO; j++){
            lado = (j + 0.5) * it; 
            area = lado * lado;
            pedaco = pedaco + 4.0 / (1.0 + area);
        }
    }
    pi = it * pedaco;
    fim = omp_get_wtime();
    paralelo = (fim-inicio);
    printf("execucao paralela com %d threads conseguiu:   %0.53f em %f segundos\n\n",LINHAS,pi,paralelo);
    printf("O speedup foi de %f, e a eficiencia foi de %f!\n",(serial/paralelo),((serial/paralelo)/LINHAS));

    return 0;
}