# openMP Tasks

As tasks em openMP são nada mais que pequenas divisões de tarefas entre as threads paralelizadas, de forma explícita e dinâmica, no sentido que são indeterminadas sub execuções, fazendo com que possam ser processadas enquanto for necessário. As tasks são incluidas em listas de tarefas e a velocidade de execução ou ordem depende exclusivamente da máquina, fazendo com que a tarefa possa ser adiada ou realizada imediatamente.

* Essas são também umas das *principais diferenças* entre as openMP tasks e as openMP sections, já que além de estáticas, as openMp sections são bem divididas entre as threads, em ordem.
