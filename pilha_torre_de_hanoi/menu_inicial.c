#include <stdio.h>
#include <stdlib.h>

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
        printf("<Novo Jogo>\n");
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
    do {
        opcao = menu_inicial(opcao);
        } while (opcao != 0);   
    return 0;
}