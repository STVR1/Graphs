#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

// The class to build adjency list for our Graph

class Graph {
private:

    vector<vector<int>> adjList;

public:

    // The constuctor to build Graph

    Graph(vector<vector<int>> const& edges, int n) {
        adjList.resize(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < edges.size(); j++) {
                if (i == edges[j][0]) {
                    for (int k = 1; k < 2; k++) adjList[i].push_back(edges[j][k]);
                }
            }
        }
    }

    // The function to show our Graph (adjacency list)

    void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (int v : adjList[i]) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // The function to move along the Graph and to mark visited vertices

    void DFS(int i, vector<bool>& visited) {
        visited[i] = true;
        for (int u : adjList[i]) {
            if (!visited[u]) {
                DFS(u, visited);
            }
        }
    }

    // The function to check: Is this Graph is strongly connected?

    bool isStronglyConnected() {
        for (int i = 0; i < adjList.size(); i++) {
            vector<bool> visited(adjList.size());
            DFS(i, visited);
            if (find(visited.begin(), visited.end(), false) != visited.end()) {
                return false;
            }
        }
        return true;
    }

};

// The function to check the path to file

string check() {
    string pathcheck;
    regex checking("^([A-Za-z0-9[:space:]]+[:]{1}){1}(([\\\\]{1}[A-Za-z0-9[:space:]]+)*([\\\\]{1}[A-Za-z0-9[:space:]]+(.txt){1}){1}){1}$");
    do {
        cout << "Input the path for txt file\n";
        getline(cin, pathcheck);
    } while (!regex_match(pathcheck, checking));
    return pathcheck;
}

// The function to read all edges of Graph from file

int reading(vector<vector<int>>& edges) {
    fstream file;
    string path=check(), temp;
    int size = 0, n = 0;
    file.open(path, fstream::in);
    if (file.is_open()) {
        while (getline(file, temp)) size++;
        file.close();
        if (size == 0) {
            cout << "Your file is empty" << endl;
            return 0;
        }
        edges.resize(size);
        for (int i = 0; i < size; i++) {
            edges[i].resize(2);
        }
        file.open(path);
        for (int i = 0; i < size; i++) {
            file >> edges[i][0] >> temp >> edges[i][1];
            if (n < edges[i][0] || n < edges[i][1]) {
                if (edges[i][0] < edges[i][1]) n = edges[i][1];
                else n = edges[i][0];
            }
        }
        file.close();
    }
    else {
        cout << "Error. Can't open it\n";
        return 0;
    }
    return n+1;
}

// The main function

int main() {
    vector<vector<int>> edges;
    int n = reading(edges);
    if (n>0) { 
        Graph graph(edges, n);
        graph.printGraph();
        if (graph.isStronglyConnected()) {
            cout << "\nThe graph is strongly connected";
        }
        else {
            cout << "\nThe graph is not strongly connected";
        }
    }
    return 0;
}