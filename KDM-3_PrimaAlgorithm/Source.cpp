#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>

#define ANSI_COLOR_BLUE "\033[34m"
#define ANSI_COLOR_RESET "\033[0m"
#define ANSI_COLOR_GREEN "\033[32m"
#define ANSI_COLOR_RED "\033[31m"

using namespace std;

void CheckData(int&);

class Graph {
private:
	int v;
	int e;
	vector<vector<int>> matrix;
public:
	Graph();
	void SetGraph(const int&, const int&, const int&);
	void Show();
	void PrimaAlgorithm();
	void AddEdge(const int&, const int&, const int&);
};

/**
 * @brief Конструктор за замовченням
*/
Graph::Graph() {

	this->v = 11;
	this->e = 18;
	this->matrix.resize(this->v, vector<int>(this->v, 0));
	this->AddEdge(0, 1, 1);
	this->AddEdge(0, 2, 2);
	this->AddEdge(0, 3, 4);
	this->AddEdge(1, 4, 3);
	this->AddEdge(1, 6, 2);
	this->AddEdge(2, 4, 7);
	this->AddEdge(2, 5, 6);
	this->AddEdge(3, 5, 2);
	this->AddEdge(3, 6, 3);
	this->AddEdge(4, 7, 7);
	this->AddEdge(4, 8, 5);
	this->AddEdge(5, 7, 7);
	this->AddEdge(5, 9, 3);
	this->AddEdge(6, 8, 5);
	this->AddEdge(6, 9, 4);
	this->AddEdge(7, 10, 4);
	this->AddEdge(8, 10, 1);
	this->AddEdge(9, 10, 4);
}

/**
 * @brief Метод, який додає ребро до графа
 * @param i Перша вершина
 * @param j Друга Вершина
 * @param weight Вага
*/
void Graph::AddEdge(const int& i, const int& j, const int& weight) {

	this->matrix[i][j] = weight;
	this->matrix[j][i] = weight;
}

/**
 * @brief Метод, який створює граф
 * @param var Режим створення графа
 * @param v Кількість вершин
 * @param e Кількість ребер
*/
void Graph::SetGraph(const int& var, const int& v, const int& e) {

	this->v = v;
	this->e = e;
	this->matrix.clear();
	this->matrix.resize(this->v, vector<int>(this->v, 0));

	if (var == 16) {
		this->AddEdge(0, 1, 1);
		this->AddEdge(0, 2, 2);
		this->AddEdge(0, 3, 4);
		this->AddEdge(1, 4, 3);
		this->AddEdge(1, 6, 2);
		this->AddEdge(2, 4, 7);
		this->AddEdge(2, 5, 6);
		this->AddEdge(3, 5, 2);
		this->AddEdge(3, 6, 3);
		this->AddEdge(4, 7, 7);
		this->AddEdge(4, 8, 5);
		this->AddEdge(5, 7, 7);
		this->AddEdge(5, 9, 3);
		this->AddEdge(6, 8, 5);
		this->AddEdge(6, 9, 4);
		this->AddEdge(7, 10, 4);
		this->AddEdge(8, 10, 1);
		this->AddEdge(9, 10, 4);
	}
	if (var == 30) {
		this->AddEdge(0, 1, 5);
		this->AddEdge(0, 2, 3);
		this->AddEdge(0, 3, 2);
		this->AddEdge(1, 4, 7);
		this->AddEdge(1, 6, 1);
		this->AddEdge(2, 4, 7);
		this->AddEdge(2, 5, 4);
		this->AddEdge(3, 5, 7);
		this->AddEdge(3, 6, 5);
		this->AddEdge(4, 7, 2);
		this->AddEdge(4, 8, 6);
		this->AddEdge(5, 7, 4);
		this->AddEdge(5, 9, 2);
		this->AddEdge(6, 8, 3);
		this->AddEdge(6, 9, 3);
		this->AddEdge(7, 10, 4);
		this->AddEdge(8, 10, 1);
		this->AddEdge(9, 10, 4);
	}
	if (var == 0) {
		cout << "Enter relationship between vertex" << endl;
		cout << "Example: Va to Vb = weight" << endl;
		int i, j, w;
		for (int n = 0; n < e; n++) {
			do {
				cin >> i >> j >> w;
				if (matrix[i - 1][j - 1] != 0) cout << "Find Dublicate! Please Reentry: ";
			} while (matrix[i - 1][j - 1] != 0);	
			this->AddEdge(i - 1, j - 1, w);
		}
	}
}

