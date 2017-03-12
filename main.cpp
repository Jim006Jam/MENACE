#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;
int maxstatesize = 9;
vector <string> fstates;
vector <string> sstates;
vector <vector<int>> fpebs;
vector <vector<int>> spebs;

//Basic Functions
class cell {
	private:
		bool cross = false;
		bool naught = false;
	public:
		bool get_cross() {
			return cross;
		}
		bool get_naught() {
			return naught;
		}
		void set_cross() {
			cross = true;
		}
		void set_naught() {
			naught = true;
		}
};

string rotate(string s) {
	string a;
	a += s.substr(6,1);
	a += s.substr(3,1);
	a += s.substr(0,1);
	a += s.substr(7,1);
	a += s.substr(4,1);
	a += s.substr(1,1);
	a += s.substr(8,1);
	a += s.substr(5,1);
	a += s.substr(2,1);
	return a;
}

vector <string> transform(string s) {
	vector <string> transforms;
	string a = s;
	for(int i = 0; i < 3; i ++) {
		string b = rotate(a);
		transforms.push_back(b);
		a = b;
	}
	
	a="";
	for (int i = 6; i < 9; i++) {
		a += s.substr(i,1);
	}
	for (int i = 3; i < 6; i++) {
		a += s.substr(i,1);
	}
	for (int i = 0; i < 3; i++) {
		a += s.substr(i,1);
	}
	transforms.push_back(a);
	
	a = rotate(a);
	transforms.push_back(a);
	
	for (int i = 0; i < 2; i ++) {
		a = rotate(a);
	}
	transforms.push_back(a);

	a = "";
	for (int i = 2; i > -1; i--) {
		a += s.substr(i,1);
	}
	for (int i = 5; i > 2; i--) {
		a += s.substr(i,1);
	}
	for (int i = 8; i > 5; i--) {
		a += s.substr(i,1);
	}
	transforms.push_back(a);
	return transforms;
}

int check_movenum(string s) {
	int temp = 0;
	for(int i = 0; i < maxstatesize; i ++) {
		if(s[i] == '-') {
			temp++;
		}
	}
	return temp;
}

int check_movenum(cell cells[9]) {
	int temp = 0;
	for(int i = 0; i < 9; i ++) {
		if((cells[i].get_cross() == 0) && (cells[i].get_naught() == 0)) {
			temp++;
		}
	}
	return temp;
}



//Loading, Saving and Printing
void load_files() {
	string::size_type sz;
	//Reading in first player states and probs
	string line;
	ifstream firstfile ("first_player_menace.txt");
	ifstream secondfile ("second_player_menace.txt");
	if (firstfile.is_open()) {
		for(int ln = 0; ln < 304 ; ln++) {
			getline(firstfile,line,' ');
			string s = line;
			fstates.push_back(s);
			int i = 0;
			vector <int> vec;
			for(int i = 0; i < 9; i++) {
				int a;
				getline(firstfile,line,'[');
				getline(firstfile,line,']');
				try {
					a = stoi(line,&sz);
				} catch (invalid_argument&) {
					//Do Nothing just catch error
				}
				vec.push_back(a);
			}
			fpebs.push_back(vec);
			getline(firstfile,line,'\n');
		}
	} else {
		cout << "Could not open file" << endl;
	}
	//Reading in second player states and probs
	if (secondfile.is_open()) {
		for(int ln = 0; ln < 289 ; ln++) {
			getline(secondfile,line,' ');
			string s = line;
			sstates.push_back(s);
			int i = 0;
			vector <int> vec;
			for(int i = 0; i < 9; i++) {
				int a;
				getline(secondfile,line,'[');
				getline(secondfile,line,']');
				try {
					a = stoi(line,&sz);
				} catch (invalid_argument&) {
					//Do Nothing just catch error
				}
				vec.push_back(a);
			}
			spebs.push_back(vec);
			getline(secondfile,line,'\n');
		}
	} else {
		cout << "Could not open file" << endl;
	}
	secondfile.close();
}

void save_files() {
	ofstream myfile;
	myfile.open ("first_player_menace.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < fstates.size(); i++) {
		myfile << fstates[i] << " ";
		for(int j = 0; j < maxstatesize; j++) {
			myfile << "[" << fpebs[i][j] << "]" << " ";
		} if(i != 304) {
			myfile << endl;
		}
	}
	myfile.close();
	myfile.open ("second_player_menace.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < sstates.size(); i++) {
		myfile << sstates[i] << " ";
		for(int j = 0; j < maxstatesize; j++) {
			myfile << "[" << spebs[i][j] << "]" << " ";
		} if(i != 304) {
			myfile << endl;
		}
	}
	myfile.close();
}

void print_menu(int menu) {
	if (menu == 1) {
		cout << "Main Menu" << endl;
		cout << "1 - Train Menace" << endl;
		cout << "2 - Play Menace" << endl;
		cout << "3 - Test The AI's" << endl;
		cout << "4 - Exit" << endl;
	} else if (menu == 2) {
		cout << "Choose an opponent" << endl;
		cout << "1 - \"Perfect Player\" - Not Implemented Yet" << endl;
		cout << "2 - \"Logical Player\"" << endl;
		cout << "3 - Randomly Placing Player" << endl;
		cout << "4 - Back" << endl;
	}
}

