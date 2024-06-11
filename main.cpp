#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;



//LISTA QUE RECEBE O PROGRAMA NEE


typedef string Chave;

// Classe que representa um no da lista

class Linha {
public:
  string linha;
  int posicao;

// Construtor padrao 
  Linha(){
    linha = " ";
  }

// Construtor com parametros
  Linha(string str){
    linha = str;
  }


// Metodo que retorna a posicao 
 int getposicao(){
   return posicao;
 }

// Metodo que guarda a posicao
 void setposicao(int pos){
   posicao = pos;
 }

// Funcao operator compara os valores do membro linha de dois objetos Linha e retorna true 
//   se forem iguais, ou false caso contrario.
  bool operator == (const Linha& other) const {
    return linha == other.linha;
  }

// Funcao para imprimir a linha
  void print(){
    cout << "Linha : "<< linha << endl;
  }

};


// Classe que representa a lista encadeada

class Lista {
public:
  Linha *linhas; 
  int TAM;
  int n;


// Construtor para lista 
  Lista (){
    TAM = 300;
    linhas = new Linha[TAM];
    n = 0;
  }


// Metodo usado para adicionar linha de codigo em NEE
  void insere(Linha l){
    if(n < TAM){
        linhas[n] = l;
        n++;
    }
    else{
      cout << "Lista cheia" << endl;
    }
  }


// Metodo para buscar dentro da lista
  Linha busca(Linha k){
    for(int i = 0; i < n; i++){
      if(linhas[i] == k){
        return linhas[i];
      }
    }
    return Linha();
  }


// Busca a posicao da linha na lista
  int buscarPosicao(int posicao){
    for ( int i = 0; i < n; i++){
      if (linhas[i].getposicao() == posicao){
        return i;
      }
    }
    return -1;
  }
};
 


// PILHA DINAMICA QUE CHECA ELEMENTOS (LINHAS) NO PROGRAMA NEE


// Classe para representar um no da pilha

class NO{
  public:
    int data;
    NO* next;


// Funcao para inicializar um novo no com um valor dado
  NO(int numLinha){
    data = numLinha;
    next = nullptr;
  }
};


// Classe para representar a pilha
class Pilha{
  public:
    NO* top;


// Construtor para inicializar a pilha (topo da pilha vazio)
  Pilha(){
    top = nullptr;
  }


// Metodo para verificar se a pilha esta vazia
  bool isempty(){
    return top == nullptr;
  }


// Metodo para empilhar uma linha na pilha
  void push(int linha){
    NO* newNode = new NO(linha);
    newNode->next = top;
    top = newNode;
  }


// Metodo para desempilhar a linha do topo da pilha
  int pop(){
    if (isempty()){
      cout << "Pilha vazia" << endl;
      return -1;
    }
    int dadoTemp = top->data;   // Armazena o valor do topo
    NO* temp = top;  // Armazena o endereço do topo
    top = top->next; // Atualiza o topo para o "proximo" no
    delete  temp;   // Libera a memoria do topo anterior
    
    return dadoTemp; // Retorna o valor do topo anterior
  }
};


// Busca a posicao da linha na lista
int buscar(string main, Lista* Nee){
  for (int i = 0; i < Nee->n; i++){
    if (Nee->linhas[i].linha == main){
      return Nee->linhas[i].posicao;
    }
  }
  return 0;
};

// Converte posicao para linha da lista
string converte(int position, Lista* Nee){
  for (int i = 0; i < Nee->n; i++){
    if (Nee->linhas[i].posicao == position){
      return Nee->linhas[i].linha;
    }
  }
  return Linha().linha;
};

// Busca comando usando a posicao
string buscaComando(int position, Lista *Nee){
  for (int i = 0; i < Nee->n; i++){
    if (Nee->linhas[i].posicao == position){
      return Nee->linhas[i].linha;
    }
  } 
  return Linha().linha;
};

// Busca funcao nee 
string buscafunc(string func, Lista *Nee){
  for (int i = 0; i < Nee->n; i++){
    if (Nee->linhas[i].linha == func+" :"){
      return Nee->linhas[i].linha;
    }
  }
  return Linha().linha;
};

// Interpreta a linguagem nee
void executar(string main, Lista *Nee){
  Pilha pilha;
  int inicio = buscar(main, Nee); // busca a funcao main (Z)

  pilha.push(inicio); // empilha a funcao main (Z)

  while(true){
    int position = pilha.pop();
    position++;
    
    string proxCommand = buscaComando(position, Nee); // busca o proximo comando
    
    if(proxCommand.length() > 7){ // se o proximo comando for um print
      string print = proxCommand.substr(10); 
      cout << print << " "; 
      pilha.push(position); 
    }
    else if(proxCommand == ""){ // se o proximo comando for vazio 
      if(pilha.isempty()){ 
        break; 
      }
    }
    else{ // se o proximo comando for uma funcao
        pilha.push(position); 
        proxCommand = proxCommand.substr(4);
      
        string func = buscafunc(proxCommand, Nee); 
        int positionNext = buscar(func , Nee); 
        string commandNext = buscaComando(positionNext, Nee); 
      
        pilha.push(positionNext); 
    }
      
  }
  
};



int main(){

  const int TAM = 300;
  string programaNEE[TAM];//vetor que recebe o programa NEE

  Lista lista;
  string k;
  
  string linhaNEE;
  int position = 0;
  while(linhaNEE != "~"){
    getline(cin, linhaNEE);//recebe a linha do programa NEE 
    
    lista.insere(linhaNEE);//insere a linha no vetor
    lista.linhas[position].setposicao(position);
    position++;
  }

  string main = "Z :"; // comeca a buscar a funcao main (Z)

  executar(main, &lista);
 
  return 0;

}
