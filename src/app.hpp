#ifndef APP_HPP
#define APP_HPP

#include "graph.hpp"
#include "leitura.hpp"
#include "timer.hpp"
#include <ctime>
#include "tsp.hpp"
#include "metrics.hpp"
#include <stdio_ext.h>

class App {
    private:
    Graph graph;
    bool status = false;


    void waitForKeyPressed();

    void displayMenuOptions();
    void displayMenuInitGraph();
    void displayMenuSaveOptions();
    void initGraphFromTsp();
    void initGraphFromTxt();
    void initGraphFromJson();
    void displayGraphOrder();
    void displayGraphSize();
    void displayVertexNeighbors();
    void displayDfsPath();
    void displayDfsForest();
    void displayVertexDegree();
    void isArticulation();
    void isBridge();
    void graphInfo();
    void displayTSPSolve();
    void displayMetrics();
    void displayMenuContructiveAlgorithms();
    void displayMenuImprovementAlgorithms();
    void applyClosestNeighbor();
    void applySavings();
    void apply2Opt();
    void apply3Opt();
    void generateJson();
    void generateTxt();
    void exit();

    public:
    void run();
};

void App::initGraphFromTsp() {
    cout << "Nome do arquivo: ";
    string filename;
    getline(cin, filename);
    vector<Graph::Edge> edge_list = leitura::read_tsplib_format("data/tsplib/" + filename);
    int n  = leitura::get_length_from_tsp_format("data/tsplib/" + filename);

    graph = Graph(edge_list, n);
    status = true;
}

void App::initGraphFromTxt() {
    cout << "Nome do Arquivo: ";
    string filename;
    getline(cin, filename);
    int n = leitura::get_length_txt("data/txt/" + filename);
    vector<Graph::Edge> edgeList = leitura::read_txt("data/txt/" + filename);

    graph = Graph(edgeList, n);
    status = true;
}

void App::initGraphFromJson() {
    cout << "Nome do arquivo: ";
    string filename;
    cin >> filename;

    vector<Graph::Edge> edgeList = leitura::read_json("data/json/" + filename);
    int n = leitura::get_length_json("data/json/" + filename);

    graph = Graph(edgeList, n);
    status = true;
}

void App::displayGraphOrder() {
    cout << endl << "A ordem do grafo eh: " << graph.order() << endl << endl;
}

void App::displayGraphSize() {
    cout << endl << "O tamanho do grafo eh: " << graph.size() << endl << endl;
}

void App::displayVertexNeighbors() {
    cout << "Mostrar vizinhos de qual vertice? ";
    int vertex;
    cin >> vertex;

    for(int neigh : graph.neighbors(vertex)) {
        cout << vertex << " conecta ao vertice " << neigh << endl;
    }
    cout << endl;
}

void App::displayDfsPath() {
    cout << "DFS a partir de qual vertice? ";
    int vertex;
    cin >> vertex;
    vector<int> dfs = graph.dfs(vertex);
    cout << endl << "O tamanho do caminho eh " << dfs.size() << endl;
    cout << dfs[0];
    for(int i=1; i<dfs.size(); i++) cout << " " << dfs[i];
    cout << endl << endl;
}

void App::displayDfsForest() {
    vector<vector<int>> forest = graph.connectedComponents();
    cout << endl << "Existem " << forest.size() << " componentes conexas no grafo" << endl << endl;
    for(int i=0; i<forest.size(); i++) {
        cout << "Componente #" << i+1 << " tem tamanho " << forest[i].size() << endl;
        cout << forest[i][0];
        for(int j=1; j<forest[i].size(); j++) cout << " " << forest[i][j];
        cout << endl << endl;
    }
}

void App::displayVertexDegree() {
    int vertex;
    cout << "Determinar grau de qual vertice? ";
    cin >> vertex;
    cout << endl << "O grau do vertice eh: " << graph.degree(vertex) << endl << endl;
}

void App::isArticulation() {
    int vertex;
    cout << "Vertice a ser analisado: ";
    cin >> vertex;
    if(graph.articulation(vertex)) cout << endl << "O vertice eh articulacao!" << endl << endl;
    else                           cout << endl << "O vertice nao eh articulacao!" << endl << endl;
}

void App::isBridge() {
    int to, from;
    cout << "Aresta a ser analisada: (from, to) ";
    cin >> from >> to;
    Graph::Edge edge(from, to);
    if(graph.bridge(edge)) cout << endl << "A aresta eh ponte!" << endl << endl;
    else                   cout << endl << "A aresta nao eh ponte!" << endl << endl;
}

