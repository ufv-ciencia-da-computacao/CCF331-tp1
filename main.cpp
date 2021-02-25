#include <iostream>
#include <fstream> 
#include "json.hpp"

using json = nlohmann::json;
using namespace ::std;
int main () {
    ifstream grafos_file("Grafo.json");
    json obj;

    grafos_file >> obj;      

    cout << "Nodes: " << obj["data"]["nodes"] << endl;
}