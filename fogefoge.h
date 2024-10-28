#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'



void move(char direcao);
int acabou();

int ehdirecao(char direcao);


// Funções dos Fantasmas

void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);

// Pegou a pilula
void explodepilula();
void explodepilula2(int xheroi, int yheroi, int somax, int somay, int qtd);



