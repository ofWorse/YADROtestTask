#include "menu.h"
#include "text.h"
#include "inputProtection.h"
#include "menuItems.h"
#include <cstdlib>

void startMenu(Tape tape) {
	int userChoice;
	do {
		menu(numberMenu::START_MENU);
		switch (inputProtection(userChoice, 1, 2); static_cast<startMenuChoice>(userChoice)) {
			case(startMenuChoice::START):
				mainMenu(tape);
				break;
			case(startMenuChoice::EXIT):
				cout << "Программа завершена." << endl;
				exit(EXIT_SUCCESS);
				break;
		}
	} while(static_cast<startMenuChoice>(userChoice) != startMenuChoice::EXIT);
}

void mainMenu(Tape tape) {
	int userChoice;
	do {
		menu(numberMenu::MAIN_MENU);
		switch (inputProtection(userChoice, 1, 3); static_cast<mainMenuChoice>(userChoice)) {
			case(mainMenuChoice::SORT_DATA):
				tape.setupPaths();
				cout << "TODO: РЕАЛИЗОВАТЬ СОРТИРОВКУ ФАЙЛА!" << endl;
				break;
			case(mainMenuChoice::CONFIG_DATA):
				cout << "В процессе..." << endl;
				break;
			case(mainMenuChoice::BACK):
				break;
		}
	} while(static_cast<mainMenuChoice>(userChoice) != mainMenuChoice::BACK);
}

void sortingMenu(Tape tape) {
	int userChoice;
	do {
		menu(numberMenu::SORT_DATA_MENU);
		switch (inputProtection(userChoice, 1, 2); static_cast<sortMenuChoice>(userChoice)) {
			case(sortMenuChoice::SORT):
				cout << "В процессе..." << endl;
				break;
			case(sortMenuChoice::BACK):
				break;
		}
	} while(static_cast<sortMenuChoice>(userChoice) != sortMenuChoice::BACK);
}


void configMenu(Tape tape) {
	int userChoice;
	do {
		switch (inputProtection(userChoice, 1, 2); static_cast<configMenuChoice>(userChoice)) {
			case(configMenuChoice::CONFIG):
				cout << "В процессе..." << endl;
				break;
			case(configMenuChoice::BACK):
				break;
		}
	} while(static_cast<sortMenuChoice>(userChoice) != sortMenuChoice::BACK);
}


