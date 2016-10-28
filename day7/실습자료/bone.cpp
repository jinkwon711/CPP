#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
using namespace std;

class player {
public:
	string name;
	string code;
	string position;
	double winning_rate;
	player():name(""),code(""){}
	player(string n, string c, string p, double wr):name(n), code(c), position(p),winning_rate(wr){}
	/*write player class initizlier here*/
};

class team {
private:
	double teamwork = 0; //DO NOT MODIFY!
public:
	string name;
	string code;
	player *p1 = new player;
	player *p2 = new player;
	player *p3 = new player;
	player *p4 = new player;
	player *p5 = new player;
	player *p6 = new player;

	team(): name(""), code(""){}
//	team(string n, string c,player p1, player p2,player p3,player p4,player p5,player p6):name(n), code(c), p1(p1),p2(p2),p3(p3),p4(p4),p5(p5),p6(p6){}

	friend player;
	friend ostream &operator<<(ostream&,const team&);
	friend void calc_teamwork(team &);

	/*write team class initializer here*/
	/*define friend function herer*/
};

vector<player> player_list;
team t1, t2;

bool check_duplicate(player p) { //DO NOT MODIFY!
	for (auto it2 = player_list.begin(); it2 != player_list.end(); it2++) {
		if (!(*it2).code.compare(p.code)) {
			cout << "duplicate code exists! code should be unique!" << '\n';
			return true;
		}
	}
	return false;
}

ostream &operator<<(ostream &os, const player &p) { //DO NOT MODIFY!
	os << "player code : " << p.code;
	os << '\n';
	os << "player name : " << p.name;
	os << '\n';
	os << "player position : " << p.position;
	os << '\n';
	os << "player winning rate : " << p.winning_rate;
	os << '\n';
	return os;
}

ostream &operator<<(ostream &os, const team &t) { //DO NOT MODIFY!
	os << "team code : " << t.code;
	os << '\n';
	os << "team name : " << t.name;
	os << '\n';
	os << "teamwork : " << t.teamwork;
	os << '\n';
	os << "first team member : " << t.p1->name << " " << t.p1->code;
	os << '\n';
	os << "second team member : " << t.p2->name << " " << t.p2->code;
	os << '\n';
	os << "third team member : " << t.p3->name << " " << t.p3->code;
	os << '\n';
	os << "fourth team member : " << t.p4->name << " " << t.p4->code;
	os << '\n';
	os << "fifth team member : " << t.p5->name << " " << t.p5->code;
	os << '\n';
	os << "sixth team member : " << t.p6->name << " " << t.p6->code;
	os << '\n';
	return os;
}

istream &operator >> (istream &is, player &p) {
	/* write code below */
	string tempCode="0";
	double temp = -1;
	while(tempCode=="0"){
		cout << "input code : ";
		cin>> tempCode;
		cin.ignore(256, '\n');
		p.code = tempCode;
		if(check_duplicate(p)){
			tempCode="0";
		}
	}

	cout << "input name : ";
	cin >> p.name;
	cout << "input position : ";
	cin >> p.position;

	while(temp<0 || temp>100){
		cout << "input winning rate : ";
		cin >> temp;
			if(temp<0 || temp>100){
	    cout << "winning rate should be between 0 and 100" << '\n';
			}
			else p.winning_rate = temp;
	}
}
team operator*(team t1, team t2) {
	/*write code below*/
	cout << t1.name << " win!" << '\n';
	cout << t2.name << " win!" << '\n';
	cout << "Unpredictable!" << '\n';
}

void calc_teamwork(team &t) { //DO NOT MODIFY!
	t.teamwork = t.p1->winning_rate + t.p2->winning_rate + t.p3->winning_rate + t.p4->winning_rate + t.p5->winning_rate + t.p6->winning_rate;
}

void print_line() { //DO NOT MODIFY!
	cout << "======================================================================" << '\n';
}

void search_position(string position) {
	/*write code below*/
	cout << "No position exists!" << '\n';
}

void search_player_name(string name) {
	/*write code below*/
	cout << "No player exists!" << '\n';
}

void search_player_code(string code) {
	/*write code below*/
	cout << "No player exists!" << '\n';
}

void modify_player(string code) {
	/* write code below */
	cout << "input name : ";

	cout << "input position : ";

	cout << "input winning rate : ";

	cout << "No player exists!" << '\n';
}

void print_player() {
	/* write code here */
}

void delete_player(string code) {
	/* write code below */
	cout << "No such player exists in player list" << '\n';
}

bool check_team_condition() { //DO NOT MODIFY!
	if (player_list.size() > 5) return true;
	else return false;
}

void build_team(team &t) {
	/* write code below */

	cout << "Input team code : ";

	cout << "Input team name : ";

	cout << "Input first team member's code : ";

	cout << "Input second team member's code : ";

	cout << "Input third team member's code : ";

	cout << "Input fourth team member's code : ";

	cout << "Input fifth team member's code : ";

	cout << "Input sixth team member's code : ";
}

void build_best_team() {
	/* write code here */
}

