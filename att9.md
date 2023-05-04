O OpenMPI nada mais é que uma forma de programação paralela utilizando *memória distribuida*, invés de memória compartilhada como é o caso do OpenMP, ou seja, quando a execução atribui às threads atividades especificas a serem realizadas, cada processo recebe sua própria memória local, assim, cada processo que é enviado para uma subdivisão da cpu, também recebe sua parcela de memória. O MPI representa um padrão para comunicação de dados e programação paralela, por isso seu nome é uma sigla para Message Pasing  (parallismo explicito)

Para implementar, primeiro é necesário instalar o OpenMPI, em qualquer sistema operacional de sua preferência. Para compilar, acaba sendo mais simples no Linux, com os comando "mpicc -o 'programa.exe' 'programa_fonte.c'" e para executar "mpiexec -n 1 (numero de processos) ./'programa.exe'".



 O que é ?

- Aplicações

- Implementações
