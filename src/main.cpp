// #include "app.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>  
#include <ctime>
#include "timer.hpp"
#include "app.hpp"
#include "tsp.hpp"
using namespace std;

int main() {
    //
    // vector<Graph::Edge> edgeList;
    // edgeList.emplace_back(1, 2, 4);
    // edgeList.emplace_back(2, 3, 3);
    // edgeList.emplace_back(3, 4, 11);
    // edgeList.emplace_back(4, 1, 213);
    // edgeList.emplace_back(1, 3, 4);
    // edgeList.emplace_back(2, 4, 10000);
    
    
    // Graph g(edgeList, 4);
    
    // vector<int> aux = {1, 2, 3, 4};
    // do{
    //     vector<int> order = aux;
    //     for(int x : order) {
    //          cout << x << " ";
    //     }
    //     cout << endl;
    
    //     g.alg3opt(order);
    
    //     for(int x : order) {
    //          cout << x << " ";
    //     }
    //     cout << endl<< endl;
    // }while(next_permutation(aux.begin(), aux.end()));

    srand (time(NULL));
    App app;
    app.run();

    return 0;
}
