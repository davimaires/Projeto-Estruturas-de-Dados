#include <stdio.h>
#include <stdlib.h>

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

int main(){
    int haste1[10] = {-1, -1, -1, -1, -1, -1, 0, 2, 4, 5};
    int haste2[10] = {-1, -1, -1, -1, -1, -1, -1, 1, 3, 6};
    int haste3[10] = {-1, -1, -1, -1, -1, -1, -1, 7, 8, 9};

    printf("\n\n           |                      |                      |           \n");
    for(int i = 0; i < 10; i++){
        imprimePeca(haste1[i]);
        imprimePeca(haste2[i]);
        imprimePeca(haste3[i]);
        printf("\n");
    }
    printf("\n=====================================================================\n");
    printf("\n          [1]                    [2]                    [3]          \n\n\n");


    return 0;
}

