#include "Euler.hpp"

#define NOEDGE -1;

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
    if(u == v || u < 0 || v < 0 || u > n || v > n){
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

int Euler::getEdge(int u, int v)
{
    u--;
    v--;
    return mat[u][v];
}

int Euler::getAnyEdge(vector<vector<int>>& m, int u){
    for(size_t i=0;i < m.size(); i++){
        if(m[u][i] > 0){
            return i;
        }
    }
    return NOEDGE;
}

// check if the graph contain an euler circle
void Euler::eulerCircuit()
{
    cout << "The number of edges in the graph is: " << m << endl;
    if(!inOutEqual())
    {
        cout << "The graph does not contain an euler circle" << endl;
        return;
    }
    if(!oneBigSCC())
    {
        cout << "The graph does not contain an euler circle" << endl;
        cout << "There is no single strongly connected component" << endl;
        return;
    }
    cout << "The graph contain an euler circle:" << endl;
    findCircle();
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
            cout << "In-degree("<<in<<") and out-degree("<<out<<") of " << i << " are different" << endl;
            return false;
        }
    }
    return true;
}

// finding all vertices reachable from v
void Euler::fillOrder(const vector<vector<int>>& matrix, int v, vector<bool>& visited, list<int>& lst) {
    visited[v] = true;
    for (size_t i = 0; i < matrix[v].size(); i++) {
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
int Euler::DFS(const std::vector<std::vector<int>>& matrix,int v,vector<bool>& visited) {
    visited[v] = true;
    int count = 1;
    for (size_t i = 0; i < matrix[v].size(); i++){
        if (matrix[v][i] != 0 && !visited[i]) {
            count += DFS(matrix, i, visited);
        }
    }
    return count;
}

bool Euler::oneBigSCC(){
    n = mat.size();
    list<int> lst;                                           // an empty list
    vector<bool> visited(n, false);                          // array of visited with falses
    
    fillOrder(mat, 0, visited, lst);                      // DFS to fill the list with vertices reachable from it
    for (int i = 0; i < n; i++) {                            // for each vertex
        if (!visited[i]) {                                   // if it wasn't visited - False
            return false; 
        }
    }
    vector<vector<int>> transpose = getTranspose(mat,n);  // flip the edges direction (rows are columns respectively)

    for (int i = 0; i < n; i++) { visited[i] = false; }      // set each vertex to not visited again

    int v = lst.back();                                  // take the last inserted vertex
    int scc_size = DFS(transpose,v,visited);
    return scc_size==n;
}

void Euler::findCircle() {
    std::vector<std::vector<int>> copy = this->mat; // Copy of the adjacency matrix
    list<int> lst;                 // Final merged Eulerian cycle
    int start = 0;                 // Choose  starting vertex
    lst.push_back(start);          // Start the cycle from the chosen vertex
    while (true) {
        auto it = lst.begin();     // Find a vertex in the current cycle that has unused edges         
        bool foundUnusedEdge = false;
        for(; it != lst.end(); ++it) {
            if(getAnyEdge(copy,*it) != -1){  // If there's an unused edge from this vertex
                foundUnusedEdge = true;
                break;
            }
        }
        if(!foundUnusedEdge){ break; }  // No unused edges, we're done

        int v = *it;                    // Start from the vertex with edges
        list<int> newCycle;             // To hold the new cycle
        newCycle.push_back(v);          // Start the new cycle
        int u = getAnyEdge(copy, v);    // Find an edge from v
        while (u != -1) {
            copy[v][u] = 0;            // Remove the edge from the copy graph
            newCycle.push_back(u);     // Add the vertex to the new cycle
            v = u;                     // Move to the next vertex
            u = getAnyEdge(copy, v);   // Get the next edge
        }
        lst.insert(++it, ++newCycle.begin(), newCycle.end()); // Insert new cycle to main cycle at position 'it'
    }

    // Print Eulerian cycle
    for(const auto& vertex : lst) { cout<<vertex<<" "; }
    cout << endl;
}
