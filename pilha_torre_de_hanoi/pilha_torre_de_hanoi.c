#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Node {
    int disco;
    //adicionei um vetor de caracteres para armazenar o quadrado(que tem 3 bytes)
    char *visual;
    struct Node* proximo;
} Node;

typedef struct {
    Node* topo;
    int quantidadeDiscos;
} Pilha;

int potencia(int base, int expoente);

void criarPilha(Pilha* pilha) {
    pilha->topo = NULL;
    pilha->quantidadeDiscos = 0;
}

int estaVazia(Pilha* pilha) {
    if (pilha->topo == NULL) {
        return 1;
    }
    return 0;
}

int tamanhoPilha(Pilha* pilha) {
    return pilha->quantidadeDiscos;
}

//fiz a implementação dos unicodes para formar a piramide, que trabalheira pra ser bem honesto 
void empilha(Pilha* pilha, int disco) {
    
    Node *newNode = (Node *)(malloc(sizeof(Node)));
    
    if (newNode == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    
    newNode->disco = disco;
    newNode->proximo = pilha->topo;
    
    //logica da piramide o ultimo elemento sempre vai ser composto de duas vezes o elemento anterior mais 1 {[(x-1)*2] + 1}
    int quadrados = 2 * (disco - 1);
    quadrados++;
    //■ ocupa 4 bytes por ser um caracter largo 3 do caracter + 1 do /0
    int tamanhobytes = quadrados * 4;
    newNode->visual = (char *) malloc(tamanhobytes * sizeof(char));
    
    if (newNode->visual == NULL) {
        printf("Erro de alocacao de memoria para visual.\n");
        free(newNode);
        return;
    }
    //definindo cada byte do caracter
    int b = 0;
    for(int i = 0; i < quadrados; i++){
        newNode->visual[b++] = (char)0xE2;
        newNode->visual[b++] = (char)0x96;
        newNode->visual[b++] = (char)0x88;
    }
    newNode->visual[b] = '\0';
    

    pilha->topo = newNode;
    pilha->quantidadeDiscos++;
    
}

//adicionei o free(temp->visual, pois se trata de um ponteiro)
int desempilha(Pilha* pilha) {
    if (estaVazia(pilha) == 1) {
        printf("Haste vazia\n");
        return -1;
    }
    
    Node *temp = pilha->topo;
    int desempilhapedDisco = temp->disco;
    pilha->topo = pilha->topo->proximo;
    
    if(temp->visual != NULL){
        free(temp->visual);
    }
    
    free(temp);
    pilha->quantidadeDiscos--;
    
    return desempilhapedDisco;
    
}

int regrasJogo(Pilha* hasteOrigem, Pilha* hasteDestino) {
    
    if (estaVazia(hasteOrigem) == 1 ) {
        return 0;
    }

    if (estaVazia(hasteDestino) == 1) {
        return 1;
    }
    
    if ((hasteOrigem->topo->disco) < (hasteDestino->topo->disco)) {
        return 1;
    }
    
    else {
        return 0;
    }
}

void moverDisco(Pilha* hasteOrigem, Pilha* hasteDestino, int* contadorMovimento, int quantidadeInicialDiscos) {
    if (regrasJogo(hasteOrigem, hasteDestino) == 0) {
        printf("Movimento nao permitido, tentar novamente.\n");
        return;
    }
    
    int desempilhapedDisco = desempilha(hasteOrigem);
    empilha(hasteDestino, desempilhapedDisco);

    (*contadorMovimento)++;
    printf("Quantidade de movimentos atual: %d\n", *contadorMovimento);
    printf("Quantidade de movimentos IDEAL: %d\n", potencia(2, quantidadeInicialDiscos) - 1);
}

int fimJogo(Pilha* hasteDestino, int quantidadeInicialDiscos) {
    if (hasteDestino->quantidadeDiscos == quantidadeInicialDiscos) {
        return 1;
    }
    return 0;
}

//adicionei a quantidadeInicialDiscos para calcular o maior tamanho possivel da torre e centralizar os cubos de forma mais pratica
void imprimirJogo(Pilha *haste1, Pilha* haste2, Pilha* haste3, int quantidadeInicialDiscos) {
    
    Node* atual1 = haste1->topo;
    Node* atual2 = haste2->topo;
    Node* atual3 = haste3->topo;

    char caractere = '=';
    
    //descobrir o maior tamanho da torre, igual ao processo da logica da piramide (2 * (disco -1)) + 1
    int tamanhoMaximo = 2 * (quantidadeInicialDiscos-1);
    tamanhoMaximo++;
    //troquei o ->disco por ->visual, que imprime diretamente a quantidade de elementos do elemento da piramide
    printf("\n-------------------------Haste 1----------------------------\n");
    while (atual1 != NULL) {
        //definindo o tamanhoAtual e preenchendo os espacos livres com = 
        int tamanhoAtual = 2 * (atual1->disco - 1);
        tamanhoAtual++;
        int espacoLivre = (tamanhoMaximo - tamanhoAtual)/2; //dividindo por 2 por conta da esquerda e direita 
        
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("%s",atual1->visual);
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("\n");
        atual1 = atual1->proximo;
    }

    printf("-------------------------Haste 2----------------------------\n");
    while (atual2 != NULL) {
        int tamanhoAtual = 2 * (atual2->disco - 1);
        tamanhoAtual++;
        int espacoLivre = (tamanhoMaximo - tamanhoAtual)/2; //dividindo por 2 por conta da esquerda e direita 
        
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("%s",atual2->visual);
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("\n");
        atual2 = atual2->proximo;
    }

    printf("-------------------------Haste 3----------------------------\n");
    while (atual3 != NULL) {
        int tamanhoAtual = 2 * (atual3->disco - 1);
        tamanhoAtual++;
        int espacoLivre = (tamanhoMaximo - tamanhoAtual)/2; //dividindo por 2 por conta da esquerda e direita 
        
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("%s",atual3->visual);
        for(int i = 0;i < espacoLivre;i++){
            printf("%c",caractere);
        }
        printf("\n");
        atual3 = atual3->proximo;
    }
}

void clearBuffer()
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void inverterString(char* string) {
    int i;
    int tamanhoString = strlen(string);

    for (i = 0; i < (tamanhoString / 2); i++) {
        char temp = string[i];
        string[i] = string[tamanhoString - 1 - i];
        string[tamanhoString - 1 - i] = temp;
    }
}

int potencia(int base, int expoente) {
    int i;
    int resultado = 1;

    for (i = 0; i < expoente; i++) {
        resultado *= base;
    }

    return resultado;
}


int main()
{
    setlocale(LC_ALL, ""); //garantir que o programa rode em qualquer ambiente windows/linux/mac
    
    Pilha haste1;
    Pilha haste2;
    Pilha haste3;
    criarPilha(&haste1);
    criarPilha(&haste2);
    criarPilha(&haste3);
    
    int quantidadeInicialDiscos = haste1.quantidadeDiscos;
    
    char pergunta;
    int opcao = 0;
    int contadorMovimento = 0;
    
    //mudança para o jogador definir a quantidade inicial de discos no inicio, para não ter que ficar digitando 'y' cada novo disco adicionado, pode ficar repetitivo - João Manoel
    printf("Com quantos discos deseja jogar?\n");
    scanf("%d", &quantidadeInicialDiscos);
    clearBuffer();
        
    for(int i = quantidadeInicialDiscos;i > 0;i--){
        empilha(&haste1,i);
    }

    imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
    
    do {
        printf("\n#############################################################\n");
        printf("\nDigite 12 para mover disco da haste 1 para haste 2\n");
        printf("Digite 13 para mover disco da haste 1 para haste 3\n");
        printf("Digite 21 para mover disco da haste 2 para haste 1\n");
        printf("Digite 23 para mover disco da haste 2 para haste 3\n");
        printf("Digite 31 para mover disco da haste 3 para haste 1\n");
        printf("Digite 32 para mover disco da haste 3 para haste 2\n");
        printf("Digite 0 para sair do jogo\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        clearBuffer();

        printf("\n#############################################################\n\n");
        
        switch(opcao) {
            case 12:
                moverDisco(&haste1 , &haste2 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                if (fimJogo(&haste2 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 13:
                moverDisco(&haste1 , &haste3 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                if (fimJogo(&haste3 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 21:
                moverDisco(&haste2 , &haste1 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                break;
            case 23:
                moverDisco(&haste2 , &haste3 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                if (fimJogo(&haste3 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 31:
                moverDisco(&haste3 , &haste1 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                break;
            case 32:
                moverDisco(&haste3 , &haste2 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3,quantidadeInicialDiscos);
                if (fimJogo(&haste2 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 0);
    
    return 0;
}