void App::graphInfo() {
    cout << "Arquivo de saida: ";
    string filename;
    cin >> filename;
    ofstream file("data/info/" + filename);

    cout << "Ordem do grafo: " << graph.order() << endl;
    file << "Tamanho do grafo: " << graph.size() << endl;
    file << "Numero de componentes conexas: " << graph.connectedComponents().size() << endl;
}

void App::applyClosestNeighbor() {
    cout << "Vertice de inicio: ";
    int vertex;
    cin >> vertex;

    vector<int> order = graph.closestNeighborHeuristic(vertex);

    cout << "Arquivo de saida: ";
    string filename;
    cin >> filename;

    leitura::hamiltonian_cycle_to_txt(order, "data/tsplib/execucao/" + filename);
}

void App::applySavings() {
    cout << "Vertice de inicio: ";
    int vertex;
    cin >> vertex;

    vector<int> order = graph.savingsHeuristic(vertex);

    cout << "Arquivo de saida: ";
    string filename;
    cin >> filename;

    leitura::hamiltonian_cycle_to_txt(order, "data/tsplib/execucao/" + filename);
}

void App::apply2Opt() {
    cout << "Arquivo de entrada do caminho hamiltoniano inicial: ";
    string filename;
    cin >> filename;

    vector<int> order = leitura::get_hamiltonian_cycle_from_txt("data/tsplib/execucao/" + filename);

    Timer max_time(0, 1, 0);
    Timer t;
    int cntIterations = -1;
    t.start();
    while(t <= max_time and cntIterations <= 10) {
        bool status = graph.alg2opt(order);
        if(!status) {
            cntIterations++;
        } else {
            cntIterations = 0;
        }
    }
    t.stop();

    cout << "Arquivo de saida: ";
    cin >> filename;

    leitura::order_graph_to_txt(order, graph, "data/tsplib/execucao/" + filename);
}

void App::apply3Opt() {
    cout << "Arquivo de entrada do caminho hamiltoniano inicial: ";
    string filename;
    cin >> filename;

    vector<int> order = leitura::get_hamiltonian_cycle_from_txt("data/tsplib/execucao/" + filename);

    Timer max_time(0, 1, 0);
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

    cout << "Arquivo de saida: ";
    cin >> filename;

    leitura::order_graph_to_txt(order, graph, "data/tsplib/execucao/" + filename);
}

void App::generateJson() {
    cout << "Arquivo de saida: ";
    string filename;
    cin >> filename;
    leitura::edge_list_to_json(graph.toEdgeList(), graph.order(), "data/json/" + filename);
}

void App::generateTxt() {
    cout << "Arquivo de saida: ";
    string filename;
    cin >> filename;
    leitura::edge_list_to_txt(graph.toEdgeList(), graph.order(), "data/txt/" + filename);
}

void App::displayTSPSolve() {
    cout << "Digite a instancia:" << endl;
    cout << "1 - berlin52" << endl;
    cout << "2 - CH130" << endl;
    cout << "3 - D198" << endl;
    cout << ": ";
    
    int instancia;
    cin >> instancia;

    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif

    cout << "Digite o metodo" << endl;
    cout << "1 - Nearest Neighbour + 2Opt" << endl;
    cout << "2 - Savings + 2Opt" << endl;
    cout << ": ";
    
    int metodo;
    cin >> metodo;
    
    TSP tsp(graph);
    tsp.run(metodo, instancia);
}

void App::displayMetrics() {
    int option = -1;
    string path;
    string f;

    while(option != 0) {
        #ifdef _WIN32
            system("cls");
        #elif __linux__
            system("clear");
        #endif
        cout << "Digite o metodo" << endl;
        cout << "1 - Pior Caso" << endl;
        cout << "2 - Melhor Caso" << endl;
        cout << "3 - Média" << endl;
        cout << "4 - Desvio Padrão" << endl;
        cout << "0 - Sair" << endl;
        cout << ": ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Digite o diretório onde estão localizados os arquivos dos ciclos hamiltonianos gerados: ";
                cin >> path;

                f = metrics::worst_case(path);

                cout << "Pior Caso: " << f << " - " << metrics::sum(leitura::read_txt(path+"/"+f)) << endl;

                break;

            case 2:
                cout << "Digite o diretório onde estão localizados os arquivos dos ciclos hamiltonianos gerados: ";
                cin >> path;

                f = metrics::best_case(path);

                cout << "Melhor Caso: " << f << " - " << metrics::sum(leitura::read_txt(path+"/"+f)) << endl;
                break;

            case 3:
                cout << "Digite o diretório onde estão localizados os arquivos dos ciclos hamiltonianos gerados: ";
                cin >> path;

                cout << "Média: " << metrics::mean(path) << endl;
                break;

            case 4:
                cout << "Digite o diretório onde estão localizados os arquivos dos ciclos hamiltonianos gerados: ";
                cin >> path;

                cout << "Desvio Padrão: " << metrics::standard_deviation(path) << endl;
                break;

            case 0:
                exit();
                return;
                break;

            default:
                break;
        }

        waitForKeyPressed();
    }
}

