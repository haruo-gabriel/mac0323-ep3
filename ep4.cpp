#include "bits/stdc++.h"

using namespace std;

class Vertice {
public:
    string fragmento;                  // Fragmento do vértice
    int indice;                        // Índice do vértice
    vector<pair<Vertice, int>> adj;     // Lista de adjacência


    Vertice(){}
    // Construtor
    Vertice(string frag, int ind) {
        fragmento = frag;
        indice = ind;
    }

    // Adiciona um vértice adjacente
    void addAdj(Vertice Vertice, int peso) {
        adj.push_back({ Vertice, peso });
    }

    // Comparar o o sufixo e o prefixo de dois fragmentos
    int compara(Vertice v) {
        int tamanho1 = fragmento.length();
        int tamanho2 = v.fragmento.length();
        int tamanhoMenor = min(tamanho1, tamanho2);
        int tamanhoSequencia = 0;

        // Verifica as substrings do final da primeira palavra e
        // do início da segunda palavra em busca da maior sequência coincidente
        for (int i = 1; i <= tamanhoMenor; i++) {
            string finalPalavra1 = fragmento.substr(tamanho1 - i);
            string inicioPalavra2 = v.fragmento.substr(0, i);

            if (finalPalavra1 == inicioPalavra2) {
                tamanhoSequencia = i;
            }
        }

        // Retorna a maior sequência coincidente encontrada
        return tamanhoSequencia;
    }
};

class Grafo {
public:
    int V;                             // Número de vértices
    int k;                             // Tamanho mínimo de sobreposição
    vector<Vertice> Vertices;          // Vetor de adjacências
    //construtor
    Grafo(int V, int k) {
        this->V = V;
        this->k = k;
        Vertices = vector<Vertice>(V);
    }
    // Adiciona todos os vértices ao Grafo
    void addVertices() {
        string aux;
        for (int v = 0; v < V; v++) {
            cin >> aux;
            Vertices[v] = Vertice(aux, v);
        }
        for (int v = 0; v < V; v++) {
            for (int i = 0; i < V; i++) {
                if (i == v)
                    continue;
                int peso = Vertices[v].compara(Vertices[i]);
                int tamanho = Vertices[v].fragmento.size() + Vertices[i].fragmento.size() - peso;
                if (peso >= k)
                    Vertices[v].addAdj(Vertices[i], tamanho);
            }
        }
    }
    //imprime o grafo
    void imprime() {
        for (int v = 0; v < V; v++) {
            Vertice aux = Vertices[v];
            cout << aux.fragmento << " ";
            for (int i = 0; i < aux.adj.size(); i++) {
                cout << aux.adj[i].first.fragmento << " ";
            }
            cout << endl;
        }
    }
};    
//cria e testa um vertice
int main(){
    int V, k;
    cin >> V >> k;
    Grafo grafo(V, k);
    grafo.addVertices();
    grafo.imprime();

    return 0;
}