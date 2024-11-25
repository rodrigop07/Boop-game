#include <stdio.h>
#include <stdlib.h>

void exibeTabuleiro(int **tabuleiro, int linhas, int colunas);
void exibePlacar(int **placar);
void menuInicio();
int **inicializaMatrizTabuleiro();
int **inicializaMatrizPlacar();
int fazJogada(int **tabuleiro, int *jogador, int **placar);
int validaJogada(int **tabuleiro, int linha, int coluna, char gato, int *jogador, int **placar);
int verificaVitoria(int **tabuleiro, int *jogador, int **placar, int linhas, int colunas);
int** graduaGatinho(int** placar, int** tabuleiro, int* jogador, int linhas, int colunas);
int** fazBoop(int** tabuleiro, int** placar, int linha, int coluna, int linhas, int colunas, char gato);
struct NaCasa naCasa(int **tabuleiro, int linha, int coluna);
struct NaCasa{
    char tipoGato;
    int jogador;
};

int main(){
    int **tabuleiro = inicializaMatrizTabuleiro(6, 6);
    int **placar = inicializaMatrizPlacar();
    int condicao = 1;
    int jogador = 1;

    menuInicio();
    while (verificaVitoria(tabuleiro, &jogador, placar, 6, 6) == 0){
        system("cls");
        exibePlacar(placar);
        exibeTabuleiro(tabuleiro, 6, 6);
        fazJogada(tabuleiro, &jogador, placar);
        placar = graduaGatinho(placar, tabuleiro, &jogador, 6, 6);
    }

    return 0;
}

void exibeTabuleiro(int **tabuleiro,int linhas,int colunas){
    for(int c = 0; c < colunas; c++){
        for(int l = 0; l < linhas; l++){
            if(l == linhas -1){
                printf("+---+");
            }
            else{
                printf("+---");
            }
        }
        printf("\n");
        for(int l = 0; l < linhas; l++){
            if(l == linhas -1){
                if(tabuleiro[c][l] == 1){
                    printf("| \033[1;31mg\033[0m |");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 2){
                    printf("| \033[1;31mG\033[0m |");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 3){
                    printf("| \033[1;32mg\033[0m |");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 4){
                    printf("| \033[1;32mG\033[0m |");
                    printf(" %i ", c+1);
                }
                else{
                    printf("|   |");
                    printf(" %i ", c+1);
                }
            }
            else{
                if(tabuleiro[c][l] == 1){
                    printf("| \033[1;31mg\033[0m ");
                }
                else if(tabuleiro[c][l] == 2){
                    printf("| \033[1;31mG\033[0m ");
                }
                else if(tabuleiro[c][l] == 3){
                    printf("| \033[1;32mg\033[0m ");
                }
                else if(tabuleiro[c][l] == 4){
                    printf("| \033[1;32mG\033[0m ");
                }
                else{
                    printf("|   ");
                }
            }
        }
        printf("\n");
    }

    for(int l = 0; l < linhas; l++){
        if(l == linhas -1){
            printf("+---+");
        }
        else{
            printf("+---");
        }
    }
    printf("\n");
    for(int l = 0; l < linhas; l++){
        if(l == linhas -1){
            printf("  %c  ", l + 97);
        }
        else{
            printf("  %c ", l + 97);
        }
    }
    printf("\n\n");
}

struct NaCasa naCasa(int **tabuleiro, int linha, int coluna){
    struct NaCasa _naCasa;
    if(tabuleiro[linha][coluna] == 1){
        _naCasa.tipoGato = 'g';
        _naCasa.jogador = 1;
    } else if(tabuleiro[linha][coluna] == 2){
        _naCasa.tipoGato = 'G';
        _naCasa.jogador = 1;
    } else if(tabuleiro[linha][coluna] == 3){
        _naCasa.tipoGato = 'g';
        _naCasa.jogador = 2;
    } else if(tabuleiro[linha][coluna] == 4){
        _naCasa.tipoGato = 'G';
        _naCasa.jogador = 2;
    } else if(tabuleiro[linha][coluna] == 0){
        _naCasa.tipoGato = ' ';
        _naCasa.jogador = 0;
    }
    return _naCasa;
}

