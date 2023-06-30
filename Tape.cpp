#include "Tape.h"
#include <cstdlib>
#include <fstream>
#include <string>

void Tape::setupPaths(void) {
	cout << "Введите путь к исходной ленте." << endl;
	string path;
	nameFileProtected(path, false);
	this->input_path = path;
	cout << "Введите путь к будучи отсортированной ленте." << endl;
	nameFileProtected(path, false);
	this->output_path = path;
}

void Tape::makeTape(void) {
	srand(time(NULL));
	if(!this->input_path.empty() || !this->output_path.empty()) {
		writeDataToFile(input_path, this->N);
		cout << "Данные в файл \'" << input_path << "\' успешно загружены." << endl;
	}
	else {
		cout << "Для начала, введите путь к исходным файлам!" << endl;
		return;
	}
}

void Tape::readConfig(void) {
	ifstream config(this->config_path);
	int params[10];
	if(config) {
		string line;
		int i = 0;
		while(getline(config, line)) {
			params[i] = stoi(line);	
			i++;
		}
		config.close();
		this->N = params[0];
		this->M = params[1];
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
		return;
	}
}


