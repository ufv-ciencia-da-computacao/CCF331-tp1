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
    vector<Edge> toEdgeList();
    vector<vector<int>> connectedComponents();
    bool articulation(int vertex);
    bool bridge(Edge edge);
    vector<int> closestNeighborHeuristic(int vertex);
    vector<int> savingsHeuristic(int vertex);

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
    void sortAdjacentListByWeight(vector<Adjacent> &array);
    void sortEdgeListByWeight(vector<Edge> &array);
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

    // OBS: elements are sorted in decreasing order
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
        if(vis[cur]) continue;
        order.push_back(cur);
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
        if(vis[cur]) continue;
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

vector<Graph::Edge> Graph::toEdgeList() {
    vector<Edge> edgeList;
    for(int i=1; i<=N; i++) {
        for(auto neigh : adj[i]) {
            if(i <= neigh.to) {
                edgeList.emplace_back(i, neigh.to, neigh.weight);
            }
        }
    }
    return edgeList;
}

vector<int> Graph::closestNeighborHeuristic(int vertex) {
    vector<int> vis(N+1, 0);
    vis[vertex] = 1;
    vector<int> order;
    order.push_back(vertex);
    vector<Adjacent> list;
    int end = 0;
    while(!end) {
        list = adj[vertex];
        sortAdjacentListByWeight(list);
        end = 1;
        for(auto neigh : list) {
            if(!vis[neigh.to]) {
                vertex = neigh.to;
                vis[vertex] = 1;
                end=0;
                order.push_back(vertex);
                break;
            }
        }
    }
    return order;
}

void Graph::sortAdjacentListByWeight(vector<Adjacent> &array) {
    if(array.size() <= 1) return;
    vector<Adjacent> left, right;
    for(int i=0; i<array.size(); i++) {
        if(2*i < array.size()) left.push_back(array[i]);
        else right.push_back(array[i]);
    }
    sortAdjacentListByWeight(left);
    sortAdjacentListByWeight(right);
    int l=0, r=0;
    for(int i=0; i<array.size(); i++) {
        if(l < left.size() and r < right.size()) {
            if(left[l].weight < right[r].weight) array[i] = left[l++];
            else array[i] = right[r++];
        } else if(l < left.size()) {
            array[i] = left[l++];
        } else {
            array[i] = right[r++];
        }
    }
}

// Requires a complete graph
vector<int> Graph::savingsHeuristic(int vertex) {
    
    vector<int> order;
    vector<Edge> temp;
    vector<Edge> savings;
    vector<Adjacent> list;
    int I[N+1][N+1] = {};
    int matEdges[N+1][N+1] = {};

    for(int i=1; i<=N; i++) {
        I[1][i] = 2;
    }
    
    for(int i=1; i<=N; i++) {
        list = adj[i];
        for(int j=0; j<list.size(); j++) {
            matEdges[i][list[j].to] = list[j].weight;
        }
    }

    for(int i=1; i<=N; i++) {
        for(int j=i+1; j<=N; j++) {
            savings.emplace_back(i, j, matEdges[1][i] + matEdges[1][j] - matEdges[i][j]);
        }
    }

    sortEdgeListByWeight(savings);

    int s = N-1;
    for(int i=0; i<savings.size(); i++) {
        if(I[1][savings[i].from]>0 && I[1][savings[i].to]>0) {
            --I[1][savings[i].from];
            --I[1][savings[i].to];
            ++I[savings[i].from][savings[i].to];
            --s;
        }
        if(s==1) break;
    }

    // What is the best way to return this matrix? (Starting from vertex)
    /*for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cout << I[i][j] << " ";
        }
        cout << endl;
    }*/

    // Proposed way
    for(int i=1; i<=N; i++) {
        for(int j=i+1; j<=N; j++) {
            if(I[i][j]==1) {
                temp.emplace_back(i, j, 0);
            }
        }
    }

    int comp = vertex, flag;
    while(order.size()<N) {
        flag = 0;
        for(int i=0; i<temp.size(); i++) {
            if(temp[i].from == comp) {
                order.push_back(comp);
                comp = temp[i].to;
                flag=1;
                temp.erase(temp.begin()+i);
                break;
            }
        }
        if(flag==1) continue;
        for(int i=0; i<temp.size(); i++) {
            if(temp[i].to == comp) {
                order.push_back(comp);
                comp = temp[i].from;
                temp.erase(temp.begin()+i);
                break;
            }
        }
    }

    return order;

}

void Graph::sortEdgeListByWeight(vector<Edge> &array) {
    if(array.size() <= 1) return;
    vector<Edge> left, right;
    for(int i=0; i<array.size(); i++) {
        if(2*i < array.size()) left.push_back(array[i]);
        else right.push_back(array[i]);
    }
    sortEdgeListByWeight(left);
    sortEdgeListByWeight(right);
    int l=0, r=0;
    for(int i=0; i<array.size(); i++) {
        if(l < left.size() and r < right.size()) {
            if(left[l].weight > right[r].weight) array[i] = left[l++];
            else                                 array[i] = right[r++];
        } else if(l < left.size()) {
            array[i] = left[l++];
        } else {
            array[i] = right[r++];
        }
    }
}

#endif
