#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define TAMANHO 2000000				//iteracoes pra testar, 1kk = 0,5 min, 1,5kk = 2 min, 1,75kk = 3 min, 2kk = 4,5 min

#define VER 0						//se 1, nao imprime as informacoes
#define MOSTRAR 0					//mostrar arvore
	#define CHAVES 1						//imprimir os numeros dos nos
		#define TAM_NUM 4						//numero de digitos dessa iteracao
			#define MODO_IMPRESSAO 1				//entre arvore e bin, 1 e 2

//sistema operacional
//modo de impressao
//tipo de execução
//modo de percorrer arvore

struct no{

    int chave;
    int verificado;
    long int filhos;			//versao do linux n precisa dessa
    struct no* esquerda;
    struct no* direita;
};


struct descritor{

    struct no* raiz;
    int qtd;
    int qtd_folhas;				//folhas tende a ser 1/3 de qtd
};


typedef struct no elementos;
typedef struct descritor arvore;



arvore* criar(){

    arvore* apontamento;
    apontamento = (arvore*)malloc(sizeof(arvore));
    if(apontamento == NULL) exit(876);
    apontamento->raiz = NULL;
    apontamento->qtd = 0;
    return apontamento;
}


int inserir(arvore* z, int numero){

    if(z == NULL) return -1;

    elementos* novo;
    novo = (elementos*)malloc(sizeof(elementos));
    if(novo == NULL) return -2;
    novo->chave = numero;
    novo->filhos = 0;
    novo->verificado = 7;
    novo->direita = NULL;
    novo->esquerda = NULL;

    if(z->raiz == NULL){
        z->raiz = novo;
    }else{

        elementos* caminhar;
        caminhar = z->raiz;
        elementos* anterior;
        anterior = caminhar;

        int pode = 0;
        while(pode != 1){
        	
            anterior = caminhar;
            if(caminhar != NULL){
            	
            	anterior->filhos++;
                if(numero < caminhar->chave){
                    caminhar = caminhar->esquerda;
                    pode = 2;
                }else if(numero > caminhar->chave){
                    caminhar = caminhar->direita;
                    pode = 3;
                }else if(numero == caminhar->chave){
                    free(novo);
                    return 0;
                }
            }

            if(caminhar == NULL){
                if(pode == 2){
                    anterior->esquerda = novo;
                }else if(pode == 3){
                    anterior->direita = novo;
                }
                pode = 1;
            }
        }
    }
    z->qtd++;
    return 1;
}


int qts_folhas(struct no *filho, int paralelo){
    if(filho == NULL) return 0;
   
    if(filho->esquerda == NULL && filho->direita == NULL) return 1;
    return qts_folhas(filho->esquerda,paralelo) + qts_folhas(filho->direita,paralelo);
}

void embaralhar(long int* vetor){

	if(vetor == NULL) exit(222);
	srand(time(NULL));

	long int iteracoes = 0, ideal = TAMANHO, olhando, reflexo = -1;
	long int atual, novo;
	
	do{
		
		do{ olhando = rand() % ideal;
		}while(olhando == reflexo);
		reflexo = olhando;

		atual = vetor[iteracoes];
		novo = vetor[olhando];
		//printf("trocar %d em [%d] por %d em [%d]\n",atual,iteracoes,novo,olhando);
		vetor[iteracoes] = novo;
		vetor[olhando] = atual;
			
		iteracoes++;
	}while(iteracoes < ideal);
	
	return;
}

void percurso(struct no* filho){

    if(filho != NULL){
        percurso(filho->esquerda);
        percurso(filho->direita);
        free(filho);
        filho = NULL;
    }
    return;
}



void libera(arvore* z){

    if(z == NULL) return;
    if( z->raiz != NULL) percurso(z->raiz);
    z->qtd = 0;
    printf("liberado!\n");
    return;
}







int main(){

	int id, LINHAS;
	double inicio, fim;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &LINHAS);


	//------------------------------------------------------ METODO DE GALHOS
	
	double fim, inicio, paralelo, sequencial;
	arvore* z;
	long int* vetor;

	if(id == 0){
		
	    z = criar();
	
	    vetor = (long int*)malloc(TAMANHO*sizeof(long int));
	    for(int jj = 0; jj < TAMANHO; jj++) vetor[jj] = jj + 1;
		embaralhar(vetor);
		for(int jk = 0; jk < TAMANHO; jk++) inserir(z,vetor[jk]);
									
		long int media = TAMANHO / LINHAS, total = 0;
		struct no** galhos;
		
		
		if(LINHAS == 2 || LINHAS == 4){
				
			galhos = (struct no**)malloc(LINHAS*sizeof(struct no*));
				
			if(LINHAS == 2){
					
				if(z->raiz->esquerda != NULL) galhos[0] = z->raiz->esquerda;
				else{
					printf("Erro! Arvore zigue-zague\n");
					exit(750);
				}
				if(z->raiz->direita != NULL) galhos[1] = z->raiz->direita;
				else{
					printf("Erro! Arvore zigue-zague\n");
					exit(751);
				}
					
			}else{
					
				if(z->raiz->esquerda->esquerda != NULL) galhos[0] = z->raiz->esquerda->esquerda;
				else{
					printf("Erro! Arvore desbalanceada\n");
					exit(752);
				}
				if(z->raiz->direita->esquerda != NULL) galhos[1] = z->raiz->direita->esquerda;
				else{
					printf("Erro! Arvore desbalanceada\n");
					exit(753);
				}
				if(z->raiz->esquerda->direita != NULL) galhos[2] = z->raiz->esquerda->direita;
				else{
					printf("Erro! Arvore desbalanceada\n");
					exit(754);
				}
				if(z->raiz->direita->direita != NULL) galhos[3] = z->raiz->direita->direita;
				else{
					printf("Erro! Arvore desbalanceada\n");
					exit(755);
				}
			}
		}else{
			printf("Erro! o método Galhos não pode utilizar threads não expoentes de 2!\n");
			exit(756);
		}
		
		inicio = MPI_Wtime();
	}
	
	struct no** galho;
	galhos = (struct no**)malloc(sizeof(struct no*));
	long int designado, total = 0;
	
	MPI_Scatter(galhos, 1, MPI_ELEMENTOS, galho, 1, MPI_ELEMENTOS, 0, MPI_COMM_WORLD);
	designado = qts_folhas((galho*),1);
	
	printf("Processo %d achou %d folhas!\n",id,designado);
	MPI_Send(&designado, 1, MPI_ELEMENTOS, 0, 0, MPI_COMM_WORLD);
	
	if(rank == 0){
		
		long int receber;
		for(int i = 1; i < LINHAS; i++){
    		MPI_Recv(&receber, 1, MPI_ELEMENTOS, i, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    		total += receber;
		}
		total += designado;
		
		printf("O total foi de %d folhas!",total);
		fim = MPI_Wtime();
		printf("Quantidade de Folhas totais: %d, encontradas pelas threads: x paralelamente em %lf segundos!",total,(fim-inicio));
		libera(z);
	}

    MPI_Finalize();
    return 0;
}