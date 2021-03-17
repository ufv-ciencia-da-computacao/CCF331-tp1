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
    void displayGraphOrder();
    void initGraphFromTxt();

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
    cout << ": ";
}

void App::displayGraphOrder() {
    cout << endl << "A ordem do grafo eh: " << graph.order() << endl << endl;
}

void App::initGraphFromTxt() {

}

void App::run() {
    while(1) {
        int option;
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
        
        default:
            break;
        }
        waitForKeyPressed();
    }
}

#endif