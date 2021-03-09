#ifndef GRAPH_HPP
#define GRAPH_HPP

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
    vector<Edge> dfsReturnEdges(int from, vector<int> &vis, vector<int> &visEdges);
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
    return N;
}

int Graph::size() {
    return M;
}

vector<int> Graph::neighbors(int vertex) {
    vector<int> neigh;
    for(int i=0;i<adj[vertex].size(); i++) {
        neigh.push_back(adj[vertex][i].to);
    }
    return neigh;
}

int Graph::degree(int vertex) {
    return adj[vertex].size();
}

vector<int> Graph::dfs(int from) {
    vector<int> vis(N + 1, 0);
    return dfs(from, vis);
}

vector<Graph::Edge> Graph::dfsReturnEdges(int from) {
    vector<int> vis(N+1, 0), visEdges(M+1, 0);
    return dfsReturnEdges(from, vis, visEdges);
}

vector<vector<int>> Graph::connectedComponents() {
    vector<vector<int>> dfs_forest;
    vector<int> vis (N + 1, 0);

    for(int i = 1; i <= N; ++i)
        if(!vis[i]) dfs_forest.push_back(dfs(i, vis));

    return dfs_forest;
}

bool Graph::articulation(int vertex) {
    vector<vector<int>> dfs_forest_origin = connectedComponents();
    int len_origin = dfs_forest_origin.size();

    vector<vector<int>> dfs_forest;
    vector<int> vis (N + 1, 0);
    vis[vertex] = 1;

    for(int i = 1; i <= N; ++i)
        if(!vis[i]) dfs_forest.push_back(dfs(i, vis));
    
    if(dfs_forest.size() > len_origin) return true;
    return false;
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

vector<Graph::Edge> Graph::dfsReturnEdges(int from, vector<int> &vis, vector<int> &visEdges) {
    vis[from] = 1;
    vector<Graph::Edge> returnEdges;
    for(auto neigh : adj[from]) {
        if(!vis[neigh.to]) {
            visEdges[neigh.id] = 1;
            vector<Graph::Edge> path = dfsReturnEdges(neigh.to, vis, visEdges);
            returnEdges.insert(returnEdges.end(), path.begin(), path.end());
        } else if(!visEdges[neigh.id]) {
            visEdges[neigh.id] = 1;
            returnEdges.emplace_back(from, neigh.to, neigh.weight);
        }
    }
    return returnEdges;
}

#endif
