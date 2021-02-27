#include <iostream>
#include <fstream> 
#include "leitura.hpp"

using namespace ::std;

void print_graph(vector<pair<int,float>> adj[], int V) { 
    int v;
    double w; 
    for (int u = 1; u < V; u++)  { 
        cout << "Vértice " << u << " conecta-se ao\n"; 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)  { 
            v = it->first; 
            w = it->second; 
            cout << "\tVértice " << v << " com peso = " << w << "\n"; 
        } 
        cout << "\n"; 
    } 
} 

int main () {
    int V = leitura::get_length_json();
    vector<pair<int,float>> adj[V+1];
    leitura::read_json(adj);

    print_graph(adj, V);
}