#include "Euler.hpp"

using namespace std;
enum
{
    valid = 1,
    invalid = 0
};

Euler::Euler(int n, int m) : n(n), m(m)
{
    if (Euler::checkValid(n, m) == invalid)
    {
        cout << "Invalid input" << endl;
        this->n = 0;
        this->m = 0;
        return;
    }
    mat.resize(n, std::vector<int>(n, 0));
}

// n is the number of vertices and m is the number of edges
int Euler::checkValid(int n, int m)
{
    if (n <= 0 || m < 0)
    { // should be atleast 1 vertex and non-negative amount of edges
        return invalid;
    }

    if (m > n * (n - 1))
    { // m should be less than n*(n-1)
        return invalid;
    }

    return valid;
}

void Euler::printMat()
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat[0].size() - 1; j++)
        {
            cout << mat[i][j] << " |";
        }
        cout << mat[i][mat[0].size() - 1] << endl;
    }
}

void Euler::newEdge(int u, int v)
{
    u--;
    v--;
    mat[u][v] = 1;
    this->m++;
    cout << "Successfuly added the edge" << endl;
}

void Euler::removeEdge(int u, int v)
{
    u--;
    v--;
    mat[u][v] = 0;
    this->m--;
    cout << "Successfuly removed the edge" << endl;
}

// check if the graph contain an euler circle
void Euler::eulerCircuit()
{
}
