# OpenMP Tasks

As tasks em openMP são nada mais que pequenas divisões de tarefas entre as threads paralelizadas, de forma explícita e dinâmica, no sentido que são indeterminadas sub execuções, fazendo com que possam ser processadas enquanto for necessário. As tasks são incluidas em listas de tarefas e a velocidade de execução ou ordem depende exclusivamente da máquina e são indefinidas, fazendo com que a tarefa possa ser adiada ou realizada imediatamente.

* Essas são também umas das *principais diferenças* entre as openMP tasks e as openMP sections, já que além de estáticas, as openMp sections são bem divididas entre as threads, em ordem.
* Elas são muito úteis para equilibrar o trabalho das threads e também como já citado para iterações dinâmicas. Entretanto, não são capazes de serem aplicadas em todo ou qualquer problema, pois sem utilidade total, seu uso é descartável.
* A task que estiver sendo executada será a tarefa corrente ou atual.

# Implementação

As tasks podem ter quatro tipos de variaveis declaradas usando palavras reservadas, que seriam **private** (criar uma nova variavel local ao escopo de cada thread), firstprivate, que faz o mesmo da instrução anterior mas inicializa essa variável com algum valor pré existente dela, e a **shared** que intuitivamente é compartilhada e está disponível na memória para qualquer thread.

1. Primeiro inicializamos a região paralela, utilizando sempre "#pragma omp" para cada diretiva
2. Então, usamos a diretiva *single* como primeiro comando para inicializar a região da lista de tarefas.
3. A partir desse momento, será assinalada uma tarefa sempre que uma linha de código for executada com a diretiva *task*, seja isso feito de maneira dinâmica ou estática.
4. Finalizamos esta seção com uma barreira, pode ser a diretiva *taskwait* (barreira para a task e suas filhas), ou *taskgroup*, que barra toda a árvore que descende dessa task raiz
