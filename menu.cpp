#include "inputProtection.h"
#include "menuItems.h"
#include "text.h"
#include "menu.h"
#include <cstdlib>

void startMenu(void) {
	int userChoice;
	do {
		menu(numberMenu::START_MENU);
		switch (inputProtection(userChoice, 1, 2); static_cast<startMenuChoice>(userChoice)) {
			case(startMenuChoice::START):
				mainMenu();
				break;
			case(startMenuChoice::EXIT):
				cout << "Программа завершена." << endl;
				exit(EXIT_SUCCESS);
				break;
		}
	} while(static_cast<startMenuChoice>(userChoice) != startMenuChoice::EXIT);
}

void mainMenu(void) {
	int userChoice;
	Tape tape;
	tape.readConfig();
	do {
		menu(numberMenu::MAIN_MENU);
		switch (inputProtection(userChoice, 1, 4); static_cast<mainMenuChoice>(userChoice)) {
			case(mainMenuChoice::SORT_DATA):
				if(tape.consistPaths()) {
					rewritePathsMenu(tape);
				} else { 
					tape.setupPaths();
					tape.makeTape();
					tape.sortTape();
				}
				break;
			case(mainMenuChoice::SHIFT_DATA):
				if(tape.getTape().empty()) {
					cout << "Лента пуста!" << endl;
					break;
				}
				shiftDataMenu(tape);
				break;
			case(mainMenuChoice::CONFIG_DATA):
				tape.rewriteConfig();
				tape.readConfig();
				break;
			case(mainMenuChoice::BACK):
				break;
		}
	} while(static_cast<mainMenuChoice>(userChoice) != mainMenuChoice::BACK);
}

void shiftDataMenu(Tape tape) {
	int userChoice;
	do {
		menu(numberMenu::SHIFT_DATA_MENU);
		switch (inputProtection(userChoice, 1, 3); static_cast<shiftDataMenuChoice>(userChoice)) {
			case(shiftDataMenuChoice::RIGHT):
				tape.moveData(true);
				break;
			case(shiftDataMenuChoice::LEFT):
				tape.moveData(false);
				break;
			case(shiftDataMenuChoice::BACK):
				break;
		}
	} while(static_cast<shiftDataMenuChoice>(userChoice) != shiftDataMenuChoice::BACK);
}

void rewritePathsMenu(Tape tape) {
	int userChoice;
	do {
		menu(numberMenu::REWRITE_PATHS_MENU);
		switch (inputProtection(userChoice, 1, 3); static_cast<rewritePathsMenuChoice>(userChoice)) {
			case(rewritePathsMenuChoice::YES):
				tape.setupPaths();
				break;
			case(rewritePathsMenuChoice::NO):
				cout << "Операция отменена." << endl;
				break;
			case(rewritePathsMenuChoice::BACK):
				break;
		}
	} while(static_cast<rewritePathsMenuChoice>(userChoice) != rewritePathsMenuChoice::BACK);
}

void sortingMenu(Tape tape) {
	int userChoice;
	do {
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


