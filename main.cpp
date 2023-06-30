#include <cstdlib>
#include <locale.h>
#include "menu.h"
#include "text.h"

int main(void) {
	setlocale(LC_ALL, "RU");

	Tape tape;
	tape.readConfig();

	hello();
	startMenu(tape);
	std::system("pause");
	return EXIT_SUCCESS;
}
