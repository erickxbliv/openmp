# O que é MPI?

O OpenMPI nada mais é que uma forma de programação paralela utilizando *memória distribuida*, invés de memória compartilhada como é o caso do OpenMP, ou seja, quando a execução atribui às threads atividades especificas a serem realizadas, cada processo recebe sua própria memória local, assim, cada processo que é enviado para uma subdivisão da cpu, também recebe sua parcela de memória. O MPI representa um padrão para comunicação de dados e programação paralela, por isso seu nome é uma sigla para Message Pasing Interface (parallismo explicito).

# Suas aplicações

Ele é muito útil na paralelização, e tem uma função única de ranqueamento das threads, é uma forma bem menos implícita de representar o identificadores de cada parcela do processo. Todo código possui uma *mensagem*, que possui destino, origem e conteúdo, *grupo*, que são os processos, *comunicador*, que é um objeto local que possui o conjunto de processos que podem ser contactados e uma **função global** que contém todos os processos definidos pelo usuário.

# Sua implementação

* Para implementar, primeiro é necesário instalar o OpenMPI, em qualquer sistema operacional de sua preferência. 
* Para compilar, acaba sendo mais simples no Linux, com os comando "mpicc -o 'programa.exe' 'programa_fonte.c'" e para executar "mpiexec -n 1 (numero de processos) ./'programa.exe'".
* Como visto em aula, abaixo podemos ver um exemplo simples da implementação de um programa paralelizado utilizando memória distribuída.


#include <mpi.h>
int main(){
   
   MPI_Init(NULL, NULL);        //Iniciando MPI
   int ncpus;
   MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
   int meu_rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
         //Comando(s) a serem realizados por cada processo
         printf("Hello world do processador rank #%d/%d\n",meu_rank, ncpus);
   MPI_Finalize();              // Finalizando MPI
}