void exibePlacar(int **placar){
    printf("+---------------------------------------------------+ \n");
    printf("|        \033[1;31mJogador 1\033[0m         |       \033[1;32mJogador 2\033[0m        | \n");
    printf("+--------------+-----------+-------------+----------+ \n");
    printf("|  \033[1;31mGatinhos: %d\033[0m |  \033[1;31mGatos: %d\033[0m | \033[1;32mGatinhos: %d\033[0m | \033[1;32mGatos: %d\033[0m | \n", placar[1][1], placar[1][2], placar[2][1], placar[2][2]);
    printf("+--------------+-----------+-------------+----------+ \n");
    printf("\n");
}

int **inicializaMatrizTabuleiro(){
    int **tabuleiro;

    tabuleiro = (int **)malloc(6 * sizeof(int *));

    for (int i = 0; i < 6; i++) {
        tabuleiro[i] = (int *)malloc(6 * sizeof(int));
    }

    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 6; b++) {
            tabuleiro[a][b] = 0;
        }
    }

    return tabuleiro;
}

int **inicializaMatrizPlacar(){
    int **placar;

    placar = (int **)malloc(2 * sizeof(int *));

    for (int i = 1; i <= 2; i++) {
        placar[i] = (int *)malloc(2 * sizeof(int));
    }

    for (int a = 1; a <= 2; a++) {
        for (int b = 1; b <= 2; b++) {
            if(b == 1){
                placar[a][b] = 8;
            }
            else{
                placar[a][b] = 0;
            }
        }
    }

    return placar;
}

int fazJogada(int **tabuleiro, int *jogador, int **placar){

    int linha;
    char coluna, gato;
    int jogadaValida = 0;

    while(jogadaValida == 0){

        if(*jogador == 1){
            printf("///////////////////////////////////////\n");
            printf("//////// \033[1;31mJogada do jogador 1:\033[0m /////////\n");
            printf("// Use G para gato e g para gatinho) //\n");
            printf("/////////// Exemplo: a 1 G ////////////\n");
            printf("///////////////////////////////////////\n\n");
        }
        if(*jogador == 2){
            printf("///////////////////////////////////////\n");
            printf("//////// \033[1;32mJogada do jogador 2:\033[0m ////////\n");
            printf("// Use G para gato e g para gatinho) //\n");
            printf("/////////// Exemplo: a 1 G ////////////\n");
            printf("///////////////////////////////////////\n\n");
        }
        /*
        printf("///////////////////////////////////////\n");
        printf("//////// Jogada do jogador %d: ////////\n", *jogador);
        printf("// Use G para gato e g para gatinho) //\n");
        printf("/////////// Exemplo: a 1 G ////////////\n");
        printf("///////////////////////////////////////\n\n");
        */

        scanf(" %c %i %c", &coluna, &linha, &gato);

        linha--;
        int colunaIndex = (int)(coluna - 'a');
        jogadaValida = validaJogada(tabuleiro, linha, colunaIndex, gato, jogador, placar);
        //tabuleiro = fazBoop(tabuleiro, placar, linha, coluna, gato);
        exibePlacar(placar);
        exibeTabuleiro(tabuleiro, 6, 6);
    }
    return 1;
}

