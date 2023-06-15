#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAMANHO 2000000					//iteracoes pra testar, 1kk = 0,5 min, 1,5kk = 2 min, 1,75kk = 3 min, 2kk = 4,5 min

#define VER 0						//se 1, nao imprime as informacoes
#define MOSTRAR 0					//mostrar arvore
	#define CHAVES 1						//imprimir os numeros dos nos
		#define TAM_NUM 8						//numero de digitos dessa iteracao
			#define MODO_IMPRESSAO 2				//entre arvore e bin, 1 e 2

#define CRIAR 1
	#define SALVAR 0

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


int qts_folhas(struct no *filho){
    if(filho == NULL) return 0;
   
    if(filho->esquerda == NULL && filho->direita == NULL) return 1;
    return qts_folhas(filho->esquerda) + qts_folhas(filho->direita);
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


/*
void impressao(struct no* filho){
	
	switch(TAM_NUM){
	    case 1:
		    printf("%01d",filho->chave);
		    break;
	    case 2:
		    printf("%02d",filho->chave);
		    break;
	    case 3:
		    printf("%03d",filho->chave);
		    break;
	    case 4:
		    printf("%04d",filho->chave);
		    break;
	    case 5:
		    printf("%05d",filho->chave);
		    break;
	    case 6:
			printf("%06d",filho->chave);
		    break;
	    case 7:
		    printf("%07d",filho->chave);
		    break;
	    case 8:
		    printf("%08d",filho->chave);
		    break;
	}
	return;
}




void mostrar_csv(struct no* filho, int* x, int* y){
													
    if(filho != NULL){
    	
    	HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	int x_no = (*x), y_no = (*y);
    	
    	//gotoyx((*x),(*y));
		//SetConsoleTextAttribute(hConsole, 0x70);
		//if(CHAVES) impressao(filho);
		//else printf("O");
		
		//SetConsoleTextAttribute(hConsole, 7);
		//if(filho->esquerda != NULL || filho->direita != NULL) printf("%c",196);

    	(*y) += TAM_NUM + 1;
    	if(filho->direita != NULL) mostrar_csv(filho->direita,x,y);
    	
		if(filho->esquerda != NULL){
			if(filho->direita != NULL){
				
				(*x)++;
				//gotoyx((*x),((*y)- (2 + CHAVES)));
				//if(CHAVES) printf("%c%c%c",192,196,196);
				//else printf("%c%c",192,196);
				
				for(int i = x_no + 1; i < (*x); i++){
					//gotoyx(i,y_no + (TAM_NUM - 2));
					//gotoyx(i,y_no + ((TAM_NUM)/2));
					//printf("%c",179);
				}
			} 
			mostrar_csv(filho->esquerda,x,y);
		}
		(*y) -= (TAM_NUM + 1);
		
		
		
		
    }else return;
    
    
    
    return;
}

void mostrar_tree(struct no* filho, int* x, int* y){
		
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if(filho != NULL){
	
    	if(filho->direita != NULL){
    		(*y) += TAM_NUM;
    		mostrar_tree(filho->direita,x,y);
		} 
		
		gotoyx((*x),(*y));
		SetConsoleTextAttribute(hConsole, 0x70);
		if(CHAVES) impressao(filho);
		else printf("O");
		SetConsoleTextAttribute(hConsole, filho.verificado);
		
		if(filho->esquerda == NULL && filho->direita == NULL){
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			printf(")");
			SetConsoleTextAttribute(hConsole, 7);
		}else if(filho->esquerda == NULL && filho->direita != NULL) printf("%c",217);
		else if(filho->esquerda != NULL && filho->direita == NULL) printf("%c",191);
		else printf("%c",180);
		
		int linha;
		if(filho->esquerda != NULL && (filho->esquerda)->direita != NULL){
			linha = ((filho->esquerda)->direita)->filhos;
			linha++;
			for(int i = 1; i <= linha; i++){
				gotoyx(((*x)+i),(*y)+1+(TAM_NUM-1));
				printf("%c",179);
			}
		} 
		
		if(filho->direita != NULL && (filho->direita)->esquerda != NULL){
			linha = ((filho->direita)->esquerda)->filhos;
			linha++;
			for(int i = 1; i <= linha; i++){
				gotoyx(((*x)-i),(*y)+1+(TAM_NUM-1));
				printf("%c",179);
			}
		} 
		
		if(filho->esquerda != NULL){
			(*y) += TAM_NUM;
			(*x)++;
			mostrar_tree(filho->esquerda,x,y);
			(*x)--;
		}
        (*y) -= TAM_NUM;
    }else return;
    
    (*x)++;
    return;
}



void mostrar_root(struct no* filho, int* x, int* y){
													
    if(filho != NULL){
    	
    	HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	int x_no = (*x), y_no = (*y);
    	
    	gotoyx((*x),(*y));
		SetConsoleTextAttribute(hConsole, 0x70);
		if(CHAVES) impressao(filho);
		else printf("O");
		
		SetConsoleTextAttribute(hConsole, 7);
		if(filho->esquerda != NULL || filho->direita != NULL) printf("%c",196);

    	(*y) += TAM_NUM + 1;
    	if(filho->direita != NULL) mostrar_root(filho->direita,x,y);
    	
		if(filho->esquerda != NULL){
			if(filho->direita != NULL){
				
				(*x)++;
				gotoyx((*x),((*y)- (2 + CHAVES)));						//podia fazer de uma forma mais dinamica pra ficar no meio de qualquer numero
				if(CHAVES) printf("%c%c%c",192,196,196);
				else printf("%c%c",192,196);
				
				for(int i = x_no + 1; i < (*x); i++){
					gotoyx(i,y_no + (TAM_NUM - 2));
					printf("%c",179);
				}
			} 
			mostrar_root(filho->esquerda,x,y);
		}
		(*y) -= (TAM_NUM + 1);
		
    }else return;
    
    											
    
    return;
}


void imprimir(arvore* z){

    if(z == NULL){
        printf("Arvore nula!\n");
        return;
        
    }else if(MODO_IMPRESSAO == 1){
    	if(z->qtd >= 9000){
    		printf("A arvore nao cabe no terminal\n");
        	return;
		}
	}else if(MODO_IMPRESSAO == 2){
    	if(z->qtd_folhas >= 9000){
    		printf("A arvore nao cabe no terminal\n");
        	return;
		}
	}
    
    if( z->raiz != NULL){
    	
    	int* x = (int*)malloc(sizeof(int));
    	int* y = (int*)malloc(sizeof(int));
    	*x = 0;
    	*y = 0;

		if(MODO_IMPRESSAO == 1)	mostrar_tree(z->raiz,x,y);
		else if(MODO_IMPRESSAO == 2) mostrar_root(z->raiz,x,y);
		else if(MODO_IMPRESSAO == 3) mostrar_csv(z->raiz,x,y);
		
    }else printf("vazia!\n");
    return;
}
*/

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

	double fim, inicio;
    arvore* z;
    long int* vetor;
    z = criar();

    vetor = (long int*)malloc(TAMANHO*sizeof(long int));
    for(int jj = 0; jj < TAMANHO; jj++) vetor[jj] = jj + 1;
    
    inicio = omp_get_wtime();
	embaralhar(vetor);
	fim = omp_get_wtime();
	if(!VER) printf("%lf segundos para embaralhar!\n",(fim-inicio));
	
	inicio = omp_get_wtime();
	for(int jk = 0; jk < TAMANHO; jk++) inserir(z,vetor[jk]);

	
	fim = omp_get_wtime();
	if(!VER) printf("%lf segundos para preencher!\n",(fim-inicio));
	
	inicio = omp_get_wtime();
	z->qtd_folhas = qts_folhas(z->raiz);
	fim = omp_get_wtime();
    
    libera(z);
    printf("Quantidade de Folhas: %d, sequencialmente em %lf segundos!",z->qtd_folhas,(fim-inicio));
    return 0;
}