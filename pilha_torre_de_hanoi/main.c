#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

typedef struct Node {
    int disco;
    struct Node* proximo;
} Node;

typedef struct {
    Node* topo;
    int quantidadeDiscos;
} Pilha;

int menuInicial(Pilha* haste1, Pilha* haste2, Pilha* haste3, int* quantidadeInicialDiscos, int* contaMovimentos);
int menuMovimentos();
void instrucoes();
void creditos();
void limparBuffer();
void limparTela();
void pressioneQualquerTecla();
void sleep_ms(int ms);  
void inverterString(char* string);
int potencia(int base, int expoente);
void ranking(int contagem_jogador, int minimo);

void criarPilha(Pilha* pilha) {
    pilha->topo = NULL;
    pilha->quantidadeDiscos = 0;
}

int isEmpty(Pilha* pilha) {
    if (pilha->topo == NULL) {
        return 1;
    }
    return 0;
}

int tamanhoPilha(Pilha* pilha) {
    return pilha->quantidadeDiscos;
}

void push(Pilha* pilha, int disco) {
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

int pop(Pilha* pilha) {
    if (isEmpty(pilha) == 1) {
        printf("Haste vazia\n");
        return -1;
    }
    
    Node *temp = pilha->topo;
    int poppedDisco = temp->disco;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->quantidadeDiscos--;
    
    return poppedDisco;
    
}

void limparPilha(Pilha* pilha) {
    while(isEmpty(pilha) == 0) {
        pop(pilha);
    }
}

int regrasJogo(Pilha* hasteOrigem, Pilha* hasteDestino) {
    
    if (isEmpty(hasteOrigem) == 1 ) {
        return 0;
    }

    if (isEmpty(hasteDestino) == 1) {
        return 1;
    }
    
    if ((hasteOrigem->topo->disco) < (hasteDestino->topo->disco)) {
        return 1;
    }
    
    else {
        return 0;
    }
}

void moverDisco(Pilha* hasteOrigem, Pilha* hasteDestino, int* contaMovimentos, int quantidadeInicialDiscos) {
    limparTela();
    if (regrasJogo(hasteOrigem, hasteDestino) == 0) {
        printf("Movimento nao permitido, tentar novamente.\n");
        return;
    }
    
    int poppedDisco = pop(hasteOrigem);
    push(hasteDestino, poppedDisco);

    (*contaMovimentos)++;

    printf("Fase: %d\n", quantidadeInicialDiscos - 2);
    printf("Numero Minimo de Movimentos: %d                   Seus movimentos: %d  \n\n", potencia(2, quantidadeInicialDiscos) - 1, (*contaMovimentos));
}

int fimJogo(Pilha* hasteDestino, int quantidadeInicialDiscos) {
    if (hasteDestino->quantidadeDiscos == quantidadeInicialDiscos) {
        return 1;
    }
    return 0;
}

void gerarStrDisco(int disco, int raioBaseMaximo, char* strDisco) {
    int i;

    for (i = 0; i < 2 * raioBaseMaximo + 1; i++) {
        strDisco[i] = ' ';
    }
    strDisco[2 * raioBaseMaximo + 1] = '\0';

    int meioDisco = raioBaseMaximo;

    if (disco == 0) {
        strDisco[meioDisco] = '|';
        return;
    }

    int tamanhoDisco = 2 * disco + 1;

    int inicioDisco = meioDisco - disco;

    for (i = 0; i < tamanhoDisco; i++) {
        strDisco[inicioDisco + i] = '-';
    }

    char numeroDisco[12];
    sprintf(numeroDisco, "%d", disco);
    int len = strlen(numeroDisco);

    int inicioNumero = meioDisco - len / 2;
    for (i = 0; i < len; i++) {
        strDisco[inicioNumero + i] = numeroDisco[i];
    }
}

void imprimirTabuleiro(Pilha* haste1, Pilha* haste2, Pilha* haste3, int quantidadeInicialDiscos, int raioBaseMaximo) {
    Node* noAtualHaste1 = haste1->topo;
    Node* noAtualHaste2 = haste2->topo;
    Node* noAtualHaste3 = haste3->topo;

    quantidadeInicialDiscos = quantidadeInicialDiscos + 1;

    int discosHaste1[quantidadeInicialDiscos];
    int discosHaste2[quantidadeInicialDiscos];
    int discosHaste3[quantidadeInicialDiscos];

    int quantidadeDiscosHaste1 = haste1->quantidadeDiscos;
    int quantidadeDiscosHaste2 = haste2->quantidadeDiscos;
    int quantidadeDiscosHaste3 = haste3->quantidadeDiscos;

    int i;

    for (i = 0; i < quantidadeInicialDiscos; i++) {
        if (i < quantidadeInicialDiscos - quantidadeDiscosHaste1) {
            discosHaste1[i] = 0;
        }
        else {
            discosHaste1[i] = noAtualHaste1->disco;
            noAtualHaste1 = noAtualHaste1->proximo;
        }
    
        if (i < quantidadeInicialDiscos - quantidadeDiscosHaste2) {
            discosHaste2[i] = 0;
        }
        else {
            discosHaste2[i] = noAtualHaste2->disco;
            noAtualHaste2 = noAtualHaste2->proximo;
        }
    
        if (i < quantidadeInicialDiscos - quantidadeDiscosHaste3) {
            discosHaste3[i] = 0;
        }
        else {
            discosHaste3[i] = noAtualHaste3->disco;
            noAtualHaste3 = noAtualHaste3->proximo;
        }
    }
    
    char strDisco1[2*raioBaseMaximo + 2];
    char strDisco2[2*raioBaseMaximo + 2];
    char strDisco3[2*raioBaseMaximo + 2];

    for(i = 0; i < quantidadeInicialDiscos; i++) {
        gerarStrDisco(discosHaste1[i], raioBaseMaximo, strDisco1);
        gerarStrDisco(discosHaste2[i], raioBaseMaximo, strDisco2);
        gerarStrDisco(discosHaste3[i], raioBaseMaximo, strDisco3);

        printf("       %s        %s        %s\n", strDisco1, strDisco2, strDisco3);
    }
    printf("==============================================================================\n");
    //printf("          [1]                    [2]                    [3]          \n\n");
}

void solucaoTorreHanoi(int n, Pilha* hasteOrigem, Pilha* hasteDestino, Pilha* hasteAuxiliar, int* contadorMovimento, int quantidadeInicialDiscos, Pilha* haste1, Pilha* haste2, Pilha* haste3) {
    if (n == 0) {
        return;
    }

    solucaoTorreHanoi(n - 1, hasteOrigem, hasteAuxiliar, hasteDestino, contadorMovimento, quantidadeInicialDiscos, haste1, haste2, haste3);
    limparTela();

    moverDisco(hasteOrigem, hasteDestino, contadorMovimento, quantidadeInicialDiscos);

    imprimirTabuleiro(haste1, haste2, haste3, quantidadeInicialDiscos, quantidadeInicialDiscos);
    sleep_ms(500);

    solucaoTorreHanoi(n - 1, hasteAuxiliar, hasteDestino, hasteOrigem, contadorMovimento, quantidadeInicialDiscos, haste1, haste2, haste3);
}

int escolherFase() {
    int faseAtual = 0;

    printf("1. Fase 1: 3  Discos\n");
    printf("2. Fase 2: 4  Discos\n");
    printf("3. Fase 3: 5  Discos\n");
    printf("4. Fase 4: 6  Discos\n");
    printf("5. Fase 5: 7  Discos\n");
    printf("6. Fase 6: 8  Discos\n");
    printf("7. Fase 7: 9  Discos\n");
    printf("8. Fase 8: 10 Discos\n");
    printf("\nSelecione o numero correspondente a fase que deseja jogar: ");
    scanf("%d", &faseAtual);

    if (faseAtual >= 1 && faseAtual <= 8){
        return faseAtual;
    }
    else{
        printf("Opção invalida! Tente novamente.\n");
            pressioneQualquerTecla();
            limparTela();
            escolherFase();
    }
}

void inicializarFase(Pilha* haste1, Pilha* haste2, Pilha* haste3, int* quantidadeInicialDiscos, int* contaMovimentos, int faseAtual) {
    limparPilha(haste1);
    limparPilha(haste2);
    limparPilha(haste3);

    (*quantidadeInicialDiscos) = faseAtual + 2;
    (*contaMovimentos) = 0;

    criarPilha(haste1);
    criarPilha(haste2);
    criarPilha(haste3);

    int numeroMinimoMovimentos = potencia(2, (*quantidadeInicialDiscos)) - 1;

    int i;

    for (i = (*quantidadeInicialDiscos); i > 0; i--) {
        push(haste1, i);
    }

    printf("Fase: %d\n", faseAtual);
    printf("Numero Minimo de Movimentos: %d                   Seus movimentos: %d  \n", numeroMinimoMovimentos, (*contaMovimentos));

    // raioBaseMaximo = quantidadeInicialDiscos
    imprimirTabuleiro(haste1, haste2, haste3, (*quantidadeInicialDiscos), (*quantidadeInicialDiscos));
}

int jogadaAtual(Pilha* hasteOrigem, Pilha* hasteDestino, Pilha* haste1, Pilha* haste2, Pilha* haste3, int quantidadeInicialDiscos, int* contaMovimentos) {
    moverDisco(hasteOrigem, hasteDestino, contaMovimentos, quantidadeInicialDiscos);

    imprimirTabuleiro(haste1, haste2, haste3, quantidadeInicialDiscos, quantidadeInicialDiscos);

    if (hasteDestino != haste1) {
        if (fimJogo(hasteDestino , quantidadeInicialDiscos) == 1) {
        printf("Parabens, voce resolveu a Torre de Hanoi!\n");
        ranking(*contaMovimentos, potencia(2,quantidadeInicialDiscos) - 1);
        return 0;
        }
    }

    return 1;
}

int jogoAtual (Pilha* haste1, Pilha* haste2, Pilha* haste3, int faseAtual, int quantidadeInicialDiscos, int* contaMovimentos) {
    int opcao = 0;

    do {
        opcao = menuMovimentos();

        switch (opcao) {
            case 12:
                if ((jogadaAtual(haste1, haste2, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 13:
                if ((jogadaAtual(haste1, haste3, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 21:
                if ((jogadaAtual(haste2, haste1, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 23:
                if ((jogadaAtual(haste2, haste3, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 31:
                if ((jogadaAtual(haste3, haste1, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 32:
                if ((jogadaAtual(haste3, haste2, haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos)) == 0) {
                    return 1;
                }
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                printf("Pressione alguma tecla para continuar.\n");
                pressioneQualquerTecla();
                return 0;
            default:
                printf("\n\nOpcao invalida\n");
                pressioneQualquerTecla();
                limparTela();
        }
    }  while(opcao != 0);
}

int menuMovimentos() {
        int opcao = 0;

        printf("\nDigite 12 para mover disco da haste 1 para haste 2\n");
        printf("Digite 13 para mover disco da haste 1 para haste 3\n");
        printf("Digite 21 para mover disco da haste 2 para haste 1\n");
        printf("Digite 23 para mover disco da haste 2 para haste 3\n");
        printf("Digite 31 para mover disco da haste 3 para haste 1\n");
        printf("Digite 32 para mover disco da haste 3 para haste 2\n");
        printf("Digite 0 para sair do jogo atual\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        return opcao;
}

int menuInicial(Pilha* haste1, Pilha* haste2, Pilha* haste3, int* quantidadeInicialDiscos, int* contaMovimentos) {
    limparTela();
    int opcao = 0;
    int faseAtual = 1;
    char pergunta;

    (*quantidadeInicialDiscos) = 0;
    (*contaMovimentos) = 0;
    criarPilha(haste1);
    criarPilha(haste2);
    criarPilha(haste3);

    printf("=============================================\n");
    printf("              \033[1;36mTORRE DE HANOI\033[0m\n");
    printf("=============================================\n");
    printf("  \033[1;32m1\033[0m - Novo Jogo\n");
    printf("  \033[1;32m2\033[0m - Escolher Fase\n");
    printf("  \033[1;32m3\033[0m - Como Jogar\n");
    printf("  \033[1;32m4\033[0m - Creditos\n");
    printf("  \033[1;32m5\033[0m - Extra\n");
    printf("  \033[1;32m0\033[0m - Sair\n");
    printf("=============================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    limparTela();
    
    switch (opcao) {
        case 1:
            while (1) {
                inicializarFase(haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos, faseAtual);

                if ((jogoAtual(haste1, haste2, haste3, faseAtual, *quantidadeInicialDiscos, contaMovimentos)) == 1) {
                    printf("Deseja ir para a proxima fase? (y/n)\n");
                    scanf("%c", &pergunta);
                    limparBuffer();

                    if (pergunta == 'y') {
                        faseAtual++;
                        limparTela();
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            break;
        case 2:
            faseAtual = escolherFase();
            limparTela();
            inicializarFase(haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos, faseAtual);
            jogoAtual(haste1, haste2, haste3, faseAtual, *quantidadeInicialDiscos, contaMovimentos);
            printf("Pressione alguma tecla para continuar.\n");
            pressioneQualquerTecla();
            break;
        case 3:
            instrucoes();
            break;
        case 4:
            creditos();
            break;
        case 5:
            faseAtual = escolherFase();
            limparTela();
            inicializarFase(haste1, haste2, haste3, quantidadeInicialDiscos, contaMovimentos, faseAtual);
            solucaoTorreHanoi(*quantidadeInicialDiscos, haste1, haste3, haste2, contaMovimentos, *quantidadeInicialDiscos, haste1, haste2, haste3);
            printf("Pressione alguma tecla para continuar.\n");
            pressioneQualquerTecla();
            break;
        case 0:
            printf("Programa encerrado pelo usuario.\n\n");
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
            pressioneQualquerTecla();
            limparTela();
    }
    return opcao;
}

void instrucoes() {
    printf("Lorem Ipsum\n\n");
    printf("Pressione qualquer tecla para voltar para o inicio.\n");
    pressioneQualquerTecla();
    limparTela();
}

void creditos() {
   printf("=============================================\n");
    printf("              \033[1;36m Creditos\033[0m\n");
    printf("=============================================\n");
    printf("Davi\n");
    printf("Guilherme Acioly\n");
    printf("Joao Manoel Rodrigues de Oliveira\n");
    printf("Pressione qualquer tecla para voltar para o inicio.\n");
    pressioneQualquerTecla();
    limparTela();
}

void limparBuffer()
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

void ranking(int contagem_jogador,int minimo){
  if(contagem_jogador == minimo){
    printf(" \u2605 \u2605 \u2605\n");
  }
  else if(contagem_jogador <= minimo + minimo/2){
    printf(" \u2605 \u2605 \u2606\n");
  }
  else{
    printf(" \u2605 \u2606 \u2606\n");
  }
}

void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pressioneQualquerTecla() {
    #ifdef _WIN32
    fflush(stdout);
    getch();
    #else
    system("stty raw");
    getchar();
    system("stty cooked");
    #endif
}

void sleep_ms(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

int main() {
    setlocale(LC_ALL, "");

    Pilha haste1;
    Pilha haste2;
    Pilha haste3;

    criarPilha(&haste1);
    criarPilha(&haste2);
    criarPilha(&haste3);

    int quantidadeInicialDiscos = 0;
    int contaMovimentos = 0;

    limparTela();
    int opcao;
    printf("============================================================\n");
    printf("Instituto Federal de Educacao, Ciencia e Tecnologia do Ceara\n");
    printf("              Curso de Engenharia de Computacao             \n");
    printf("                Disciplina: Estrutura de Dados              \n");
    printf("                   Professora: Rebeca Rivas               \n\n");
    printf("Alunos: Davi                                                \n");
    printf("        Guilherme                                           \n");
    printf("        Joao Manoel                                         \n");
    printf("============================================================\n");
    printf("\nPressione qualquer tecla para iniciar.\n");
    pressioneQualquerTecla();
    limparTela();

    while(1) {
        opcao = menuInicial(&haste1, &haste2, &haste3, &quantidadeInicialDiscos, &contaMovimentos);

        if (opcao == 0) {
            break;
        }
    }
    
    limparPilha(&haste1);
    limparPilha(&haste2);
    limparPilha(&haste3);
    
    return 0;
}

