#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define TAM_MAX_NUM 5				

#define TAMANHO 100
#define DIGITO_ATUAL 2				//MUDAR TAMBEM NO PRINT DA CHAVE DO NO



//CONSIDERACOES, TAMANHO MAX E 9000 PELO TAMANHO DO TERMINAL
//IMPRESSAO DO 'NO' PELO MEIO DEIXA OS NUMEROS EM ORDEM PERFEITA PELAS LINHAS, DECRESCENTE SE COMECAR NA ESQUERDA

void gotoyx(int x, int y){						//usando o gotoxy ao contrario pra ficar igual a logica de uma matriz real
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){y,x});   //trabalha com matriz, comeca em [0][0]
}

struct no{

    int chave;
    int verificado;
    long int filhos;						//assim eu sei cada subarvore quantos filhos tem hehe
    struct no* esquerda;
    struct no* direita;

};


struct descritor{

    struct no* raiz;
    int qtd;

};


typedef struct no elementos;
typedef struct descritor arvore;
//typedef struct no* raiz;


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
    novo->verificado = 0;
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
                    //anterior->filhos--;
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



/*
void mostrar(struct no* filho, int* x, int* y){

    if(filho != NULL){
    	
    	if(filho->direita != NULL){
    		(*y)++;
    		mostrar(filho->direita,x,y);
		} 
    	
		gotoyx((*x),(*y));
		printf("%d",filho->chave);
		
		if(filho->esquerda != NULL){
			(*y)++;
			(*x)++;
			mostrar(filho->esquerda,x,y);
			(*x)--;
		}
        
        (*y)--;

    }else return;
    
    (*x)++;
    return;
}
*/


void mostrar(struct no* filho, int* x, int* y){
	
													//Sleep(1000);
													//gotoyx(25,100);
													//printf("%d e %d            ",(*x),(*y));
													
													//gotoyx((*x),(*y));
													//printf("a");
													
													
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	gotoyx((*x),(*y));
	SetConsoleTextAttribute(hConsole, 0x70);
	printf("%02d",filho->chave);
	SetConsoleTextAttribute(hConsole, 7);

	if(filho->esquerda == NULL && filho->direita == NULL){
		SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
		printf(")");//printf(" %c",186);
		SetConsoleTextAttribute(hConsole, 7);
	}else if(filho->esquerda == NULL && filho->direita != NULL) printf("%c",217);
	else if(filho->esquerda != NULL && filho->direita == NULL) printf("%c",191);
	else printf("%c",180);
	
	(*x)++;

    if(filho != NULL){
    	
    	
    	
    	if(filho->direita != NULL){
    		(*y) += DIGITO_ATUAL;
    		//printf("%c",218);
    		mostrar(filho->direita,x,y);
    		(*y) += DIGITO_ATUAL;
		} 
    	
    												//Sleep(750);
		
		
		
		
		int linha;
		if(filho->esquerda != NULL && (filho->esquerda)->direita != NULL){
			linha = ((filho->esquerda)->direita)->filhos;
			linha++;
			//gotoyx(25,100);
			//printf("%d    ",linha);
			
			for(int i = 1; i <= linha; i++){
				gotoyx(((*x)+i),(*y)+1+(DIGITO_ATUAL-1));
				printf("%c",179);
			}
		} 
		
		
		if(filho->direita != NULL && (filho->direita)->esquerda != NULL){
			linha = ((filho->direita)->esquerda)->filhos;
			linha++;
			//linha = linha * -1;
			//gotoyx(25,100);
			//printf("%d    ",linha);
			
			for(int i = 1; i <= linha; i++){
				gotoyx(((*x)-i),(*y)+1+(DIGITO_ATUAL-1));
				printf("%c",179);
			}
		} 
		
		
		//a folha podia ter outra cor
		//cada no ter uma corzinha pra mostrar
		//a cor q imprime o no poderia ser diferente para o processo q achou ela
		
		
		
		
		if(filho->esquerda != NULL){
			(*y) += TAM_MAX_NUM;
			(*x)++;
			//printf("%c",192);
			mostrar(filho->esquerda,x,y);
			(*x)--;
		}
        
        (*y) -= TAM_MAX_NUM;

    }else return;
    
    (*x)++;
    
    
										    //gotoyx((*x),(*y));
										    //printf("%c",179);
    
    
    return;
}










/*
void mostrar(struct no* filho, int metodo){

    if(filho != NULL){

        if(metodo == 1) printf("[%d], ",filho->chave);
        mostrar(filho->esquerda,metodo);
        if(metodo == 2) printf("[%d], ",filho->chave);
        mostrar(filho->direita,metodo);
        if(metodo == 3) printf("[%d], ",filho->chave);

    }
    return;
}
*/


void imprimir(arvore* z){

    if(z == NULL){
        printf("erro!\n");
        return;
    }
    if( z->raiz != NULL){
    	
    	int* x = (int*)malloc(sizeof(int));
    	int* y = (int*)malloc(sizeof(int));
    	*x = 0;
    	*y = 0;

        mostrar(z->raiz,x,y);

    }else printf("vazia!\n");
    return;
}


void percurso(struct no* filho){

    if(filho != NULL){

        percurso(filho->esquerda);
        percurso(filho->direita);
        //printf("[%d], ",filho->chave);
        free(filho);
        filho = NULL;

    }
    return;

}


void libera(arvore* z){

    if(z == NULL) return;
    if( z->raiz != NULL) percurso(z->raiz);
    z->qtd = 0;
    printf("\n\nliberado!\n");
    return;
}










int main(){

    arvore* z;
    z = criar();

	/*
    inserir(z,8);
    inserir(z,4);
    inserir(z,3);
    inserir(z,6);
    inserir(z,5);
    inserir(z,9);
    inserir(z,2);
    inserir(z,1);
    inserir(z,7);
    inserir(z,546);
    */
    
    int* vetor;
    vetor = (int*)malloc(TAMANHO*sizeof(int));
    
    for(int jj = 0; jj < TAMANHO; jj++){
    	vetor[jj] = -1;
	}
    
    int pode = 0;
    
    srand(time(NULL));
    int numero, antigo = 0;

    getch();
    
    for(int kk = 1; kk <= TAMANHO; kk++){
    	
    	numero = rand() % TAMANHO;
    	if(numero != antigo){
    		
    		
    		pode = 1;
    		for(int kj = 0; kj < kk; kj++){
    			if(vetor[kj] == numero) pode = 0;
			}
    		if(pode){
	    		inserir(z,numero);
	    		antigo = numero;
	    		vetor[kk] = numero;
	    		//printf("%d\n",kk);
			}else kk--;
		}
	}
    
    
    
    //system("clear");
    
    
    
    /*
    inserir(z,2);
    inserir(z,1);
    inserir(z,4);
    inserir(z,3);
    inserir(z,5);
    */
    
    imprimir(z);
    
    
    libera(z);
    getch();
    return 0;
}
