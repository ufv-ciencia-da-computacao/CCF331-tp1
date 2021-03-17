#ifndef APP_HPP
#define APP_HPP

#include "graph.hpp"
#include "leitura.hpp"

class App {
    private:
    Graph graph;
    bool status;
    
    void waitForKeyPressed();
    void displayMenuOptions();

    void initGraphFromTxt();
    void displayGraphOrder();
    void displayGraphSize();
    
    void displayVertexDegree();


    void isArticulation();
    void isBridge();

    public:
    void run();
};

void App::waitForKeyPressed() {
    cout << "Aperte ENTER para continuar...";
    fflush(stdin);
    getchar();
}

void App::displayMenuOptions() {
    cout << endl;
    cout << "Menu:" << endl;
    cout << "1 - Inicializar Grafo" << endl;
    cout << "2 - Ordem do Grafo" << endl;
    cout << "3 - Tamanho do Grafo" << endl;
    cout << "4 - Vizinhos de um vertice" << endl;
    cout << "5 - Grau de um vertice" << endl;
    cout << "6 - Busca em profundidade" << endl;
    cout << "7 - Numero e vertices de componentes conexas" << endl;
    cout << "8 - Verificar se vertice eh articulacao" << endl;
    cout << "9 - Verificar se aresta eh ponte" << endl;
    cout << "10 - Execucao automatica" << endl; //Para o teste da biblioteca faça um programa principal que leia o arquivo texto e salve em um arquivo texto as diversas informações sobre o grafo lido.
    cout << "0 - Sair" << endl;
    cout << ": ";
}

void App::initGraphFromTxt() {

}

void App::displayGraphOrder() {
    cout << endl << "A ordem do grafo eh: " << graph.order() << endl << endl;
}

void App::displayGraphSize() {
    cout << endl << "O tamanho do grafo eh: " << graph.size() << endl << endl;
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

void App::run() {
    int option = -1;
    while(option != 0) {
        displayMenuOptions();
        cin >> option;

        switch (option)
        {
        case 1:
            initGraphFromTxt();
            break;

        case 2:
            displayGraphOrder();
            break;
        
        case 3:
            displayGraphSize();
            break;
        
        case 4:
            break;
        
        case 5:
            displayVertexDegree();
            break;
        
        case 6:
            break;
        
        case 7:
            break;
        
        case 8:
            isArticulation();
            break;
        
        case 9:
            isBridge();
            break;
        
        case 10:
            break;
        
        case 0:
            cout << endl << "Sair" << endl << endl;
            break;
        
        default:
            break;
        }
        //waitForKeyPressed();
    }
}

#endif