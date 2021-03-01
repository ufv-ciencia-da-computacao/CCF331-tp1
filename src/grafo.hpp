#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace ::std;

class Grafo {

    public:

    struct Edge {
        int from;
        int to;
        double weight;

        Edge(){};

        Edge(int _from, int _to, double _weight) {
            from = _from;
            to = _to;
            weight = _weight;
        }
    };

    Grafo(vector<Edge> edgeList) {
        
    };

    void dfs(vector<int> &visitOrder, vector<Edge> returnEdges) {
        int n = adj.size();
		vector<int> vis(n, 0), visEdge(n, 0), returnEdgesList;
		
		int comp = 0;

        for(int i = 1; i <= n; ++i) {
			if(!vis[i]) {
                // clear visit order every time to create the visit forest
                dfsIntern(i, vis, visEdge, visitOrder, returnEdgesList, ++comp);
            }
        }
    };



    private:

    struct Adjacent {
        int to;
        int id;
        double weight;

        Adjacent(){};

        Adjacent(int _to, double _weight, int _id) {
            to = _to;
            id = _id;
            weight = _weight;
        };
    };

    vector<vector<Adjacent>> adj;
    vector<Edge> edgeList;

    void dfsIntern(int from, vector<int> &vis, vector<int> &visEdges, vector<int> &visitOrder, vector<int> &returnEdges, int comp){
        vis[from] = comp;
        visitOrder.push_back(from);
        for(auto adjacent : adj[from]) {
            if(!vis[adjacent.to]) {
                visEdges[adjacent.id] = 1;
                dfsIntern(adjacent.to, vis, visEdges, visitOrder, returnEdges, comp);
            } else {
                if(!visEdges[adjacent.id]) {
                    returnEdges.push_back(adjacent.id);
                }
            }
        }
    };
   
};

#endif