void print_logo() { // DO NOT MODIFY!
	print_line();
	cout << ",--.   ,--.        ,--.            ,--.   ,--.                        " << '\n';
	cout << "|   `.'   | ,--,--.`--',--,--,     |   `.'   | ,---. ,--,--, ,--.,--. " << '\n';
	cout << "|  |'.'|  |' ,-.  |,--.|      |    |  |'.'|  || .-. :|      ||  ||  | " << '\n';
	cout << "|  |   |  |` '-'  ||  ||  ||  |    |  |   |  |`   --.|  ||  |'  ''  ' " << '\n';
	cout << "`--'   `--' `--`--'`--'`--''--'    `--'   `--' `----'`--''--' `----'  " << '\n';
	print_line();
}

void show_help() { //DO NOT MODIFY!
	cout << "Command list" << '\n';
	cout << "help - print commands" << '\n';
	cout << "new player - Insert new player" << '\n';
	cout << "search player - Search player from list" << '\n';
	cout << "delete player - Remove player from player list" << '\n';
	cout << "modify player - Modify player from player list" << '\n';
	cout << "print player - Print all player" << '\n';
	cout << "build team - Build a new team" << '\n';
	cout << "build best team - Build a best team" << '\n';
	cout << "print team - Print all team" << '\n';
	cout << "simulate - Simulate teams" << '\n';
	cout << "exit - To terminate program" << '\n';
	print_line();
}

int check_command(string command) { //DO NOT MODIFY!
	if (!command.compare("new player")) {
		player p;
		cin >> p;
		player_list.emplace_back(p);
		print_line();
	}
	else if (!command.compare("print player")) {
		if (player_list.empty()) {
			cout << "player list is empty" << '\n';
			print_line();
		}
		else print_player();
	}
	else if (!command.compare("search player")) {
		int select = -1;
		string keyword;
		if (player_list.empty()) {
			cout << "player list is empty" << '\n';
			print_line();
		}
		else {
			do {
				cout << "Select keyword to search" << '\n';
				cout << "0 : Search with player code" << '\n';
				cout << "1 : Search with player name" << '\n';
				cout << "2 : Search with player position" << '\n';
				print_line();
				cin >> select;
				cin.ignore(256, '\n');
				switch (select) {
				case 0:
					cout << "Input player code : ";
					cin >> keyword;
					cin.ignore(256, '\n');
					print_line();
					search_player_code(keyword);
					break;
				case 1:
					cout << "Input player name : ";
					cin >> keyword;
					cin.ignore(256, '\n');
					print_line();
					search_player_name(keyword);
					break;
				case 2:
					cout << "Input position : ";
					cin >> keyword;
					cin.ignore(256, '\n');
					print_line();
					search_position(keyword);
					break;
				default:
					cout << "Invalid keyword!" << '\n';
					print_line();
					break;
				}
			} while (select < 0 || select>2);
		}
	}
	else if (!command.compare("delete player")) {
		string name;
		if (player_list.empty()) {
			cout << "player list is empty" << '\n';
			print_line();
		}
		else {
			cout << "Input player code : ";
			cin >> name;
			cin.ignore(256, '\n');
			delete_player(name);
			print_line();
		}
	}

	else if (!command.compare("build team")) {
		int cond;
		if (check_team_condition()) {
			cout << "select team to build" << '\n';
			cout << "0 : Team 1" << '\n';
			cout << "1 : Team 2" << '\n';
			cin >> cond;
			cin.ignore(256, '\n');
			if (cond == 0) build_team(t1);
			else if (cond == 1) build_team(t2);
			print_line();
		}
		else cout << "Not enough players to a build team" << '\n';
	}
	else if (!command.compare("build best team")) {
		if (check_team_condition()) build_best_team();
		else cout << "Not enough players to build a team" << '\n';
		print_line();
	}
	else if (!command.compare("simulate")) {
		if (!t1.name.compare("")) cout << "Team 1 is empty!" << '\n';
		else if (!t2.name.compare("")) cout << "Team 2 is empty!" << '\n';
		else t1*t2;
		print_line();
	}
	else if (!command.compare("print team")) {
		if (!t1.name.compare("")) cout << "Team 1 is empty!" << '\n';
		else cout << t1;
		print_line();
		if (!t2.name.compare("")) cout << "Team 2 is empty!" << '\n';
		else cout << t2;
		print_line();
	}
	else if (!command.compare("modify player")) {
		string code;
		if (player_list.empty()) {
			cout << "player list is empty" << '\n';
			print_line();
		}
		else {
			cout << "Input player code to modify : ";
			cin >> code;
			cin.ignore(256, '\n');
			modify_player(code);
			print_line();
		}
	}
	else if (!command.compare("help")) {
		print_logo();
		show_help();
	}
	else if (!command.compare("exit")) return 0;
	else {
		cout << command << '\n';
		cout << "Invalid command!" << '\n';
	}
	return 1;
}

int main() {
	print_logo();
	show_help();
	string command;
	do {
		getline(cin, command);
	} while (check_command(command));

	return 0;
}
