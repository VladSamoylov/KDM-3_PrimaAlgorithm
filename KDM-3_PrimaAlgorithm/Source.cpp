#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class Graph {
private:
	int v;
	int e;
	vector<vector<int>> matrix;
public:
	Graph();

	void Show();
	void PrimaAlgorithm();
	void AddEdge(const int&, const int&, const int&);
};

Graph::Graph() {

	this->v = 11;
	this->e = 18;
	this->matrix.resize(v, vector<int>(v, 0));
	this->AddEdge(0, 1, 1);
	this->AddEdge(0, 2, 2);
	this->AddEdge(0, 3, 4);
	this->AddEdge(1, 4, 3);
	this->AddEdge(1, 6, 2);
	this->AddEdge(2, 4, 7);
	this->AddEdge(2, 5, 6);
	this->AddEdge(3, 5, 2);
	this->AddEdge(3, 6, 3);
	this->AddEdge(4, 7, 4);
	this->AddEdge(4, 8, 6);
	this->AddEdge(5, 7, 7);
	this->AddEdge(5, 9, 3);
	this->AddEdge(6, 8, 5);
	this->AddEdge(6, 9, 4);
	this->AddEdge(7, 10, 4);
	this->AddEdge(8, 10, 1);
	this->AddEdge(9, 10, 4);
}

void Graph::AddEdge(const int& i, const int& j, const int& weight) {

	this->matrix[i][j] = weight;
	this->matrix[j][i] = weight;
}

void Graph::Show() {

	cout << "-----------Graph-----------\n";
	for (int i = 0; i < this->v; i++) {
		for (int j = 0; j < this->v; j++) {
			if (this->matrix[i][j] != 0) {
				cout << setw(1) << left << "V" << setw(2) << i + 1 << setw(5) << " to V" << setw(2) << j + 1 << setw(3) << " = " << this->matrix[i][j] << endl;
			}
		}
	}
}

void Graph::PrimaAlgorithm() {

	constexpr int inf = numeric_limits<int>::max();
	int v0;
	int d_count = 0;
	int s_count = 1;
	int min_i = inf, min_j = inf, min_w = inf;
	vector<int> v_tree;
	vector<int> not_v_tree;
	vector<vector<int>> e_tree(this->v, vector<int>(this->v, 0));

	cout << "\nSet any vertex v0: ";
	cin >> v0;
	v_tree.push_back(v0 - 1);
	for (int i = 0; i < this->v; i++) {
		if (i != v0 - 1) not_v_tree.push_back(i);
	}
	
	while (!not_v_tree.empty()) {
		cout << "\nD" << d_count << " { ";
		for (int i = 0; i < v_tree.size(); i++) {
			cout << v_tree[i] + 1;
			if (i + 1 != v_tree.size()) cout << ", ";
		}cout << " }" << endl;
		cout << "Unselected vertices { ";
		for (int i = 0; i < not_v_tree.size(); i++) {
			cout << not_v_tree[i] + 1;
			if (i + 1 != not_v_tree.size()) cout << ", ";
		}cout << " }" << endl;

		cout << "_______________S" << s_count << "_______________" << endl;
		cout << "D" << d_count << " : \n";
		for (int i = 0; i < this->v; i++) {
			auto ftree = find(v_tree.begin(), v_tree.end(), i);
			for (int j = 0; j < this->v; j++) {
				auto fnottree = find(not_v_tree.begin(), not_v_tree.end(), j);
				if (ftree != v_tree.end() && fnottree != not_v_tree.end() && this->matrix[i][j] != 0) {
					cout << "(" << i + 1 << ',' << j + 1 << ") = " << this->matrix[i][j] << endl;
					if (this->matrix[i][j] < min_w) { min_w = matrix[i][j]; min_i = i; min_j = j; }
				}
			}
		}
		cout << "min w = " << min_w << endl;
		e_tree[min_i][min_j] = min_w;
		auto ftree = find(v_tree.begin(), v_tree.end(), min_i);
		if (ftree != v_tree.end()) { v_tree.push_back(min_j); not_v_tree.erase(remove(not_v_tree.begin(), not_v_tree.end(), min_j), not_v_tree.end()); }
		else { v_tree.push_back(min_i); not_v_tree.erase(remove(not_v_tree.begin(), not_v_tree.end(), min_i), not_v_tree.end()); }
		d_count++; s_count++;
		min_w = inf; min_i = inf; min_j = inf;
	}

	

}


int main() {

	Graph g;
	g.Show();
	g.PrimaAlgorithm();

	return 0;
}
