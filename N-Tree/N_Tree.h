#pragma once

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class N_Tree {

private:

	struct info {
		int key = 0;
		vector<int> vertex;
	};

	vector<info> edges;

	// The meaning of degree

	int degree = -1;

public:

	// The constuctor for our tree 

	N_Tree (string path, int degree) {
		this->degree = degree;
		if (degree != -1) {
			ifstream file(path);
			if (file.is_open()) {
				int num = 0, counter = 0, size = 1;
				while (file >> num) {
					int index = size - 1;
					if (counter == 0) {
						edges.resize(size);
						edges[index].key = num;
						counter++;
					}
					else {
						edges[index].vertex.push_back(num);
						counter++;
					}
					if (counter == degree + 1) {
						size++, counter = 0;
					}
				}
				file.close();
			}
			else cout << "Can't open [" << path << "]" << endl;
		}
		else cout << "Degree doesn't define" << endl;
	}

	// The constructor to create root firstly

	N_Tree(int num_1) {
		edges.resize(1);
		edges[0].key = num_1;
		this->degree = 0;
	}

	// The destructor 

	~N_Tree() {
	
	}

	// The function to set user's degree

	void set_degree(int degree) {
		this->degree = degree;
	}

	// The function to get a root 

	int get_root(int i) {
		return edges[i].key;
	}

	// The function to get a child 

	int get_child(int i, int j) {
		return edges[i].vertex[j];
	}

	// The function to return the size of tree 

	int size() {
		return edges.size();
	}
	
	// The function to return the amount of adjacent nodes

	int size_2(int i) {
		return edges[i].vertex.size();
	}

	// The function to check, if our tree is N-ary tree

	bool check_status() {
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].vertex.size() > degree) return false;
		}
		return true;
	}

	// The function to save our tree

	void save(string path) {
		ofstream file(path);
		if (file.is_open()) {
			for (int i = 0; i < edges.size(); i++) {
				file << edges[i].key << "\t";
				for (int j = 0; j < edges[i].vertex.size(); j++) file << edges[i].vertex[j] << "\t";
				file << endl;
			}
		}
		else cout << "Couldn't save [" << path << "]" << endl;
	}

	// The function to show N-ary tree

	void show() {
		if (edges.size() > 0) {
			if (check_status() == true)cout << "*****Your " << degree << "-ary tree*****" << endl;
			else cout << "This is not a " << degree << "-ary tree" << endl;
			for (int i = 0; i < edges.size(); i++) {
				cout << edges[i].key << "\t";
				for (int j = 0; j < edges[i].vertex.size(); j++) cout << edges[i].vertex[j] << "\t";
				cout << endl;
			}
		}
		else cout << "Isn't created" << endl;
	}

	// The function to push node

	void push_node(int num_1, int num_2) {
		bool pushed = false;
		for (int i = edges.size() - 1; i >= 0; i--) {
			if (edges[i].key == num_1) {
				edges[i].vertex.push_back(num_2);
				pushed = true;
				break;
			}
		}
		if (pushed == false) {
			for (int i = edges.size() - 1; i >= 0; i--) {
				for (int j = 0; j < edges[i].vertex.size(); j++) {
					if (edges[i].vertex[j] == num_1) {
						edges.resize(edges.size() + 1);
						edges[edges.size() - 1].key = num_1;
						edges[edges.size() - 1].vertex.push_back(num_2);
						pushed = true;
						break;
					}
				}
				if (pushed == true)break;
			}
		}
		if (pushed == false)cout << "Couldn't push " << num_1 << " -> " << num_2 << "" << endl;
	}

	// The function to pop node

	void pop_node(int num_1, int num_2) {
		int index = -1;
		bool pop = false;
		for (int i = edges.size() - 1; i >= 0; i--) {
			if (edges[i].key == num_1) {
				index = i;
				break;
			}
		}
		if (index != -1) {
			if (edges.size() == 1 && edges[index].vertex.size() == 0 && num_1 == num_2) {
				edges.resize(0);
				this->degree = -1;
				pop = true;
				index = -1;
			}
			else if (edges.size() == 1 && num_1 == num_2) {
				edges[0].key = edges[0].vertex[0];
				edges[0].vertex.resize(edges[0].vertex.size()-1);
				pop = true;
				index = -1;
			}
		}
		if (index != -1) {
			for (int j = 0; j < edges[index].vertex.size(); j++) {
				if (edges[index].vertex[j] == num_2 && edges[index].vertex.size() == 1 && edges.size() != 1) {
					if (index == edges.size() - 1) {
						edges.resize(edges.size() - 1);
					}
					else {
						edges[index] = edges[edges.size() - 1];
						edges.resize(edges.size() - 1);
					}
					pop = true;
					break;
				}
				else if (edges[index].vertex[j] == num_2) {
					if (j == edges[index].vertex.size() - 1)edges[index].vertex.resize(edges[index].vertex.size() - 1);
					else {
						edges[index].vertex[j] = edges[index].vertex[edges[index].vertex.size() - 1];
						edges[index].vertex.resize(edges[index].vertex.size() - 1);
					}
					pop = true;
					break;
				}
			}
		}
		if (pop == false)cout << "Couldn't delete " << num_1 << " -> " << num_2 << "" << endl;
	}

};