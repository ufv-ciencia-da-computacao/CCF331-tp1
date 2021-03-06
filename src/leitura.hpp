#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip>
#include "json.hpp"
#include "graph.hpp"

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

int get_length_json(string filename) {
    ifstream grafos_file(filename);
    json obj;

    grafos_file >> obj;  
    int length_vertices = obj["data"]["nodes"]["length"];

    grafos_file.close();
    
    return length_vertices;
}

vector<Graph::Edge> read_json(string filename) {
    ifstream grafos_file(filename);
    json obj;

    grafos_file >> obj; 

    unordered_map<int, int> map_id_node;

    vector<Graph::Edge> edge_list;

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

        edge_list.emplace_back(from, to, label);
    }

    grafos_file.close();

    return edge_list;
}

int get_length_txt(string filename) {
    ifstream infile;
    infile.open(filename);

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

vector<Graph::Edge> read_txt(string filename) {
    ifstream infile;
    infile.open(filename);

    vector<Graph::Edge> edge_list;

    if (infile.is_open()) {
        string line;
        
        getline(infile, line);

        while (getline(infile, line)) {
            stringstream ss(line);
            int vertice_from;
            int vertice_to;
            double weight;

            ss >> vertice_from >> vertice_to >> weight;
            edge_list.emplace_back(vertice_from, vertice_to, weight);
        }
    }

    infile.close();
    return edge_list;
}

void edge_list_to_txt(vector<Graph::Edge> edge_list, int N, string filename) {
    ofstream outfile;
    outfile.open(filename);

    outfile << N << endl;

    for (Graph::Edge e: edge_list)  { 
        if (e.from > e.to) outfile << e.to << " " << e.from << " " << e.weight << endl;
        else outfile << e.from << " " << e.to << " " << e.weight << endl;
    } 

    outfile.close();
}

void edge_list_to_json(vector<Graph::Edge> edge_list, int N, string filename) {
    fstream template_json("template.json");
    json obj;
    template_json >> obj;
    
    int counter_edges = 1;
    set<int> vis;
    for (Graph::Edge e: edge_list) {
        if (vis.find(e.from)==vis.end()) {
            json node = json {{to_string(e.from), json {{"id", e.from}, {"label", to_string(e.from)}}}};
            obj["data"]["nodes"]["_data"].insert(node.begin(), node.end());
            vis.insert(e.from);
        } 
        if (vis.find(e.to)==vis.end()) {
            json node = json {{to_string(e.to), json {{"id", e.to}, {"label", to_string(e.to)}}}};
            obj["data"]["nodes"]["_data"].insert(node.begin(), node.end());
            vis.insert(e.to);
        }

        json json_edge = json{{to_string(counter_edges), json{{"from", e.from}, 
                                                {"to", e.to}, 
                                                {"label", to_string(e.weight)}, 
                                                {"id", counter_edges}, 
                                                {"color", json::value_t::object}}}};
        
        obj["data"]["edges"]["_data"].insert(json_edge.begin(), json_edge.end());

        counter_edges++;                       
    }

    obj["data"]["nodes"]["length"] = N;
    obj["data"]["edges"]["length"] = edge_list.size();

    // "1":{"id":1,"label":"1"} nodes
    // {"1":{"from":1,"to":2,"label":"1.2","id":"1","color":{}}, edges

    ofstream outfile;
    outfile.open(filename);

    outfile << obj;

    outfile.close();
    template_json.close();
}

}
#endif
