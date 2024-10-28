#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fogefoge_mapa.h"

// AQUI PERTENCE AS FUNÇÕES DO MAPA




void copiamapa(MAPA* destino, MAPA* origem)
{
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocamapa(destino); // Criei um novo mapa copiado do anterior, só precisava das linhas e colunas.

    for (int i = 0; i < origem->linhas; i++)
    {
       // Maneira arcaica de se copiar um mapa;
       // for (int j = 0; j < origem->colunas; j++)
       // {
       //     destino->matriz[i][j] = origem->matriz[i][j];
       // }

       // Maneira atual usando função STRINGCOPY
        strcpy(destino->matriz[i], origem->matriz[i]);
        // 1° = quem vai copiar
        // 2° = quem vai ser copiado 
    }

}



// Preciso do MAPA* m -> Toda função que dos MAPAS, precisam do MAPA* m para funcionar
int ehvalida(MAPA* m, int x, int y)
{
    // X não pode ser maior que o número de linhas, pois não tem mais matriz/mapa
    if (x >= m->linhas)
        return 0;
    // Y não pode ser maior que o número de colunas, pois não tem mais matriz/mapa
    if (y >= m->colunas)
        return 0;

    return 1;
}

int ehvazia(MAPA* m, int x, int y) // Destino_x e Destino_y
{
    // Checando se a nova posição é igual a '.', se for, ele retorna 1 e prosegue com o código.
    return m->matriz[x][y] == VAZIO;
    
}

int podeandar(MAPA* m, char personagem, int destinox, int destinoy)
{
    return ehvalida(m, destinox, destinoy) 
    && !ehparede(m, destinox, destinoy)
    && !ehpersonagem(m, personagem, destinox, destinoy); // Para que os fantasmas não se atropelem, mas possam se chocar contra o jogador
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino)
{
    char personagem = m->matriz[xorigem][yorigem]; // RETORNA O SIMBOLO QUE ESTÁ! SE FOR O PLAYER, É O "@"

    m->matriz[xdestino][ydestino] = personagem; // Aqui o personagem anda.
    m->matriz[xorigem][yorigem] = VAZIO; // A posição de origem recebe "."

}

// Char c -> player
int encontramapa(MAPA* m, POSICAO* p, char c)
{
    // Procurando o FOGE-FOGE (@)
    for (int i = 0; i < m->linhas; i++)
    {
        for (int j = 0; j < m->colunas; j++)
        {
            if (m->matriz[i][j] == c)
            {
                p->x = i;
                p->y = j;
                
                return 1;
            }
        } 
    }

    return 0;
}

int ehparede(MAPA* m, int xdestino, int ydestino)
{
    return m->matriz[xdestino][ydestino] == PAREDE_VERTICAL || m->matriz[xdestino][ydestino] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* m, char personagem, int xdestino, int ydestino)
{
    return m->matriz[xdestino][ydestino] == personagem;
}


void liberamapa(MAPA* m)
{
    // Preciso acessar o conteúdo do ponteiro, pra isso, eu uso (*m).matriz ou m->matriz

    // Limpeza da alocação de memória
    for (int i = 0; i < m->linhas; i++)
    {
        free(m->matriz[i]);
    }
    // Limpeza final da alocação de memória
    free(m->matriz);
}

void alocamapa(MAPA* m)
{
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++)
    {                                     // Preciso botar +1 por causa do "\0" que pertence ao arquivo de texto;
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

void lemapa(MAPA* m)
{
    // Abrindo um arquivo.
    FILE* f;
    // "r" -> read | Apenas lê o arquivo.
    f = fopen("C:\\Users\\lucas\\ProjetoC\\C\\mapa.txt", "r");
    if (f == 0)
    {
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    // Na primeira linha do arquivo, se encontra as dimensões da minha matriz (linhas e colunas)
    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
    printf("Linhas: %d\nColunas: %d\n", m->linhas, m->colunas);

    alocamapa(m);



    

    // Salva uma linha do arquivo mapa.txt na matriz mapa e depois desce.
    for (int i = 0; i < 5; i++)
    {   
        // Sempre que uso esse código, ele pega a primeira linha, toda vez que rodo, ele desce uma linha.
        fscanf(f, "%s", m->matriz[i]);
    }

    // Fechando o arquivo f (mapa.txt)
    fclose(f);


}

void imprimemapa(MAPA* m)
{
    // Exibindo o mapa no terminal
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", m->matriz[i]);
    }
    // Outro maneira de fazer isso
    /*
    // Esse método leva mais linhas, mas faz a mesma coisa que o código acima.
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
    */

}