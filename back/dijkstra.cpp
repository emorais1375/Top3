//Eduardo Morais, Jackson Gomes e Robson Borges
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

const int INFINITO = INT_MAX;
#define NIL -1

template<class T>
class No{
private:
    T item;
    No *prox;
public:
    No(){}
    T getItem() {
        return this->item;
    }
    void setItem(T item) {
        this->item = item;
    }
    No* getProx() {
        return this->prox;
    }
    void setProx(No* prox) {
        this->prox = prox;
    }
};

template <class T>
class Fila{
private:
    No<T> *frente, *tras;
    int tam;
public:
	Fila();
	void enfileira(T);
	bool vazia();
	No<T>* pos(int);
	T desenfileira();
	int getTam(){
        return this->tam;
    }    
};
template<class T>
Fila<T>::Fila(){
    this->frente = new No<T>();
    this->frente->setProx(NULL);
    this->tras = this->frente;
    this->tam = 0;
}
template<class T>
void Fila<T>::enfileira(T item){
    No<T> *aux = new No<T>();
    this->tras->setProx(aux);
    this->tras = aux;
    this->tras->setProx(NULL);
    this->tras->setItem(item);
    this->tam++;
}

template<class T>
bool Fila<T>::vazia(){
    return this->tam == 0;
}
template<class T>
No<T>* Fila<T>::pos(int n){
    int i = 0;
    for(No <T> *index = this->frente->getProx(); index != NULL; index = index->getProx()){
        if(i == n){
            return index;
        }
        i++;
    }
    return NULL;
}
template<class T>
T Fila<T>::desenfileira(){
    No<T> *aux = new No<T>();
    aux = this->frente;
    this->frente = this->frente->getProx();
    delete aux;
    this->tam--;
    return this->frente->getItem();
}

template <class T>
class FilaPrioridades{
private:
    Fila<pair<T, T>> *heap;
    int heapSize;
public:
    FilaPrioridades();
    void insere(pair<T, T>);
    void heapficaAcima(int);
    void heapficaAbaixo(int);
    pair<T, T> extraiMinimo();

    int getPai(int i){
        return static_cast<int>(floor(i/2));
    }
    int getEsq(int i){
        return (2 * i + 1);
    }
    int getDir(int i){
        return (2 * i + 2);
    }
    bool vazia(){
        return this->heap->vazia();
    }
};
template <class T>
FilaPrioridades<T>::FilaPrioridades(){
    this->heap = new Fila<pair<T, T>>;
    this->heapSize = 0;
}
template<class T>
void FilaPrioridades<T>::insere(pair<T, T> item){
        this->heap->enfileira(item);
        this->heapficaAcima(this->heapSize);
        this->heapSize++;
    }
template<class T>
void FilaPrioridades<T>::heapficaAcima(int i){
    int pai = getPai(i);
    if(i > 0 && this->heap->pos(pai)->getItem().first > this->heap->pos(i)->getItem().first){
        pair<T, T> aux = this->heap->pos(pai)->getItem();
        this->heap->pos(pai)->setItem(this->heap->pos(i)->getItem());
        this->heap->pos(i)->setItem(aux);
        this->heapficaAcima(pai);
    }
}
template<class T>
void FilaPrioridades<T>::heapficaAbaixo(int i){
    int esq = getEsq(i);
    int dir = getDir(i);
    int menor = i;
    if (esq < this->heapSize && this->heap->pos(esq)->getItem().first < this->heap->pos(i)->getItem().first)
        menor = esq;

    if (dir < this->heapSize && this->heap->pos(dir)->getItem().first < this->heap->pos(menor)->getItem().first)
        menor = dir;
        
    if (menor != i){
        pair<T, T> aux = this->heap->pos(i)->getItem();
        this->heap->pos(i)->setItem(this->heap->pos(menor)->getItem());
        this->heap->pos(menor)->setItem(aux);
        this->heapficaAbaixo(menor);
    }
}
template<class T>
pair<T, T> FilaPrioridades<T>::extraiMinimo(){
    pair<T, T> minimo = this->heap->desenfileira();
    this->heapSize--;
    this->heapficaAbaixo(0);
    return minimo;
}

