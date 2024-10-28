#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'


struct mapa
{
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

struct posicao
{
    int x;
    int y;
};

typedef struct posicao POSICAO;

// Para fantasma
void copiamapa(MAPA* destino, MAPA* origem);

void liberamapa(MAPA* m);
void lemapa(MAPA* m);
void alocamapa(MAPA* m);
void imprimemapa(MAPA* m);
int encontramapa(MAPA* m, POSICAO* p, char c);

int ehvalida(MAPA* m, int x, int y);
int ehvazia(MAPA* m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
int podeandar(MAPA* m, char personagem, int destinox, int destinoy);

int ehparede(MAPA* m, int xdestino, int ydestino);
int ehpersonagem(MAPA* m, char personagem, int xdestino, int ydestino);


// Dando apelidos a STRUCTs.
//typedef struct mapa MAPA;
// typedef     -> função que define apelido de structs
// struct mapa -> escolha uma struct
// MAPA        -> escolhendo um novo apelido