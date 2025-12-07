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
    printf("Número Mínimo de Movimentos: %d                   Seus movimentos: %d  \n", numeroMinimoMovimentos, contaMovimentos);
    tabuleiro();
}

/////////////////////
//Controle de Fluxo//
/////////////////////

//Controla o estado do jogo.
void jogo (int faseAtual){
    fase(faseAtual);
}

//Exibe o menu inicial e direciona o jogador através das opções.
int menu_inicial(int opcao){
    printf("=============================================\n");
    printf("              \033[1;36mTORRE DE HANOI\033[0m\n");
    printf("=============================================\n");
    printf("  \033[1;32m1\033[0m - Novo Jogo\n");
    printf("  \033[1;32m2\033[0m - Escolher Dificuldade\n");
    printf("  \033[1;32m3\033[0m - Como Jogar\n");
    printf("  \033[1;32m4\033[0m - Créditos\n");
    printf("  \033[1;32m0\033[0m - Sair\n");
    printf("=============================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparTela();
    
    switch (opcao) {
        case 1:
        jogo(1);
        break;
        case 2:
        printf("<Escolher Dificuldade>\n");
        break;
        case 3:
        printf("<Como Jogar>\n");
        break;
        case 4:
        printf("<Créditos>\n");
        break;
        case 0:
        printf("<Você tem certeza que quer sair?>\n");
        break;
        default:
                printf("Opção inválida! Tente novamente.\n");
            }
            
    if (opcao == 0){
        printf("\nPressione qualquer tecla para encerrar");
        limparTela();
        getchar();
        getchar();
    }
    return opcao;
}

int main() {
    int opcao;
    limparTela();
    printf("============================================================\n");
    printf("Instituto Federal de Educação, Ciência e Tecnologia do Ceará\n");
    printf("              Curso de Engenharia de Computação             \n");
    printf("                Disciplina: Estrutura de Dados              \n");
    printf("                   Professora: Rebeca Rivas               \n\n");
    printf("Alunos: Davi                                                \n");
    printf("        Guilherme                                           \n");
    printf("        João Manoel                                         \n");
    printf("============================================================\n");
    printf("\nPressione qualquer tecla para iniciar");
    pressioneQualquerTecla();
    limparTela();
    opcao = menu_inicial(opcao);
    return 0;
}