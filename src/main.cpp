// #include "app.hpp"
#include <iostream>
#include "timer.hpp"
#include "app.hpp"
using namespace std;

int main() {

    Timer max_time(0, 1, 0);
    Timer t;
    int cntIterations = -1;
    t.start();
    while(t <= max_time and cntIterations <= 10) {
    }
    t.stop();

    cout << t << endl;

    // vector<Graph::Edge> edgeList;
    // edgeList.emplace_back(1, 2, 1);
    // edgeList.emplace_back(1, 3, 2);
    // edgeList.emplace_back(1, 4, 3);
    // edgeList.emplace_back(2, 3, 7);
    // edgeList.emplace_back(2, 4, 1);
    // edgeList.emplace_back(3, 4, 4);
    // Graph g(edgeList, 4);

    // vector<int> order = g.closestNeighborHeuristic(1);

    // for(int x : order) {
    //     cout << x << " ";
    // }
    // cout << endl;

    // g.alg3opt(order);

    // for(int x : order) {
    //     cout << x << " ";
    // }
    // cout << endl;

    // App app;
    // app.run();

    return 0;
}