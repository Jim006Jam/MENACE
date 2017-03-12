#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;
int maxstatesize = 9;
vector <string> fstates;
vector <string> sstates;
vector <vector<int>> fpebs;
vector <vector<int>> spebs;
vector <int> stats;

bool check_win(string s) {
	if(((s[0] == 'x') && (s[1] == 'x') && (s[2] == 'x')) || ((s[0] == 'o') && (s[1] == 'o') && (s[2] == 'o'))) {
		return true;
	}
	else if(((s[3] == 'x') && (s[4] == 'x') && (s[5] == 'x')) || ((s[3] == 'o') && (s[4] == 'o') && (s[5] == 'o'))) {
		return true;
	}
	else if(((s[6] == 'x') && (s[7] == 'x') && (s[8] == 'x')) || ((s[6] == 'o') && (s[7] == 'o') && (s[8] == 'o'))) {
		return true;
	}
	else if(((s[0] == 'x') && (s[4] == 'x') && (s[8] == 'x')) || ((s[0] == 'o') && (s[4] == 'o') && (s[8] == 'o'))) {
		return true;
	}
	else if(((s[2] == 'x') && (s[4] == 'x') && (s[6] == 'x')) || ((s[2] == 'o') && (s[4] == 'o') && (s[6] == 'o'))) {
		return true;
	}
	else if(((s[0] == 'x') && (s[3] == 'x') && (s[6] == 'x')) || ((s[0] == 'o') && (s[3] == 'o') && (s[6] == 'o'))) {
		return true;
	}
	else if(((s[1] == 'x') && (s[4] == 'x') && (s[7] == 'x')) || ((s[1] == 'o') && (s[4] == 'o') && (s[7] == 'o'))) {
		return true;
	}
	else if(((s[2] == 'x') && (s[5] == 'x') && (s[8] == 'x')) || ((s[2] == 'o') && (s[5] == 'o') && (s[8] == 'o'))) {
		return true;
	} else {
		return false;
	}
}

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

