#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
enum
{
    valid = 1,
    invalid = 0
};

class Euler
{
    std::vector<std::vector<int>> mat;
    int n, m;

public:
    Euler() : n(0), m(0) {}

    Euler(int n, int m): n(n), m(m)
    {
        if(checkValid(n, m) == invalid){
            cout << "Invalid input" << endl;
            this->n = 0;
            this->m = 0;
            return;
        }
        mat.resize(n, std::vector<int>(n, 0));
    }

    // n is the number of vertices and m is the number of edges
    int checkValid(int n, int m)
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

    void printMat()
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

    void newEdge(int u, int v)
    {
        u--;
        v--;
        mat[u][v] = 1;
        this->m++;
        cout << "Successfuly added the edge" << endl;
    }

    void removeEdge(int u, int v)
    {
        u--;
        v--;
        mat[u][v] = 0;
        this->m--;
        cout << "Successfuly removed the edge" << endl;
    }

    // check if the graph contain an euler circle
    void eulerCircuit(){
        
    }
};
