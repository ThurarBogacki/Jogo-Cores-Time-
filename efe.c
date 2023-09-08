#include "tela.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int matriz[5][5];
    bool partida;
    bool jogar;
    bool ganhou;
    int pontos;
} jogo;

typedef struct 
{
    float pontos[3];
    char nome[3][15];
}rank;

void letra_aleatoria(jogo *tabuleiro)
{
    int posx, posy, l;
    bool tem_jogada = false;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (tabuleiro->matriz[i][j] == 0)
            {
                tem_jogada = true;
            }
        }
    }
    if (tem_jogada == true)
    {
        do
        {
            posx = rand()%5;
            posy = rand()%5;
            l = rand()%4;
        } while (tabuleiro->matriz[posx][posy] != 0);

        if (l == 0)
        {
            tabuleiro->matriz[posx][posy] = 3;
        }
        else
        {
            tabuleiro->matriz[posx][posy] = 1;
        }
    }
}


void rotateMatrix(jogo *tabuleiro) {
    // Realiza a rotação da matriz
    for (int camada = 0; camada < 5 / 2; camada++) {
        int primeiro = camada;
        int ultimo = 5 - 1 - camada;

        for (int i = primeiro; i < ultimo; i++) {
            int offset = i - primeiro;
            int top = tabuleiro->matriz[primeiro][i];
            tabuleiro->matriz[primeiro][i] = tabuleiro->matriz[ultimo - offset][primeiro];
            tabuleiro->matriz[ultimo - offset][primeiro] = tabuleiro->matriz[ultimo][ultimo - offset];
            tabuleiro->matriz[ultimo][ultimo - offset] = tabuleiro->matriz[i][ultimo];
            tabuleiro->matriz[i][ultimo] = top;
        }
    }
}

void movimento(jogo *tabuleiro){
    for (int i = 0; i < 5; i++){
        for (int j = 4; j >= 0; j--){
            if(tabuleiro->matriz[i][j] != 0 && j!=4){
                if(tabuleiro->matriz[i][j+1] == 0){
                    tabuleiro->matriz[i][j+1] = tabuleiro->matriz[i][j];
                    tabuleiro->matriz[i][j] = 0;
                    tabuleiro->pontos +=1;
                    j = 4;
                }
            }
        }
    }
}

void tela_cria_tabuleiro()
{
    tela_retangulo(0, 0, 700, 700, 0, 0, 11);
    for (int i = 150; i < 600; i++)
    {
        for (int j = 100; j < 501; j++)
        {
            tela_retangulo(j, i, j + 100, i + 100, 2, 5, 10);
            j += 99;
        }
        i += 99;
    }
}
void imprime_pontos(int number, char *output){
    if (number >= 0 && number <= 9999) {
        snprintf(output, 5, "%d", number);
    } else {
        *output = '\0';
    }
}

void desenha_estado_atual(jogo *tabuleiro){
    int posx, posy;
    char pontuacao[5];
    int pontos = tabuleiro->pontos;
    posx = 150;
    posy = 200;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (tabuleiro->matriz[i][j] == 1){
                tela_retangulo(posx-50, posy-50, posx+50, posy+50, 2, 5, 12);
                tela_texto(posx, posy, 38, 5, "A");
            }else if (tabuleiro->matriz[i][j] == 3){
                tela_retangulo(posx-50, posy-50, posx+51, posy+51, 2, 5, 13);
                tela_texto(posx, posy, 38, 5, "B");
            }else if (tabuleiro->matriz[i][j] == 9){
                tela_retangulo(posx-50, posy-50, posx+50, posy+50, 2, 5, 14);
                tela_texto(posx, posy, 38, 5, "C");
            }else if (tabuleiro->matriz[i][j] == 27){
                tela_retangulo(posx-50, posy-50, posx+50, posy+50, 2, 5, 15);
                tela_texto(posx, posy, 38, 5, "D");
            }else if (tabuleiro->matriz[i][j] == 81){
                tela_retangulo(posx-50, posy-50, posx+50, posy+50, 2, 5, 16);
                tela_texto(posx, posy, 38, 5, "E");
            }else if (tabuleiro->matriz[i][j] == 243){
                tela_retangulo(posx-50, posy-50, posx+50, posy+50, 2, 5, 17);
                tela_texto(posx, posy, 38, 5, "F");
                tabuleiro->ganhou = true;
                tabuleiro->partida = false;
            }
            posx +=100;
        }
        posy += 100;
        posx = 150;
    }
    imprime_pontos(pontos, pontuacao);
    tela_texto(350, 80, 35, 5, pontuacao);
}

