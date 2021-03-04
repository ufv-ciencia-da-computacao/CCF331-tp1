#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

class Graph {

    public:
    struct Edge {
        int from;
        int to;
        double weight;

        Edge(int _from, int _to) {
            from = _from;
            to = _to;
            weight = 0;
        }

        Edge(int _from, int _to, double _weight) {
            from = _from;
            to = _to;
            weight = _weight;
        }
    };
    
    Graph(vector<Edge> edgeList, int n);
    int order();
    int size();
    vector<int> neighbors(int vertex);
    int degree(int vertex);
    vector<int> dfs(int from);
    vector<Edge> dfsReturnEdges(int from);
    vector<vector<int>> connectedComponents();
    bool articulation(int vertex);
    bool bridge(Edge edge);

    private:
    struct Adjacent {
        int to;
        int id;
        double weight;

        Adjacent(int _to, double _weight, int _id) {
            to = _to;
            id = _id;
            weight = _weight;
        };
    };
    vector<vector<Adjacent>> adj;
    int N, M;

    vector<int> dfs(int from, vector<int> &vis);
    vector<int> dfsReturnEdges(int from, vector<int> &vis, vector<int> visEdges);

    // void dfsIntern(int from, vector<int> &vis, vector<int> &visEdges, vector<int> &visitOrder, vector<Grafo::Edge> &returnEdges, int comp){
    //     vis[from] = comp;
    //     visitOrder.push_back(from);
    //     for(auto adjacent : adj[from]) {
    //         if(!vis[adjacent.to]) {
    //             visEdges[adjacent.id] = 1;
    //             dfsIntern(adjacent.to, vis, visEdges, visitOrder, returnEdges, comp);
    //         } else {
    //             if(!visEdges[adjacent.id]) {
    //                 returnEdges.emplace_back(from, adjacent.to, adjacent.weight);
    //             }
    //         }
    //     }
    // };

    // Graph(vector<Edge> edgeList, int n)
    // {
    //     adj.assign(n+1, vector<Adjacent>());
    //     int m = edgeList.size();
    //     for(int i=0; i<m; i++) {
    //         auto edge = edgeList[i];
    //         adj[edge.from].emplace_back(edge.to, edge.weight, i);
    //         adj[edge.to].emplace_back(edge.from, edge.weight, i);
    //     }

    //     for(int i=0; i<=n; i++) {
    //         sort(adj[i].begin(), adj[i].end(), [&](Adjacent a, Adjacent b) {
    //             return a.to < b.to;
    //         });
    //     }
    // };

    // void dfs(vector<int> &visitOrder, vector<Edge> returnEdges) {
    //     int n = adj.size();
	// 	vector<int> vis(n, 0), visEdge(n, 0);
		
	// 	int comp = 0;

    //     for(int i = 1; i <= n; ++i) {
	// 		if(!vis[i]) {
    //             // clear visit order every time to create the visit forest
    //             dfsIntern(i, vis, visEdge, visitOrder, returnEdges, ++comp);
    //         }
    //     }
    // };
};

Graph::Graph(vector<Edge> edgeList, int n) {

}

int Graph::order() {

}

int Graph::size() {

}

vector<int> Graph::neighbors(int vertex) {

}

int Graph::degree(int vertex) {

}

vector<int> Graph::dfs(int from) {

}

vector<Graph::Edge> Graph::dfsReturnEdges(int from) {

}

vector<vector<int>> Graph::connectedComponents() {

}

bool Graph::articulation(int vertex) {

}

bool Graph::bridge(Graph::Edge edge) {

}

vector<int> Graph::dfs(int from, vector<int> &vis) {
    vector<int> order;
    vis[from] = 1;
    order.push_back(from);
    for(auto neigh : adj[from]) {
        if(!vis[neigh.to]) {
            vector<int> path = dfs(neigh.to, vis);
            order.insert(order.end(), path.begin(), path.end());
        }
    }
    return order;
}

vector<int> Graph::dfsReturnEdges(int from, vector<int> &vis, vector<int> visEdges) {
    
}

#endif
