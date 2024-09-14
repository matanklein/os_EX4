#include "Euler.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    int opt;
    if (argc == 1){
        cerr << "Not enough arguments!" << endl;
        cout << "Usage: ./main -v <number of vertices> -e <number of edges> -s <seed>" << endl;
        return -1;
    }

    size_t n, m, seed;
    std::mt19937 gen;
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1)
    {
        switch (opt)
        {
        case 'e':
            m = atoi(optarg);
            break;
        case 'v':
            n = atoi(optarg);
            break;
        case 's':
            seed = atoi(optarg);
            gen.seed(seed);
            break;
        case '?':
            std::cerr << "Unknown option: -" << char(optopt) << std::endl;
            return -1;
        }
    }

    if(m > n*(n-1)){
        cerr << "Too many edges!" << endl;
        return -1;
    }
    if(m < 0 || n <= 0){
        cerr << "Invalid input!" << endl;
        return -1;
    }

    // create a graph with n vertices and m edges
    Euler graph(n, 0);

    std::uniform_int_distribution<size_t> distrib(1, n);

    // set the counter to count the number of edges added
    size_t counter = 0;

    while (counter < m){ // while the number of edges added is less than m
        size_t i = distrib(gen);
        size_t j = distrib(gen);
        if (i==j || graph.getEdge(i,j)==1){ continue; } // no self loops or multiple edges
        graph.newEdge(i, j);
        counter++;
    }
    graph.printMat();
    graph.eulerCircuit();

    return 0;
}