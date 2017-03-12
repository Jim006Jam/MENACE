#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;
int maxstatesize = 9;

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

int main() {
	while(0 == 0) {
		vector <string> transforms;
		string response;
		cin >> response;
		transforms = transform(response);
		transforms.push_back(response);
		for (int i = 0; i < transforms.size(); i ++) {
			cout << transforms[i] << endl;
		}
	}
}