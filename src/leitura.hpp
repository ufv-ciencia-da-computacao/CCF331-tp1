#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <iostream>
#include <fstream> 
#include "json.hpp"

using json = nlohmann::json;
using namespace ::std;

namespace leitura{
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

        cout << from << " " << to << " " << label << endl;

        adj[from].push_back(make_pair(to, label));
        adj[to].push_back(make_pair(from, label));
    }
}
}
#endif