void print_grid(cell cells[9]){
	int cell_num = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			cout << "|";
			if (cells[cell_num].get_cross() == true) {
				cout << "X";
			}
			else if (cells[cell_num].get_naught() == true) {
				cout << "O";
			}
			else {
				cout << " ";
			}
			cout << "|";
			cell_num++;
		}
		cout << endl;
	}
	cout << endl;
};
//Used Primarily for testing
void print_states() {
	cout << endl << "-----THESE ARE THE FIRST PLAYER STATES-----" << " " << fstates.size() << endl;
	for (int i = 0; i < fstates.size()-1; i ++) {
		cout << fstates[i] << " |";
		for (int j = 0; j < maxstatesize; j ++) {
			cout << fpebs[i][j] << "|";
		}
		cout << endl;
	}
	
	cout << endl << "-----THESE ARE THE SECOND PLAYER STATES-----" << " " << sstates.size() << endl;
	
	for (int i = 0; i < sstates.size()-1; i ++) {
		cout << sstates[i] << " |";
		for (int j = 0; j < maxstatesize; j ++) {
			cout << spebs[i][j] << "|";
		}
		cout << endl;
	}
}

void remove_minus() {
	for (int i = 0; i < fstates.size(); i ++) {
		for(int j = 0; j < maxstatesize; j ++) {
			if(fpebs[i][j] < 0) {
				fpebs[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < sstates.size(); i ++) {
		for(int j = 0; j < maxstatesize; j ++) {
			if(spebs[i][j] < 0) {
				spebs[i][j] = 0;
			}
		}
	}
}


//Checking and Adjusting values
int check_index(string s,char x) {
	int index;
	vector <string> transforms;
	vector <int> total;
	transforms = transform(s);
	transforms.push_back(s);
	if(x == 'x') {
		for (int i = 0; i < transforms.size(); i ++) {
			for(int j = 0; j < fstates.size(); j ++) {
				if(transforms[i] == fstates[j]) {
					index = j;
				}
			}
		}
	} else if (x == 'o'){
		for (int i = 0; i < transforms.size(); i ++) {
			for(int j = 0; j < sstates.size();j++) {
				if(transforms[i] == sstates[j]) {
					index = j;
				}
			}
		}
	}
	return index;
}

int check_game(cell cells[9]) {
	int game_over = 0;
	int size = check_movenum(cells);
	if (((cells[0].get_cross() + cells[1].get_cross() + cells[2].get_cross()) == 3) ||
		((cells[3].get_cross() + cells[4].get_cross() + cells[5].get_cross()) == 3) ||
		((cells[6].get_cross() + cells[7].get_cross() + cells[8].get_cross()) == 3) ||
		((cells[0].get_cross() + cells[3].get_cross() + cells[6].get_cross()) == 3) ||
		((cells[1].get_cross() + cells[4].get_cross() + cells[7].get_cross()) == 3) ||
		((cells[2].get_cross() + cells[5].get_cross() + cells[8].get_cross()) == 3) ||
		((cells[0].get_cross() + cells[4].get_cross() + cells[8].get_cross()) == 3) ||
		((cells[2].get_cross() + cells[4].get_cross() + cells[6].get_cross()) == 3)) {
			game_over = (-1);
		}
	else if (((cells[0].get_naught() + cells[1].get_naught() + cells[2].get_naught()) == 3) ||
		((cells[3].get_naught() + cells[4].get_naught() + cells[5].get_naught()) == 3) ||
		((cells[6].get_naught() + cells[7].get_naught() + cells[8].get_naught()) == 3) ||
		((cells[0].get_naught() + cells[3].get_naught() + cells[6].get_naught()) == 3) ||
		((cells[1].get_naught() + cells[4].get_naught() + cells[7].get_naught()) == 3) ||
		((cells[2].get_naught() + cells[5].get_naught() + cells[8].get_naught()) == 3) ||
		((cells[0].get_naught() + cells[4].get_naught() + cells[8].get_naught()) == 3) ||
		((cells[2].get_naught() + cells[4].get_naught() + cells[6].get_naught()) == 3)){
		game_over = (-2);
	}
	else if(size == 0) {
		game_over = (-3);
	}
	return game_over;
};

int detect_win(cell cells[9], char x) {
	if(x == 'x') {
		if (((cells[1].get_cross() + cells[2].get_cross() == 2) || (cells[4].get_cross() + cells[8].get_cross() == 2) || (cells[3].get_cross() + cells[6].get_cross() == 2)) && ((cells[0].get_cross() == 0) && (cells[0].get_naught() == 0))) {
			return 0;
		}
		if (((cells[0].get_cross() + cells[2].get_cross() == 2) || (cells[4].get_cross() + cells[7].get_cross() == 2)) && ((cells[1].get_cross() == 0) && (cells[1].get_naught() == 0))){
			return 1;
		}
		if (((cells[0].get_cross() + cells[1].get_cross() == 2) || (cells[5].get_cross() + cells[8].get_cross() == 2) || (cells[4].get_cross() + cells[6].get_cross() == 2)) && ((cells[2].get_cross() == 0) && (cells[2].get_naught() == 0))){
			return 2;
		}
		if (((cells[0].get_cross() + cells[6].get_cross() == 2) || (cells[4].get_cross() + cells[5].get_cross() == 2)) && ((cells[3].get_cross() == 0) && (cells[3].get_naught() == 0))){
			return 3;
		}
		if (((cells[3].get_cross() + cells[5].get_cross() == 2) || (cells[1].get_cross() + cells[7].get_cross() == 2) || (cells[0].get_cross() + cells[8].get_cross() == 2) || (cells[2].get_cross() + cells[6].get_cross() == 2)) && ((cells[4].get_cross() == 0) && (cells[4].get_naught() == 0))){
			return 4;
		}
		if (((cells[2].get_cross() + cells[8].get_cross() == 2) || (cells[3].get_cross() + cells[4].get_cross() == 2)) && ((cells[5].get_cross() == 0) && (cells[5].get_naught() == 0))){
			return 5;
		}
		if (((cells[0].get_cross() + cells[3].get_cross() == 2) || (cells[7].get_cross() + cells[8].get_cross() == 2) || (cells[2].get_cross() + cells[4].get_cross() == 2)) && ((cells[6].get_cross() == 0) && (cells[6].get_naught() == 0))){
			return 6;
		}
		if (((cells[1].get_cross() + cells[4].get_cross() == 2) || (cells[6].get_cross() + cells[8].get_cross() == 2)) && ((cells[7].get_cross() == 0) && (cells[7].get_naught() == 0))){
			return 7;
		}
		if (((cells[6].get_cross() + cells[7].get_cross() == 2) || (cells[2].get_cross() + cells[5].get_cross() == 2) || (cells[0].get_cross() + cells[4].get_cross() == 2)) && ((cells[8].get_cross() == 0) && (cells[8].get_naught() == 0))){
			return 8;
		}
	} else if(x == 'o') {
		if (((cells[1].get_naught() + cells[2].get_naught() == 2) || (cells[4].get_naught() + cells[8].get_naught() == 2) || (cells[3].get_naught() + cells[6].get_naught() == 2)) && ((cells[0].get_cross() == 0) && (cells[0].get_naught() == 0))) {
			return 0;
		}
		if (((cells[0].get_naught() + cells[2].get_naught() == 2) || (cells[4].get_naught() + cells[7].get_naught() == 2)) && ((cells[1].get_cross() == 0) && (cells[1].get_naught() == 0))){
			return 1;
		}
		if (((cells[0].get_naught() + cells[1].get_naught() == 2) || (cells[5].get_naught() + cells[8].get_naught() == 2) || (cells[4].get_naught() + cells[6].get_naught() == 2)) && ((cells[2].get_cross() == 0) && (cells[2].get_naught() == 0))){
			return 2;
		}
		if (((cells[0].get_naught() + cells[6].get_naught() == 2) || (cells[4].get_naught() + cells[5].get_naught() == 2)) && ((cells[3].get_cross() == 0) && (cells[3].get_naught() == 0))){
			return 3;
		}
		if (((cells[3].get_naught() + cells[5].get_naught() == 2) || (cells[1].get_naught() + cells[7].get_naught() == 2) || (cells[0].get_naught() + cells[8].get_naught() == 2) || (cells[2].get_naught() + cells[6].get_naught() == 2)) && ((cells[4].get_cross() == 0) && (cells[4].get_naught() == 0))){
			return 4;
		}
		if (((cells[2].get_naught() + cells[8].get_naught() == 2) || (cells[3].get_naught() + cells[4].get_naught() == 2)) && ((cells[5].get_cross() == 0) && (cells[5].get_naught() == 0))){
			return 5;
		}
		if (((cells[0].get_naught() + cells[3].get_naught() == 2) || (cells[7].get_naught() + cells[8].get_naught() == 2) || (cells[2].get_naught() + cells[4].get_naught() == 2)) && ((cells[6].get_cross() == 0) && (cells[6].get_naught() == 0))){
			return 6;
		}
		if (((cells[1].get_naught() + cells[4].get_naught() == 2) || (cells[6].get_naught() + cells[8].get_naught() == 2)) && ((cells[7].get_cross() == 0) && (cells[7].get_naught() == 0))){
			return 7;
		}
		if (((cells[6].get_naught() + cells[7].get_naught() == 2) || (cells[2].get_naught() + cells[5].get_naught() == 2) || (cells[0].get_naught() + cells[4].get_naught() == 2)) && ((cells[8].get_cross() == 0) && (cells[8].get_naught() == 0))){
			return 8;
		}
	}
	return -1;
}

void adjust_pebs(vector <int> moves, vector <string> states,int result,int men) {
	if(men == 2) {
		for(int i = 0; i < states.size(); i ++) {
			int in;
			int newmove;
			string state;
			int index = check_index(states[i],'o');
			vector <string> transforms = transform(states[i]);
			transforms.push_back(states[i]);
			for(int j = 0; j < transforms.size(); j ++) {
				if(transforms[j] == sstates[index]) {
					in = j;
				}
			}
			for(int j = 0; j < maxstatesize; j ++) {
				if(j == moves[i]) {
					state+= 'o';
				} else {
					state+= '-';
				}
			}
			transforms = transform(state);
			transforms.push_back(state);
			for(int j = 0; j < maxstatesize; j ++) {
				if(transforms[in][j] == 'o') {
					newmove = j;
				}	
			}
			int movenum = check_movenum(states[i]);
			if(result == 0) {
				if(movenum == 8) {
					spebs[index][newmove] -= 1;
				} else if (movenum == 6) {
					spebs[index][newmove] -= 1;
				} else if (movenum == 4) {
					spebs[index][newmove] -= 1;
				} else {
					spebs[index][newmove] -= 1;
				}
			} else if(result == 1) {
				if(movenum == 8) {
					spebs[index][newmove] += 3;
				} else if (movenum == 6) {
					spebs[index][newmove] += 3;
				} else if (movenum == 4) {
					spebs[index][newmove] += 3;
				} else {
					spebs[index][newmove] += 3;
				}
			} else if(result == 2) {
				if(movenum == 8) {
					spebs[index][newmove] += 1;
				} else if (movenum == 6) {
					spebs[index][newmove] += 1;
				} else if (movenum == 4) {
					spebs[index][newmove] += 1;
				} else {
					spebs[index][newmove] += 1;
				}
			}
		}
	} else if (men == 1) {
		for(int i = 0; i < states.size(); i ++) {
			int in;
			int newmove;
			string state;
			int index = check_index(states[i],'x');
			vector <string> transforms = transform(states[i]);
			transforms.push_back(states[i]);
			for(int j = 0; j < transforms.size(); j ++) {
				if(transforms[j] == fstates[index]) {
					in = j;
				}
			}
			for(int j = 0; j < maxstatesize; j ++) {
				if(j == moves[i]) {
					state+= 'x';
				} else {
					state+= '-';
				}
			}
			transforms = transform(state);
			transforms.push_back(state);
			for(int j = 0; j < maxstatesize; j ++) {
				if(transforms[in][j] == 'x') {
					newmove = j;
				}	
			}
			int movenum = check_movenum(states[i]);
			if(result == 0) {
				if(movenum == 9) {
					fpebs[index][newmove] -= 1;
				} else if (movenum == 7) {
					fpebs[index][newmove] -= 1;
				} else if (movenum == 5) {
					fpebs[index][newmove] -= 2;
				} else if (movenum == 3) {
					fpebs[index][newmove] -= 3;
				}
			} else if(result == 1) {
				if(movenum == 9) {
					fpebs[index][newmove] +=1;
				} else if (movenum == 7) {
					fpebs[index][newmove] +=1;
				} else if (movenum == 5) {
					fpebs[index][newmove] +=2;
				} else if (movenum == 3) {
					fpebs[index][newmove] +=3;
				}
			} else if(result == 2) {
				if(movenum == 9) {
					fpebs[index][newmove] +=1;
				} else if (movenum == 7) {
					fpebs[index][newmove] +=1;
				} else if (movenum == 5) {
					fpebs[index][newmove] +=1;
				} else if (movenum == 3) {
					fpebs[index][newmove] +=1;
				}
			}
		}
	}
}



//Player and AI Moves
int user_move(cell cells[],char x) {
	string decision;
	string::size_type sz;
	int decisionint;
	int size = check_movenum(cells);
	while (0 == 0) {
		cout << "1-9 :";
		getline(cin, decision);
		try {
			decisionint = stoi(decision,&sz);
		} catch (invalid_argument&) {
			//Do nothing, just catch teh error.
		}
		if ((cells[decisionint-1].get_cross() == 0) && (cells[decisionint-1].get_naught() == 0)) {
			if (x == 'x') {
				return decisionint-1;
			} else {
				return decisionint-1;
			}
		} else {
			cout << "Please Choose A Valid Move" << endl;
		}
	}
};

int men_move(string s,char x) {
	int index;
	vector <int> total;
	vector <int> movelist;
	vector <string> transforms;
	int size = check_movenum(s);
	if(size == 1) {
		for(int i = 0; i < maxstatesize; i ++) {
			if (s[i] == '-') {
				return i;
			}
		}
	} else {
		if(x == 'x') {
			index = check_index(s,x);
			int t = 0;
			for (int i = 0; i < maxstatesize; i++) {
				if(fpebs[index][i] > 0) {
					t = t + fpebs[index][i];
					total.push_back(t);
					movelist.push_back(i);
				}
			}
			if(t == 0) {
				for(int i = 0; i < maxstatesize; i ++) {
					if (s[i] == '-') {
						return i;
					}
				}
			}
			transforms = transform(fstates[index]);
			transforms.push_back(fstates[index]);
			/*for(int i = 0; i < movelist.size(); i ++) {
				cout << fpebs[index][movelist[i]];
			}
			cout << endl;*/
			int in = 0;
			for(int i = 0; i < transforms.size(); i ++) {
				if(s == transforms[i]) {
					in = i;
				}
			}
			int chance = rand() %t;
			string temp = "---------";
			for(int i = 0; i < total.size(); i ++) {
				if(i == 0) {
					if((chance >= 0) && (chance < total[i])) {
						if(in == 7) {
							return movelist[i];
						} else {
							temp[movelist[i]] = 'x';
							transforms = transform(temp);
							for(int j = 0; j < maxstatesize; j++) {
								if(transforms[in][j] == 'x') {
									return j;
								}
							}
						}
					}
				} else {
					if ((chance >= total[i-1]) && (chance < total[i])) {
						if(in == 7) {
							return movelist[i];
						} else {
							temp[movelist[i]] = 'x';
							transforms = transform(temp);
							for(int j = 0; j < maxstatesize; j++) {
								if(transforms[in][j] == 'x') {
									return j;
								}
							}
						}
					}
				}
			}
		} else if (x == 'o'){
			index = check_index(s,x);
			int t = 0;
			for (int i = 0; i < maxstatesize; i++) {
				if(spebs[index][i] > 0) {
					t = t + spebs[index][i];
					total.push_back(t);
					movelist.push_back(i);
				}
			}
			if(t == 0) {
				for(int i = 0; i < maxstatesize; i ++) {
					if (s[i] == '-') {
						return i;
					}
				}
			}
			transforms = transform(sstates[index]);
			transforms.push_back(sstates[index]);
			/*for(int i = 0; i < movelist.size(); i ++) {
				cout << spebs[index][movelist[i]];
			}
			cout << endl;*/
			int in = 0;
			for(int i = 0; i < transforms.size(); i ++) {
				if(s == transforms[i]) {
					in = i;
				}
			}
			int chance = rand() %t;
			string temp = "---------";
			for(int i = 0; i < total.size(); i ++) {
				if(i == 0) {
					if((chance >= 0) && (chance < total[i])) {
						if(in == 7) {
							return movelist[i];
						} else {
							temp[movelist[i]] = 'o';
							transforms = transform(temp);
							for(int j = 0; j < maxstatesize; j++) {
								if(transforms[in][j] == 'o') {
									return j;
								}
							}
						}
					}
				} else {
					if ((chance >= total[i-1]) && (chance < total[i])) {
						if(in == 7) {
							return movelist[i];
						} else {
							temp[movelist[i]] = 'o';
							transforms = transform(temp);
							for(int j = 0; j < maxstatesize; j++) {
								if(transforms[in][j] == 'o') {
									return j;
								}
							}
						}
					}
				}
			}
		}
	}
} 

int perf_move(cell cells[],char x) {
	bool movemade = false;
	while(movemade == false) {
		if(x == 'x') {
			// Go for the win
			int move = detect_win(cells,'x');
			if((move > -1) && (move < 9)) {
				return move;
			}
			// Block
			move = detect_win(cells,'o');
			if((move > -1) && (move < 9)) {
				return move;
			}
			while(movemade == false) {
				int tactic = rand() %1;
				if(tactic == 0) {
					if(check_movenum(cells) == 9) {
						return 4;
					}
					if(check_movenum(cells) == 7) {
						if(cells[1].get_naught() == 1) {
							return 6;
						} else if(cells[3].get_naught() == 1) {
							return 8;
						} else if(cells[5].get_naught() == 1) {
							return 0;
						} else if(cells[7].get_naught() == 1) {
							return 2;
						} else if(cells[0].get_naught() == 1) {
							return 8;
						} else if(cells[2].get_naught() == 1) {
							return 6;
						} else if(cells[6].get_naught() == 1) {
							return 2;
						} else if(cells[8].get_naught() == 1) {
							return 0;
						}
					}
					if(check_movenum(cells) == 5) {
						if(cells[1].get_naught() == 1) {
							if(cells[0].get_cross() == 1) {
								return 6;
							} else if(cells[2].get_cross() == 1) {
								return 8;
							}
						} else if(cells[3].get_naught() == 1) {
							if(cells[0].get_cross() == 1) {
								return 2;
							} else if(cells[6].get_cross() == 1) {
								return 8;
							}
						} else if(cells[5].get_naught() == 1) {
							if(cells[2].get_cross() == 1) {
								return 0;
							} else if(cells[8].get_cross() == 1) {
								return 6;
							}
						} else if(cells[7].get_naught() == 1) {
							if(cells[6].get_cross() == 1) {
								return 0;
							} else if(cells[8].get_cross() == 1) {
								return 2;
							}
						}
					}
					vector <int> moves;
					for(int i = 0; i < maxstatesize; i ++) {
						if((cells[i].get_cross() == 0) && cells[i].get_naught() == 0) {
							moves.push_back(i);
						}
					}
					move = rand() % moves.size();
					return moves[move];
				} else if(tactic == 1) {
					if(check_movenum(cells) == 9) {
						move = rand() % 4;
						if(move == 1) {
							return 0;
						} else if(move == 2) {
							return 2;
						} else if(move == 3) {
							return 6;
						} else if(move == 4) {
							return 8;
						}
					} else if(check_movenum(cells) == 7) {
						if(cells[0].get_cross() == 1) {
							if(cells[2].get_naught() == 1 || cells[1].get_naught() == 1) {
								return 6;
							} else if(cells[4].get_naught() == 1) {
								return 8;
							} else {
								return 2;
							}
						} else if(cells[2].get_cross() == 1) {
							if(cells[0].get_naught() == 1 || cells[1].get_naught() == 1) {
								return 8;
							} else if(cells[4].get_naught() == 1) {
								return 6;
							} else {
								return 0;
							}
						} else if(cells[6].get_cross() == 1) {
							if(cells[8].get_naught() == 1 || cells[7].get_naught() == 1) {
								return 0;
							} else if(cells[4].get_naught() == 1) {
								return 2;
							} else {
								return 8;
							}
						} else if(cells[8].get_cross() == 1) {
							if(cells[6].get_naught() == 1 || cells[7].get_naught() == 1) {
								return 2;
							} else if(cells[4].get_naught() == 1) {
								return 0;
							} else {
								return 6;
							}
						}
					} else if(check_movenum(cells) == 5) {
						if((cells[0].get_naught() == 1) || (cells[2].get_naught() == 1) || (cells[6].get_naught() == 1) || (cells[8].get_naught() == 1)) {
							for(int i = 0; i < maxstatesize; i = i+2) {
								if((cells[i].get_cross() == 0) && (cells[i].get_naught() == 0) && (i != 4)) {
									return i;
								}
							}
						} else if((cells[1].get_naught() == 1) && (cells[3].get_naught() == 1)) {
							return 8;
						} else if((cells[1].get_naught() == 1) && (cells[5].get_naught() == 1)) {
							return 6;
						} else if((cells[3].get_naught() == 1) && (cells[7].get_naught() == 1)) {
							return 2;
						} else if((cells[5].get_naught() == 1) && (cells[7].get_naught() == 1)) {
							return 0;
						}
					}
					vector <int> moves;
					for(int i = 0; i < maxstatesize; i ++) {
						if((cells[i].get_cross() == 0) && cells[i].get_naught() == 0) {
							moves.push_back(i);
						}
					}
					move = rand() % moves.size();
					if((cells[moves[move]].get_cross() == 0) && (cells[moves[move]].get_naught() == 0)) {
						return moves[move];
					}
				}
			}
		} else if(x == 'o') {
			// Go for the win
			int move = detect_win(cells,'o');
			if((move > -1) && (move < 9)) {
				return move;
			}
			// Block
			move = detect_win(cells,'x');
			if((move > -1) && (move < 9)) {
				return move;
			}
			while(movemade == false) {
				if(check_movenum(cells) == 8) {
					if(cells[4].get_cross() == 1) {
						move = rand() % 3;
						if(move == 0) {
							return 0;
						} else if(move == 1) {
							return 2;
						} else if(move == 2) {
							return 6;
						} else if(move == 3) {
							return 8;
						}
					} else {
						return 4;
					}
				} else if (check_movenum(cells) == 6) {
					if(cells[4].get_cross() == 1) {
						if((cells[0].get_cross() == 0) && (cells[0].get_naught() == 0)) {
							return 0;
						} else if ((cells[2].get_cross() == 0) && (cells[2].get_naught() == 0)) {
							return 2;
						} else if ((cells[6].get_cross() == 0) && (cells[6].get_naught() == 0)) {
							return 6;
						} else if ((cells[8].get_cross() == 0) && (cells[8].get_naught() == 0)) {
							return 8;
						}
					} else if(cells[4].get_naught() == 1) {
						if((cells[1].get_cross() == 0) && (cells[7].get_cross() == 0)) {
							return 1;
						} else if((cells[3].get_cross() == 0) && (cells[5].get_cross() == 0)) {
							return 3;
						} else if((cells[5].get_cross() == 0) && (cells[3].get_cross() == 0)) {
							return 5;
						} else if((cells[7].get_cross() == 0) && (cells[1].get_cross() == 0)) {
							return 7;
						} else {
							if((cells[1].get_cross() == 1) && (cells[3].get_cross() == 1)) {
								return 0;
							} else if((cells[1].get_cross() == 1) && (cells[5].get_cross() == 1)) {
								return 2;
							} else if((cells[7].get_cross() == 1) && (cells[3].get_cross() == 1)) {
								return 6;
							} else if((cells[7].get_cross() == 1) && (cells[5].get_cross() == 1)) {
								return 8;
							}
						}
					} else {
						if(cells[0].get_naught() == 1) {
							return 1;
						} else if(cells[2].get_naught() == 1) {
							return 1;
						} else if(cells[6].get_naught() == 1) {
							return 7;
						} else if(cells[8].get_naught() == 1) {
							return 7;
						}
					}
				} else if(check_movenum(cells) == 4) {
					if((cells[1].get_cross() == 1) && (cells[3].get_cross() == 1) && (cells[0].get_cross() == 0) && (cells[0].get_naught() == 0)) {
						return 0;
					} else if((cells[1].get_cross() == 1) && (cells[5].get_cross() == 1) && (cells[2].get_cross() == 0) && (cells[2].get_naught() == 0)) {
						return 2;
					} else if((cells[7].get_cross() == 1) && (cells[3].get_cross() == 1) && (cells[6].get_cross() == 0) && (cells[6].get_naught() == 0)) {
						return 6;
					} else if((cells[7].get_cross() == 1) && (cells[5].get_cross() == 1) && (cells[8].get_cross() == 0) && (cells[8].get_naught() == 0)) {
						return 8;
					}
				}
				vector <int> moves;
				for(int i = 0; i < maxstatesize; i ++) {
					if((cells[i].get_cross() == 0) && cells[i].get_naught() == 0) {
						moves.push_back(i);
					}
				}
				move = rand() % moves.size();
				if((cells[moves[move]].get_cross() == 0) && (cells[moves[move]].get_naught() == 0)) {
					return moves[move];
				}
			}
		}
	}
}

int log_move(cell cells[],char x) {
	bool movemade = false;
	while(movemade == false) {
		if(x == 'x') {
			// Go for the win
			int move = detect_win(cells,'x');
			if((move > -1) && (move < 9)) {
				return move;
			}
			// Block
			move = detect_win(cells,'o');
			if((move > -1) && (move < 9)) {
				return move;
			}
			while(movemade == false) {
				move = rand() %9;
				if((cells[move].get_cross() == 0) && (cells[move].get_naught() == 0)) {
					return move;
				}
			}
		} else if(x == 'o') {
			// Go for the win
			int move = detect_win(cells,'o');
			if((move > -1) && (move < 9)) {
				return move;
			}
			// Block
			move = detect_win(cells,'x');
			if((move > -1) && (move < 9)) {
				return move;
			}
			while(movemade == false) {
				move = rand() %9;
				if((cells[move].get_cross() == 0) && (cells[move].get_naught() == 0)) {
					return move;
				}
			}
		}
	}
}

int rand_move(cell cells[]) {
	bool movemade = false;
	while(movemade == false) {
		int r = rand() %9;
		if((cells[r].get_cross() == 0) && (cells[r].get_naught() == 0)) {
			return r;
			movemade = true;
		}
	}
}


//Main Game Functions
int game(string p1, string p2) {
	vector <int> menmoves;
	vector <string> menstates;
	cell cells[9];
	for(int i = 0; i < 9; i++) {
		if((i == 0) || (i == 2) || (i == 4) || (i == 6) || (i == 8)) {
			int move;
			if(p1 == "Menace") {
				string state;
				for(int j = 0; j< maxstatesize; j ++) {
					if(cells[j].get_cross() == true) {
						state += 'x';
					} else if(cells[j].get_naught() == true) {
						state += 'o';
					} else {
						state += '-';
					}
				}
				while(0 == 0) {
					move = men_move(state,'x');
					if((cells[move].get_cross() == 0) && (cells[move].get_naught() == 0)) {
						break;
					}
				}
				cells[move].set_cross();
				menmoves.push_back(move);
				menstates.push_back(state);
				print_grid(cells);
			} else if(p1 == "Perfect") {
				move = perf_move(cells,'x');
				cells[move].set_cross();
				print_grid(cells);
			} else if(p1 == "Logical") {
				move = log_move(cells,'x');
				cells[move].set_cross();
				print_grid(cells);
			} else if(p1 == "Random") {
				move = rand_move(cells);
				cells[move].set_cross();
				print_grid(cells);
			} else if(p1 == "Player") {
				if(i == 0) {
					cin.ignore();
				}
				move = user_move(cells,'x');
				cells[move].set_cross();
				print_grid(cells);
			}
		} else {
			int move;
			if(p2 == "Menace") {
				string state;
				for(int j = 0; j < maxstatesize; j ++) {
					if(cells[j].get_cross() == true) {
						state += 'x';
					} else if(cells[j].get_naught() == true) {
						state += 'o';
					} else {
						state += '-';
					}
				}
				while(0 == 0) {
					move = men_move(state,'o');
					if((cells[move].get_cross() == 0) && (cells[move].get_naught() == 0)) {
						break;
					}
				}
				cells[move].set_naught();
				menmoves.push_back(move);
				menstates.push_back(state);
				print_grid(cells);
			} else if(p2 == "Perfect") {
				move = perf_move(cells,'o');
				cells[move].set_naught();
				print_grid(cells);
			} else if(p2 == "Logical") {
				move = log_move(cells,'o');
				cells[move].set_naught();
				print_grid(cells);
			} else if(p2 == "Random") {
				move = rand_move(cells);
				cells[move].set_naught();
				print_grid(cells);
			} else if(p2 == "Player") {
				if(i == 1) {
					cin.ignore();
				}
				move = user_move(cells,'o');
				cells[move].set_naught();
				print_grid(cells);
			}
		}
		if(check_game(cells) == -1) {
			cout << p1 << " Wins!" << endl;
			if(p1 == "Menace") {
				adjust_pebs(menmoves,menstates,1,1);
			} else if(p2 == "Menace") {
				adjust_pebs(menmoves,menstates,0,2);
			}
			return 1;
		} else if(check_game(cells) == -2) {
			cout << p2 << " Wins!" << endl;
			if(p2 == "Menace") {
				adjust_pebs(menmoves,menstates,1,2);
			} else if(p1 == "Menace") {
				adjust_pebs(menmoves,menstates,0,1);
			}
			return 2;
		} else if(check_game(cells) == -3) {
			cout << "It's a Draw!" << endl;
			if(p1 == "Menace") {
				adjust_pebs(menmoves,menstates,2,1);
			} else if(p2 == "Menace") {
				adjust_pebs(menmoves,menstates,2,2);
			}
			return 3;
		}
	}
}

void auto_play(int player) {
	int response;
	int win = 0;
	int draw = 0;
	cout << "How Many Games do you want to auto play?" << endl;
	cin >> response;
	if(player == 1) {
		for(int i = 0; i < response; i ++) {
			int r = rand() %100;
			int temp;
			if(r < 50) {
				cout << "Menace Goes First" << endl;
				temp = game("Menace","Perfect");
				if(temp == 1) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			} else {
				cout << "Perfect Goes First" << endl;
				temp = game("Perfect","Menace");
				if(temp == 2) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			}
			remove_minus();
		}
	} else if(player == 2) {
		for(int i = 0; i < response; i ++) {
			int r = rand() %100;
			int temp;
			if(r < 50) {
				cout << "Menace Goes First" << endl;
				temp = game("Menace","Logical");
				if(temp == 1) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			} else {
				cout << "Logical Goes First" << endl;
				temp = game("Logical","Menace");
				if(temp == 2) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			}
			remove_minus();
		}
	} else if(player == 3) {
		for(int i = 0; i < response; i ++) {
			int r = rand() %100;
			int temp;
			if(r < 50) {
				cout << "Menace Goes First" << endl;
				temp = game("Menace","Random");
				if(temp == 1) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			} else {
				cout << "Random Goes First" << endl;
				temp = game("Random","Menace");
				if(temp == 2) {
					win++;
				} else if(temp == 3) {
					draw++;
				}
			}
			remove_minus();
		}
	}
	cout << "A Total of " << response << " games were played" << endl;
	cout << "Menace Won - " << win << " games, and Drew - " << draw << " games" << endl;
	save_files();
}

int main() {
	srand(time(0));
	load_files();
	while(0 == 0) {
		print_menu(1);
		int response;
		cin >> response;
		if(response == 1) {
			print_menu(2);
			while (0 == 0) {
				int response2;
				cin >> response2;
				if(response2 == 1) {
					auto_play(1);
					break;
				} else if (response2 == 2) {
					auto_play(2);
					break;
				} else if (response2 == 3) {
					auto_play(3);
					break;
				} else if(response2 == 4) {
					break;
				} else {
					cout << "Please Enter A Valid Response" << endl;
				}
			}
		} else if (response == 2) {
			int r = rand() %100;
			if(r < 50) {
				cout << "Menace Goes First" << endl;
				game("Menace","Player");
			} else {
				cout << "Player Goes First" << endl;
				game("Player","Menace");
			}
		} else if (response == 3) {
			print_menu(2);
			while (0 == 0) {
				int response2;
				cin >> response2;
				if(response2 == 1) {
					//int r = rand() %100;
					int r = 51;
					if(r < 50) {
						cout << "Perfect Player Goes First" << endl;
						game("Perfect","Player");
					} else {
						cout << "Player Goes First" << endl;
						game("Player","Perfect");
					}
					break;
				} else if (response2 == 2) {
					int r = rand() %100;
					if(r < 50) {
						cout << "Logical Player Goes First" << endl;
						game("Logical","Player");
					} else {
						cout << "Player Goes First" << endl;
						game("Player","Logical");
					}
					break;
				} else if (response2 == 3) {
					int r = rand() %100;
					if(r < 50) {
						cout << "Random Goes First" << endl;
						game("Random","Player");
					} else {
						cout << "Player Goes First" << endl;
						game("Player","Random");
					}
					break;
				} else if(response2 == 4) {
					break;
				} else {
					cout << "Please Enter A Valid Response" << endl;
					print_menu(1);
				}
			}
		} else if (response == 4) {
			save_files();
			break;
		} else if (response == 5) {
			print_states();
		} else {
			cout << "Please Enter A Valid Response" << endl;
		}
	}
}