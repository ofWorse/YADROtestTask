#include "Tape.h"
#include "inputProtection.h"
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
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

void Tape::sortTape(void) {
	return;
}

void Tape::rewriteConfig(void) {

	string str{};
	int num;
	ofstream config(this->config_path);
	cout << "Введите новые параметры для конфигурационного файла." << endl;
	cout << "Введите длину ленты N." << endl;
	inputProtection(num, 1, INT_MAX);
	str += to_string(num) + "\n";
	cout << "Введите ограничение по использованию оперативной памяти M." << endl;
	inputProtection(num, 1, num - 1);
	str += to_string(num) + "\n";
	cout << "Введите число задержки по записи/чтению элемента ленты." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";
	cout << "Введите число перемотки ленты." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";
	cout << "Введите число сдвига ленты на одну позицию." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";

	if(config) {
		config << str << endl;
	}
	else 
		cout << "Ошибка открытия файла!" << endl;
	config.close();
}

void Tape::readConfig(void) {
	ifstream config(this->config_path);
	vector<int> params;
	string line;
	while(getline(config, line)) {
		istringstream iss(line);
		string stringNumber;

		while(getline(iss, stringNumber, ' ')) {
			try {
				int number = stoi(stringNumber);
				params.push_back(number);
			} catch (const invalid_argument &e) {
				cerr << "Ошибка преобразования строки в число: " << stringNumber << "." << endl;
			}
		}
	}
	this->N = params.at(0);
	this->M = params.at(1);
}

