#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <utility>

using namespace std;

map <string, int> genre_list;
map <string, int> source_list;

static int g_count;
static int s_count;

class Movie {
public:
	string name;
	string genre;
	string source;
	int jenre_index;
	int source_index;
	double production, gross, rating;

	Movie() : name(""), genre(""), source(""), production(0), gross(0), rating(0), jenre_index(0), source_index(0) {}
	Movie(vector<string> input) :
		name(input[0]), genre(input[1]), source(input[2]), production(stod(input[3])), gross(stod(input[4])), rating(stod(input[5])) {
		if(genre_list.count(genre) == 0) {
			genre_list[genre] = g_count++;
		}
		if(source_list.count(source) == 0) {
			source_list[source] = s_count++;
		}
		jenre_index = genre_list.find(genre)->second;
		source_index = source_list.find(source)->second;
	}

	void print() {
		cout << name << "\t" << genre << "\t" << source << "\t" << production << "\t" << gross << "\t" << rating << endl;
		return;
	}
};

vector<Movie> movie_database;
vector<Movie> pivoted_db;
vector<string> pivot_table;
static int type_of_pivot_table;

void pivoting_1(int category) {

	pivoted_db = movie_database;

	if(category == 0) {
		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					return a.jenre_index < b.jenre_index;	// ascending order
				}
		);
	}
	else if(category == 1) {
		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					return a.source_index < b.source_index;	// ascending order
				}
		);
	}
}

void pivoting_2(int categ1, int categ2) {

	pivoted_db = movie_database;

	if(categ1 == 0) {
		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					return a.jenre_index < b.jenre_index;	// ascending order
				}
		);

		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					if(a.jenre_index == b.jenre_index) {
						return a.source_index < b.source_index;
					}
					else {
						return a.jenre_index < b.jenre_index;
					}
				}
		);
	}
	else if(categ1 == 1) {
		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					return a.source_index < b.source_index;	// ascending order
				}
		);

		stable_sort(pivoted_db.begin(), pivoted_db.end(),
				[] (const Movie &a, const Movie &b) -> bool {
					if(a.source_index == b.source_index) {
						return a.jenre_index < b.jenre_index;
					}
					else {
						return a.source_index < b.source_index;
					}
				}
		);
	}
}


string calc(string func, vector<double> numbers) {
	double result = 0;
	double size = numbers.size();

	double total = 0;
	for(auto &n : numbers) {
		total+=n;
	}

	if(func.compare("ave") == 0) {
		result = total / size;
	}
	else if(func.compare("tot") == 0) {
		result = total;
	}
	else if(func.compare("cnt") == 0) {
		result = size;
	}
	else if(func.compare("min") == 0) {
		result = *min_element(numbers.begin(), numbers.end());
	}
	else if(func.compare("max") == 0) {
		result = *max_element(numbers.begin(), numbers.end());
	}

	return to_string(result);
}

int get_category_index(string col) {
	int category;
	if(col.compare("Genre") == 0) {
		category = 0;
	}
	else if(col.compare("Source") == 0) {
		category = 1;
	}
	else {
		category = -1;
	}
	return category;
}

int get_figure_index(string fig) {
	int figure;
	if(fig.compare("Production") == 0) {
		figure = 0;
	}
	else if(fig.compare("Gross") == 0) {
		figure = 1;
	}
	else if(fig.compare("Rating") == 0) {
		figure = 2;
	}
	else {
		figure = -1;
	}
	return figure;
}

void pivot1(string col, string fig, string func) {
	int category = get_category_index(col);
	int figure = get_figure_index(fig);

	pivoted_db.clear();
	pivot_table.clear();

	pivoting_1(category); // pivot conversion from movie_db to pivoted_db

	pivot_table.push_back(col);
	pivot_table.push_back(fig);

	bool new_flag = true;
	vector<double> numbers;
	string last_input;
	for(auto &it : pivoted_db) {
		string categ;
		if(category == 0)
			categ = it.genre;
		else if(category == 1)
			categ = it.source;

		if(new_flag || categ.compare(last_input) != 0) {
			if(!new_flag)
				pivot_table.push_back(calc(func, numbers));
			last_input = categ;
			pivot_table.push_back(categ);	//push new categ
			numbers.clear();
			new_flag = false;
		}

		double num = 0;
		if(figure == 0)
			num = it.production;
		else if(figure == 1)
			num = it.gross;
		else if(figure == 2)
			num = it.rating;
		numbers.push_back(num);

	}
	pivot_table.push_back(calc(func, numbers));
	type_of_pivot_table = 0;
}

