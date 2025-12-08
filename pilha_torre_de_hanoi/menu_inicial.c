#include <stdio.h>
#include <stdlib.h>

//////////////////////
//Funções de suporte//
//////////////////////

//Identifica o sistema (Windows ou Unix) e aplica o comando correspondente para apagar o terminal.
//Usada nas transições de tela.
void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

//Identifica o sistema (Windows ou Unix) e aplica os comandos correspondentes para ler um caracter qualquer e descartá-lo.
//Usada quando é necessária uma confirmação do jogador.
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

//Retorna o resultado da potenciação da base pelo expoente passados como argumentos.
//Usada para calcular o número mínimo de jogadas em cada fase
int potencia(int base, int expoente) {
    int resultado = 1;                   
    for (int i = 0; i < expoente; i++) {
        resultado *= base;
    }
    return resultado;
}

////////////////////
//Funções gráficas//
////////////////////

//Imprime uma peca com base no número passado como argumento.
//Cada peça tem um tamanho e um número únicos que a identificam visualmente.
void imprimePeca(int peca){
    switch (peca) {
        case 0:                               
        printf("          -0-          ");
        break;
        case 1:
        printf("         --1--         ");
        break;
        case 2:
        printf("        ---2---        ");
        break;
        case 3:
        printf("       ----3----       ");
        break;
        case 4:
        printf("      -----4-----      ");
        break;
        case 5:
        printf("     ------5------     ");
        break;
        case 6:
        printf("    -------6-------    ");
        break;
        case 7:
        printf("   --------7--------   ");
        break;
        case 8:
        printf("  ---------8---------  ");
        break;
        case 9:
        printf(" ----------9---------- ");
        break;
        default:
        printf("           |           ");
    }
}

//Imprime o estado atual do tabuleiro, com as peças ordenadas em suas respectivas hastes.
//Usada dentro do jogo, no início e sempre que o jogador faz uma jogada.
void tabuleiro(){
    int haste1[10] = {-1, -1, -1, -1, -1, -1, 0, 2, 4, 5};
    int haste2[10] = {-1, -1, -1, -1, -1, -1, -1, 1, 3, 6};
    int haste3[10] = {-1, -1, -1, -1, -1, -1, -1, 7, 8, 9};
    
    printf("\n           |                      |                      |           \n");
    for(int i = 0; i < 10; i++){
        imprimePeca(haste1[i]);
        imprimePeca(haste2[i]);
        imprimePeca(haste3[i]);
        printf("\n");
    }
    printf("=====================================================================\n");
    printf("          [1]                    [2]                    [3]          \n\n");
}

//Imprime a tela do jogo, identificando o número da fase, o número mínimo de jogadas e
//o número de jogadas realizadas até o momento.
//Usada dentro do jogo, no início e sempre que o jogador faz uma jogada.
void fase(int faseAtual){
    int quantidadeInicialDiscos = faseAtual + 2;
    int numeroMinimoMovimentos = potencia(2, quantidadeInicialDiscos) - 1;
    int contaMovimentos = 0;
    
    printf("Fase: %d\n", faseAtual);
    printf("Numero Minimo de Movimentos: %d                   Seus movimentos: %d  \n", numeroMinimoMovimentos, contaMovimentos);
    tabuleiro();
}

////////////////////////////////////////////
//  Funções da Estrutura de Dados: Pilha  //
//Implementada por meio de Lista Encadeada//
////////////////////////////////////////////

typedef struct Node {
    int disco;
    struct Node* proximo;
} Node;

typedef struct {
    Node* topo;
    int quantidadeDiscos;
} Pilha;

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
    int discoDesempilhado = temp->disco;
    pilha->topo = pilha->topo->proximo;
    free(temp);
    pilha->quantidadeDiscos--;
    return discoDesempilhado;
}


/////////////////////
//Controle de Fluxo//
/////////////////////

//Controla o estado do jogo.
void jogo (int faseAtual){
    fase(faseAtual);
}

int escolherFase(int faseAtual){
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
            pressioneQualquerTecla();
            limparTela();
            escolherFase(faseAtual);
    }
}

///////////////////
//Telas estáticas//
///////////////////

int menu_inicial();

void instrucoes(){
    printf("Lorem Ipsum\n\n");
    printf("Pressione qualquer tecla para voltar para o inicio.\n");
    pressioneQualquerTecla();
    pressioneQualquerTecla();
    limparTela();
    menu_inicial(1);
}

void creditos(){
    printf("Lorem Ipsum\n\n");
    printf("Pressione qualquer tecla para voltar para o inicio.\n");
    pressioneQualquerTecla();
    pressioneQualquerTecla();
    limparTela();
    menu_inicial(1);
}

//Exibe o menu inicial e direciona o jogador através das opções.
int menu_inicial(int opcao){
    int faseAtual = 1;
    printf("=============================================\n");
    printf("              \033[1;36mTORRE DE HANOI\033[0m\n");
    printf("=============================================\n");
    printf("  \033[1;32m1\033[0m - Novo Jogo\n");
    printf("  \033[1;32m2\033[0m - Escolher Fase\n");
    printf("  \033[1;32m3\033[0m - Como Jogar\n");
    printf("  \033[1;32m4\033[0m - Creditos\n");
    printf("  \033[1;32m0\033[0m - Sair\n");
    printf("=============================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    limparTela();
    
    switch (opcao) {
        case 1:
            jogo(faseAtual);
            break;
            case 2:
            faseAtual = escolherFase(faseAtual);
            limparTela();
            jogo(faseAtual);
            break;
        case 3:
            instrucoes();
            break;
        case 4:
            creditos();
            break;
        case 0:
            printf("Programa encerrado pelo usuario.\n\n");
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
            pressioneQualquerTecla();
            pressioneQualquerTecla();
            limparTela();
            menu_inicial(1);
    }
    return opcao;
}

int main() {
    limparTela();
    int opcao;
    printf("============================================================\n");
    printf("Instituto Federal de Educacao, Ciencia e Tecnologia do Ceara\n");
    printf("              Curso de Engenharia de Computacao             \n");
    printf("                Disciplina: Estrutura de Dados              \n");
    printf("                   Professora: Rebeca Rivas               \n\n");
    printf("Alunos: Davi                                                \n");
    printf("        Guilherme                                           \n");
    printf("        João Manoel                                         \n");
    printf("============================================================\n");
    printf("\nPressione qualquer tecla para iniciar.\n");
    pressioneQualquerTecla();
    limparTela();
    opcao = menu_inicial(opcao);
    return 0;
}