#include <fstream>
#include <iostream>
#include <vector>
#include "file.h"

using namespace std;

class Tape {
private:
	vector<int> tape;
	string input_path;
	string output_path;
	
	string config_path = "./configFile.txt";
	
	size_t N;
	size_t M;
public:
	Tape(void) = default;

	void readConfig(void);
	void setupPaths(void);
	void makeTape(void);
	void sortTape(void);	
};
