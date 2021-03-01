#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <utility>
#include <set>

using namespace ::std;

class Grafo {
    private:
    vector<vector<pair<int, double>>> adj;

    void dfsIntern(int from, vector<int> &vis, set<pair<int,int>> &visEdges, vector<int> &visitOrder, vector<pair<int,int>> &returnEdges, int comp){
        vis[from] = comp;
        visitOrder.push_back(from);
        for(auto to : adj[from]) {
            if(!vis[to.first]) {
                visEdges.insert(make_pair(from, to.first));
                visEdges.insert(make_pair(to.first, from));
                dfsIntern(to.first, vis, visEdges, visitOrder, returnEdges);
            } else {
                if(visEdges.find(make_pair(from, to.first)) == visEdges.end()) {
                    returnEdges.push_back(make_pair(from, to.first));
                }
            }
        }
    }

    public:
    void dfs(vector<int> &visitOrder, vector<pair<int, int>> returnEdges) {
        int n = adj.size();
		vector<int> vis(n, 0);
        set<pair<int,int>> visEdges;
		
		int comp = 0;

        for(int i = 1; i <= n; ++i)
			if(!vis[i]) dfsIntern(i, vis, visEdges, visitOrder, returnEdges, ++comp);
    };
};

#endif
