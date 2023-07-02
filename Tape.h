#include <cstddef>
#include <vector>
#include "file.h"

using namespace std;

class ITape {
public:
	void virtual makeTape(void) = 0;
	void virtual sortTape(void) = 0;	
	void virtual moveData(bool right) = 0;	
};


class Tape : public ITape {
private:
	vector<int> tape{};
	string input_path{};
	string output_path{};
	
	string config_path = "./configFile.txt";
	string tmp_dir_path	=  "./tmp/";

	size_t N;
	size_t M;
	int recording_delay;
	int tape_rewinding;
	int shift_step;
	
	void shiftLeft(void); 
	void shiftRight(void); 
	void splitVectorsAndSort(void);
	void sortEveryFile(int begin, int countOfFiles, vector<int> &tape);
public:
	Tape(void) = default;

	void makeTape(void) override;
	void sortTape(void) override;	
	void moveData(bool right) override;	
	void setupPaths(void);
	void rewriteConfig(void);
	void readConfig(void);

	bool consistPaths(void);

	vector<int> getTape(void) {return tape;};
};
