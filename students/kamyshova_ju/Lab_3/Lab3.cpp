#include "stdafx.h"
#include <iostream>
#include "menu.h"
#include "villages.h"

int main()
{
	setlocale(0, "Rus");
    system("color 5E");
	Menu menu;
	Villages village;
	bool proverka = false;

	menu.helloWorld();
	menu.print_in_menu();
	if(menu.getVar_menu() == 1)
		proverka = village.from_file();
	if(menu.getVar_menu() == 2)
		proverka = village.from_keyboard();
	if(proverka)
	{
		village.main_function();
		menu.helloWorld();
		menu.print_out_menu();
		if(menu.getVar_menu() == 1)
		    village.save_to_file();
	    if(menu.getVar_menu() == 2)
		    village.print_on_screen();
	}
	else
		menu.error_message();
	system("Pause");
	return 0;
}