void App::displayMenuContructiveAlgorithms() {
    cout << "Escolha o algotitmo construtivo:" << endl;
    cout << "1 - Vizinho mais proximo" << endl;
    cout << "2 - Algoritmo de economia" << endl;
    cout << ": ";
    int option;
    cin >> option;

    switch(option) {
        case 1:
            applyClosestNeighbor();
            break;

        case 2:
            applySavings();
            break;

        default:
            break;
    }
}

void App::displayMenuImprovementAlgorithms() {
    cout << "Escolha o algotitmo de melhoria:" << endl;
    cout << "1 - 2 OPT" << endl;
    cout << "2 - 3 OPT" << endl;
    cout << ": ";
    int option;
    cin >> option;
    switch(option) {
        case 1:
            apply2Opt();
            break;

        case 2:
            apply3Opt();
            break;

        default:
            break;
    }
}

void App::waitForKeyPressed() {
    cout << "Aperte ENTER para continuar...";
    #ifdef _WIN32
        fflush(stdin);
    #elif __linux__
        __fpurge(stdin);
    #endif
    getchar();
}

/* 
    Para o teste da biblioteca faça um programa principal que leia o arquivo texto e salve em um arquivo texto as diversas informações sobre o grafo lido.
*/
void App::displayMenuOptions() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
    cout << "Menu:" << endl;
    cout << "1 - Inicializar Grafo" << endl;
    cout << "2 - Metricas" << endl;
    if(status) {
        cout << "3 - Ordem do Grafo" << endl;
        cout << "4 - Tamanho do Grafo" << endl;
        cout << "5 - Vizinhos de um vertice" << endl;
        cout << "6 - Grau de um vertice" << endl;
        cout << "7 - Busca em profundidade" << endl;
        cout << "8 - Floresta de profundidade" << endl;
        cout << "9 - Verificar se vertice eh articulacao" << endl;
        cout << "10 - Verificar se aresta eh ponte" << endl;
        cout << "11 - Execucao automatica" << endl;
        cout << "12 - Aplicar heuristica construtiva" << endl;
        cout << "13 - Aplicar heuristica de melhoria" << endl;
        cout << "14 - TSP Solver" << endl;
        cout << "15 - Salvar" << endl;
    }
    cout << "0 - Sair" << endl;
    cout << ": ";
}

void App::displayMenuInitGraph() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
    cout << "Inicializar com" << endl;
    cout << "1 - Json" << endl;
    cout << "2 - Txt" << endl;
    cout << "3 - TSP" <<  endl;
    cout << ": ";
    int option;
    cin >> option;
    cin.ignore();
    switch (option)
    {
    case 1:
        initGraphFromJson();
        break;

    case 2:
        initGraphFromTxt();
        break;
    
    case 3: 
        initGraphFromTsp();
        break;

    default:
        break;
    }
}

void App::displayMenuSaveOptions() {
    system("cls");
    cout << "Salvar como" << endl;
    cout << "1 - Json" << endl;
    cout << "2 - Txt" << endl;
    cout << ": ";
    int option;
    cin >> option;
    switch (option)
    {
    case 1:
        generateJson();
        break;

    case 2:
        generateTxt();
        break;
    
    default:
        break;
    }
}

void App::exit() {
    cout << endl << "Sair" << endl << endl;
}


void App::run() {
    int option = -1;
    while(option != 0) {
        displayMenuOptions();
        cin >> option;
        cin.ignore();

        switch (option)
        {
        case 1:
            displayMenuInitGraph();
            break;

        case 2:
            displayMetrics();
            break;

        case 3:
            displayGraphOrder();
            break;

        case 4:
            displayGraphSize();
            break;

        case 5:
            displayVertexNeighbors();
            break;

        case 6:
            displayVertexDegree();
            break;

        case 7:
            displayDfsPath();
            break;

        case 8:
            displayDfsForest();
            break;

        case 9:
            isArticulation();
            break;

        case 10:
            isBridge();
            break;

        case 11:
            graphInfo();
            break;

        case 12:
            displayMenuContructiveAlgorithms();
            break;
        
        case 13:
            displayMenuImprovementAlgorithms();
            break;

        case 14:
            displayTSPSolve();
            break;
        
       
        case 15:
            displayMenuSaveOptions();
            break;

        case 0:
            exit();
            return;
            break;

        default:
            break;
        }

        waitForKeyPressed();
    }
}

#endif
