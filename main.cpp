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
    if (argc == 1)
    {
        cerr << "Not enough arguments!" << endl;
        cout << "Usage: ./main -v <number of vertices> -e <number of edges> -s <seed>" << endl;
        return -1;
    }

    size_t n, m, seed;
    std::mt19937 gen;
    while ((opt = getopt(argc, argv, "v:e:")) != -1)
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

    Euler graph(n, m);

    std::uniform_int_distribution<> distrib(0, 1);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(distrib(gen) == 1)
            {
                graph.newEdge(i, j);
            }
        }
    }

    graph.printMat();

    graph.eulerCircuit();

    return 0;
}