#include <iostream>
#include "Menu.h"
#include <ctime>

int main()
{
	srand(time(NULL));
	Menu menu; //Tworze sobie obiektklasy menu, z kt�rego potem steruje programem
	menu.mainMenu();

	exit(EXIT_SUCCESS);
}
