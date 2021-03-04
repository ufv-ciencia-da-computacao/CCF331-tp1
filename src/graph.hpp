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
            weight = 1;
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

        bool operator < (const Adjacent &b) {
            return to < b.to;
        };
    };
    vector<vector<Adjacent>> adj;
    int N, M;

    vector<int> dfs(int from, vector<int> &vis);
    vector<Edge> dfsReturnEdges(int from, vector<int> &vis, vector<int> visEdges);
};

Graph::Graph(vector<Edge> edgeList, int n) {
    N = n;
    M = edgeList.size();
    adj.assign(N+1, vector<Adjacent>());
    for(int i=0; i<M; i++) {
        Edge e = edgeList[i];
        adj[e.from].emplace_back(e.to, e.weight, i);
        adj[e.to].emplace_back(e.from, e.weight, i);
    }

    for(int i=0; i<=N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
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

vector<Graph::Edge> Graph::dfsReturnEdges(int from, vector<int> &vis, vector<int> visEdges) {
    
}

#endif
