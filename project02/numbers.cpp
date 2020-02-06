#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){

	if(argc < 3){
		cout << "USAGE: ./numbers.cpp <file> <number>\n";
		return 0;
		}

	ofstream file;
	file.open(argv[1]);

	int amount = atoi(argv[2]);
	int random;
	srand(time(NULL));

	for(int i = 0; i < amount; i++){
		random = rand();
		file << random << '\n';
	}

	file.close();

	return 0;
}