void generate_states() {
	char state[maxstatesize];
	//empty
	string s;
	for(int i = 0; i < maxstatesize; i++) {
		s += '-';
	}
	fstates.push_back(s);
	
	//first move
	for(int i = 0; i < maxstatesize; i ++) {
		for(int j = 0; j < maxstatesize; j ++) {
			state[j] = '-';
		}
		state[i] = 'x';
		string str;
		for(int c = 0; c < maxstatesize; c++) {
			str+=state[c];
		}
		sstates.push_back(str);
	}
	
	// second move
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for(int k = 0; k < maxstatesize; k ++) {
				state[k] = '-';
			}
			state[i] = 'x';
			state[j] = 'o';
			int a = 0;
			for(int k = 0; k < maxstatesize; k++) {
				if(state[k] == 'x' || state[k] == 'o') {
					a++;
				}
			}
			if (a == 2) {
				string str;
				for(int c = 0; c < maxstatesize; c++) {
					str+=state[c];
				}
				fstates.push_back(str);
			}
		}
	}
	
	//third move
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for(int l = 0; l < maxstatesize; l ++) {
					state[l] = '-';
				}
				state[i] = 'x';
				state[j] = 'o';
				state[k] = 'x';
				int a = 0;
				for(int l = 0; l < maxstatesize; l++) {
					if(state[l] == 'x' || state[l] == 'o') {
						a++;
					}
				}
				if (a == 3) {
					string str;
					for(int c = 0; c < maxstatesize; c++) {
						str+=state[c];
					}
					sstates.push_back(str);
				}
			}
		}
	}

	//fourth move
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for(int l = 0; l < maxstatesize; l ++) {
					for(int m = 0; m < maxstatesize; m ++) {
						state[m] = '-';
					}
					state[i] = 'x';
					state[j] = 'o';
					state[k] = 'x';
					state[l] = 'o';
					int a = 0;
					for(int m = 0; m < maxstatesize; m++) {
						if(state[m] == 'x' || state[m] == 'o') {
							a++;
						}
					}
					if (a == 4) {
						string str;
						for(int c = 0; c < maxstatesize; c++) {
							str+=state[c];
						}
						fstates.push_back(str);
					}
				}
			}
		}
	}
	
	//fifth move
	for (int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for (int l = 0; l < maxstatesize; l ++) {
					for (int m = 0; m < maxstatesize; m ++) {
						for (int n = 0; n < maxstatesize; n ++) {
							state[n] = '-';
						}
						state[i] = 'x';
						state[j] = 'o';
						state[k] = 'x';
						state[l] = 'o';
						state[m] = 'x';
						int a = 0;
						for(int n = 0; n < maxstatesize; n++) {
							if(state[n] == 'x' || state[n] == 'o') {
								a++;
							}
						}
						if (a == 5) {
							string str;
							for(int c = 0; c < maxstatesize; c++) {
								str+=state[c];
							}
							sstates.push_back(str);
						}
					}
				}
			}
		}
	}
	
	//sixth move
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for(int l = 0; l < maxstatesize; l ++) {
					for(int m = 0; m < maxstatesize; m ++) {
						for(int n = 0; n < maxstatesize; n ++) {
							for(int o = 0; o < maxstatesize; o ++) {
								state[o] = '-';
							}
							state[i] = 'x';
							state[j] = 'o';
							state[k] = 'x';
							state[l] = 'o';
							state[m] = 'x';
							state[n] = 'o';
							int a = 0;
							for(int o = 0; o < maxstatesize; o++) {
								if(state[o] == 'x' || state[o] == 'o') {
									a++;
								}
							}
							if (a == 6) {
								string str;
								for(int c = 0; c < maxstatesize; c++) {
									str+=state[c];
								}
								fstates.push_back(str);
							}
						}
					}
				}
			}
		}
	}
	
	//seventh move
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for(int l = 0; l < maxstatesize; l ++) {
					for(int m = 0; m < maxstatesize; m ++) {
						for(int n = 0; n < maxstatesize; n ++) {
							for(int o = 0; o < maxstatesize; o ++) {
								for(int p = 0; p < maxstatesize; p ++) {
									state[p] = '-';
								}
								state[i] = 'x';
								state[j] = 'o';
								state[k] = 'x';
								state[l] = 'o';
								state[m] = 'x';
								state[n] = 'o';
								state[o] = 'x';
								int a = 0;
								for(int p = 0; p < maxstatesize; p++) {
									if(state[p] == 'x' || state[p] == 'o') {
										a++;
									}
								}
								if (a == 7) {
									string str;
									for(int c = 0; c < maxstatesize; c++) {
										str+=state[c];
									}
									sstates.push_back(str);
								}
							}
						}
					}
				}
			}
		}
	}
	/*
	//eigth move (only required for possible seventh moves)
	fstates = fstates;
	for(int i = 0; i < maxstatesize; i ++) {
		for (int j = 0; j < maxstatesize; j ++) {
			for (int k = 0; k < maxstatesize; k ++) {
				for(int l = 0; l < maxstatesize; l ++) {
					for(int m = 0; m < maxstatesize; m ++) {
						for(int n = 0; n < maxstatesize; n ++) {
							for(int o = 0; o < maxstatesize; o ++) {
								for(int p = 0; p < maxstatesize; p ++) {
									for(int q = 0; q < maxstatesize; q ++) {
										state[q] = '-';
									}
									state[i] = 'x';
									state[j] = 'o';
									state[k] = 'x';
									state[l] = 'o';
									state[m] = 'x';
									state[n] = 'o';
									state[o] = 'x';
									state[p] = 'o';
									int a = 0;
									for(int q = 0; q < maxstatesize; q++) {
										if(state[q] == 'x' || state[q] == 'o') {
											a++;
										}
									}
									if (a == 8) {
										string str;
										for(int c = 0; c < maxstatesize; c++) {
											str+=state[c];
										}
										fstates.push_back(str);
									}
								}
							}
						}
					}
				}
			}
		}
	}*/
	cout << "States Generated" << endl;
	stats.push_back(fstates.size());
	stats.push_back(sstates.size());
}

