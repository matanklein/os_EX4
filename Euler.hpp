#include <vector>
#include <iostream>
#include <string>
#include <fstream>

class Euler
{

private:
    std::vector<std::vector<int>> mat;
    int n, m;

    int checkValid(int n, int m);

public:

    Euler() : n(0), m(0) {}

    Euler(int n, int m);

    void printMat();

    void newEdge(int u, int v);

    void removeEdge(int u, int v);

    /**
     * @brief This function will check if the graph has an euler circle or not
     */
    void eulerCircuit(){
        
    }
};