int validaJogada(int **tabuleiro, int linha, int coluna, char gato, int *jogador, int **placar){
    //system("cls");
    int gatinho = placar[*jogador][1];
    int gatoG = placar[*jogador][2];

    if(gato == 'g'){
        if(gatinho == 0){
            printf("///////////////////////////////////////////////////\n");
            printf("///// Gatinhos insuficientes. Tente novamente//////\n");
            printf("///////////////////////////////////////////////////\n\n");
            return 0;
        }
    }
    if(gato == 'G'){
        if(gatoG == 0){
            printf("////////////////////////////////////////////////\n");
            printf("///// Gatos insuficientes. Tente novamente//////\n");
            printf("////////////////////////////////////////////////\n\n");
            return 0;
        }
    }
    if (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6 && (gato == 'g' || gato == 'G')) {
        struct NaCasa _naCasa = naCasa(tabuleiro, linha, coluna);
        if(_naCasa.tipoGato == ' '){
            if(*jogador == 1){
                if(gato == 'g'){
                    tabuleiro[linha][coluna] = 1;
                }else if(gato == 'G') {
                    tabuleiro[linha][coluna] = 2;
                }
                placar[*jogador][(gato == 'g' ? 1 : 2)] = placar[*jogador][(gato == 'g' ? 1 : 2)] - 1;
                *jogador = 2;
                tabuleiro = fazBoop(tabuleiro, placar, linha, coluna, 6, 6, gato);
                return 1;
            }
            if(*jogador == 2){
                if(gato == 'g'){
                    tabuleiro[linha][coluna] = 3;
                }else if(gato == 'G') {
                    tabuleiro[linha][coluna] = 4;
                }
                placar[*jogador][(gato == 'g' ? 1 : 2)] = placar[*jogador][(gato == 'g' ? 1 : 2)] - 1;
                *jogador = 1;
                tabuleiro = fazBoop(tabuleiro, placar, linha, coluna, 6, 6, gato);
                return 1;
            }

        } else {
            printf("//////////////////////////////////////////////////////////\n");
            printf("///// Essa posicao ja esta ocupada. Tente novamente. /////\n");
            printf("//////////////////////////////////////////////////////////\n\n");
        }
    } else {
        printf("/////////////////////////////////////////////////\n");
        printf("///// Movimento invalido, tente novamente. //////\n");
        printf("/////////////////////////////////////////////////\n\n");
    }
    return 0;
}



int verificaVitoria(int **tabuleiro, int *jogador, int **placar, int linhas, int colunas){
        for(int i = 0 ; i < linhas ; i++){
            for(int j = 0 ; j < colunas - 2 ; j++){
                if(tabuleiro[i][j] == 0){
                    continue;
                } else if(tabuleiro[i][j] == tabuleiro[i][j+1] && tabuleiro[i][j+1] == tabuleiro[i][j+2]){
                    if(tabuleiro[i][j] == 2){
                        printf("O jogador 1 ganhou\n");
                        return 1;
                    } else if(tabuleiro[i][j] == 4){
                        printf("O jogador 2 ganhou\n");
                        return 1;
                    }
                }
            }
        }

        for(int i = 0 ; i < linhas - 2 ; i++){
            for(int j = 0 ; j < colunas ; j++){
                if(tabuleiro[i][j] == 0){
                    continue;
                } else if(tabuleiro[i][j] == tabuleiro[i+1][j] && tabuleiro[i+1][j] == tabuleiro[i+2][j]){
                    if(tabuleiro[i][j] == 2){
                        printf("O jogador 1 ganhou\n");
                        return 1;
                    } else if(tabuleiro[i][j] == 4){
                        printf("O jogador 2 ganhou\n");
                        return 1;
                    }
                }
            }
        }
        for(int i = 0 ; i < linhas - 2 ; i++){
            for(int j = 0 ; j < colunas - 2 ; j++){
                if(tabuleiro[i][j] == 0){
                    continue;
                } else if(tabuleiro[i][j] == tabuleiro[i+1][j+1] && tabuleiro[i+1][j+1] == tabuleiro[i+2][j+2]){
                    if(tabuleiro[i][j] == 2 || tabuleiro[i][j] == 4){
                        if(tabuleiro[i][j] == 2){
                        printf("O jogador 1 ganhou\n");
                        return 1;
                    } else if(tabuleiro[i][j] == 4){
                        printf("O jogador 2 ganhou\n");
                        return 1;
                    }
                    }
                }
            }
        }
        for(int i = 0 ; i < linhas - 2 ; i++){
            for(int j = colunas - 1 ; j > 1 ; j--){
                if(tabuleiro[i][j] == 0){
                    continue;
                } else if(tabuleiro[i][j] == tabuleiro[i+1][j-1] && tabuleiro[i+1][j-1] == tabuleiro[i+2][j-2]){
                    if(tabuleiro[i][j] == 2){
                        printf("O jogador 1 ganhou\n");
                        return 1;
                    } else if(tabuleiro[i][j] == 4){
                        printf("O jogador 2 ganhou\n");
                        return 1;
                    }
                }
            }
        }
        if(placar[*jogador][1] == 0 || placar[*jogador][1] == 0){
            printf("O jogador %d ganhou\n", *jogador);
            return 1;
        }
        return 0;
}

