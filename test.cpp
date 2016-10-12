#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class PixelBoard {
public:
	PixelBoard() {};

	void hi(int m, int n) {

		row = m, col = n;
		board = new char*[m];

		for (int i = 0; i < m; ++i)
			board[i] = new char[n];

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = 'O';
			}
		}
		return;
	}

	void clean() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				board[i][j] = 'O';
			}
		}
		return;
	}

	void mark(int x, int y, string c) {
		if((x-1 < 0 || x-1 >= col) || (y-1 < 0 || y-1 >= row)) {
			return;
		}
		board[y-1][x-1] = c.at(0);
		return;
	}

	void vertical(int x, int y1, int y2, string c) {
		if(y1 >= y2) {
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}
		for(int i = y1-1; i <= y2-1; i++) {
			board[i][x-1] = c.at(0);
		}
	}

	void horizon(int x1, int x2, int y, string c) {
		if(x1 >= x2) {
			int temp = x1;
			x1 = x2;
			x2 = temp;
		}
		for(int i = x1-1; i <= x2-1; i++) {
			board[y-1][i] = c.at(0);
		}
	}

	void fill(int x1, int y1, int x2, int y2, string c) {
		for(int i = x1; i <= x2; i++) {
			for(int j = y1; j <= y2; j++) {
				board[j-1][i-1] = c.at(0);
			}
		}
	}

	void rect(int x1, int y1, int x2, int y2, string c) {
		this->vertical(x1, y1, y2, c);
		this->vertical(x2, y1, y2, c);
		this->horizon(x1, x2, y1, c);
		this->horizon(x1, x2, y2, c);
	}

	void change(int x, int y, string c) {
		mark(x, y, c);
		change_rec(x, y, c);
	}
	void change_rec(int x, int y, string c) {
		if(!(x>0 && x<=col && y>0 && y<=row))
			return;
		else {
			if(board[y-1][x-1] == 'O' || board[y-1][x-1] == 'C') {
				mark(x, y, c);
				change_rec(x-1, y, c);
				change_rec(x+1, y, c);
				change_rec(x, y-1, c);
				change_rec(x, y+1, c);
			}
			else return;
		}
	}


	//TODO
	void mark_if_empty(int i, int j, string c) {
		if((i-1 < 0 || i-1 >= col) || (j-1 < 0 || j-1 >= row)) {
			return;
		}
		if(board[j-1][i-1] == 'O') {
			board[j-1][i-1] = c.at(0);
		}
	}

	void bye() {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	}

private:
	int row;
	int col;
	char **board;

};
int main() {

	int t, m, n;
	string input;

	getline(cin, input);
	istringstream ss(input);
	vector<string> command;

	string temp;
	while(ss >> temp) {
		command.push_back(temp);
	}

	t = stoi(command[0]);
	m = stoi(command[1]);
	// n = stoi(command[2]);


	while(1) {
		getline(cin, input);
		istringstream ss(input);
		vector<string> command;

		string temp;
		while(ss >> temp) {
			command.push_back(temp);
		}

	}

	return 0;
}