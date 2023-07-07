#include <stdio.h>
#include <stdlib.h>

char matrix[3][3]; /* A matriz do jogo */

char check(void);
void init_matrix(void);
void get_playe_move(void);
void disp_matrix(void);



/* Inicializa a Matriz */
void init_matrix(void)
{
    int i, j;

    for(i=0;i<3;i++)
    for(j=0;j<3;j++) matrix[i][j] = ' ';
}

/* Obtém a jogada do jogador 1 */
void get_playe_move(void){
    int x, y;

    printf("Digite as coordenadas para o X: ");
    scanf("%d%d",&x,&y);

    x--; y--;

    if(matrix[x][y]!=' ') {
        printf("Posicao invalida, tente de novo!\n");
        get_player_move();
    }
    else matrix[x][y] = 'X';
}

/* Obtém a jogada do jogador 2 */
void get_player_move(void){
    int i, j;
    for(i=0;i<3;i++) {
        for(j=0;j<3;j++)
        if(matrix[i][j]==' ') break;
        if(matrix[i][j]==' ') break;
    }

    if(i*j==9) {
        printf("EMPATE!\n");
        exit(0);
    }
    else
    matrix[i][j] = 'O';
}

/* Mostra a matriz na tela */
void disp_matrix(void){
    int t;
    for(t=0;t<3;t++) {
        printf(" %c | %c | %c ", matrix[t][0], matrix[t][1], matrix[t][2]);
            if(t!=2) printf("\n---|---|---|\n");
    }
    printf("\n");
}



void main(void){
    char done;

    printf("JOGO DA VELHA\n");
    printf("Jogador 1 x Jogador 2\n");

    done = ' ';

    init_matrix();
    do {
        disp_matrix();
        get_player_move();
        done = check(); /* Verifica se há vencedor */
        if(done != ' ') break; /* Vencedor */
        done = check(); /* Verifica se há vencedor */
    } while(done==' ');

    if(done=='X') printf("Jogador 1 ganhou!\n");
    else printf("Jogador 1 perdeu!\n");
    disp_matrix(); /* Mostra as Posições finais */
}