string get_category(Movie& m, int cat) {
	string result;
	if(cat == 0)
		result = m.genre;
	else if(cat == 1)
		result = m.source;
	return result;
}
void pivot2(string col1, string col2, string fig, string func) {

	int category1 = get_category_index(col1);
	int category2 = get_category_index(col2);
	int figure = get_figure_index(fig);

	pivoted_db.clear();
	pivot_table.clear();

	pivoting_2(category1, category2); // pivot conversion from movie_db to pivoted_db

	pivot_table.push_back(col1);
	pivot_table.push_back(col2);
	pivot_table.push_back(fig);

	bool new_flag = true;
	vector<double> numbers;
	string last_input1;
	string last_input2;
	for(auto &it : pivoted_db) {
		string categ1 = get_category(it, category1);
		string categ2 = get_category(it, category2);

		if(new_flag || categ1.compare(last_input1) != 0 || categ2.compare(last_input2) != 0) {
			if(!new_flag)
				pivot_table.push_back(calc(func, numbers));
			last_input1 = categ1;
			last_input2 = categ2;
			pivot_table.push_back(categ1);	//push new categ
			pivot_table.push_back(categ2);
			numbers.clear();
			new_flag = false;
		}

		double num = 0;
		if(figure == 0)
			num = it.production;
		else if(figure == 1)
			num = it.gross;
		else if(figure == 2)
			num = it.rating;
		numbers.push_back(num);

	}
	pivot_table.push_back(calc(func, numbers));
	type_of_pivot_table = 1;
}

void original_table() {
	cout << "Name" << "\t" << "Genre" << "\t" << "Source" << "\t" << "Production" << "\t" << "Gross" << "\t" << "Rating" << endl;

	vector<Movie>::iterator it = movie_database.begin();
	while(it != movie_database.end()) {
		it->print();
		it++;
	}
}

void print_pivot_table() {

	cout.precision(2);
	cout<<fixed;

	if(type_of_pivot_table == 0) { // pivot 1
		cout << pivot_table[0] << "\t" << pivot_table[1] << endl;
		for(int i = 2; i < pivot_table.size(); i++) {
			stringstream ss(pivot_table[i+1]);
			double x;
			ss >> x;
			cout << pivot_table[i] << "\t" << x << endl;
			i++;
		}
	}
	else if(type_of_pivot_table == 1) {
		cout << pivot_table[0] << "\t" << pivot_table[1] << "\t" << pivot_table[2] << endl;
		for(int i = 3; i < pivot_table.size(); i++) {
			stringstream ss(pivot_table[i+2]);
			double x;
			ss >> x;
			cout << pivot_table[i] << "\t" << pivot_table[++i] << "\t" << x << endl;
			i++;
		}
	}

}

int calc_length(double min, double max, double num) {
	int result;
	if(min == max)
		result = 20;
	else if(num == min)
		result = 0;
	else if(num == max)
		result = 20;
	else {
		double unit = (max-min)/20;
		result = ceil((num-min)/unit);
	}
	return result;
}


