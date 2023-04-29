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

    vector<vector<bool>> adjMatrix;

public:

    // The constructor to build Graph

    Graph(string path) {
        string temp;
        fstream file(path, fstream::in);
        if (file.is_open()) {
            int i = 0;
            bool start = true;
            while (file >> temp) {
                if (temp == "|" && start == true) {
                    adjMatrix.resize(i + 1);
                    start = false;
                }
                else if (temp == "|" && start == false) {
                    start = true;
                    i++;
                }
                else {
                    if (temp == "1") adjMatrix[i].push_back(true);
                    else adjMatrix[i].push_back(false);
                }
            }
            file.close();
        }
        else cout << "Can't open [" << path << "]" << endl;
    }

    // The function to show our Graph (adjacency list)

    void printGraph() {
        for (int i = 0; i < adjMatrix.size(); i++) {
            if (i == 0) cout << "\t" << i << "\t";
            else cout << i << "\t";
        }
        cout << endl;
        for (int i = 0; i < adjMatrix.size(); i++) {
            cout << i << "\t";
            for (int v : adjMatrix[i]) {
                cout << v << "\t";
            }
            cout << endl;
        }
    }

    // The function to move along the Graph and to mark visited vertices

    void DFS(int i, vector<bool>& visited) {
        visited[i] = true;
        for (int j = 0; j < adjMatrix[i].size();j++) {
            if (adjMatrix[i][j] == true) {
                if (!visited[j]) {
                    DFS(j, visited);
                }
            }
        }
    }

    // The function to check: Is this Graph is strongly connected?

    bool isStronglyConnected() {
        for (int i = 0; i < adjMatrix.size(); i++) {
            vector<bool> visited(adjMatrix.size());
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

// The main function

int main() {
    string path = "Graph5.txt";
    Graph graph(path);
    graph.printGraph();
    if (graph.isStronglyConnected()) {
        cout << "\nThe graph is strongly connected";
    }
    else {
        cout << "\nThe graph is not strongly connected";
    }
    return 0;
}