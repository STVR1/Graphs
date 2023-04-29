#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

class Graph {

private:

    vector<vector<int>> incedenceList;

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
                    incedenceList.resize(i + 1);
                    start = false;
                }
                else if (temp == "|" && start == false) {
                    start = true;
                    i++;
                }
                else incedenceList[i].push_back(stoi(temp));
            }
            file.close();
        }
        else cout << "Can't open [" << path << "]" << endl;
    }

    // The function to show our Graph (incedence list)

    void printGraph() {
        for (int i = 0; i < incedenceList.size(); i++) {
            for (int v : incedenceList[i]) {
                cout << v << "\t";
            }
            cout << endl;
        }
    }

    // The function to move along the Graph and to mark visited vertices

    void DFS(int i, vector<bool>& visited) {
        bool stop_cycle = false;
        int j = 0;
        visited[i] = true;
        for (int u : incedenceList[i]) {
            stop_cycle = false;
            if (u > 0) {
                for (j = 0; j < incedenceList.size(); j++) {
                    for (int k = 0; k < incedenceList[j].size(); k++) {
                        if (u == -incedenceList[j][k] && j != i) {
                            stop_cycle = true;
                            break;
                        }
                    }
                    if (stop_cycle == true) break;
                }
                if (j == incedenceList.size())j--;
                if (!visited[j]) {
                    DFS(j, visited);
                }
            }
        }
    }

    // The function to check: Is this Graph is strongly connected?

    bool isStronglyConnected() {
        for (int i = 0; i < incedenceList.size(); i++) {
            vector<bool> visited(incedenceList.size());
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

int main() {
    string path = check();
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