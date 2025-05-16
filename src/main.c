#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void exibeTabuleiro(int **tabuleiro, int linhas, int colunas);
void exibePlacar(int **placar);
void menuInicio();
void printColoredText(const char *text, int textColor, int bgColor);
void setColor(int textColor, int bgColor);
void resetColor();
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

void salvarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2);
void carregarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2);
void liberarTabelas(int** tabela1, int linhas1, int** tabela2, int linhas2);
void validarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2);
int arquivoExiste(const char* nomeArquivo);

int main(){
    int **tabuleiro = inicializaMatrizTabuleiro(6, 6);
    int **placar = inicializaMatrizPlacar();
    int condicao = 1;
    int jogador = 1;
    const char* nomeArquivo = "tabuleiro.bin";
    menuInicio();
    validarTabelas(nomeArquivo, tabuleiro, 6, 6, placar, 2, 2);

    while(verificaVitoria(tabuleiro, &jogador, placar, 6, 6) == 0){
        exibePlacar(placar);
        exibeTabuleiro(tabuleiro, 6, 6);
        fazJogada(tabuleiro, &jogador, placar);
        graduaGatinho(placar, tabuleiro, &jogador, 6, 6);
        salvarTabelas(nomeArquivo, tabuleiro, 6, 6, placar, 2, 2);
    }

    return 0;
}

