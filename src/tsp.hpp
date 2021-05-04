#ifndef TSP_HPP
#define TSP_HPP

#include "graph.hpp"
#include "leitura.hpp"
#include "timer.hpp"
#include <stdlib.h>
#include <time.h>  
#include <ctime>

class TSP {
    private:
        Graph graph;
        int metodo;
        int instancia;
        void initGraphFromTsp(string filename);
        void applyClosestNeighbor(int vertex, string filename);
        void applySavings(int vertex, string filename);
        void apply2Opt(string input_filename, string output_filename, Timer max_time);
        void apply3Opt(string input_filename, string output_filename, Timer max_time);
    public:
        void run(int metodo, int instancia);
        
        TSP(Graph g) {
            graph = g;
        }
};


void TSP::applyClosestNeighbor(int vertex, string filename) {

    vector<int> order = graph.closestNeighborHeuristic(vertex);
    leitura::hamiltonian_cycle_to_txt(order, filename);
}

void TSP::applySavings(int vertex, string filename) {

    vector<int> order = graph.savingsHeuristic(vertex);
    leitura::hamiltonian_cycle_to_txt(order, filename);
}

void TSP::apply2Opt(string input_filename, string output_filename, Timer max_time) {

    vector<int> order = leitura::get_hamiltonian_cycle_from_txt(input_filename);

    Timer t;
    int cntIterations = -1;
    t.start();
    while(t <= max_time and cntIterations <= 10) {
        bool status = graph.alg3opt(order);
        if(!status) {
            cntIterations++;
        } else {
            cntIterations = 0;
        }
    }
    t.stop();

    leitura::order_graph_to_txt(order, graph, output_filename);
}

void TSP::apply3Opt(string input_filename, string output_filename, Timer max_time) {
    vector<int> order = leitura::get_hamiltonian_cycle_from_txt(input_filename);

    Timer t;
    int cntIterations = -1;
    t.start();
    while(t <= max_time and cntIterations <= 10) {
        bool status = graph.alg3opt(order);
        if(!status) {
            cntIterations++;
        } else {
            cntIterations = 0;
        }
    }
    t.stop();

    leitura::order_graph_to_txt(order, graph, output_filename);
}

void TSP::run(int metodo, int instancia) {

    string pattern = "data/tsplib/";
    vector<int> qtdVertex = {52, 130, 198};
    vector<string> directories = {pattern+"berlin/", pattern+"churritz/", pattern+"reinelt/"};
    
    string directory_active = directories[instancia-1];
    int randomBound = qtdVertex[instancia-1];

    set<int> vertices;
    Timer max_time(3, 0, 0);
    for (int i = 1; i <= 30; i++) {
        int randVertex = (rand() % randomBound + 1);

        while (vertices.count(randVertex) > 0) randVertex = (rand() % randomBound + 1);
        vertices.insert(randVertex);

        if (metodo == 1) {
            string hamiltonian_path_output = directory_active+"metodo1/hamiltonian_"+to_string(i);
            string tsp_output = directory_active+"metodo1/tsp_"+to_string(i);

            applyClosestNeighbor(randVertex, hamiltonian_path_output);
            apply2Opt(hamiltonian_path_output, tsp_output, max_time);
        } else {
            string hamiltonian_path_output = directory_active+"metodo2/hamiltonian_"+to_string(i);
            string tsp_output = directory_active+"metodo2/tsp_"+to_string(i);

            applySavings(randVertex, hamiltonian_path_output);
            apply3Opt(hamiltonian_path_output, tsp_output, max_time);
        }        
    }
    
}

#endif