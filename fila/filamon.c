#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//fogo é fraco contra agua, agua e fraco contra ar,ar e fraco contra terra e terra e fraco contra fogo
const int fogo = 1,agua = 2,ar = 3, terra = 4;

typedef struct pokemon{
  char nome[50];
  int tipo;
  int vida;
  int ataque;
  struct pokemon* proxpokemon;
  int chance_captura;
}Pokemon;

Pokemon pokedex[20] = {
    {"Chaminha",fogo,40,15,NULL,100},
    {"Xama",fogo,80,30,NULL,80},
    {"Chamao",fogo,160,60,NULL,50},
    {"Mega Chamas",fogo,320,120,NULL,25},//pokemons de fogo
    {"Aguinha",agua,40,15,NULL,100},
    {"Agua",agua,80,30,NULL,80},
    {"Aguao",agua,160,60,NULL,50},
    {"Mega Agua",agua,320,120,NULL,25}, //pokemons de agua
    {"Arzinho",ar,40,15,NULL,100},
    {"Brisa",ar,80,30,NULL,80},
    {"Arzao",ar,160,60,NULL,50},
    {"Mega Ar",ar,320,120,NULL,25}, //pokemons de ar
    {"Graminha",terra,40,15,NULL,100},
    {"Grama",terra,80,30,NULL,80},
    {"Gramao",terra,160,60,NULL,50},
    {"Mega Grama",terra,320,120,NULL,25} //pokemons de terra
};

typedef struct treinador{
  char nome[50];
  Pokemon *atual;
  Pokemon *final;
  int qtd_pokemons;
}Treinador;

typedef struct no{
  Treinador treinador;
  struct no* prox;
}No;

typedef struct fila{
  No *primeiro;
  No *ultimo;
  int tamanho;
}Fila;

void InserirPokemon(Treinador* treinador,Pokemon pokemon);
void RemoverPokemon(Treinador* treinador);

void InicializarFila(Fila* torre);
void inserirFila(Fila* torre, Treinador Treinador);
Treinador removerFila(Fila* torre);

void Batalhar(Treinador* Jogador,Fila* torre);
void continuarBatalha(Treinador* Jogador,Fila* torre);

void Captura(Treinador* catcher);
void ComecoJogo(Treinador* Jogador);

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
  Fila torre;
  InicializarFila(&torre);

  Pokemon charmander = {"Charmander", fogo,150,50, NULL,100};
  Pokemon piplup = {"piplup", agua,100,70, NULL,100};

  Treinador Joao;
  strcpy(Joao.nome, "Joao");
  Joao.atual = NULL;
  Joao.final = NULL;
  Joao.qtd_pokemons = 0;

  InserirPokemon(&Joao, charmander);

  Treinador Lucas;
  strcpy(Lucas.nome, "Lucas");
  Lucas.atual = NULL;
  Lucas.final = NULL;
  Lucas.qtd_pokemons = 0;

  InserirPokemon(&Lucas, charmander);
  InserirPokemon(&Lucas, piplup);

  inserirFila(&torre,Lucas);

  //inserir todos os treinadores...

  Treinador Jogador;
    strcpy(Jogador.nome, "Ash");
    Jogador.atual = NULL;
    Jogador.final = NULL;
    Jogador.qtd_pokemons = 0;
    
    Pokemon pikachu = {"Pikachu", ar, 120, 60, NULL,1};
    InserirPokemon(&Jogador, pikachu);

    Batalhar(&Jogador,&torre);

    return 0;
}

void InserirPokemon(Treinador* treinador, Pokemon pokemon){
  Pokemon* NovoPokemon = (Pokemon*) malloc(sizeof(Pokemon));
  
  if(NovoPokemon == NULL){
    printf("Erro ao alocar meomoria\n");
    return;
  }

  strcpy(NovoPokemon->nome,pokemon.nome);
  NovoPokemon->tipo = pokemon.tipo;
  NovoPokemon->vida = pokemon.vida;
  NovoPokemon->ataque = pokemon.ataque;
  NovoPokemon->proxpokemon = NULL;

  if(treinador->atual == NULL){
    treinador->atual = NovoPokemon;
    treinador->final = NovoPokemon;
  }
  else{
    treinador->final->proxpokemon = NovoPokemon;
    treinador->final = NovoPokemon;
  }
  
  treinador->qtd_pokemons++;
}

void RemoverPokemon(Treinador* treinador){
  if(treinador->atual == NULL){
    printf("O treinador nao tem mais pokemons!\n");
    return;
  }

  Pokemon* temp = treinador->atual;
  treinador->atual = treinador->atual->proxpokemon;
  free(temp);
  treinador->qtd_pokemons--;

  if(treinador->atual == NULL){
    treinador->final = NULL;
  }

}

void InicializarFila(Fila* torre){
  torre->primeiro = NULL;
  torre->ultimo = NULL;
  torre->tamanho = 0;
}

