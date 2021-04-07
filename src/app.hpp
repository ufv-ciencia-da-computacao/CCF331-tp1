#ifndef APP_HPP
#define APP_HPP

#include "graph.hpp"
#include "leitura.hpp"

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
    void generateJson();
    void generateTxt();
    void exit();

    public:
    void run();
};

void App::waitForKeyPressed() {
    cout << "Aperte ENTER para continuar...";
    fflush(stdin);
    getchar();
}

/* 
    Para o teste da biblioteca faça um programa principal que leia o arquivo texto e salve em um arquivo texto as diversas informações sobre o grafo lido.
*/
void App::displayMenuOptions() {
    system("cls");
    cout << "Menu:" << endl;
    cout << "1 - Inicializar Grafo" << endl;
    if(status) {
        cout << "2 - Ordem do Grafo" << endl;
        cout << "3 - Tamanho do Grafo" << endl;
        cout << "4 - Vizinhos de um vertice" << endl;
        cout << "5 - Grau de um vertice" << endl;
        cout << "6 - Busca em profundidade" << endl;
        cout << "7 - Floresta de profundidade" << endl;
        cout << "8 - Verificar se vertice eh articulacao" << endl;
        cout << "9 - Verificar se aresta eh ponte" << endl;
        cout << "10 - Execucao automatica" << endl; 
        cout << "11 - Salvar" << endl;
    }
    cout << "0 - Sair" << endl;
    cout << ": ";
}

void App::displayMenuInitGraph() {
    system("cls");
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

    file << "Ordem do grafo: " << graph.order() << endl;
    file << "Tamanho do grafo: " << graph.size() << endl;
    file << "Numero de componentes conexas: " << graph.connectedComponents().size() << endl;
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
            displayGraphOrder();
            break;

        case 3:
            displayGraphSize();
            break;

        case 4:
            displayVertexNeighbors();
            break;

        case 5:
            displayVertexDegree();
            break;

        case 6:
            displayDfsPath();
            break;

        case 7:
            displayDfsForest();
            break;

        case 8:
            isArticulation();
            break;

        case 9:
            isBridge();
            break;

        case 10:
            graphInfo();
            break;

        case 11:
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