void generate_pebs() {
	for(int i = 0; i < fstates.size(); i ++) {
		vector <int> vec;
		vector <string> transforms;
		vec.assign(9,0);
		transforms = transform(fstates[i]);
		transforms.push_back(fstates[i]);
		for(int j = 0; j < sstates.size(); j++) {
			int movenum = check_movenum(sstates[j]);
			for(int k = 0; k < transforms.size(); k ++) {
				int movenum2 = check_movenum(transforms[k]);
				vector <int> pos;
				for (int l = 0; l < maxstatesize; l ++) {
					if(movenum == movenum2-1) {
						if((transforms[k][l] != sstates[j][l]) && (fstates[i][l] == '-')) {
							pos.push_back(l);
						}
					}
				}
				if(pos.size() == 1) {
					if(movenum2 == 9) {
						vec[pos[0]] = 4;
					} else if(movenum2 == 7) {
						vec[pos[0]] = 3;
					} else if(movenum2 == 5) {
						vec[pos[0]] = 2;
					} else if(movenum2 == 3) {
						vec[pos[0]] = 1;
					}
				}
			}
		}
		fpebs.push_back(vec);
	}
	
	for(int i = 0; i < sstates.size(); i ++) {
		int t = 0;
		int movenum = check_movenum(sstates[i]);
		vector <int> vec;
		vec.assign(9,0);
		if(movenum != 2) {
			vector <string> transforms;
			transforms = transform(sstates[i]);
			transforms.push_back(sstates[i]);
			for(int j = 0; j < fstates.size(); j++) {
				int movenum2 = check_movenum(fstates[j]);
				for(int k = 0; k < transforms.size(); k ++) {
					int movenum3 = check_movenum(transforms[k]);
					vector <int> pos;
					for (int l = 0; l < maxstatesize; l ++) {
						if(movenum2 == movenum3-1) {
							if((transforms[k][l] != fstates[j][l]) && (sstates[i][l] == '-')) {
								pos.push_back(l);
							}
						}
					}
					if(pos.size() == 1) {
						if(movenum3 == 8) {
							vec[pos[0]] = 4;
						} else if(movenum3 == 6) {
							vec[pos[0]] = 3;
						} else if(movenum3 == 4) {
							vec[pos[0]] = 2;
						}
					}
				}
			}
		} else {
			for (int j = 0; j < maxstatesize; j++) {
				if(sstates[i][j] == '-') {
					vec[j] = 1;
				}
			}
		}
		spebs.push_back(vec);
	}
	cout << "Pebs Generated" << endl;
}

void remove_winstates() {
	for (int i = 0; i < fstates.size(); i++) {
		if (check_win(fstates[i]) == true) {
			fstates.erase(fstates.begin()+i);
		}
	}
	for (int i = 0; i < sstates.size(); i++) {
		if (check_win(sstates[i]) == true) {
			sstates.erase(sstates.begin()+i);
		}
	}
}

void remove_dupes() {
	for(int i = 0; i < fstates.size(); i++) {
		for (int j = i; j < fstates.size(); j ++) {
			if((i != j) && (fstates[i].compare(fstates[j]) == 0)) {
				int temp = 0;
				for(int k = i; k < maxstatesize; k++) {
					if(fstates[i][k] != fstates[j][k]) {
						temp++;
					}
				}
				if(temp == 0) {
					fstates.erase(fstates.begin()+j);
				}
			}
		}
	}
	for(int i = 0; i < sstates.size(); i++) {
		for (int j = i; j < sstates.size(); j ++) {
			if((i != j) && (sstates[i].compare(sstates[j]) == 0)) {
				int temp = 0;
				for(int k = i; k < maxstatesize; k++) {
					if(sstates[i][k] != sstates[j][k]) {
						temp++;
					}
				}
				if(temp == 0) {
					sstates.erase(sstates.begin()+j);
				}
			}
		}
	}
}

void remove_transforms() {
	vector <string> transforms;
	for(int i = 0; i < fstates.size(); i++) {
		transforms = transform(fstates[i]);
		for(int j = 0; j < transforms.size(); j++) {
			for(int k = i+1; k < fstates.size(); k++) {
				if (i != k) {
					int temp = 0;
					for(int l = 0; l < maxstatesize; l++) {
						if(transforms[j][l] != fstates[k][l]) {
							temp++;
						}
					}
					if(temp == 0) {
						fstates.erase(fstates.begin()+k);
					}
				}
			}
		}
	}
	for(int i = 0; i < sstates.size(); i++) {
		transforms = transform(sstates[i]);
		for(int j = 0; j < transforms.size(); j++) {
			for(int k = i+1; k < sstates.size(); k++) {
				if (i != k) {
					int temp = 0;
					for(int l = 0; l < maxstatesize; l++) {
						if(transforms[j][l] != sstates[k][l]) {
							temp++;
						}
					}
					if(temp == 0) {
						sstates.erase(sstates.begin()+k);
					}
				}
			}
		}
	}
}

