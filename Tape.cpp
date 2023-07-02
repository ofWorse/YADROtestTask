#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <type_traits>
#include <vector>
#include "Tape.h"
#include "inputProtection.h"


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
	if(consistPaths()) {
		writeDataToFile(input_path, this->N);
		this->tape = writeDataToVector(this->input_path);
		cout << "Данные в файл " << input_path << " успешно загружены." << endl;
	}
	else {
		cout << "Для начала, введите путь к исходным файлам!" << endl;
		return;
	}
}

void Tape::sortEveryFile(void) {
}

// 20, 2. 10 векторов.
void Tape::splitVectorsAndSort(void) {
	int count = (this->tape.size()) / this->M;
	vector<int> tmpTape, copyTape = this->tape;
	for(int i = 1; i <= count; i++) {
		for(int j = 0; j < this->M; j++) {
			tmpTape.push_back(copyTape.front());
			copyTape.erase(copyTape.begin());
		}
		writeVectorToFile(tmpTape, this->tmp_dir_path + "tmp" + to_string(i) + ".txt");
		tmpTape.clear();
	}
	if(!copyTape.empty()) {
		for(const auto &num : copyTape) tmpTape.push_back(num);
		writeVectorToFile(tmpTape, this->tmp_dir_path + "tmpLast.txt");
		tmpTape.clear();
	}
	// TODO: Далее требуется отсортировать tmp файлы.
	sortEveryFile();	
}

void Tape::sortTape(void) {
	cout << " Начало сортировки..." << endl;

	if(this->tape.size() > this->M) { //TODO: переделать
		splitVectorsAndSort();	
	}	
	else {
		sort(this->tape.begin(), this->tape.end());
		writeVectorToFile(this->tape, this->output_path);
	}

	cout << " Конец сортировки." << endl;
	cout << " Отсортированная лента записана в файл: " << this->output_path << endl;
}

void Tape::shiftLeft(void) {
	//this->shift_step %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.rbegin(), tape.rbegin() + shift_step, tape.rend());
}

void Tape::shiftRight(void) {
	//shift_amount %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.begin(), tape.begin() + shift_step, tape.end());
}

void Tape::moveData(bool right) {
	right ? shiftRight() : shiftLeft();
	writeVectorToFile(this->tape, this->input_path);	
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
	if(params.size() >= 5) {
		this->N = params.at(0);
		this->M = params.at(1);
		this->recording_delay = params.at(2);
		this->tape_rewinding = params.at(3);
		this->shift_step = params.at(4);
	}
	config.close();
}

bool Tape::consistPaths(void) {
	return !(this->input_path.empty() || this->output_path.empty());
}
