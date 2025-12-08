#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int disco;
    struct Node* proximo;
} Node;

typedef struct {
    Node* topo;
    int quantidadeDiscos;
} Pilha;

void inverterString();
int potencia();

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

void empilha(Pilha* pilha, int disco) {
    Node *newNode = (Node *)(malloc(sizeof(Node)));
    
    if (newNode == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    
    newNode->disco = disco;
    newNode->proximo = pilha->topo;
    pilha->topo = newNode;
    pilha->quantidadeDiscos++;
    
}

int desempilha(Pilha* pilha) {
    if (estaVazia(pilha) == 1) {
        printf("Haste vazia\n");
        return -1;
    }
    
    Node *temp = pilha->topo;
    int desempilhapedDisco = temp->disco;
    pilha->topo = pilha->topo->proximo;
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

void imprimirJogo(Pilha *haste1, Pilha* haste2, Pilha* haste3) {
    Node* atual1 = haste1->topo;
    Node* atual2 = haste2->topo;
    Node* atual3 = haste3->topo;

    int i;
    char caractere = '=';

    printf("\n-------------------------Haste 1----------------------------\n");
    while (atual1 != NULL) {
        int quantidadeCaracteres = atual1->disco;
        char strAtual[quantidadeCaracteres];

        memset(strAtual, caractere, quantidadeCaracteres);

        printf("%s%d%s\n", strAtual, atual1->disco, strAtual);

        atual1 = atual1->proximo;
    }

    printf("-------------------------Haste 2----------------------------\n");
    while (atual2 != NULL) {
        int quantidadeCaracteres = atual2->disco;
        char strAtual[quantidadeCaracteres];

        memset(strAtual, caractere, quantidadeCaracteres);

        printf("%s%d%s\n", strAtual, atual2->disco, strAtual);
        atual2 = atual2->proximo;
    }

    printf("-------------------------Haste 3----------------------------\n");
    while (atual3 != NULL) {
        int quantidadeCaracteres = atual3->disco;
        char strAtual[quantidadeCaracteres];

        memset(strAtual, caractere, quantidadeCaracteres);

        printf("%s%d%s\n", strAtual, atual3->disco, strAtual);
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
    Pilha haste1;
    Pilha haste2;
    Pilha haste3;
    criarPilha(&haste1);
    criarPilha(&haste2);
    criarPilha(&haste3);
    
    empilha(&haste1, 2);
    empilha(&haste1, 1);
    
    int quantidadeInicialDiscos = haste1.quantidadeDiscos;
    
    char pergunta;
    int opcao = 0;
    int contadorMovimento = 0;
    
    
    do {
        printf("Aumentar quantidade de discos? y/n\n(Valor Atual: %d)\n", quantidadeInicialDiscos);
        printf("Opcao: ");
        scanf("%c", &pergunta);
        clearBuffer();
        
        if (pergunta == 'y') {
            empilha(&haste1, 1);
            quantidadeInicialDiscos = haste1.quantidadeDiscos;

            Node* atual = haste1.topo;
            int valorAtual = 1;
            
            while (atual != NULL) {
                atual->disco = valorAtual;
                atual = atual->proximo;
                valorAtual++;
            }
        } 
        else {
            break;
        }
        
    } while(1);

    imprimirJogo(&haste1, &haste2, &haste3);
    
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
                imprimirJogo(&haste1, &haste2, &haste3);
                if (fimJogo(&haste2 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 13:
                moverDisco(&haste1 , &haste3 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3);
                if (fimJogo(&haste3 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 21:
                moverDisco(&haste2 , &haste1 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3);
                break;
            case 23:
                moverDisco(&haste2 , &haste3 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3);
                if (fimJogo(&haste3 , quantidadeInicialDiscos) == 1) {
                    printf("Parabens, voce resolveu a Torre de Hanoi!\n");
                    return 0;
                }
                break;
            case 31:
                moverDisco(&haste3 , &haste1 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3);
                break;
            case 32:
                moverDisco(&haste3 , &haste2 , &contadorMovimento, quantidadeInicialDiscos);
                imprimirJogo(&haste1, &haste2, &haste3);
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