void agrupa(jogo *tabuleiro){
    for (int i = 0; i < 5; i++){
        for (int j = 4; j >= 0; j--){
            if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j+1] && tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j-1] && j < 4 && j > 0){
                tabuleiro->matriz[i][j+1] = tabuleiro->matriz[i][j]*3;
                if(tabuleiro->matriz[i][j] == 1){
                    tabuleiro->pontos += 30;
                }else if(tabuleiro->matriz[i][j] == 3){
                    tabuleiro->pontos += 90;
                }else if(tabuleiro->matriz[i][j] == 9){
                    tabuleiro->pontos += 270;
                }else if(tabuleiro->matriz[i][j] == 27){
                    tabuleiro->pontos += 810;
                }else if(tabuleiro->matriz[i][j] == 81){
                    tabuleiro->pontos += 2430;
                }
                tabuleiro->matriz[i][j] = 0;
                tabuleiro->matriz[i][j-1] = 0;
            }
        }
    }
}
void sorteia_letra(int matriz_antes[5][5], jogo *tabuleiro){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(matriz_antes[i][j] != tabuleiro->matriz[i][j]){
                    letra_aleatoria(tabuleiro);
                    i = 6;
                    j = 6;
            }
        }
    }
}
void movimento_up(jogo *tabuleiro){
    int matriz_antes[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            matriz_antes[i][j] = tabuleiro->matriz[i][j];
        }
    }
        rotateMatrix(tabuleiro);
        movimento(tabuleiro);
        agrupa(tabuleiro);
        movimento(tabuleiro);
        agrupa(tabuleiro);
        movimento(tabuleiro);
        rotateMatrix(tabuleiro);
        rotateMatrix(tabuleiro);
        rotateMatrix(tabuleiro);
        sorteia_letra(matriz_antes, tabuleiro);
}

void movimento_down(jogo * tabuleiro){
    int matriz_antes[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            matriz_antes[i][j] = tabuleiro->matriz[i][j];
        }
    }
    rotateMatrix(tabuleiro);
    rotateMatrix(tabuleiro);
    rotateMatrix(tabuleiro);
    movimento(tabuleiro);
    agrupa(tabuleiro);
    movimento(tabuleiro);
    rotateMatrix(tabuleiro);
    sorteia_letra(matriz_antes, tabuleiro);
}
void movimento_left(jogo *tabuleiro){
    int matriz_antes[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            matriz_antes[i][j] = tabuleiro->matriz[i][j];
        }
    }
        rotateMatrix(tabuleiro);
        rotateMatrix(tabuleiro);
        movimento(tabuleiro);
        agrupa(tabuleiro);
        movimento(tabuleiro);
        rotateMatrix(tabuleiro);
        rotateMatrix(tabuleiro);
        sorteia_letra(matriz_antes, tabuleiro);
}
void movimento_rigth(jogo *tabuleiro){
    int matriz_antes[5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            matriz_antes[i][j] = tabuleiro->matriz[i][j];
        }
    }
        movimento(tabuleiro);
        agrupa(tabuleiro);
        movimento(tabuleiro);
        sorteia_letra(matriz_antes, tabuleiro);
}
void zera_matriz(jogo *tabuleiro)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tabuleiro->matriz[i][j] = 0;
        }
    }
    tabuleiro->partida = true;
    tabuleiro->pontos = 0;
    tabuleiro->jogar = true;
    tabuleiro->ganhou = false;
    letra_aleatoria(tabuleiro);
}
void verifica_estado(jogo *tabuleiro){
    bool aux = false;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j<5; j++){
            if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j+1] && tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j-1] && j>0 && j<4){
                aux = true;
            }else if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i+1][j] && tabuleiro->matriz[i][j] == tabuleiro->matriz[i-1][j] && i>0 && i<4){
                aux = true;
            }
        }
    }
    tabuleiro->partida = aux;
}   
void verifica_jogada(jogo *tabuleiro){
    int aux = 0;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j<5; j++){
            if(tabuleiro->matriz[i][j] != 0){
                aux++;
            }
        }
    }
    if(aux == 25){
        verifica_estado(tabuleiro);
    }
}
void inicia_partida(jogo *tabuleiro)
{
    int tecla;
    tela_atualiza();
    tela_cria_tabuleiro();
    desenha_estado_atual(tabuleiro);
    tecla = tela_tecla();
    switch (tecla)
    {
    case c_up:
        movimento_up(tabuleiro);
        break;
    case c_down:
        movimento_down(tabuleiro);
        break;
    case c_left:
        movimento_left(tabuleiro);
        break;
    case c_right:
        movimento_rigth(tabuleiro);
        break;
    case c_enter:
        tabuleiro->jogar = false;
        break;
    }
    verifica_jogada(tabuleiro);
}