//Not needed without 8th move state generation
/*void remove_eigth() {
	for (int i = 0; i < fstates.size(); i ++ ) {
		int temp;
		for (int j = 0; j < maxstatesize; j ++) {
			if (fstates[i][j] == '-') {
				temp++;
			}
		}
		if(temp == 1) {
			fstates.erase(fstates.begin()+i);
		}
	}
}*/

void print_stats() {
	cout << "-------------Fun Facts-------------" << endl;
	cout << "After Complete Generation fstates had " << stats[0] << " states in it" << endl;
	cout << "After Complete Generation sstates had " << stats[1] << " states in it" << endl;
	cout << "After searching for Game Ending states, " << stats[2] << " and " << stats[3] << " states were removed from both state lists respectively" << endl;
	cout << "After searching for Duplicate states, " << stats[4] << " and " << stats[5] << " states were removed from both state lists respectively" << endl;
	cout << "After searching for Transformed states, " << stats[6] << " and " << stats[7] << " states were removed from both state lists respectively" << endl;
	cout << "After all that there are now " << fstates.size() << " and " << sstates.size() << " left in the two state lists respectively" << endl;
}

void write_tofile() {
	ofstream myfile;
	myfile.open ("first_player_menace.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < fstates.size(); i++) {
		myfile << fstates[i] << " ";
		for(int j = 0; j < maxstatesize; j++) {
			if (j == 8) {
				myfile << "[" << fpebs[i][j] << "]";
			} else {
				myfile << "[" << fpebs[i][j] << "]" << " ";
			}
		}if(i != 303) {
			myfile << endl;
		}
	}
	myfile.close();
	myfile.open ("second_player_menace.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < sstates.size(); i++) {
		myfile << sstates[i] << " ";
		for(int j = 0; j < maxstatesize; j++) {
			if (j == 8) {
				myfile << "[" << spebs[i][j] << "]";
			} else {
				myfile << "[" << spebs[i][j] << "]" << " ";	
			}
		}if(i != 288) {
			myfile << endl;
		}
	}
	myfile.close();
}

void write_tofile2() {
	ofstream myfile;
	myfile.open ("first_player_menace_alistair.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < fstates.size(); i++) {
		for(int j = 0; j < maxstatesize; j++) {
			if(fstates[i][j] == '-') {
				myfile << "E";
			} else if(fstates[i][j] == 'x') {
				myfile << "X";
			} else if (fstates[i][j] == 'o') {
				myfile << "O";
			}
			if(j < 8) {
				myfile << ",";
			}
		} myfile << "~";
		for(int j = 0; j < maxstatesize; j++) {
			if (j == 8) {
				myfile << fpebs[i][j];
			} else {
				myfile << fpebs[i][j] << ",";
			}
		}
		myfile << endl;
	}
	myfile.close();
	
	myfile.open ("second_player_menace_alistair.txt",std::ofstream::out | std::ofstream::trunc);
	for(int i = 0; i < sstates.size(); i++) {
		for(int j = 0; j < maxstatesize; j++) {
			if(sstates[i][j] == '-') {
				myfile << "E";
			} else if(sstates[i][j] == 'x') {
				myfile << "X";
			} else if (sstates[i][j] == 'o') {
				myfile << "O";
			}
			if(j < 8) {
				myfile << ",";
			}
		} myfile << "~";
		for(int j = 0; j < maxstatesize; j++) {
			if (j == 8) {
				myfile << spebs[i][j];
			} else {
				myfile << spebs[i][j] << ",";
			}
		}
		myfile << endl;
	}
	myfile.close();
}

int main() {
	generate_states();
	for (int i = 0; i < 5; i++) {
		remove_winstates();
	}
	stats.push_back(stats[0] - fstates.size());
	stats.push_back(stats[1] - sstates.size());
	cout << "Win States Removed" << endl;
	for(int i = 0; i < 3; i++) {
		remove_dupes();
	}
	stats.push_back(stats[0] - stats[2] - fstates.size());
	stats.push_back(stats[1] - stats[3] - sstates.size());
	cout << "Dupes Removed" << endl;
	remove_transforms();
	stats.push_back(stats[0] - stats[2] - stats[4] - fstates.size());
	stats.push_back(stats[1] - stats[3] - stats[5] - sstates.size());
	cout << "Transforms Removed" << endl;
	generate_pebs();
	print_stats();
	write_tofile();
	write_tofile2();
	cout << "Done" << endl;
}