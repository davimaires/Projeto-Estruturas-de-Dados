#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

Pokemon pokedex[16] = {
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
void peek(Treinador* Jogador);

void RemoverPokemonsTreinados(Treinador* treinador);
void LimparTorre(Fila* torre);

void InicializarFila(Fila* torre);
void inserirFila(Fila* torre, Treinador Treinador);
void RemoverFila(Fila* torre);
void GerarTorre(Fila* torre);

void Batalhar(Treinador* Jogador,Fila* torre);
void continuarBatalha(Treinador* Jogador,Fila* torre);
char BatalharSelvagem(Treinador* Jogador, Pokemon* selvagem);

void CurarFilamons(Treinador* Jogador);
void TrocarFilamon(Treinador* Jogador);
bool Captura(Treinador* catcher,Pokemon* selvagem);
void ComecoJogo(Treinador* Jogador);

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){
  srand(time(NULL));

  Fila torre;
  InicializarFila(&torre);

  Treinador Jogador;
    strcpy(Jogador.nome, "Ash");
    Jogador.atual = NULL;
    Jogador.final = NULL;
    Jogador.qtd_pokemons = 0;

  ComecoJogo(&Jogador);
  GerarTorre(&torre);
  Batalhar(&Jogador,&torre);
  
  RemoverPokemonsTreinados(&Jogador);
  LimparTorre(&torre);

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
  NovoPokemon->chance_captura = pokemon.chance_captura;

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

void RemoverPokemonsTreinados(Treinador* treinador){
  while(treinador->atual != NULL){
    RemoverPokemon(treinador);
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

  RemoverPokemonsTreinados(&temp->treinador);

  torre->primeiro = torre->primeiro->prox;
  free(temp);
  
  torre->tamanho--;

  if(torre->primeiro == NULL){
    torre->ultimo = NULL;
  }
}

void LimparTorre(Fila* torre){
  while(torre->primeiro != NULL){
    RemoverFila(torre);
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
  CurarFilamons(Jogador);
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

  int op = 0;
  int inicial = 0;
  int lista = 0;
  char* tipagem;
  printf("Digite o numero do pokemon que deseja escolher\n");

  do{
    for(int i = 0;i<16;i+=4){

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
     lista = (i/4) + 1;
     printf("%d. - Nome: %s\n",lista, pokedex[i].nome);
     printf("Tipo: %s\n",tipagem);
     printf("Vida: %d\n",pokedex[i].vida);
     printf("Dano: %d\n\n\n",pokedex[i].ataque);
    }
    
    scanf("%d",&inicial);
    
    switch (inicial){
      case 1: //fogo
        InserirPokemon(Jogador,pokedex[0]);
        op = 2;
        break;
      case 2: //agua
        InserirPokemon(Jogador,pokedex[4]);
        op = 2;
        break;
      case 3: //ar
        InserirPokemon(Jogador,pokedex[8]);
        op = 2;
        break;
      case 4: //terra
        InserirPokemon(Jogador,pokedex[12]);
        op = 2;
        break;
      default:
        printf("Esse filamon nao esta na lista! escolha outro!\n");
    }

  }while(op != 2);

  printf("Agora que voce ja tem seu companheiro, batalhe contra filamons selvagens e forme seu time!\n");
  printf("Lembre-se, quanto menor for a vida do Filamon selvagem, maior sera sua chance de captura\n");

  char cap;
  for(int i = 0;i < 6;){
    Pokemon selvagem = pokedex[rand() % 16];
    printf("Um %s selvagem apareceu!\n",selvagem.nome);
    cap = BatalharSelvagem(Jogador,&selvagem);

    if(cap == 's'){
      if(Captura(Jogador,&selvagem) == true){
        i++;
      }
    }

    CurarFilamons(Jogador);
    
    if(Jogador->atual == NULL){
      printf("Fim de jogo, mais sorte na proxima\n");
      return;
    }
  }

}

bool Captura(Treinador* catcher,Pokemon* selvagem){
  int tentativa = rand() % 100;
  char resp;

  printf("Voce deseja capturar %s? (s/n)\n",selvagem->nome);
  scanf(" %c",&resp);
  limparBuffer();

  if(selvagem->chance_captura >= tentativa && (resp == 's' || resp == 'S')){
    if(catcher->qtd_pokemons == 6){
      printf("Maximo de pokemons atingidos!\n");
      return false;
    }
    else{
      InserirPokemon(catcher,*selvagem);
      printf("%s Capturado com Sucesso!!\n",selvagem->nome);
      return true;
    }
  }
  else{
    printf("%s fugiu\n",selvagem->nome);
    return false;
    }
  }

char BatalharSelvagem(Treinador* Jogador, Pokemon* selvagem){
  char acao;

  printf("Hora do duelo!\n");

  while(Jogador->atual->vida > 0 && selvagem->vida > 0){
   printf("Seu %s - Vida: %d\n",Jogador->atual->nome,Jogador->atual->vida);
   printf("%s selvagem - Vida: %d\n",selvagem->nome,selvagem->vida);

   printf("\nAcoes:\n");

    printf("(a) Atacar\n");
    printf("(c) Tentar capturar\n");
    printf("(f) Fugir\n");
    printf("(t) Trocar de Filamon\n");
    printf("Escolha: ");
    scanf(" %c", &acao);
    limparBuffer();

    if(acao == 'f' || acao == 'F'){
      printf("\nVoce fugiu!\n");
      return 'n';
    }
    else if(acao == 't' || acao == 'T'){
      if(Jogador->qtd_pokemons == 1){
        printf("Voce nao tem outros filamons para trocar\n");
        continue;
      }
    
      TrocarFilamon(Jogador);
      printf("\n%s entrou na batalha!\n", Jogador->atual->nome);

      printf("Enquanto voce trocava, %s lancou um ataque!\n",selvagem->nome);
      Jogador->atual->vida -= selvagem->ataque;
      printf("%s causou %d de dano\n",selvagem->nome,selvagem->ataque);

      if(Jogador->atual->vida <= 0){
        printf("\nseu %s foi derrotado!\n", Jogador->atual->nome);
        RemoverPokemon(Jogador);
        if(Jogador->atual == NULL){
          printf("Todos os seus filamons foram derrotados, fim de jogo\n");
          return 'n';
        }
        printf("seu %s entrou na batalha!", Jogador->atual->nome);
      }
      continue;
    }
    else if(acao == 'c' || acao == 'C'){
      return 's';
    }
    else if(acao == 'a' || acao == 'A'){
        selvagem->vida -= Jogador->atual->ataque;
        printf("\n%s atacou e causou %d de dano!\n", Jogador->atual->nome, Jogador->atual->ataque);
        
        if(Jogador->atual->tipo == fogo && selvagem->tipo == terra){
          selvagem->vida -= Jogador->atual->ataque;
          printf("Super efetivo! Causou mais %d de dano!\n", Jogador->atual->ataque);
        }
        else if(Jogador->atual->tipo + 1 == selvagem->tipo){
          selvagem->vida -= Jogador->atual->ataque;
          printf("Super efetivo! Causou mais %d de dano!\n", Jogador->atual->ataque);
        }
        
        if(selvagem->vida <= 0){
          printf("\n%s foi derrotado e fugiu!\n", selvagem->nome);
          return 'n';
        }
        
        Jogador->atual->vida -= selvagem->ataque;
        printf("%s contra-atacou e causou %d de dano!\n", selvagem->nome, selvagem->ataque);
        
        if(selvagem->tipo == fogo && Jogador->atual->tipo == terra){
          Jogador->atual->vida -= selvagem->ataque;
          printf("Super efetivo! Causou mais %d de dano!\n", selvagem->ataque);
        }
        else if(selvagem->tipo + 1 == Jogador->atual->tipo){
          Jogador->atual->vida -= selvagem->ataque;
          printf("Super efetivo! Causou mais %d de dano!\n", selvagem->ataque);
        }
        
        if(Jogador->atual->vida <= 0){
          printf("\n%s foi derrotado!\n", Jogador->atual->nome);
          RemoverPokemon(Jogador);
          
          if(Jogador->atual == NULL){
            printf("\nVoce nao tem mais filamons!\n");
            return 'n';
          }
          
          printf("\n%s entrou na batalha!\n", Jogador->atual->nome);
        }
      }
      else {
        printf("\nAcao invalida!\n");
      }
    }
  return 'n';
}

void TrocarFilamon(Treinador* Jogador){
  int escolha = 0;

  printf("Seu time:\n");
  peek(Jogador);

  printf("Digite o numero do filamon que deseja usar 2 - %d",Jogador->qtd_pokemons);
  scanf("%d",&escolha);

  if(escolha < 2 || escolha > Jogador->qtd_pokemons){
    printf("Escolha invalida, filamon atual continuara em campo\n");
    return;
  }

  Pokemon* atual = Jogador->atual;
  Pokemon* anterior = NULL;
  Pokemon* escolhido = Jogador->atual;

  for(int i = 1;i < escolha;i++){
    anterior = escolhido;
    escolhido = escolhido->proxpokemon;
  }

  anterior->proxpokemon = escolhido->proxpokemon;
  
  if(escolhido == Jogador->final){
    Jogador->final = anterior;
  }

  escolhido->proxpokemon = Jogador->atual;
  Jogador->atual = escolhido;

}

void peek(Treinador* Jogador){
  Pokemon* mostrar = Jogador->atual;
  int count = 1;
  char* tipagem;

  while(mostrar != NULL){
    
    switch(mostrar->tipo){
      case 1:
        tipagem = "Fogo";
        break;
      case 2:
        tipagem = "Agua";
        break;
      case 3:
        tipagem = "Ar";
        break;
      case 4:
        tipagem = "Terra";
        break;
      default:
        printf("Tipo desconhecido...\n");
    }

    printf("%d. %s - Tipo: %s | Vida : %d | Dano: %d\n",count, mostrar->nome,tipagem,mostrar->vida,mostrar->ataque);

    if(count == 1){
      printf("Filamon em campo...\n");
    }

    mostrar = mostrar->proxpokemon;
    count++;
  }
}

void GerarTorre(Fila* torre){
  char* nomes[] = {"Brock", "Misty", "Lt. Surge", "Erika", "Sabrina", 
                   "Koga", "Blaine"};
  
  //os treinadores mais fracos tem menos filamons
  int qtd_por_treinador[7] = {1, 2, 2, 3, 3, 4, 4};
  
  int dano_maximo[7] = {30, 60, 90, 120, 180, 240, 400};
  
  printf("\nGerando torre\n");
  
  for(int nivel = 0; nivel < 7; nivel++){
    Treinador novo_treinador;
    strcpy(novo_treinador.nome, nomes[nivel]);
    novo_treinador.atual = NULL;
    novo_treinador.final = NULL;
    novo_treinador.qtd_pokemons = 0;
    
    int qtd_filamons = qtd_por_treinador[nivel];
    int dano_total_acumulado = 0;
    int dano_alvo = dano_maximo[nivel];
    
    printf("Treinador %d: %s - ", nivel + 1, novo_treinador.nome);
    
    for(int i = 0; i < qtd_filamons; i++){
      // Calcula quanto dano resta para atingir o alvo
      int dano_restante = dano_alvo - dano_total_acumulado;
      int dano_medio_necessario = dano_restante / (qtd_filamons - i);
      
      int melhor_index = 0;
      int menor_diferenca = 10000;
      
      for(int j = 0; j < 16; j++){
        int diferenca = abs(pokedex[j].ataque - dano_medio_necessario);
        
        // Garante que não ultrapasse o dano total máximo
        if(dano_total_acumulado + pokedex[j].ataque <= dano_alvo + 20){
          if(diferenca < menor_diferenca){
            menor_diferenca = diferenca;
            melhor_index = j;
          }
        }
      }
      
      Pokemon filamon_escolhido = pokedex[melhor_index];
      dano_total_acumulado += filamon_escolhido.ataque;
      
      InserirPokemon(&novo_treinador, filamon_escolhido);
      printf("%s(%d)", filamon_escolhido.nome, filamon_escolhido.ataque);
      if(i < qtd_filamons - 1) printf(", ");
    }
    
    printf(" | Dano Total: %d\n", dano_total_acumulado);
    inserirFila(torre, novo_treinador);
  }
  
  printf("\nTorre gerada com sucesso! 7 treinadores adicionados.\n");
}

void CurarFilamons(Treinador* Jogador){
  if(Jogador->atual == NULL){
    printf("Não há Filomons para curar!\n");
    return;
  }
  
  Pokemon* atual = Jogador->atual;
  int Filamons_curados = 0;

  printf("Curando Filamons pos batalha...\n");

  while(atual != NULL){
    for(int i = 0;i<16;i++){
      if(strcmp(atual->nome,pokedex[i].nome) == 0){
        int cura = pokedex[i].vida - atual->vida;
        atual->vida = pokedex[i].vida;

        if(cura > 0){
          printf("%s recuperou +%d pontos de Vida!\n",atual->nome,cura);
          Filamons_curados++;
        }
        break;
      }
    }
    atual = atual->proxpokemon;
  }
  if(Filamons_curados > 0){
    printf("Cura realizada com sucesso!\n");
  }
}