int** graduaGatinho(int** placar, int** tabuleiro, int* jogador, int linhas, int colunas){
    for(int i = 0 ; i < linhas ; i++){
        for(int j = 0 ; j < colunas - 2 ; j++){
            if((tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 3) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 4) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 5)){
               if((tabuleiro[i][j] == 1 || tabuleiro[i][j] == 2) && (tabuleiro[i][j+1] == 1 || tabuleiro[i][j+2] == 2) && (tabuleiro[i][j+2] == 1 || tabuleiro[i][j+2] == 2)){
                placar[1][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i][j+1] = 0;
                tabuleiro[i][j+2] = 0;
               }
            }
            if((tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 9) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 10) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 11)){
               if((tabuleiro[i][j] == 3 || tabuleiro[i][j] == 4) && (tabuleiro[i][j+1] == 3 || tabuleiro[i][j+2] == 4) && (tabuleiro[i][j+2] == 3 || tabuleiro[i][j+2] == 4)){
                placar[2][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i][j+1] = 0;
                tabuleiro[i][j+2] = 0;
               }
            }
        }
    }
    for(int i = 0 ; i < linhas - 2 ; i++){
        for(int j = 0 ; j < colunas ; j++){
            if((tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 3) || (tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 4) || (tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 5)){
               if((tabuleiro[i][j] == 1 || tabuleiro[i][j] == 2) && (tabuleiro[i+1][j] == 1 || tabuleiro[i+1][j] == 2) && (tabuleiro[i+2][j] == 1 || tabuleiro[i+2][j] == 2)){
                placar[1][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j] = 0;
                tabuleiro[i+2][j] = 0;
               }
            }
            if((tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 9) || (tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 10) || (tabuleiro[i][j] + tabuleiro[i+1][j] + tabuleiro[i+2][j] == 11)){
               if((tabuleiro[i][j] == 3 || tabuleiro[i][j] == 4) && (tabuleiro[i+1][j] == 3 || tabuleiro[i+1][j] == 4) && (tabuleiro[i+2][j] == 3 || tabuleiro[i+2][j] == 4)){
                placar[2][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j] = 0;
                tabuleiro[i+2][j] = 0;
               }
            }
        }
    }
    for(int i = 0 ; i < linhas - 2 ; i++){
        for(int j = 0 ; j < colunas - 2 ; j++){
            if((tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 3) || (tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 4) || (tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 5)){
               if((tabuleiro[i][j] == 1 || tabuleiro[i][j] == 2) && (tabuleiro[i+1][j+1] == 1 || tabuleiro[i+1][j+1] == 2) && (tabuleiro[i+2][j+2] == 1 || tabuleiro[i+2][j+2] == 2)){
                placar[1][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j+1] = 0;
                tabuleiro[i+2][j+2] = 0;
               }
            }
            if((tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 9) || (tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 10) || (tabuleiro[i][j] + tabuleiro[i+1][j+1] + tabuleiro[i+2][j+2] == 11)){
               if((tabuleiro[i][j] == 3 || tabuleiro[i][j] == 4) && (tabuleiro[i+1][j+1] == 3 || tabuleiro[i+1][j+1] == 4) && (tabuleiro[i+2][j+2] == 3 || tabuleiro[i+2][j+2] == 4)){
                placar[2][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j+1] = 0;
                tabuleiro[i+2][j+2] = 0;
               }
            }
        }
    }
    for(int i = 0 ; i < linhas - 2 ; i++){
        for(int j = colunas - 1 ; j > 1 ; j--){
            if((tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 3) || (tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 4) || (tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 5)){
               if((tabuleiro[i][j] == 1 || tabuleiro[i][j] == 2) && (tabuleiro[i+1][j-1] == 1 || tabuleiro[i+1][j-1] == 2) && (tabuleiro[i+2][j-2] == 1 || tabuleiro[i+2][j-2] == 2)){
                placar[1][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j-1] = 0;
                tabuleiro[i+2][j-2] = 0;
               }
            }
            if((tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 9) || (tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 10) || (tabuleiro[i][j] + tabuleiro[i+1][j-1] + tabuleiro[i+2][j-2] == 11)){
               if((tabuleiro[i][j] == 3 || tabuleiro[i][j] == 4) && (tabuleiro[i+1][j-1] == 3 || tabuleiro[i+1][j-1] == 4) && (tabuleiro[i+2][j-2] == 3 || tabuleiro[i+2][j-2] == 4)){
                placar[2][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i+1][j-1] = 0;
                tabuleiro[i+2][j-2] = 0;
               }
            }
        }
    }
    return placar;
}