void pivot_chart() {
	cout.precision(2);
	cout<<fixed;
	//create a hashtable
	char legend1;
	map<string, string> legend_map;
	int offset;

	if(pivot_table[0].compare("Genre") == 0) {
		legend1 = 'A';
		offset = 17;
	}
	else if(pivot_table[0].compare("Source") == 0) {
		legend1 = '1';
		offset = 1;
	}

	/* creates a new table from the pivoted data */

	if(type_of_pivot_table == 0) {
		//map<string, double> pivot_chart;
		vector<pair<string, double> > pivot_chart;
		for(int i = 2; i < pivot_table.size(); i = i+2) {
			stringstream ss(pivot_table[i+1]);
			double x;
			ss >> x;
			if(offset == 17) {
				pivot_chart.push_back(make_pair(string(1, '0'+(genre_list.find(pivot_table[i])->second)+offset), x));
				//pivot_chart[string(1, '0'+(genre_list.find(pivot_table[i])->second)+offset)] = x;
				legend_map[string(1, '0'+(genre_list.find(pivot_table[i])->second)+offset)] = pivot_table[i];
			}
			else if(offset == 1) {
				pivot_chart.push_back(make_pair(string(1, '0'+(source_list.find(pivot_table[i])->second)+offset), x));
				//pivot_chart[string(1, '0'+(source_list.find(pivot_table[i])->second)+offset)] = x;
				legend_map[string(1, '0'+(source_list.find(pivot_table[i])->second)+offset)] = pivot_table[i];
			}
		}


		/* print */

		double min = min_element(pivot_chart.begin(), pivot_chart.end(),
				[] (const pair<string, double> &a, const pair<string, double> &b) -> bool {
					return a.second < b.second;
				}
		)->second;

		double max = max_element(pivot_chart.begin(), pivot_chart.end(),
				[] (const pair<string, double> &a, const pair<string, double> &b) -> bool {
					return a.second < b.second;
				}
		)->second;

		for(auto &x : pivot_chart) {
			int n = calc_length(min, max, x.second);
			cout << x.first << "|" << string(n, '=') << x.second << endl;
		}

		cout << string(25, '-') << endl;
		for(auto &y : legend_map) {
			cout << y.first << ": " << y.second << endl;
		}

	}
	else if(type_of_pivot_table == 1) {

		char legend2;

		map<string, string> legend_map2;

		if(pivot_table[1].compare("Genre") == 0) {
			legend2 = 'A';
		}
		else if(pivot_table[1].compare("Source") == 0) {
			legend2 = '1';
		}

		//map<string, double> pivot_chart;
		vector<pair<string, double> > pivot_chart;
		for(int i = 3; i < pivot_table.size(); i++) {
			stringstream ss(pivot_table[i+2]);
			double x;
			ss >> x;
			string lg1;
			string lg2;

			if(offset == 17) {
				lg1 = string(1, '0'+(genre_list.find(pivot_table[i])->second)+17);
				lg2 = string(1, '0'+(source_list.find(pivot_table[i+1])->second)+1);
//				pivot_chart[string(1, '0'+(genre_list.find(pivot_table[i])->second)+offset)] = x;
//				legend_map[string(1, '0'+(genre_list.find(pivot_table[i])->second)+offset)] = pivot_table[i];
			}
			else if(offset == 1) {
				lg1 = string(1, '0'+(source_list.find(pivot_table[i])->second)+1);
				lg2 = string(1, '0'+(genre_list.find(pivot_table[i+1])->second)+17);
//				pivot_chart[string(1, '0'+(source_list.find(pivot_table[i])->second)+offset)] = x;
//				legend_map[string(1, '0'+(source_list.find(pivot_table[i])->second)+offset)] = pivot_table[i];
			}
//
//			if(legend_map.count(pivot_table[i]) == 0)
//				lg1 = string(1, legend1);
//			else
//				lg1 = legend_map[pivot_table[i]];
//
//			if(legend_map2.count(pivot_table[i+1]) == 0)
//				lg2 = string(1, legend2);
//			else
//				lg2 = legend_map2[pivot_table[i+1]];

			pivot_chart.push_back(make_pair(lg1+lg2, x));
			//pivot_chart[lg1 + lg2] = x;

			if(legend_map.count(pivot_table[i]) == 0) {
				legend_map[pivot_table[i]] = lg1;
			}

			if(legend_map2.count(pivot_table[i+1]) == 0)
				legend_map2[pivot_table[i+1]] = lg2;
			i+=2;
		}

		/* print */
		double min = min_element(pivot_chart.begin(), pivot_chart.end(),
				[] (const pair<string, double> &a, const pair<string, double> &b) -> bool {
					return a.second < b.second;
				}
		)->second;

		double max = max_element(pivot_chart.begin(), pivot_chart.end(),
				[] (const pair<string, double> &a, const pair<string, double> &b) -> bool {
					return a.second < b.second;
				}
		)->second;

		char cmp = (pivot_chart.begin()->first).at(0);
		for(auto &x : pivot_chart) {
			if(x.first.at(0) != cmp) {
				cout << "  |" << endl;
			}

			int n = calc_length(min, max, x.second);

			cout << x.first << "|" << string(n, '=') << x.second << endl;
			cmp = x.first.at(0);
		}

		cout << string(25, '-') << endl;

		vector<string> lmap;
		for(auto &y : legend_map) {
			lmap.push_back(y.second + ": " + y.first);
		}
		stable_sort(lmap.begin(), lmap.end(),
				[] (const string &a, const string &b) -> bool {
					return a.at(0) < b.at(0);	// ascending order
				}
		);

		for(auto &y : lmap) {
			cout << y << endl;
		}


		lmap.clear();
		for(auto &y : legend_map2) {
			lmap.push_back(y.second + ": " + y.first);
		}
		stable_sort(lmap.begin(), lmap.end(),
				[] (const string &a, const string &b) -> bool {
					return a.at(0) < b.at(0);	// ascending order
				}
		);
		for(auto &y : lmap) {
			cout << y << endl;
		}
	}
}

int main() {

	/* static variable initialization */
	g_count = 0;
	s_count = 0;

	int n;
	int i = 0;
	cin >> n;
	cin.ignore(256, '\n');

	while(i<n) {
		string input;
		string buf;
		vector<string> input_vector;
		getline(cin, input);
		istringstream ss(input);
		while(ss >> buf) {
			input_vector.push_back(buf);
		}
		Movie m = Movie(input_vector);
		movie_database.push_back(m);
		i++;
	}

	while(1) {
		string input;
		string buf;
		vector<string> input_vector;
		getline(cin, input);
		if(!input.empty()) {
			istringstream ss(input);
			while(ss >> buf) {
				input_vector.push_back(buf);
			}
			string command = input_vector[0];

			if(command.compare("originaltable") == 0) {
				original_table();
			}
			else if(command.compare("pivottable") == 0) {
				print_pivot_table();
			}
			else if(command.compare("pivotchart") == 0) {
				pivot_chart();
			}
			else if(command.compare("pivot1") == 0) {
				pivot1(input_vector[1], input_vector[2], input_vector[3]);
			}
			else if(command.compare("pivot2") == 0) {
				pivot2(input_vector[1], input_vector[2], input_vector[3], input_vector[4]);
			}
			else if(command.compare("close") == 0) {
				return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	return 0;
}
