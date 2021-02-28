#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
using namespace ::std;

namespace leitura{

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
};

int get_length_json() {
    ifstream grafos_file("Grafo.json");
    json obj;

    grafos_file >> obj;  
    int length_vertices = obj["data"]["nodes"]["length"];

    return length_vertices;
}
void read_json(vector<pair<int, float>> adj[]) {
    ifstream grafos_file("Grafo.json");
    json obj;

    grafos_file >> obj; 

    unordered_map<int, int> map_id_node;

    for (auto &el: obj["data"]["nodes"]["_data"].items()) {
        auto& dict = el.value();

        auto id = dict["id"].get<int>();
        auto label = stoi(dict["label"].get<string>());
        map_id_node[id] = label;
    }

    for (auto& el : obj["data"]["edges"]["_data"].items()) {
        auto& dict = el.value();
        
        auto to = map_id_node[dict["to"].get<int>()];
        auto from = map_id_node[dict["from"].get<int>()];
        auto label = stof(dict["label"].get<string>());

        adj[from].push_back(make_pair(to, label));
        adj[to].push_back(make_pair(from, label));
    }
}


int get_length_txt() {
    ifstream infile;
    infile.open("grafo.txt");

    if (infile.is_open()) {
        string line;
        
        getline(infile, line);
        stringstream ss (line);
        int V;
        ss >> V;

        return V;
    }
    
    infile.close();
}

void read_txt(vector<pair<int, float>> adj[]) {
    ifstream infile;
    infile.open("grafo.txt");

    if (infile.is_open()) {
        string line;
        
        getline(infile, line);

        while (getline(infile, line)) {
            stringstream ss(line);
            int vertice_from;
            int vertice_to;
            float weight;

            ss >> vertice_from >> vertice_to >> weight;

            adj[vertice_from].push_back(make_pair(vertice_to, weight));
            adj[vertice_to].push_back(make_pair(vertice_from, weight));
        }
    }

    infile.close();
}

void graph_to_txt(vector<pair<int, float>> adj[], int V) {
    ofstream outfile;
    outfile.open("grafo.txt");

    outfile << V << endl;

    unordered_map<pair<int, int>, bool, hash_pair> vis;

    int v;
    double w; 
    for (int u = 1; u <= V; u++)  { 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++)  { 
            v = it->first; 
            w = it->second;

            pair<int, int> from_to = make_pair(u, v);
            pair<int, int> to_from = make_pair(v, u);
            if (vis[from_to] == false && vis[to_from] == false) {
                outfile << u << " " << v << " " << w << endl; 
                vis[from_to] = true;  
                vis[to_from] = true;    
            }
        } 
    } 

    outfile.close();
}

void graph_to_json(vector<pair<int, float>> adj[], int V) {
    fstream template_json("template.json");
    json obj;
    template_json >> obj;
    
    unordered_map<pair<int, int>, bool, hash_pair> vis;

    int edges = 1;
    for (int u = 1; u <= V; u++) {
        json node = json {{to_string(u), json {{"id", u}, {"label", to_string(u)}}}};
        obj["data"]["nodes"]["_data"].insert(node.begin(), node.end());
        
        for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
            int v = it->first;
            float w = it->second;

            pair<int, int> from_to = make_pair(u, v);
            pair<int, int> to_from = make_pair(v, u);
            if (vis[from_to] == false && vis[to_from] == false) {

                json edge = json{{to_string(edges), json{{"from", u}, 
                                                        {"to", v}, 
                                                        {"label", to_string(w)}, 
                                                        {"id", edges}, 
                                                        {"color", json::value_t::object}}}};
                
                obj["data"]["edges"]["_data"].insert(edge.begin(), edge.end());

                edges++;                
                vis[from_to] = true;  
                vis[to_from] = true;    
            }            
        }
    }

    obj["data"]["nodes"]["length"] = V;
    obj["data"]["edges"]["length"] = edges;

    // "1":{"id":1,"label":"1"} nodes
    // {"1":{"from":1,"to":2,"label":"1.2","id":"1","color":{}}, edges

    ofstream outfile;
    outfile.open("grafo_out.json");

    outfile << obj;

    outfile.close();
    template_json.close();
}

}
#endif