int arquivoExiste(const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "rb");
    if (file) {
        fclose(file);
        return 1;
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
                    printf("|");
                    printColoredText(" g ", 0x0004, 0);
                    printf("|");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 2){
                    printf("|");
                    printColoredText(" G ", 0x0004, 0);
                    printf("|");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 3){
                    printf("|");
                    printColoredText(" g ", 0x0002, 0);
                    printf("|");
                    printf(" %i ", c+1);
                }
                else if(tabuleiro[c][l] == 4){
                    printf("|");
                    printColoredText(" G ", 0x0002, 0);
                    printf("|");
                    printf(" %i ", c+1);
                }
                else{
                    printf("|   |");
                    printf(" %i ", c+1);
                }
            }
            else{
                if(tabuleiro[c][l] == 1){
                    printf("|");
                    printColoredText(" g ", 0x0004, 0);
                }
                else if(tabuleiro[c][l] == 2){
                    printf("|");
                    printColoredText(" G ", 0x0004, 0);
                }
                else if(tabuleiro[c][l] == 3){
                    printf("|");
                    printColoredText(" g ", 0x0002, 0);
                }
                else if(tabuleiro[c][l] == 4){
                    printf("|");
                    printColoredText(" G ", 0x0002, 0);
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

void salvarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2) {
    FILE* file = fopen(arquivo, "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fwrite(&linhas1, sizeof(int), 1, file);
    fwrite(&colunas1, sizeof(int), 1, file);
    for (int i = 0; i < linhas1; i++) {
        fwrite(tabela1[i], sizeof(int), colunas1, file);
    }

    fwrite(&linhas2, sizeof(int), 1, file);
    fwrite(&colunas2, sizeof(int), 1, file);
    for (int i = 1; i <= linhas2; i++) {
        fwrite(&tabela2[i][1], sizeof(int), colunas2, file);
    }

    fclose(file);
    printf("Tabelas salvas com sucesso no arquivo '%s'.\n", arquivo);
}

void carregarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2) {
    FILE* file = fopen(arquivo, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    int linhasSalvas1, colunasSalvas1;
    fread(&linhasSalvas1, sizeof(int), 1, file);
    fread(&colunasSalvas1, sizeof(int), 1, file);
    if (linhasSalvas1 != linhas1 || colunasSalvas1 != colunas1) {
        printf("Dimensões da tabela 1 no arquivo não correspondem às esperadas.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < linhas1; i++) {
        fread(tabela1[i], sizeof(int), colunas1, file);
    }

    int linhasSalvas2, colunasSalvas2;
    fread(&linhasSalvas2, sizeof(int), 1, file);
    fread(&colunasSalvas2, sizeof(int), 1, file);
    if (linhasSalvas2 != linhas2 || colunasSalvas2 != colunas2) {
        printf("Dimensões da tabela 2 no arquivo não correspondem às esperadas.\n");
        fclose(file);
        return;
    }
    for (int i = 1; i <= linhas2; i++) {
        fread(&tabela2[i][1], sizeof(int), colunas2, file);
    }

    fclose(file);
    printf("Tabelas carregadas com sucesso do arquivo '%s'.\n", arquivo);
}

void liberarTabelas(int** tabela1, int linhas1, int** tabela2, int linhas2) {
    if (tabela1 != NULL) {
        for (int i = 0; i < linhas1; i++) {
            free(tabela1[i]);
        }
        free(tabela1);
    }

    if (tabela2 != NULL) {
        for (int i = 1; i <= linhas2; i++) {
            free(tabela2[i]);
        }
        free(tabela2);
    }
}

void validarTabelas(const char* arquivo, int** tabela1, int linhas1, int colunas1, int** tabela2, int linhas2, int colunas2) {
    printf("Deseja carregar o jogo de onde parou? (s/n): ");
    char resposta;
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        FILE* file = fopen(arquivo, "rb");
        if (file == NULL) {
            printf("Nenhum arquivo salvo encontrado. Prosseguindo com as tabelas atuais.\n");
            return;
        }
        fclose(file);

        carregarTabelas(arquivo, tabela1, linhas1, colunas1, tabela2, linhas2, colunas2);
    } else {
        salvarTabelas(arquivo, tabela1, linhas1, colunas1, tabela2, linhas2, colunas2);
    }
    system("cls");
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
    system("cls");
    printf("+---------------------------------------------------+ \n");
    printf("|"); printColoredText("          Jogador 1       ", 0x0004, 0); resetColor(); printf("|"); printColoredText("         Jogador 2  ", 0x0002, 0); resetColor(); printf("    |\n");
    printf("+--------------+-----------+-------------+----------+ \n");
    printf("|"); printColoredText("  Gatinhos: ", 0x0004, 0); setColor(0x0004, 0); printf("%d ", placar[1][1]); resetColor(); printf("|"); setColor(0x0004, 0); printf(" Gatos: "); printf("%d ", placar [1][2]); resetColor(); printf(" |"); setColor(0x0002, 0); printf(" Gatinhos: "); printf("%d ", placar[2][1]); resetColor(); printf("|"); setColor(0x0002, 0); printf(" Gatos: "); printf("%d ", placar[2][2]); resetColor(); printf("|\n");
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

    if(*jogador == 1){
            printf("///////////////////////////////////////\n");
            printf("//////// "); printColoredText("Jogada do jogador 1: ", 0x0004, 0); printf("/////////\n");
            printf("// Use G para gato e g para gatinho) //\n");
            printf("/////////// Exemplo: a 1 G ////////////\n");
            printf("///////////////////////////////////////\n\n");
        }
        if(*jogador == 2){
            printf("///////////////////////////////////////\n");
            printf("//////// "); printColoredText("Jogada do jogador 2: ", 0x0002, 0); printf("/////////\n");
            printf("// Use G para gato e g para gatinho) //\n");
            printf("/////////// Exemplo: a 1 G ////////////\n");
            printf("///////////////////////////////////////\n\n");
        }

    while(jogadaValida == 0){
        scanf(" %c %i %c", &coluna, &linha, &gato);
        linha--;
        int colunaIndex = (int)(coluna - 'a');
        jogadaValida = validaJogada(tabuleiro, linha, colunaIndex, gato, jogador, placar);
    }
    return 1;
}

int validaJogada(int **tabuleiro, int linha, int coluna, char gato, int *jogador, int **placar){
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
        if((placar[1][1] == 0 && placar[1][2] == 0)){
            printf("O jogador 1 ganhou\n");
            return 1;
        }
        if((placar[2][1] == 0 && placar[2][2] == 0)){
            printf("O jogador 2 ganhou\n");
            return 1;
        }
        return 0;
}

int** graduaGatinho(int** placar, int** tabuleiro, int* jogador, int linhas, int colunas){
    for(int i = 0 ; i < linhas ; i++){
        for(int j = 0 ; j < colunas - 2 ; j++){
            if((tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 3) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 4) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 5)){
               if((tabuleiro[i][j] == 1 || tabuleiro[i][j] == 2) && (tabuleiro[i][j+1] == 1 || tabuleiro[i][j+1] == 2) && (tabuleiro[i][j+2] == 1 || tabuleiro[i][j+2] == 2)){
                placar[1][2] += 3;
                tabuleiro[i][j] = 0;
                tabuleiro[i][j+1] = 0;
                tabuleiro[i][j+2] = 0;
               }
            }
            if((tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 9) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 10) || (tabuleiro[i][j] + tabuleiro[i][j+1] + tabuleiro[i][j+2] == 11)){
               if((tabuleiro[i][j] == 3 || tabuleiro[i][j] == 4) && (tabuleiro[i][j+1] == 3 || tabuleiro[i][j+1] == 4) && (tabuleiro[i][j+2] == 3 || tabuleiro[i][j+2] == 4)){
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
            if(linha - 2 >= 0 && coluna + 2 < colunas){
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
                    tabuleiro[linha][coluna-2] = tabuleiro[linha][coluna-1];
                    tabuleiro[linha][coluna-1] = 0;
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
                if(tabuleiro[linha+2][coluna-2] == 0 && gato == 'g' && (tabuleiro[linha+1][coluna-1] == 1 || tabuleiro[linha+1][coluna-1] == 3)){
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

void printColoredText(const char *text, int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, 7);
}

void resetColor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
}

void setColor(int textColor, int bgColor){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void menuInicio(){
    setColor(0x0001, 0);
    printf("\t\t\t\t                                                                  ++::                        ..--++ \n");
    printf("\t\t\t\t                                                                  ::....                    ::..::++ \n");
    printf("\t\t\t\t                                                                  --....--                ::----::++ \n");
    printf("\t\t\t\t                                                                   ------::              ::::----::  \n");
    printf("\t\t\t\t                                                                   --::::++            ..::++++++    \n");
    printf("\t\t\t\t                                                                   ::++mm          ..  ....--mmMM    \n");
    printf("\t\t\t\t                                                                   ::++..  ..            ....::MM    \n");
    printf("\t\t\t\t                                                                   --..  ..      --..--    ....::    \n");
    printf("\t\t\t\t                                                                         ..  ..--::::    ..          \n");
    printf("\t\t\t\t                                                                       --  ....--::--..  @@----..    \n");
    printf("\t\t\t\t                                                                       --..--##--::--##..----....    \n");
    printf("\t\t\t\t                     ....  ....                                ..      --::----..------::::--....    \n");
    printf("\t\t\t\t                 ....  ....            ....                    ..    ..----..----::------..----      \n");
    printf("\t\t\t\t               --..::----::    ..    ....            ..    ::  ----  --::......MMMMmm  --..::        \n");
    printf("\t\t\t\t              --..--::--::--..........--......            --++::----------..--  --MM++..::..--       \n");
    printf("\t\t\t\t            ----++----::..--..::--......--::--::..        --::--::----++mm++------++::........       \n");
    printf("\t\t\t\t          ::::::--------::------..++--------::::--      ..--mm::----++mm++mm++----::::....--         \n");
    printf("\t\t\t\t        ::++--::--::--::::::--::--------::++mm++::  --------mm::..--::++++++mmMMMM::::++----         \n");
    printf("\t\t\t\t      --::::--::--::----::++::--::::::::::--::mm--..----::mm++++----::::++::++mmmmmm++++----..       \n");
    printf("\t\t\t\t      --..++++::++----::++::++++----::::::++++++::----::++MMmm::--::::::::++++++mm++mm::::--..       \n");
    printf("\t\t\t\t    --::..++++::::::::++mm::::--::++::++::mm++MM++++..::MMmm++++------::::++mmmm++++++mm::--..       \n");
    printf("\t\t\t\t    ----..::++++++++++mm++::::::::++mmMMmmmm::mm++++--::MMmm++--------::::::mmMMMMmm++++++::..       \n");
    printf("\t\t\t\t  --------++mm++++mmmm++::mm++mmmm@@MMMMMM++mm++++++::--++++::::++::++::++::..::..::mmmmmm++         \n");
    printf("\t\t\t\t  ::--::::--  ..::++--::::  ------  ++mm++--++++++mmmmmm++mmmm++mm++::::mm++mm::--..    ::::..       \n");
    printf("\t\t\t\t  ::::----------..------..--....  ..      ....                  --mm++++::::++----..  ..  ::::--     \n");
    printf("\t\t\t\t  ++mm++++::++++::++::++++++::--::--::..----........----  ......    ++mm++++++::++--........MM::     \n");
    printf("\t\t\t\t  MMMM@@MMmm++MM@@mm++++++::++mm++::++::--++mmmm::::++::::..::..--....mmmmmm++++++::::--..::++::     \n");
    printf("\t\t\t\t  ::MM@@MMMMmm@@mm@@@@MMMMmmmmmmMMmmmmmm++++++mmmmMM++mmmm::::::::----MMmmmmMMmm++mm::----MM++--     \n");
    printf("\t\t\t\t    MM@@@@@@@@MM##MMMM@@MMMMMMMMMMMMMMMMmmMMMMMM@@MM++mm@@mmMMmm++                                   \n");
    printf("\t\t\t\t        ..MM@@##@@##@@MMMMMM++::--..                                                                 \n\n");
    resetColor();

    setColor(0x0006, 0);
    printf("\t\t\t\t\t__/\\\\\\\\\\\\\\_________/\\\\\\____________/\\\\\\_______/\\\\\\\\\\\\\\_____________\n");
    printf("\t\t\t\t\t_\\/\\\\\\/////////\\\\\\_____/\\\\\\///\\\\\\________/\\\\\\///\\\\\\____\\/\\\\\\/////////\\\\\\___________\n");
    printf("\t\t\t\t\t _\\/\\\\\\_______\\/\\\\\\___/\\\\\\/__\\///\\\\\\____/\\\\\\/__\\///\\\\\\__\\/\\\\\\_______\\/\\\\\\___________\n");
    printf("\t\t\t\t\t  _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\___/\\\\\\______\\//\\\\\\__/\\\\\\______\\//\\\\\\_\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/____________\n");
    printf("\t\t\t\t\t   _\\/\\\\\\/////////\\\\\\_\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\/////////______________\n");
    printf("\t\t\t\t\t    _\\/\\\\\\_______\\/\\\\\\_\\//\\\\\\______/\\\\\\__\\//\\\\\\______/\\\\\\__\\/\\\\\\_______________________\n");
    printf("\t\t\t\t\t     _\\/\\\\\\_______\\/\\\\\\__\\///\\\\\\__/\\\\\\_____\\///\\\\\\__/\\\\\\____\\/\\\\\\_______________________\n");
    printf("\t\t\t\t\t      _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/_____\\///\\\\\\\\\\/________\\///\\\\\\\\\\/_____\\/\\\\\\_______________________\n");
    printf("\t\t\t\t\t       _\\/////////////_________\\/////____________\\/////_______\\///________________________\n");
    printf("\n\t\t\t\t\t                                   Seja bem-vindo ao Boop!\n");
    resetColor();

    system("pause");
    system("cls");
}
