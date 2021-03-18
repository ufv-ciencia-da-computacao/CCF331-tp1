#include <iostream>
#include <fstream> 
#include "leitura.hpp"
#include "graph.hpp"

using namespace ::std;

// // void print_graph(vector<Graph::Edge> edge_list) { 
// //     int v;
// //     double w; 

// //     for (Graph::Edge e: edge_list)  { 
// //         if (e.from > e.to) cout << e.from << " " << e.to << " " << e.weight << endl;
// //         else cout << e.to << " " << e.from << " " << e.weight << endl;
// //     } 
// // } 

int main () {
    int N = leitura::get_length_txt("grafo1.txt");
    vector<Graph::Edge> edge_list = leitura::read_txt("grafo1.txt");

    // leitura::edge_list_to_json(edge_list, N, "grafo_out.json");
    // leitura::edge_list_to_txt(edge_list, N, "grafo_out.txt");


    Graph g(edge_list, N);

    vector<Graph::Edge> edg = g.dfsReturnEdges(1); 
    vector<int> path = g.dfs(1);

    cout << edg.size() << endl;
    for(auto e : edg) {
        cout << e.from << " " << e.to << endl;
    }

    cout << path.size() << endl;
    for(int node : path) cout << node << " ";
    cout << endl;
}


// #include "app.hpp"

// int main() {

//     App app;

//     app.run();

//     return 0;
// }