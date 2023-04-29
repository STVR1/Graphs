#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include<fstream>

using namespace std;

// The class Graph to complete the mission

typedef vector<vector<int>> graph;

class Graph {

private:

	graph basic;        // The graph to store the basic graph

	graph example;      // The graph to store the graph-example

    graph compare;      // The graph to store the transposed graph-example

    vector<pair<vector<int>, vector<int>>> Result;  // The list of all extracted graphs

    // The graph to remove all repeated extracted graphs and write them into Result

    void remove_repeated(vector<pair<vector<int>, vector<int>>>& list) {
        int check = 0;
        for (int i = 0; i < list.size(); i++) {
            if (!Result.empty()) {
                for (int j = 0; j < Result.size(); j++) {
                    check = 0;
                    for (int k = 0; k < example[0].size(); k++) {
                        for (int p = 0; p < example[0].size(); p++) if (list[i].second[k] == Result[j].second[p]) check++;
                    }
                    if (check == example[0].size()) break;
                    if (j == Result.size() - 1) Result.push_back(make_pair(list[i].first, list[i].second));
                }
            }
            else Result.push_back(make_pair(list[i].first, list[i].second));
        }
    }

    // The method to compare our extracted graph with graph example

    bool comparison(graph& current, vector<int>& edges) {
        vector<bool> check;
        for (int i = 0; i < compare.size(); i++) {
            for (int j = 0; j < current.size(); j++) {
                if (compare[i] == current[j]) {
                    check.push_back(true);
                    edges.push_back(j);
                }
            }
        }
        if (check.size() == example[0].size()) return true;
        else return false;
    }

    // The method to create our possible graph to extract

    void creation(vector<int>& vertices, vector<pair<vector<int>, vector<int>>>& list) {
        graph current(basic[0].size());
        vector<int> edges;
        for (int j = 0; j < basic[0].size(); j++) {
            for (int i = 0; i < vertices.size(); i++) current[j].push_back(basic[vertices[i]][j]);
        }
        if (comparison(current, edges)) list.push_back(make_pair(vertices, edges));
    }
 
    // The method to select possible graph to extract 

    void selection() {
        if (!basic.empty() && !example.empty()) {
            vector<int> vertices;
            vector<pair<vector<int>, vector<int>>> list;
            int j = 0;
            for (int i = 0; i < basic.size(); i++) {
                vertices.push_back(i);
                for (int step = 0; step < basic.size(); step++) {
                    j = step;
                    while (vertices.size() < example.size() - 1) {
                        if (j != i) vertices.push_back(j);
                        j++;
                    }
                    while (j < basic.size()) {
                        if (j != i)vertices.push_back(j);

                        if (vertices.size() == example.size()) {
                            creation(vertices, list);

                            vertices.pop_back();
                        }
                        j++;
                    }
                    while (vertices.size() != 1) vertices.pop_back();
                }
                while (vertices.size() != 0) vertices.pop_back();
            }
            j = basic.size() - 1;
            for (int i = basic.size() - 1; 0 <= i; i--) {
                vertices.push_back(i);
                for (int step = basic.size() - 1; 0 <= step; step--) {
                    j = step;
                    while (vertices.size() < example.size() - 1) {
                        if (j != i) vertices.push_back(j);
                        j--;
                    }
                    while (j < basic.size()) {
                        if (j != i)vertices.push_back(j);

                        if (vertices.size() == example.size()) {
                            creation(vertices, list);

                            vertices.pop_back();
                        }
                        j--;
                    }
                    while (vertices.size() != 1) vertices.pop_back();
                }
                while (vertices.size() != 0) vertices.pop_back();
            }
            remove_repeated(list);
        }
    }

public:

    // The constructor to create graph basic and graph-example

    Graph(string path_basic, string path_example) {
        bool all = false;
        do{
            string temp;
            ifstream file;
            if (all == false) file.open(path_basic);
            else file.open(path_example);
            if (file.is_open()) {
                int i = 0;
                bool start = true;
                while (file >> temp) {
                    if (temp == "|" && start == true) {
                        if (all == false)basic.resize(i + 1);
                        else example.resize(i + 1);
                        start = false;
                    }
                    else if (temp == "|" && start == false) {
                        start = true;
                        i++;
                    }
                    else {
                        if (all == false)basic[i].push_back(stoi(temp));
                        else example[i].push_back(stoi(temp));
                    }
                }
                file.close();
            }
            else cout << "Can't open [" << path_basic << "]" << endl;
            if (all == false) all = true;
            else all = false;
        } while (all == true);
        compare.resize(example[0].size());
        for (int j = 0; j < example[0].size(); j++) {
            for (int i = 0; i < example.size(); i++) {
                compare[j].push_back(example[i][j]);
            }
        }
    }

    // The method to extract all possible graphs according to graph-example (for user)

    void extract() {
        selection();
    }

    // The method to print the basic graph

	void print_basic() {
        if (!basic.empty()) {
            cout << "*****Your Basic Matrix*****" << endl;
            for (int i = 0; i < basic[0].size(); i++) {
                if (i == 0) cout << "\t" << i + 1 << "\t";
                else cout << i + 1 << "\t";
            }
            cout << endl;
            for (int i = 0; i < basic.size(); i++) {
                cout << i << "\t";
                for (int v : basic[i]) {
                    cout << v << "\t";
                }
                cout << endl;
            }
        }
	}

    // The method to print the graph-example

    void print_example() {
        if (!example.empty()) {
            cout << "*****Your Example Matrix*****" << endl;
            for (int i = 0; i < example[0].size(); i++) {
                if (i == 0) cout << "\t" << i + 1 << "\t";
                else cout << i + 1 << "\t";
            }
            cout << endl;
            for (int i = 0; i < example.size(); i++) {
                cout << i << "\t";
                for (int v : example[i]) {
                    cout << v << "\t";
                }
                cout << endl;
            }
        }
    }

    // The method to print all extracted graphs (print vertices and edges)

    void list_extracted() {
        if (!Result.empty()) {
            for (int i = 0; i < Result.size(); i++) {
                cout << endl << "Vertices: ";
                for (int j = 0; j < example.size(); j++) cout << Result[i].first[j] << "\t";
                cout << endl << endl;
                cout << "Edges: ";
                for (int j = 0; j < example[0].size(); j++) cout << Result[i].second[j] + 1 << "\t";
                cout << endl;
            }
        }
        else cout << "Nothing found" << endl;
    }

};

// The function to check the inputed path

string path_check() {
    string path;
    regex check("^([A-Za-z0-9[:space:]]+[:]{1}){1}(([\\\\]{1}[A-Za-z0-9[:space:]]+)*([\\\\]{1}[A-Za-z0-9[:space:]]+(.txt){1}){1}){1}$");
    cout << "Input the path to the .txt file" << endl;
    getline(cin, path);
    while (!regex_match(path, check)) {
        cout << "Error. Input the correct path to the .txt file" << endl;
        getline(cin, path);
    }
    return path;
}

int main() {
    string first=path_check(), second = path_check();
    Graph test(first, second);
    test.print_basic();
    test.print_example();
    cout << endl;
    test.extract();
    test.list_extracted();
    return 0;
}