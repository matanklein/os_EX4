#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <list>

class Euler
{

private:
    std::vector<std::vector<int>> mat;
    int n, m;

    int checkValid(int n, int m);

    bool inOutEqual();

    bool oneBigSCC();

    void fillOrder(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::list<int> &lst);

    std::vector<std::vector<int>> getTranspose(const std::vector<std::vector<int>> &matrix, int n);

    int DFS(const std::vector<std::vector<int>>& matrix, int v, std::vector<bool>& visited);

public:

    Euler() : n(0), m(0) {}

    Euler(int n, int m);

    void printMat();

    void newEdge(int u, int v);

    void removeEdge(int u, int v);

    int getEdge(int u, int v);

    int getAnyEdge(std::vector<std::vector<int>>& m, int u);

    /**
     * @brief This function will check if the graph has an euler circle or not.
     * For a directed graph to have an Eulerian circuit, it must satisfy two conditions:
     *  1. All vertices with nonzero degree belong to a single strongly connected component.
     *  2. In-degree and out-degree of every vertex are same.
     */
    void eulerCircuit();

    void findCircle();
};