int** fazBoop(int** tabuleiro, int** placar, int linha, int coluna, int linhas, int colunas, char gato){
    if(linha - 1 >= 0 && coluna - 1 >= 0){
        if(tabuleiro[linha-1][coluna-1] != 0){
            if(linha - 2 >= 0 && coluna - 2 >= 0){
                if(tabuleiro[linha-2][coluna-2] == 0 && gato == 'G'){
                    tabuleiro[linha-2][coluna-2] = tabuleiro[linha-1][coluna-1];
                    tabuleiro[linha-1][coluna-1] = 0;
                }
                if(tabuleiro[linha-2][coluna-2] == 0 && gato == 'g' && (tabuleiro[linha-1][coluna-1] == 1 || tabuleiro[linha-1][coluna-1] == 3)){
                    tabuleiro[linha-2][coluna-2] = tabuleiro[linha-1][coluna-1];
                    tabuleiro[linha-1][coluna-1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha-1][coluna-1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha-1][coluna-1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha-1][coluna-1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha-1][coluna-1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha-1][coluna-1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha-1][coluna-1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha-1][coluna-1] = 0;
                        }
                        if(tabuleiro[linha-1][coluna-1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha-1][coluna-1] = 0;
                        }
                    }
                }
        }
    }
    if(linha - 1 >= 0){
        if(tabuleiro[linha-1][coluna] != 0){
            if(linha - 2 >= 0){
                if(tabuleiro[linha-2][coluna] == 0 && gato == 'G'){
                    tabuleiro[linha-2][coluna] = tabuleiro[linha-1][coluna];
                    tabuleiro[linha-1][coluna] = 0;
                }
                if(tabuleiro[linha-2][coluna] == 0 && gato == 'g' && (tabuleiro[linha-1][coluna] == 1 || tabuleiro[linha-1][coluna] == 3)){
                    tabuleiro[linha-2][coluna] = tabuleiro[linha-1][coluna];
                    tabuleiro[linha-1][coluna] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha-1][coluna] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha-1][coluna] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha-1][coluna] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha-1][coluna] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha-1][coluna] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha-1][coluna] == 1){
                            placar[1][1]++;
                            tabuleiro[linha-1][coluna] = 0;
                        }
                        if(tabuleiro[linha-1][coluna] == 3){
                            placar[2][1]++;
                            tabuleiro[linha-1][coluna] = 0;
                        }
                    }
                }
        }
    }
    if(linha - 1 >= 0 && coluna + 1 < colunas){
        if(tabuleiro[linha-1][coluna+1] != 0){
            if(linha - 2 >= 0 && coluna + 2 <= colunas){
                if(tabuleiro[linha-2][coluna+2] == 0 && gato == 'G'){
                    tabuleiro[linha-2][coluna+2] = tabuleiro[linha-1][coluna+1];
                    tabuleiro[linha-1][coluna+1] = 0;
                }
                if(tabuleiro[linha-2][coluna+2] == 0 && gato == 'g' && (tabuleiro[linha-1][coluna+1] == 1 || tabuleiro[linha-1][coluna+1] == 3)){
                    tabuleiro[linha-2][coluna+2] = tabuleiro[linha-1][coluna+1];
                    tabuleiro[linha-1][coluna+1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha-1][coluna+1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha-1][coluna+1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha-1][coluna+1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha-1][coluna+1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha-1][coluna+1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha-1][coluna+1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha-1][coluna+1] = 0;
                        }
                        if(tabuleiro[linha-1][coluna+1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha-1][coluna+1] = 0;
                        }
                    }
                }
        }
    }
    if(coluna - 1 >= 0){
        if(tabuleiro[linha][coluna-1] != 0){
            if(coluna - 2 >= 0){
                if(tabuleiro[linha][coluna-2] == 0 && gato == 'G'){
                    tabuleiro[linha][coluna-2] = tabuleiro[linha][coluna+1];
                    tabuleiro[linha][coluna-2] = 0;
                }
                if(tabuleiro[linha][coluna-2] == 0 && gato == 'g' && (tabuleiro[linha][coluna-1] == 1 || tabuleiro[linha][coluna-1] == 3)){
                    tabuleiro[linha][coluna-2] = tabuleiro[linha][coluna-1];
                    tabuleiro[linha][coluna-1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha][coluna-1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha][coluna-1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha][coluna-1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha][coluna-1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha][coluna-1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha][coluna-1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha][coluna-1] = 0;
                        }
                        if(tabuleiro[linha][coluna-1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha][coluna-1] = 0;
                        }
                    }
                }
        }
    }
    if(coluna + 1 < colunas){
        if(tabuleiro[linha][coluna+1] != 0){
            if(coluna + 2 < colunas){
                if(tabuleiro[linha][coluna+2] == 0 && gato == 'G'){
                    tabuleiro[linha][coluna+2] = tabuleiro[linha][coluna+1];
                    tabuleiro[linha][coluna+1] = 0;
                }
                if(tabuleiro[linha][coluna+2] == 0 && gato == 'g' && (tabuleiro[linha][coluna+1] == 1 || tabuleiro[linha][coluna+1] == 3)){
                    tabuleiro[linha][coluna+2] = tabuleiro[linha][coluna+1];
                    tabuleiro[linha][coluna+1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha][coluna+1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha][coluna+1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha][coluna+1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha][coluna+1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha][coluna+1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha][coluna+1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha][coluna+1] = 0;
                        }
                        if(tabuleiro[linha][coluna+1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha][coluna+1] = 0;
                        }
                    }
                }
        }
    }
    if(linha + 1 < linhas && coluna - 1 >= 0){
        if(tabuleiro[linha+1][coluna-1] != 0){
            if(linha + 2 < linhas && coluna - 2 >= 0){
                if(tabuleiro[linha+2][coluna-2] == 0 && gato == 'G'){
                    tabuleiro[linha+2][coluna-2] = tabuleiro[linha+1][coluna-1];
                    tabuleiro[linha+1][coluna-1] = 0;
                }
                if(tabuleiro[linha+1][coluna-1] == 0 && gato == 'g' && (tabuleiro[linha+1][coluna-1] == 1 || tabuleiro[linha+1][coluna-1] == 3)){
                    tabuleiro[linha+2][coluna-2] = tabuleiro[linha+1][coluna-1];
                    tabuleiro[linha+1][coluna-1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha+1][coluna-1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha+1][coluna-1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha+1][coluna-1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha+1][coluna-1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha+1][coluna-1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha+1][coluna-1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha+1][coluna-1] = 0;
                        }
                        if(tabuleiro[linha+1][coluna-1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha+1][coluna-1] = 0;
                        }
                    }
                }
        }
    }
    if(linha + 1 < linhas ){
        if(tabuleiro[linha+1][coluna] != 0){
            if(linha + 2 < linhas){
                if(tabuleiro[linha+2][coluna] == 0 && gato == 'G'){
                    tabuleiro[linha+2][coluna] = tabuleiro[linha+1][coluna];
                    tabuleiro[linha+1][coluna] = 0;
                }
                if(tabuleiro[linha+2][coluna] == 0 && gato == 'g' && (tabuleiro[linha+1][coluna] == 1 || tabuleiro[linha+1][coluna] == 3)){
                    tabuleiro[linha+2][coluna] = tabuleiro[linha+1][coluna];
                    tabuleiro[linha+1][coluna] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha+1][coluna] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha+1][coluna] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha+1][coluna] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha+1][coluna] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha+1][coluna] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha+1][coluna] == 1){
                            placar[1][1]++;
                            tabuleiro[linha+1][coluna] = 0;
                        }
                        if(tabuleiro[linha+1][coluna] == 3){
                            placar[2][1]++;
                            tabuleiro[linha+1][coluna] = 0;
                        }
                    }
                }
        }
    }
    if(linha + 1 < linhas && coluna + 1 < colunas){
        if(tabuleiro[linha+1][coluna+1] != 0){
            if(linha + 2 < linhas && coluna + 2 < colunas){
                if(tabuleiro[linha+2][coluna+2] == 0 && gato == 'G'){
                    tabuleiro[linha+2][coluna+2] = tabuleiro[linha+1][coluna+1];
                    tabuleiro[linha+1][coluna+1] = 0;
                }
                if(tabuleiro[linha+1][coluna+1] == 0 && gato == 'g' && (tabuleiro[linha+1][coluna+1] == 1 || tabuleiro[linha+1][coluna+1] == 3)){
                    tabuleiro[linha+2][coluna+2] = tabuleiro[linha+1][coluna+1];
                    tabuleiro[linha+1][coluna+1] = 0;
                }
                } else {
                    if(gato == 'G'){
                        if(tabuleiro[linha+1][coluna+1] == 1){
                            placar[1][1]++;
                        }
                        if(tabuleiro[linha+1][coluna+1] == 2){
                            placar[1][2]++;
                        }
                        if(tabuleiro[linha+1][coluna+1] == 3){
                            placar[2][1]++;
                        }
                        if(tabuleiro[linha+1][coluna+1] == 4){
                            placar[2][2]++;
                        }
                        tabuleiro[linha+1][coluna+1] = 0;
                    }
                    if(gato == 'g'){
                        if(tabuleiro[linha+1][coluna+1] == 1){
                            placar[1][1]++;
                            tabuleiro[linha+1][coluna+1] = 0;
                        }
                        if(tabuleiro[linha+1][coluna+1] == 3){
                            placar[2][1]++;
                            tabuleiro[linha+1][coluna+1] = 0;
                        }
                    }
                }
        }
    }
    return tabuleiro;
}

