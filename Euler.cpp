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
    if(u == v || u < 0 || v < 0 || u >= n || v >= n){
        cout << "Invalid edge" << endl;
        return;
    }
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
    if(!inOutEqual())
    {
        cout << "The graph does not contain an euler circle" << endl;
        return;
    }
    if(!nonZeroDegreeOneSCC())
    {
        cout << "The graph does not contain an euler circle" << endl;
        return;
    }
    cout << "The graph contain an euler circle" << endl;
}

bool Euler::inOutEqual()
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        int in = 0, out = 0;
        for (size_t j = 0; j < mat[0].size(); j++)
        {
            in += mat[j][i];
            out += mat[i][j];
        }
        if (in != out)
        {
            return false;
        }
    }
    return true;
}

// finding all vertices reachable from v
void Euler::fillOrder(const vector<vector<int>>& matrix, int v, vector<bool>& visited, list<int>& lst) {
    visited[v] = true;
    for (int i = 0; i < matrix[v].size(); i++) {
        if (matrix[v][i] != 0 && !visited[i]) {
            fillOrder(matrix, i, visited, lst);
        }
    }
    lst.push_back(v);
}

// all edges are reversed
vector<vector<int>> Euler::getTranspose(const vector<vector<int>>& matrix, int n) {
    vector<vector<int>> transpose(n, vector<int>(n, 0));
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++){
            if (matrix[j][i] != 0) {
                transpose[i][j] = 1;
            }
        }
    }
    return transpose;
}

// DFS until all vertices cannot be visited
size_t Euler::DFS(const vector<vector<int>>& matrix, int v, vector<bool>& visited) {
    visited[v] = true;
    size_t count = 1;
    for (int i = 0; i < matrix[v].size(); i++){
        if (matrix[v][i] != 0 && !visited[i]) {
            count += DFS(matrix, i, visited);
        }
    }
    return count;
}

bool Euler::kosaraju(const vector<vector<int>>& matrix, int n) {
    list<int> lst;                                                 // an empty list
    vector<bool> visited(n, false);                                // array of visited with falses

    for (int i = 0; i < n; i++) {                                       // for each vertex
        if (!visited[i]) {                                              // if it wasn't visited 
            fillOrder(matrix, i, visited, lst);                         // DFS to fill the list with vertices reachable from it
        }
    }
    vector<vector<int>> transpose = getTranspose(matrix, n);  // flip the edges direction (rows are columns respectively)

    for (int i = 0; i < n; i++) { visited[i] = false; }                 // set each vertex to not visited again

    bool flag = false;
    while (!lst.empty()) {                                              // while the list has vertices
        int v = lst.back();                                             // take the last inserted vertex
        lst.pop_back();                                                 // remove it from the list
        if (!visited[v]) {                                              // if it wasn't visited
            if(DFS(transpose, v, visited) > 1) {                        // if there are more than one vertex reachable from v
                if(flag) {                                              // if there was already a strongly connected component
                    return false;                                       // return false
                }
                flag = true;                                            // set the flag to true
            }
        }
    }
    return true;
}

bool Euler::nonZeroDegreeOneSCC()
{
    return kosaraju(mat, mat.size());
}