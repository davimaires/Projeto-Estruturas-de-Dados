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
  float chance_captura;
  struct pokemon* proxpokemon;
}Pokemon;

Pokemon pokedex[20] = {
    {"Chaminha",fogo,40,15,NULL,1},
    {"Xama",fogo,80,30,NULL,0.8},
    {"Chamao",fogo,160,60,NULL,0.5},
    {"Mega Chamas",fogo,320,120,NULL,0.25},//pokemons de fogo
    {"Aguinha",agua,40,15,NULL,1},
    {"Agua",agua,80,30,NULL,0.8},
    {"Aguao",agua,160,60,NULL,0.5},
    {"Mega Agua",agua,320,120,NULL,0.25}, //pokemons de agua
    {"Arzinho",ar,40,15,NULL,1},
    {"Brisa",ar,80,30,NULL,0.8},
    {"Arzao",ar,160,60,NULL,0.5},
    {"Mega Ar",ar,320,120,NULL,0.25}, //pokemons de ar
    {"Graminha",terra,40,15,NULL,1},
    {"Grama",terra,80,30,NULL,0.8},
    {"Gramao",terra,160,60,NULL,0.5},
    {"Mega Grama",terra,320,120,NULL,0.25} //pokemons de terra
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

int main(){
  Fila torre;
  InicializarFila(&torre);

  Pokemon charmander = {"Charmander", fogo,150,50, NULL,1};
  Pokemon piplup = {"piplup", agua,100,70, NULL,1};

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
       torre->primeiro->treinador.atual->vida -= Jogador->atual->ataque;
    }else if(torre->primeiro->treinador.atual->tipo == terra && Jogador->primeiro->atual->tipo == fogo){
       torre->primeiro->treinador.atual->vida -= Jogador->atual->ataque;
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