void menuInicio(){
    printf("\t                                                                  ++::                        ..--++ \n");
    printf("\t                                                                  ::....                    ::..::++ \n");
    printf("\t                                                                  --....--                ::----::++ \n");
    printf("\t                                                                   ------::              ::::----::  \n");
    printf("\t                                                                   --::::++            ..::++++++    \n");
    printf("\t                                                                   ::++mm          ..  ....--mmMM    \n");
    printf("\t                                                                   ::++..  ..            ....::MM    \n");
    printf("\t                                                                   --..  ..      --..--    ....::    \n");
    printf("\t                                                                         ..  ..--::::    ..          \n");
    printf("\t                                                                       --  ....--::--..  @@----..    \n");
    printf("\t                                                                       --..--##--::--##..----....    \n");
    printf("\t                     ....  ....                                ..      --::----..------::::--....    \n");
    printf("\t                 ....  ....            ....                    ..    ..----..----::------..----      \n");
    printf("\t               --..::----::    ..    ....            ..    ::  ----  --::......MMMMmm  --..::        \n");
    printf("\t              --..--::--::--..........--......            --++::----------..--  --MM++..::..--       \n");
    printf("\t            ----++----::..--..::--......--::--::..        --::--::----++mm++------++::........       \n");
    printf("\t          ::::::--------::------..++--------::::--      ..--mm::----++mm++mm++----::::....--         \n");
    printf("\t        ::++--::--::--::::::--::--------::++mm++::  --------mm::..--::++++++mmMMMM::::++----         \n");
    printf("\t      --::::--::--::----::++::--::::::::::--::mm--..----::mm++++----::::++::++mmmmmm++++----..       \n");
    printf("\t      --..++++::++----::++::++++----::::::++++++::----::++MMmm::--::::::::++++++mm++mm::::--..       \n");
    printf("\t    --::..++++::::::::++mm::::--::++::++::mm++MM++++..::MMmm++++------::::++mmmm++++++mm::--..       \n");
    printf("\t    ----..::++++++++++mm++::::::::++mmMMmmmm::mm++++--::MMmm++--------::::::mmMMMMmm++++++::..       \n");
    printf("\t  --------++mm++++mmmm++::mm++mmmm@@MMMMMM++mm++++++::--++++::::++::++::++::..::..::mmmmmm++         \n");
    printf("\t  ::--::::--  ..::++--::::  ------  ++mm++--++++++mmmmmm++mmmm++mm++::::mm++mm::--..    ::::..       \n");
    printf("\t  ::::----------..------..--....  ..      ....                  --mm++++::::++----..  ..  ::::--     \n");
    printf("\t  ++mm++++::++++::++::++++++::--::--::..----........----  ......    ++mm++++++::++--........MM::     \n");
    printf("\t  MMMM@@MMmm++MM@@mm++++++::++mm++::++::--++mmmm::::++::::..::..--....mmmmmm++++++::::--..::++::     \n");
    printf("\t  ::MM@@MMMMmm@@mm@@@@MMMMmmmmmmMMmmmmmm++++++mmmmMM++mmmm::::::::----MMmmmmMMmm++mm::----MM++--     \n");
    printf("\t    MM@@@@@@@@MM##MMMM@@MMMMMMMMMMMMMMMMmmMMMMMM@@MM++mm@@mmMMmm++                                   \n");
    printf("\t        ..MM@@##@@##@@MMMMMM++::--..                                                                 \n\n");

    printf("\t           BBBBBBBBBBBBBBBBB        OOOOOOOOO          OOOOOOOOO     PPPPPPPPPPPPPPPPP    \n");
    printf("\t           B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO   P::::::::::::::::P   \n");
    printf("\t           B::::::BBBBBB:::::B  OO:::::::::::::OO  OO:::::::::::::OO P::::::PPPPPP:::::P  \n");
    printf("\t           BB:::::B     B:::::BO:::::::OOO:::::::OO:::::::OOO:::::::OPP:::::P     P:::::P \n");
    printf("\t             B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::O  P::::P     P:::::P \n");
    printf("\t             B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O  P::::P     P:::::P \n");
    printf("\t             B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::O  P::::PPPPPP:::::P  \n");
    printf("\t             B:::::::::::::BB  O:::::O     O:::::OO:::::O     O:::::O  P:::::::::::::PP   \n");
    printf("\t             B::::BBBBBB:::::B O:::::O     O:::::OO:::::O     O:::::O  P::::PPPPPPPPP     \n");
    printf("\t             B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O  P::::P             \n");
    printf("\t             B::::B     B:::::BO:::::O     O:::::OO:::::O     O:::::O  P::::P             \n");
    printf("\t             B::::B     B:::::BO::::::O   O::::::OO::::::O   O::::::O  P::::P             \n");
    printf("\t           BB:::::BBBBBB::::::BO:::::::OOO:::::::OO:::::::OOO:::::::OPP::::::PP           \n");
    printf("\t           B:::::::::::::::::B  OO:::::::::::::OO  OO:::::::::::::OO P::::::::P           \n");
    printf("\t           B::::::::::::::::B     OO:::::::::OO      OO:::::::::OO   P::::::::P           \n");
    printf("\t           BBBBBBBBBBBBBBBBB        OOOOOOOOO          OOOOOOOOO     PPPPPPPPPP           \n");
    printf("\n\t                                   Seja bem-vindo ao Boop!\n");
    system("pause");
}
