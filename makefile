all: ./src/json.hpp ./src/graph.hpp ./src/tsp.hpp ./src/app.hpp ./src/timer.hpp ./src/main.cpp
	g++ ./src/json.hpp ./src/leitura.hpp ./src/graph.hpp ./src/tsp.hpp ./src/app.hpp ./src/timer.hpp ./src/main.cpp -std=c++17 -o main