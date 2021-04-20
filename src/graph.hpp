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

    void alg3opt(vector<int>& order);

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

void reverseSegment(vector<int>& order, int startIndex, int endIndex) {
    int left, right;
    int N = order.size();

    int inversionSize = ((N + endIndex - startIndex + 1) % N)/2;

    left = startIndex; right = endIndex;
    for (int i = 1; i <= inversionSize; i++) {
        int aux = order[left];
        order[left] = order[right];
        order[right] = aux;

        left = (left+1)%N;
        right = (N+right-1)%N;
    }  
}

int gainFrom3Opt(int x1, int x2, int y1, int y2, int z1, int z2, int optcase, vector<vector<int>> matEdges) {
    int deleteLength, addLength;

    switch (optcase) {
        case 0:
            deleteLength = 0;
            addLength = 0;
            break;
        case 1:
            deleteLength = matEdges[x1][x2] + matEdges[z1][z2];
            addLength = matEdges[x1][z1] + matEdges[x2][z2];
            break;
        case 2:
            deleteLength = matEdges[y1][y2] + matEdges[z1][z2];
            addLength = matEdges[y1][z1] + matEdges[y2][z2];
            break;
        case 3:
            deleteLength = matEdges[x1][x2] + matEdges[y1][y2];
            addLength = matEdges[x1][y1] + matEdges[x2][y2];
            break;
        case 4:
            deleteLength = matEdges[x1][x2] + matEdges[y1][y2] + matEdges[z1][z2];
            addLength = matEdges[x1][y1] + matEdges[x2][z1] + matEdges[y2][z2];
            break;
        case 5:
            deleteLength = matEdges[x1][x2] + matEdges[y1][y2] + matEdges[z1][z2];
            addLength = matEdges[x1][z1] + matEdges[y2][x2] + matEdges[y1][z2];
            break;
        case 6:
            deleteLength = matEdges[x1][x2] + matEdges[y1][y2] + matEdges[z1][z2];
            addLength = matEdges[x1][y2] + matEdges[z1][y1] + matEdges[x2][z2];
            break;
        case 7:
            deleteLength = matEdges[x1][x2] + matEdges[y1][y2] + matEdges[z1][z2];
            addLength = matEdges[x1][y2] + matEdges[z1][x2] + matEdges[y1][z2];
            break;
    }

    return deleteLength-addLength;
}

void make3OptMove(vector<int>& order, int i, int j, int k, int optcase) {
    int N = order.size();
    
    switch (optcase) {
        case 1:
            reverseSegment(order, (k+1)%N, i);
            break;
        case 2:
            reverseSegment(order, (j+1)%N, k);
            break;
        case 3:
            reverseSegment(order, (i+1)%N, j);
            break;
        case 4:
            reverseSegment(order, (j+1)%N, k);
            reverseSegment(order, (i+1)%N, j);
            break;
        case 5:
            reverseSegment(order, (k+1)%N, i);
            reverseSegment(order, (i+1)%N, j);
            break;
        case 6:
            reverseSegment(order, (k+1)%N, i);
            reverseSegment(order, (j+1)%N, k);
            break;
        case 7:
            reverseSegment(order, (k+1)%N, i);
            reverseSegment(order, (i+1)%N, j);
            reverseSegment(order, (j+1)%N, k);
            break;
    }
}

void Graph::alg3opt(vector<int>& order) {
    bool locallyOptimal = false;
    int i, j, k;
    int x1, x2, y1, y2, z1, z2;
    int optCase[7] = {1, 2, 3, 4, 5, 6, 7};
    int moveGain;
    
    vector<vector<int>> matEdges(N+1, vector<int>(N+1));
    vector<Adjacent> list;

    for(int i=1; i<=N; i++) {
        list = adj[i];
        for(int j=0; j<list.size(); j++) {
            matEdges[i][list[j].to] = list[j].weight;
        }
    }

    while (!locallyOptimal) {
        locallyOptimal = true;
        for (int i = 0; i <= N-1; i++) {
            x1 = order[i];
            x2 = order[(i+1)%N];

            for (int counter2 = 1; counter2 <= N-3; counter2++) {
                j = (i+counter2)%N;
                y1 = order[j];
                y2 = order[(j+1)%N];

                for (int counter3 = counter2+1; counter3 <= N-1; counter3++) {
                    k = (i+counter3) %N;
                    z1 = order[k];
                    z2 = order[(k+1) %N];

                    for (int l = 0; l < 6; l++) {
                        moveGain = gainFrom3Opt(x1, x2, y1, y2, z1, z2, optCase[l], matEdges);
                        if (moveGain > 0) {
                            make3OptMove(order, i, j, k, optCase[l]);
                            locallyOptimal = false;
                            break;
                        }
                    }   
                }
            }           
        } 
    }
    
}

#endif
