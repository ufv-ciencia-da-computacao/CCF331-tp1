#include "app.hpp"

int main() {

    vector<Graph::Edge> edgeList;
    edgeList.emplace_back(1, 2, 1);
    edgeList.emplace_back(1, 3, 2);
    edgeList.emplace_back(1, 4, 3);
    edgeList.emplace_back(2, 3, 7);
    edgeList.emplace_back(2, 4, 1);
    edgeList.emplace_back(3, 4, 4);
    Graph g(edgeList, 4);

    for(int x : g.closestNeighborHeuristic(1)) {
        cout << x << " ";
    }
    cout << endl;

    // App app;
    // app.run();

    return 0;
}