#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <type_traits>
#include <iomanip>
#include <limits>
#include <queue>
#include <utility>
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


void Tape::splitVectorsAndSort(void) {
	ifstream input(this->input_path);
	if(!input) {
		cerr << "Невозможно открыть файл!" << endl;
		return;
	}

	vector<int> buffer;
	string tempFileName = "tmp";
	int tempFileCount = 0;

	while(!input.eof()) {
		buffer.clear();
		size_t bytesRead = 0;
		while(bytesRead < this->M && !input.eof()) {
			int num;
			input >> num;
			buffer.push_back(num);
			bytesRead += sizeof(int);
		}

		sort(buffer.begin(), buffer.end());

		ofstream tempFile(this->tmp_dir_path + tempFileName + to_string(tempFileCount++) + ".txt");
		if(!tempFile) {
			cerr << "Невозможно открыть временный файл!" << endl;
			return;
		}
		for(const auto &num : buffer) tempFile << num << endl;
		tempFile.close();
	}
	input.close();

	vector<ifstream> tempFiles(tempFileCount);
	vector<int> minValues(tempFileCount, numeric_limits<int>::max());
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	for(int i = 0; i < tempFileCount; i++) {
		tempFiles[i].open(this->tmp_dir_path + tempFileName + to_string(i) + ".txt");
		if(!tempFiles[i]) {
			cerr << "Невозможно открыть временный файл!" << endl;
			return;
		}
		int num;
		if(tempFiles[i] >> num) pq.push({num, i});
	}

	ofstream output(this->output_path);
	if(!output) {
		cerr << "Невозможно открыть временный файл!" << endl;
		return;
	}

	while(!pq.empty()) {
		pair<int, int> minNum = pq.top();
		pq.pop();
		output << minNum.first << endl;
		int num;
		if(tempFiles[minNum.second] >> num) pq.push({num, minNum.second});
	}

	for(int i = 0; i < tempFileCount; i++) {
		tempFiles[i].close();
		remove((this->tmp_dir_path + tempFileName + to_string(i) + ".txt").c_str());
	}
	output.close();
}


void Tape::sortTape(void) {
	cout << " Начало сортировки..." << endl;
	splitVectorsAndSort();
	cout << " Конец сортировки." << endl;
	cout << " Отсортированная лента записана в файл: " << this->output_path << endl;
}

void Tape::shiftLeft(void) {
	//this->shift_step %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.begin(), tape.begin() + shift_step, tape.end());
}

void Tape::shiftRight(void) {
	//shift_amount %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.rbegin(), tape.rbegin() + shift_step, tape.rend());
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
