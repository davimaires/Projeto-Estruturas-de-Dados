
#include <stdio.h>
#include <string.h>

#define MAX_POKEMONS 4
//fogo é fraco contra agua, agua e fraco contra ar,ar e fraco contra terra e terra e fraco contra fogo
int fogo = 1,agua = 2,ar = 3, terra = 4;

typedef struct pokemon{
  char nome[50];
  int tipo;
  int vida;
  int ataque;
  struct pokemon* proxpokemon;
}Pokemon;

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
  no *primeiro;
  no *ultimo;
  int tamanho;
}Fila;

void InserirPokemon(Treinador* treinador,Pokemon pokemon);
void RemoverPokemon(Treinador* treinador);

void InicializarFila(fila* torre);
void inserirFila(fila* torre, Treinador Treinador);
Treinador removerFila(fila* torre);
int Batalhar(Treinador* Jogador,fila* torre);

int main(){
  Fila* torre;
  Inicializar(&torre);

  Treinador Joao = {
        "Joao",
        {
            {"Charmander", fogo, 150, 50},
            {"Piplup", agua, 100, 70}
        }
    };

  inserir(&torre,Joao);

  //inserir todos os treinadores...

  Treinador Jogador = {nome_jogador,pokemons_jogador};

  Batalhar(&Jogador,&torre);
}

void InserirPokemon(Treinador* treinador, Pokemon pokemon){
  Pokemon* NovoPokemon = (Pokemon*) malloc(sizeof(Pokemon));
  
  if(NovoPokemon = NULL){
    printf("Erro ao alocar meomoria");
    return;
  }

  strcpy(NovoPokemon.nome,pokemon.nome);
  NovoPokemon.tipo = pokemon.tipo;
  NovoPokemon.vida = pokemon.vida;
  NovoPokemon.ataque = pokemon.ataque;
  
  treinador->ultimo = NovoPokemon;

}

void RemoverPokemon(Treinador* treinador){
  if(Treinador->atual == NULL){
    printf("")
  }

  Pokemon temp = treinador->atual;
  Treinador->atual = Treinador->atual->proxpokemon
  free(temp);

}

void Batalhar(Treinador* Jogador,fila* torre){
  if(Jogador.qtd_pokemons == 0){
    printf("Voce foi eliminado! chegando no %d lugar\n",torre.tamanho + 1);
    return;
  }
  if(Jogador.qtd_pokemons > 0 && torre->primeiro->no.treinador.qtd_pokemons > 0){
    continuarBatalha(Jogador,torre);
    return;
  }
  //caso o jogador ainda tenha pokemons e o treinador atual nao tiver nenhum
  remover(torre);
  Batalhar(Jogador,torre)

};

