#include <iostream>
#include <vector>
#include "file.h"

using namespace std;

class ITape {
public:
	void virtual makeTape(void) = 0;
	void virtual sortTape(void) = 0;	
};


class Tape : public ITape {
private:
	vector<int> tape;
	string input_path;
	string output_path;
	
	string config_path = "./configFile.txt";
	
	size_t N;
	size_t M;
public:
	Tape(void) = default;

	void makeTape(void) override;
	void sortTape(void) override;	
	void setupPaths(void);
	void rewriteConfig(void);
	void readConfig(void);
};
