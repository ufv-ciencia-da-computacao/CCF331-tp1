#include <iostream>
#include <fstream> 
#include "leitura.hpp"
#include "graph.hpp"

using namespace ::std;

void print_graph(vector<Graph::Edge> edge_list) { 
    int v;
    double w; 

    for (Graph::Edge e: edge_list)  { 
        if (e.from > e.to) cout << e.from << " " << e.to << " " << e.weight << endl;
        else cout << e.to << " " << e.from << " " << e.weight << endl;
    } 
} 

int main () {
    int N = leitura::get_length_txt("grafo.txt");
    vector<Graph::Edge> edge_list = leitura::read_txt("grafo.txt");

    leitura::edge_list_to_json(edge_list, N, "grafo_out.json");
    leitura::edge_list_to_txt(edge_list, N, "grafo_out.txt");
}