template<class T>
class Grafo{
private:
	float **adj;
	int ordem, tamanho;
public:
	Grafo (int);
	void inicializa(int);
	void insere(int, int, float);

	int getOrdem(){
		return ordem;
	}
	void setOrdem(int ordem){
		this->ordem = ordem;
	}
	int getTamanho(){
		return tamanho;
	}
	void setTamanho(int tamanho){
		this->tamanho = tamanho;
	}
	float** getAdj() const{
		return adj;
	}
	void setAdj(float** adj){
		this->adj = adj;
	}
};

template<class T>
Grafo<T>::Grafo (int ordem){
	inicializa(ordem);
}
template<class T>
void Grafo<T>::inicializa(int ordem){
	this->ordem = ordem;
	adj = new float*[ordem+1];
	for(int i = 1; i <= ordem; i++)
		adj[i] = new float[ordem+1];
	for(int i = 1; i <= ordem; i++)
		for (int j = 1; j <= ordem; j++)
			adj[i][j] = 0;
}
template<class T>
void Grafo<T>::insere(int vertice1, int vertice2, float peso){
	adj[vertice1][vertice2] = peso;
	adj[vertice2][vertice1] = peso;
}

class Dijkstra{
private:
	float *dist;
	int *predecessor;
	pair<float, int> temp;
public:
	void inicia(int);
	void relaxa(int u, int v, int w);
	void dijkstra(Grafo<int>&, int);
	FilaPrioridades<float> pq;
	void retornaCaminhoMinimo(vector<int>&, int, float&);
};

void Dijkstra::inicia(int TAM){	
	dist = new float[TAM];
	predecessor = new int[TAM];

	for (int i = 1; i < TAM; i++)
		dist[i] = INFINITO, predecessor[i] = NIL;
}
void Dijkstra::relaxa(int u, int v, int w){
	if(dist[v] > (dist[u] + w)){
		dist[v] = dist[u] + w;
		predecessor[v] = u;
		pq.insere({dist[v], v});
	}
}
void Dijkstra::dijkstra(Grafo<int>& g, int orig){
	int TAM = g.getOrdem() + 1;
	inicia(TAM);
	dist[orig] = 0;
		pq.insere({dist[orig], orig});
	while(!pq.vazia())
	{
		pair<float, int> p = pq.extraiMinimo();
		int u = p.second;				

		for (int v = 1; v <= g.getOrdem(); v++){
			if (g.getAdj()[u][v] != 0)
				relaxa(u, v, g.getAdj()[u][v]);
		}
	}
}
void Dijkstra::retornaCaminhoMinimo(vector<int>& caminhoMinimo, int destino, float& somaCusto){ 
	caminhoMinimo.push_back(destino);
	int min = predecessor[destino];
	while(min != NIL){
		caminhoMinimo.push_back(min);
		min = predecessor[min];
	}
	somaCusto = dist[destino];
}

class Auxiliar{
public:
	void solucao(){
		int ordem, tamanho, vertice , adjacente, origem, destino;
		float peso;	float somaCustoSaida = 0;
		vector<int> vetorCaminho;

		cin >> ordem >> tamanho;
		Grafo<int> grafo(ordem);
		for (int i = 0; i < tamanho; i++){
			cin >> vertice >> adjacente >> peso;
			grafo.insere(vertice, adjacente, peso);
		}
		cin >> origem; cin >> destino;
		Dijkstra dk;
		dk.dijkstra(grafo, origem);
		dk.retornaCaminhoMinimo(vetorCaminho, destino, somaCustoSaida);		
		
		for(int i = (int) static_cast<int>(vetorCaminho.size() - 1); (int) i > 0; i--)
			
				cout << vetorCaminho[i] << " - ";
		cout << vetorCaminho[0];
		cout << " = " << somaCustoSaida << endl;
	}
};

int main (int argc, const char* argv[])
{
	Auxiliar pp2;
	pp2.solucao();
	return 0;
}
