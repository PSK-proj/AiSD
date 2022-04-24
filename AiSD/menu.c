void menu_header()
{
	system("cls");
	printf("                   __          __        __   __   __  ___               __      __        __   __        ___  __   __   __  ___                  \n");
	printf("                  /  \\ |  | | /  ` |__/ /__` /  \\ |__)  |      /\\  |\\ | |  \\    |__) |  | |__) |__) |    |__  /__` /  \\ |__)  |                  \n");
	printf("                  \\__X \\__/ | \\__, |  \\ .__/ \\__/ |  \\  |     /~~\\ | \\| |__/    |__) \\__/ |__) |__) |___ |___ .__/ \\__/ |  \\  |                  \n");
	printf("\n");
	printf("                                                       Piotr Miernik     Oskar Ołub     1ID14B");
	printf("\n\n\n");
}

void menu_main(unsigned short *mode)
{
	unsigned char choice, exit;
	do
	{
		exit = 1;
		menu_header();
		printf("                                                      +========================================+\n");
		printf("                                                      |                  MENU                  |\n");
		printf("                                                      +----------------------------------------+\n");
		printf("                                                      | 1. Ręczne wczytywanie liczb            |\n");
		printf("                                                      |                                        |\n");
		printf("                                                      | 2. Automatyczne generowanie liczb      |\n");
		printf("                                                      |   (zapis do pliku i testy wydajności)  |\n");
		printf("                                                      |                                        |\n");
		printf("                                                      | 3. Automatyczne generowanie liczb      |\n");
		printf("                                                      |            (zapis do pliku)            |\n");
		printf("                                                      |                                        |\n");
		printf("                                                      | 4. Automatyczne generowanie liczb      |\n");
		printf("                                                      |           (testy wydajności)           |\n");
		printf("                                                      |                                        |\n");
		printf("                                                      | 0. Wyjście z programu                  |\n");
		printf("                                                      |                                        |\n");
		printf("                                                      +========================================+\n");
		printf("\n\n");
		printf("                                                                     Wybieram: ");
		scanf("%hhu", &choice);

		switch (choice)
		{
		case 1:
			*mode = 100;
			break;
		case 2:
			*mode = 211;
			break;
		case 3:
			*mode = 210;
			break;
		case 4:
			*mode = 201;
			break;
		case 0:
			*mode = 777;
			break;
		default:
			exit = 0;
			break;
		}

	} while (!exit);
}