/**
 * @brief Метод, який відображає взаємозв'язок вершин у графі
*/
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

/**
 * @brief Метод, який реалізує алгоритм Прима для знаходження остовного дерева мінімальної ваги
*/
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
	do { cin >> v0; CheckData(v0); if (v0 < 1 || v0 > this->v) cout << "You Enter wrong starting vertex! Reentry any vertex v0: "; } while (v0 < 1 || v0 > this->v);
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
		cout << "min w = " << ANSI_COLOR_RED << min_w << ANSI_COLOR_RESET << endl;
		e_tree[min_i][min_j] = min_w;
		auto ftree = find(v_tree.begin(), v_tree.end(), min_i);
		if (ftree != v_tree.end()) { v_tree.push_back(min_j); not_v_tree.erase(remove(not_v_tree.begin(), not_v_tree.end(), min_j), not_v_tree.end()); }
		else { v_tree.push_back(min_i); not_v_tree.erase(remove(not_v_tree.begin(), not_v_tree.end(), min_i), not_v_tree.end()); }
		d_count++; s_count++;
		min_w = inf; min_i = inf; min_j = inf;
	}
	min_w = 0;
	bool first_plus = true;
	cout << "\nw = ";
	for (int i = 0; i < e_tree.size(); i++) {
		for (int j = 0; j < e_tree.size(); j++) {
			if (e_tree[i][j] != 0) {
				if (i != e_tree.size() && !first_plus) cout << " + ";
				cout << ANSI_COLOR_RED << e_tree[i][j] << ANSI_COLOR_RESET;
				first_plus = false;
				min_w += e_tree[i][j];				
			}			
		}
	}	
	cout << " = " << ANSI_COLOR_GREEN << min_w << ANSI_COLOR_RESET << endl;
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки
*/
void CheckData(int& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
			cerr << "You enter wrong data! Please enter correct data: \n";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {

	int work = 1;
	int task = 0, v = 0, e = 0;
	Graph g;	
	
	while (work != 0) {
		switch (work) {
		case 1:
			g.Show();
			g.PrimaAlgorithm();
			break;
		case 2:
			cout << "Choice Graph (var 16 or 30) or set your own graph (enter - 0): ";
			cin >> task;
			CheckData(task);
			if (task == 16) { g.SetGraph(16, 11, 18); cout << "Completed...\n"; }
			else if (task == 30) { g.SetGraph(30, 11, 18); cout << "Completed...\n"; }
			else if (task == 0) {
				cout << "Set amount of vertex: ";
				do { cin >> v; CheckData(v); if (v < 1) cout << "Error! Min amount of vertex = 1 Reentry: "; } while (v < 1);
				cout << "Set amount of faces: ";
				do { cin >> e; CheckData(e); if (e < v - 1) cout << "Error! (min e = " << v - 1 << ") Reentry: "; } while (e < v - 1);
				g.SetGraph(0, v, e);
			}
			else cout << "Nothing happened..\n";
			break;
		case 3:
			g.Show();
		}

		if (work != 0) {
			cout << "\n-----------Menu of actions-----------\n";
			cout << "Enter - 1 to run Prim's Algorithm" << endl;
			cout << "Enter - 2 to set new Graph" << endl;
			cout << "Enter - 3 to show current Graph" << endl;
			cout << "Enter - 0 for Exit" << endl;
			cin >> work;
			CheckData(work);
		}
	}

	return 0;
}
