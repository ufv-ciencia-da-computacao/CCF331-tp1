#ifndef METRICS_HPP
#define METRICS_HPP

#include "leitura.hpp"
#include "graph.hpp"
#include <dirent.h>

namespace metrics {

vector<string> get_files(string path) {
    DIR *dir; 
    struct dirent *diread;
    vector<string> files;

    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            string str = diread->d_name;
            if (str.find("tsp") != string::npos) files.push_back(str);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return files;
    }

    return files;
}

int sum(vector<Graph::Edge> edge_list) {
    int sum = 0;
    for (auto &&i : edge_list) {
        sum+=i.weight;
    }
    return sum;
}

string worst_case(string path) {
    string file_worst;
    int worst_case = INT32_MIN;
    vector<string> files = get_files(path);

    for (auto &&f: files) {
        vector<Graph::Edge> edge_list = leitura::read_txt(path+"/"+f);
        int sum_case = sum(edge_list);
        if (worst_case < sum_case) {
            worst_case = sum_case;
            file_worst = f;
        }
    }

    return file_worst; 
}

string best_case(string path) {
    string file_best;
    int best_case = INT32_MAX;
    vector<string> files = get_files(path);

    for (auto &&f: files) {
        vector<Graph::Edge> edge_list = leitura::read_txt(path+"/"+f);
        int sum_case = sum(edge_list);
        if (best_case > sum_case) {
            best_case = sum_case;
            file_best = f;
        }
    }

    return file_best;  
}

double mean(string path) {
    double mean = 0;
    vector<string> files = get_files(path);
    for (auto &&f: files) {
        vector<Graph::Edge> edge_list = leitura::read_txt(path+"/"+f);
        mean += (double) sum(edge_list);
    }
    return mean/files.size();
}

double standard_deviation(string path) {
    double m = mean(path);
    vector<string> files = get_files(path);
    double sd = 0;
    for (auto &&f: files) {
        vector<Graph::Edge> edge_list = leitura::read_txt(path+"/"+f);
        sd += pow((sum(edge_list) - m), 2);
    }

    return sqrt(sd/files.size());  
}

}

#endif