int menu_final(jogo *tabuleiro, int aux){
    int tecla;
    tela_atualiza();
    tela_retangulo(0,0,700,700,2,8,8);
    if(tabuleiro->ganhou == false){
        tela_texto(350, 250, 35, 5, "TU PERDEU");
    }else if(tabuleiro->ganhou == true){
         tela_texto(350, 250, 35, 5, "TU GANHOU");
    }
    tecla = tela_tecla();
    switch (tecla)
    {
    case c_up:
        if(aux > 0){
            aux--;
        }
        break;
    case c_down:
        if(aux < 2){
            aux++;
        }
        break;
    case c_enter:
    if(aux == 2){
        tabuleiro->jogar = false;
    }else if(aux == 0){
        zera_matriz(tabuleiro);
    }
        break;
    }
    if(aux == 0){
        tela_texto(350, 320, 35, 14, "JOGAR NOVAMENTE");
        tela_texto(350, 380, 35, 5, "VER RANKING");
        tela_texto(350, 440, 35, 5, "SAIR");
    }else if(aux == 1){
        tela_texto(350, 320, 35, 5, "JOGAR NOVAMENTE");
        tela_texto(350, 380, 35, 14, "VER RANKING");
        tela_texto(350, 440, 35, 5, "SAIR");
    }else if(aux == 2){
        tela_texto(350, 320, 35, 5, "JOGAR NOVAMENTE");
        tela_texto(350, 380, 35, 5, "VER RANKING");
        tela_texto(350, 440, 35, 14, "SAIR");
    }
    return aux;
}
int main()
{
    int aux = 0;
    tela_cria_cor(0.94, 1, 0.89); // fundo tabuleiro #10
    tela_cria_cor(0.85, 1, 0.83); // fundo tela jogo #11
    tela_cria_cor(0.76, 0.98, 0.97); // fundo letra A #12
    tela_cria_cor(0.52, 0.89, 1); // fundo letra B #13
    tela_cria_cor(0.58, 0.62, 1); // fundo letra C #14
    tela_cria_cor(0.86, 0.82, 0.99); // fundo letra D #15
    tela_cria_cor(0.84, 0.67, 1); // fundo letra E #16
    tela_cria_cor(0.99, 0.60, 0.93); // fundo letra F #17
    srand(time(0));
    tela_inicio(700, 700, "EFE");
    jogo tabuleiro;
    zera_matriz(&tabuleiro);
    do
    {
        if(tabuleiro.partida == true){
            inicia_partida(&tabuleiro);
        }else if(tabuleiro.partida == false){
            aux = menu_final(&tabuleiro, aux);
        }
    }while(tabuleiro.jogar);
}