void inserirFila(Fila* torre, Treinador treinador){
  No* NovoNo = (No*)malloc(sizeof(No));
  
  if(NovoNo == NULL){
    printf("Erro ao alocar memoria\n");
    return;
  }

  NovoNo->treinador = treinador;
  NovoNo->prox = NULL;

  if(torre->primeiro == NULL){
    torre->primeiro = NovoNo;
    torre->ultimo = NovoNo;
  }
  else{
    torre->ultimo->prox = NovoNo;
    torre->ultimo = NovoNo;
  }

  torre->tamanho++;
}

void RemoverFila(Fila* torre){

  if(torre->primeiro == NULL){
    printf("Torre Vazia!\n");
    return;
  }

  No* temp = torre->primeiro;
  torre->primeiro = torre->primeiro->prox;
  free(temp);
  
  torre->tamanho--;

  if(torre->primeiro == NULL){
    torre->ultimo = NULL;
  }
}

void Batalhar(Treinador* Jogador,Fila* torre){
  if(Jogador->atual == NULL || torre->primeiro == NULL){
    printf("Voce foi eliminado! chegando no %d lugar\n",torre->tamanho + 1);
    return;
  }
  if(Jogador->qtd_pokemons > 0 && torre->primeiro->treinador.qtd_pokemons > 0){
    continuarBatalha(Jogador,torre);
    Batalhar(Jogador,torre);
    return;
  }
  //caso o jogador ainda tenha pokemons e o treinador atual nao tiver nenhum
  RemoverFila(torre);
  Batalhar(Jogador,torre);

}

void continuarBatalha(Treinador* Jogador,Fila* torre){
  while(Jogador->atual->vida > 0 && torre->primeiro->treinador.atual->vida > 0){
     torre->primeiro->treinador.atual->vida -= Jogador->atual->ataque;
     
     if(Jogador->atual->tipo == torre->primeiro->treinador.atual->tipo+1 && Jogador->atual->tipo != terra){
       torre->primeiro->treinador.atual->vida -= Jogador->atual->ataque;
    }else if(Jogador->atual->tipo == terra && torre->primeiro->treinador.atual->tipo == fogo){
       torre->primeiro->treinador.atual->vida -= Jogador->atual->ataque;
    }

     if(torre->primeiro->treinador.atual->vida <= 0){
       break;
    }

     Jogador->atual->vida -= torre->primeiro->treinador.atual->ataque;

     if(Jogador->atual->tipo+1 == torre->primeiro->treinador.atual->tipo && torre->primeiro->treinador.atual->tipo != terra){
       Jogador->atual->vida -= torre->primeiro->treinador.atual->ataque;
    }else if(torre->primeiro->treinador.atual->tipo == terra && Jogador->atual->tipo == fogo){
       Jogador->atual->vida -= torre->primeiro->treinador.atual->ataque;
    }

     if(Jogador->atual->vida <= 0){
      break;
    }
  }

  if(Jogador->atual->vida <= 0){
    printf("%s foi derrotado!\n",Jogador->atual->nome);
    RemoverPokemon(Jogador);
  }
  else if(torre->primeiro->treinador.atual->vida <= 0){
    printf("%s foi derrotado!\n",torre->primeiro->treinador.atual->nome);
    RemoverPokemon(&torre->primeiro->treinador);
  }

}

void ComecoJogo(Treinador* Jogador){
  printf("Seja bem vindo a Filamon!\n");
  printf("Nesse jogo voce tera que criar um time de Filomons para derrotar a temida torre de adversarios\n!");
  printf("Para isso, voce precisa escolher seu primeiro Filomon!\n");

  String inicial;
  int op = 0;
  String tipagem;
  printf("Digite o nome do pokemon que deseja escolher\n");

  do{
    for(int i = 0;i<20;i+4){

     switch (pokedex[i].tipo){
        case 1:
          tipagem = "fogo";
          break;
        case 2:
          tipagem = "agua";
          break;
        case 3:
          tipagem = "ar";
          break;
        case 4:
          tipagem = "terra";
          break;
        default:
          printf("Erro ao definir o tipo\n");
      }

     printf("Nome: %s\n",pokedex[i].nome);
     printf("Tipo: %s\n",tipagem);
     printf("Vida: %d\n",pokedex[i].vida);
     printf("Dano: %d\n\n\n",pokedex[i].dano);
    }

    

  }while(op != 2);
}

void Captura(Treinador* catcher,Pokemon* selvagem){
  int tentativa = rand() % 100;
  char resp;

  printf("Voce deseja capturar %s?\n",selvagem->nome);
  scanf("%c",&resp);
  limparBuffer();

  if(selvagem->chance_captura >= tentativa){
    if(catcher->qtd_pokemons == 6){
      printf("Maximo de pokemons atingidos!\n");
    }
    else{
      InserirPokemon(catcher,*selvagem);
      printf("%s Capturado com Sucesso!!\n",selvagem->nome);
    }
  }
}
