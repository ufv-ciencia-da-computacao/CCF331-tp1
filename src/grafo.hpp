#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <pair>

using namespace ::std;

class Grafo {
    private:
    vector<vector<pair<int, double>>> adj;

    void dfsIntern(int at, vector<int> &vis, vector<int> &visitOrder, vector<pair<int,int>> &returnEdges) {
        vis[at] = 1;
        visitOrder.push_back(at);
        for(auto to : adj[at]) {
            if(!vis[to.first]) {
                dfsIntern(to.first, vis, visitOrder, returnEdges);
            } else {
                returnEdges.push_back(make_pair(at, to.first));
            }
        }
    }

    public:
    void dfs(vector<int> &visitOrder, vector<pair<int, int>> returnEdges) {
        vector<int> vis(adj.size(), 0);
        dfsIntern(1, vis, visitOrder, returnEdges);
    };
};

#endif