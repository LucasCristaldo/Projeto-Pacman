#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "fogefoge_mapa.h"



/*

// Foram para o fogefoge.h, pois são variáveis que precisam estar juntas, formam uma struct.

char** mapa;
int linhas;
int colunas;

*/

// Não preciso usar mais isso, pois eu criei um TYPEDEF
//struct mapa m;
// Já que eu usei typedef
MAPA m;      
POSICAO heroi; // Tem o X e Y do heroi aqui, lembrando, é um conjusto de variáveis que precisam sempre estar juntas. 
// Veja mais em FOGEFOGE_MAPA.H
int tempilula = 0;

int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino)
{
    int opcoes[4][2] =
    {   
        {   xatual, yatual + 1  },
        {   xatual + 1, yatual  },
        {   xatual, yatual - 1  },
        {   xatual - 1, yatual  } 
    };

    srand(time(0));

    for (int i = 0; i < 10; i++)
    {
        int posicao = rand() % 4;

        if ( podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1]) )
        {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }

    }
    
    return 0;

}

void fantasmas()
{
    MAPA copia;

    copiamapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++)
    {
        for (int j = 0; j < m.colunas; j++)
        {
            if (copia.matriz[i][j] == FANTASMA )
            {
                int xdestino;
                int ydestino;

                int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

                if (encontrou)
                {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }


            }
            
        }
        
    }

    liberamapa(&copia);

}


int acabou()
{
    POSICAO pos;
    int fogefogenomapa = encontramapa(&m, &pos, HEROI); 
    return !fogefogenomapa;
}

int ehdirecao(char direcao)
{
    return  direcao == 'a' ||
            direcao == 'w' ||
            direcao == 's' ||
            direcao == 'd';
    // Retorna um inteiro, mas no caso, é 1 (true) ou 0 (false), uma booleana.
}

void move(char direcao)
{
    // Se não é uma direção, ele retorna pro do-while.
    if (!ehdirecao(direcao) )
        return; 
    
    // Eu cancelo todo a função, voltando ao do-while novamente.
    // Não preciso botar "{}" se eu vou sar uma única linha de código.

    // A posição atual vira ponto! E a nova posição ganha o player.
    //m.matriz[heroi.x][heroi.y] = '.'; -> Colocando condições

    // ProximoX e ProximoY -> Recebe a posição do HEROI 
    int proximox = heroi.x;
    int proximoy = heroi.y;

    // A escolha do player reflete o próximo movimento do "@"
    switch (direcao)
    {
        // Fazendo o teste com o "próximo", falando pra ele se mover independente de como está o mapa
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
        default:
            break;
    }

    // Fazendo os TESTES com o "PRÓXIMO"
    //Testando com o "Próximo" se ele está passando do tamanho do mapa/matriz e se estiver, ele retorna pro do-while.
     // Checando se a nova posição é diferente '.', se for, ele retorna pro do-while
    if(!podeandar(&m, HEROI, proximox, proximoy))
        return;
   
    if(ehpersonagem(&m, PILULA, proximox, proximoy))
    {
        tempilula = 1;
    }
    
    // Se ele chegou ate aqui, é porque ele PODE andar.
 
    andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
    //m.matriz[proximox][proximoy] = '@';
    //m.matriz[heroi.x][heroi.y] = '.'; // A posição de origem recebe "."
    heroi.x = proximox; // AGORA O HEROI PODE RECEBER A NOVA POSIÇÃO x -> heroi/vilao chegou ao destino.    
    heroi.y = proximoy; // AGORA O HEROI PODE RECEBER A NOVA POSIÇÃO y -> heroi/vilao chegou ao destino.


}

void explodepilula()
{
    if (!tempilula) return; // Senão tiver pilula, mata a função de primeira
    explodepilula2(heroi.x, heroi.y, 0, 1, 3);
    explodepilula2(heroi.x, heroi.y, 0, -1, 3);
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);
    explodepilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

// Funçao recursiva é quando chamamos ela de novo dentro dela mesmo.
void explodepilula2(int xheroi, int yheroi, int somax, int somay, int qtd)
{   
    if (qtd == 0) return; // Ele sai da função

    int novox = xheroi + somax;
    int novoy = yheroi + somay;
    
    if (!ehvalida(&m, novox, novoy)) return;
    if (ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd-1);
    

    // Outra maneira:
    {
    // faz o teste 3 vezes para a direita
    //for (int i = 1; i <= 3; i++)
    //{  // Precisa começar com 1, pq se for 0 ele não anda e se explode.  
    //    // Ehvalida se estamos dentro do tamanho do array linhas e colunas
    //    if( ehvalida(&m, heroi.x, heroi.y + i ))
    //    {
    //        if(ehparede(&m, heroi.x, heroi.y + i))
    //        {
    //            break;
    //        }
    //        // Quando ele chegar aqui, ele adiciona um "pontinho".
    //        m.matriz[heroi.x][heroi.y + i] = VAZIO;
    //    }
    //}
    }
    
}

int main(){

    {
    /*
    // Criando uma Matriz de 5 x 10
    char mapa[5][14+1];
    */
    /*
    // Aplicando valores a matriz.

    mapa[0][0] = '|'; 
    mapa[4][9] = '@';

    printf("%c %c\n", mapa[0][0], mapa[4][9]);
    */

   // Aprendendo a alocar memória enquanto o programa roda
    //////////

    // Alocando dinamicamente quanto de memotia eu preciso com sizeof(int/double/char)
    /*
    // Alocando uma VARIÁVEL
    int* v = malloc(sizeof(int));

    *v = 10;

    printf("Inteiro alocado: %d\n", *v);

    free(v); // Alguma hora tenho que liberar o espaço
    */

    /*
    // Alocando um ARRAY
    // Para alocar um array, basta fazer igual alocar uma variável, mas agora colocamos " * Tamanho_do_Array ";
    int* v = malloc(sizeof(int) * 50 ); // Eu disse que o tamanho do ARRAY é 50 -> int v[50];

    v[0] = 15;
    v[2] = 32;
    v[50] = 100;

    printf("Primeiro valor: %d\nSegundo valor: %d\nTerceiro valor: %d\n", v[0], v[2], v[50]);

    free(v); // Liberando espaço, alguma hora preciso fecha-lo

    */
    /*
    // Alocando uma MATRIZ
    // Eu uso for para acessar todas as pratileiras e criar mais espaço pra elas
    // Eu aviso que tenho 5 pratileiras
    int** v = malloc(sizeof(int*) * 5);
    for (int i = 0; i < 5; i++)
    {
        // Criando 10 espaços em todas as pratileiras (ou seja, guarda até 10 itens em cada pratileira)
        v[i] = malloc(sizeof(int) * 10);
    }

    // Na pratileira: 0, e no espaço: 0, eu quero guardar o número 10
    v[0][0] = 10;
    // Na pratileira: 1, e no espaço: 2, eu quero guardar o número 12
    v[1][2] = 12;
    // Exibindo as pratileiras que eu quero mostrar
    printf("Matriz 1: %d\nMatriz 2: %d\n", v[0][0], v[1][2]);

    // Fazendo a limpeza dentro de todas as pratileiras
    for (int i = 0; i < 5; i++)
    {
        // Limpando as prateleiras e seus espaços
        free(v[i]);
    }

    // Por fim, limpo a sala
    free(v);
    */

    /////////
    }
    
    lemapa(&m);

    // Encontrando o player uma única vez na matriz
    encontramapa(&m, &heroi, HEROI);

    do
    {
        printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NAO"));
        imprimemapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodepilula();

        fantasmas();

    } while (!acabou());
    

    liberamapa(&m);


}