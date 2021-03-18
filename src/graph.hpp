#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <stack>

#include <iostream>

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

    Graph();
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
        }
    };
    vector<vector<Adjacent>> adj;
    int N, M;

    vector<int> dfs(int from, vector<int> &vis);
    vector<Edge> dfsReturnEdges(int from, vector<int> &vis, vector<int> &visEdges);
};

Graph::Graph() {
    /* Empty */
}

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
        sort(adj[i].rbegin(), adj[i].rend());
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
    vector<int> visB (N+1, 0);
    vector<int> orderB;
    visB[edge.from] = 1;
    orderB = dfs(edge.to, visB);

    unordered_map<int, bool> common_path;
    for (auto v: orderB) {
        common_path[v] = true;
    }

    vector<int> visA (N+1, 0);
    vector<int> orderA;
    visA[edge.to] = 1;
    orderA = dfs(edge.from, visA);

    for (auto v: orderA) {
        if (common_path[v]==true) return false;
    }

    return true;
}

vector<int> Graph::dfs(int from, vector<int> &vis) {
    vector<int> order;
    stack<int> s; 
    s.push(from);

    while(!s.empty()){
        int cur = s.top();
        s.pop();
        if(!vis[cur]) order.push_back(cur);
        vis[cur] = 1;
        for(auto neigh : adj[cur]) {
            if(!vis[neigh.to]) {
                s.push(neigh.to);
            }
        }
    }
    return order;
}

vector<Graph::Edge> Graph::dfsReturnEdges(int from, vector<int> &vis, vector<int> &visEdges){
    vector<Graph::Edge> returnEdges;
    stack<pair<int, int>> s;
    s.push(make_pair(from, -1));

    while(!s.empty()){
        auto top = s.top();
        s.pop();
        int cur = top.first;
        int id = top.second;
        vis[cur] = 1;
        if(id != -1) visEdges[id] = 1;
        for(auto neigh : adj[cur]) {
            if(!vis[neigh.to]) {
                s.push(make_pair(neigh.to, neigh.id));
            } else if(!visEdges[neigh.id]) {
                visEdges[neigh.id] = 1;
                returnEdges.emplace_back(cur, neigh.to, neigh.weight);
            }
        }
    }
    return returnEdges;
}

#endif
