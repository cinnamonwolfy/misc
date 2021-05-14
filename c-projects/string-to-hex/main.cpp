#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, const char* argv[]){
	string argv_s[argc];

	for(int i = 0; i < argc; i++){
		argv_s[i] = argv[i];
	}

	for(int i = 1; i < argc; i++){
		for(int j = 0; j < argv_s[i].length(); j++){
			cout << hex << (int)argv_s[i][j];
		}
	}

	cout << endl;
}
