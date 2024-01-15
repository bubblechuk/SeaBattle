#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "resource.h"
int shiptmp[7], btmp[3] = { -1, -1, -1 };
int dstr1 = 0, dstr2 = 0;
//BotCoordinatesHandler is the part of Attack() and being used for defining possible ship location in PvE mode.
void BotCoordinatesHandler(int coords) {
	int j = 1;
	for (int i = 1; i < 4; i++) shiptmp[i] = coords + i;
	for (int i = 4; i < 7; i++) shiptmp[i] = coords + (i - (i + (j++)));
}
//GameRender() renders game field in the console screen, use ShowShip to define whether to show ships or not.
void GameRender(int plr[12][12], bool ShowShip) {
	int a = 65;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("\n");
	ShowShip == false ? printf("                                   Game\n") : printf("\n");
	ShowShip == false ? printf("    Player 1: %d                                              Player 2: %d\n", dstr1, dstr2) : printf("\n");
	printf("  ");
	for (int u = 0; u < 17; u++) printf(" ");
	while (a < 75) printf("%c   ", a++);
	printf("\n");
	for (int i = 1; i < 11; i++) {
		for (int u = 0; u < 17; u++) printf(" ");
		i == 10 ? printf("%d ", 0) : printf("%d ", i);
		for (int k = 0; k < 2; k++) {
			for (int j = 1; j < 11; j++) {
				if (ShowShip == true) {
					if (plr[i][j] == 5 || plr[i][j] == 0) {
						SetConsoleTextAttribute(hConsole, 9);
						for (int i = 0; i < 4; i++) printf("%c", 177);
						SetConsoleTextAttribute(hConsole, 7);
					}
					else {
						SetConsoleTextAttribute(hConsole, 2);
						for (int i = 0; i < 4; i++) printf("%c", 219);
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
				else {
					if (plr[i][j] == 1) {
						//8 for debugging purpouses
						SetConsoleTextAttribute(hConsole, 9);
						for (int i = 0; i < 4; i++) printf("%c", 177);
						SetConsoleTextAttribute(hConsole, 7);
					}
					if (plr[i][j] == 0) {
						SetConsoleTextAttribute(hConsole, 9);
						for (int i = 0; i < 4; i++) printf("%c", 177);
						SetConsoleTextAttribute(hConsole, 7);
					}
					if (plr[i][j] == 6) {
						SetConsoleTextAttribute(hConsole, 1);
						for (int i = 0; i < 4; i++) printf("%c", 176);
						SetConsoleTextAttribute(hConsole, 7);
					}
					if (plr[i][j] == 7) {
						SetConsoleTextAttribute(hConsole, 4);
						for (int i = 0; i < 4; i++) printf("%c", 178);
						SetConsoleTextAttribute(hConsole, 7);
					}
				}
			}
			printf("\n");
			if (k != 1) {
				for (int u = 0; u < 17; u++) printf(" ");
				printf("  ");
			}
		}
	}
}
//DebugRender() renders 10x10 matrix instead of beautiful game field. For debug purposes use.
void DebugRender(int plr[12][12]) {
	int a = 65;
	system("cls");
	printf("  ");
	while (a < 75) printf("%c", a++);
	printf("\n");
	for (int i = 1; i < 11; i++) {
		i == 10 ? printf("%d ", 0) : printf("%d ", i);
		for (int j = 1; j < 11; j++) {
			printf("%d", plr[i][j]);
		}
		printf("\n");
	}
}
//ShipPlacer() insert a ship into the game field according to defined coordinates and ship orientation.
int ShipPlacer(int plr[12][12], char pos[3], int shipsize) {
	int ltr = pos[0] - 96, num = pos[1] - 48;
	num == 0 ? num = 10 : false;
	switch (pos[2]) {
		//v - vertical, h horizontal 
	case ('v'): {
		//range of allowed values
		for (int i = -1; i < shipsize + 1; i++) {
			for (int j = -1; j < 2; j++) {
				if (num + i < 0 || num + i > 11 || ltr + j < 0 || ltr + j > 11) { printf("                           Number Override Error\n"); Sleep(500); return 0; }
				else if (plr[num + i][ltr + j] == 1) { printf("                           Nearby Ship Error\n"); Sleep(500); return 0; }
			}
		}
		//creating a zone around the ships to prevent them from merging
		for (int i = -1; i < shipsize + 1; i++) {
			if (num + i > 0 && num + i < 11 && ltr - 1 > 0 && ltr - 1 < 11) plr[num + i][ltr - 1] = 5;
			if (num + i > 0 && num + i < 11 && ltr > 0 && ltr < 11) plr[num + i][ltr] = 5;
			if (num + i > 0 && num + i < 11 && ltr + 1 > 0 && ltr + 1 < 11) plr[num + i][ltr + 1] = 5;
		}
		//insert the ship according to his size
		for (int i = 0; i < shipsize; i++) {
			plr[num + i][ltr] = 1;
		}
		break;
	}
	case ('h'): {
		for (int i = -1; i < shipsize + 1; i++) {
			for (int j = -1; j < 2; j++) {
				if (ltr + i < 0 || ltr + i > 11 || num + j < 0 || num + j > 11) { printf("                           Number Override Error\n"); Sleep(500); return 0; }
				else if (plr[num + j][ltr + i] == 1) { printf("                           Nearby Ship Error\n"); Sleep(500); return 0; }
			}
		}
		for (int i = -1; i < shipsize + 1; i++) {
			if (ltr + i > 0 && ltr + i < 11 && num - 1 > 0 && num - 1 < 11) plr[num - 1][ltr + i] = 5;
			if (ltr + i > 0 && ltr + i < 11 && num > 0 && num < 11) plr[num][ltr + i] = 5;
			if (ltr + i > 0 && ltr + i < 11 && num + 1 > 0 && num + 1 < 11) plr[num + 1][ltr + i] = 5;
		}
		for (int i = 0; i < shipsize; i++) {
			plr[num][ltr + i] = 1;
		}
		break;
	}
	default: { MessageBoxW(NULL, (LPCWSTR)L"Invalid input!", (LPCWSTR)L"Error!", MB_ICONERROR | MB_OK | MB_DEFBUTTON1); return 0; }
	}
	return 1;
}
//botship() is for isnerting ships automatically.
int botship(int plr[12][12], int shipsize, int ships) {
	//this is for correct amount of ships to be placed
	if (shipsize == 4 && ships == 1) return 0;
	if (shipsize == 3 && ships == 2) return 0;
	if (shipsize == 2 && ships == 3) return 0;
	if (shipsize == 1 && ships == 4) return 0;
	srand(time(NULL));
cycle:
	//this part is similar to ShipPlacer, except random values defined by rand()
	while (true) {
		int ltr = rand() % (10 + 1 - 1) + 1, num = rand() % (10 + 1 - 1) + 1;
		switch (rand() % (1 + 1 - 0) + 0) {
		case 1: {
			for (int i = -1; i < shipsize + 1; i++) {
				for (int j = -1; j < 2; j++) {
					if (num + i > 11) { goto cycle; }
					else if (plr[num + i][ltr + j] == 1) { goto cycle; }
				}
			}
			for (int i = -1; i < shipsize + 1; i++) {
				if (num + i > 0 && num + i < 11 && ltr - 1 > 0 && ltr - 1 < 11) plr[num + i][ltr - 1] = 5;
				if (num + i > 0 && num + i < 11 && ltr > 0 && ltr < 11) plr[num + i][ltr] = 5;
				if (num + i > 0 && num + i < 11 && ltr + 1 > 0 && ltr + 1 < 11) plr[num + i][ltr + 1] = 5;
			}
			for (int i = 0; i < shipsize; i++) {
				plr[num + i][ltr] = 1;
			}
			break;
		}
		case 0: {
			for (int i = -1; i < shipsize + 1; i++) {
				for (int j = -1; j < 2; j++) {
					if (ltr + i > 11) { goto cycle; }
					else if (plr[num + j][ltr + i] == 1) { goto cycle; }
				}
			}
			for (int i = -1; i < shipsize + 1; i++) {
				if (ltr + i > 0 && ltr + i < 11 && num - 1 > 0 && num - 1 < 11) plr[num - 1][ltr + i] = 5;
				if (ltr + i > 0 && ltr + i < 11 && num > 0 && num < 11) plr[num][ltr + i] = 5;
				if (ltr + i > 0 && ltr + i < 11 && num + 1 > 0 && num + 1 < 11) plr[num + 1][ltr + i] = 5;
			}
			for (int i = 0; i < shipsize; i++) {
				plr[num][ltr + i] = 1;
			}
		}
		}
		return 1;
	}
}
//ShipManager() manages ship placement before the game start
int ShipManager(int plr[12][12]) {
	dstr1 = 0, dstr2 = 0;
	int ships[4] = { 0, 0, 0, 0 };
	//player field initialize
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			plr[i][j] = 0;
		}
	}
	GameRender(plr, true);
	while (true) {
		printf("                             Input Ship Size: ");
		char ch = _getch();
		ch == (char)(-86) ? ch = 'r' : false;
		GameRender(plr, true);
		switch (ch) {
		case '4': {
			if (ships[3] == 1) {
				printf("                           Only 1 ship4 is allowed!\n"); break;
			}
			printf("                           Input coordinates: ");
			static char pos[3]; scanf("%s", pos);
			ShipPlacer(plr, pos, 4) == 1 ? ships[3]++ : false;
			GameRender(plr, true);
			break;
		}
		case '3': {
			if (ships[2] == 2) {
				printf("                           Only 2 ship3 is allowed!\n"); break;
			}
			printf("                           Input coordinates: ");
			static char pos[3]; scanf("%s", pos);
			ShipPlacer(plr, pos, 3) == 1 ? ships[2]++ : false;
			GameRender(plr, true);
			break;
		}
		case '2': {
			if (ships[1] == 3) {
				printf("                           Only 3 ship2 is allowed!\n"); break;
			}
			printf("                           Input coordinates: ");
			static char pos[3]; scanf("%s", pos);
			ShipPlacer(plr, pos, 2) == 1 ? ships[1]++ : false;
			GameRender(plr, true);
			break;
		}
		case '1': {
			if (ships[0] == 4) {
				printf("                           Only 4 ship1 is allowed!\n"); break;
			}
			printf("                           Input coordinates: ");
			static char pos[3]; scanf("%s", pos);
			ShipPlacer(plr, pos, 1) == 1 ? ships[0]++ : false;
			GameRender(plr, true);
			break;
		}
		case 'r': {
			for (int i = 4; i > 0; i--) {
				for (int j = i; j < 5; j++) {
					botship(plr, i, ships[i - 1]) == 1 ? ships[i - 1]++ : false;
				}
			}
			GameRender(plr, true);
			break;
		}
				//13 is for Enter. Enters the game if all ships are placed.
		case 13: {
			if (ships[3] == 1 && ships[2] == 2 && ships[1] == 3 && ships[0] == 4) return 1;
			else printf("Place ALL ships to enter!");
			break;
		}
			   //27 is for Escape button. Returns game to main menu.
		case 27: {
			switch (rand() % (2 + 1 - 0) + 0) {
			case 0: { PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 1: { PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 2: { PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			}
			return 0;
		}
		}

	}
}
//Attack() is for managing attacking actions during the game.
//Attack() is for managing attacking actions during the game.
int Attack(int plr[12][12], bool isBot) {
	srand(time(NULL));
	int dstr = 0, num = btmp[0], ltr = btmp[1], q = 1;
cycle:
	GameRender(plr, false);
	//ends function execution if all ships are destroyed.
	int count = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			plr[i][j] == 1 ? count++ : false;
		}
	}
	if (count == 0) return dstr;
	if (isBot == true) {
		//bot AI has 3 stages. 
		// Firstly, he randomly shoots to hit the ships
		if (btmp[2] == -1) {
			ltr = rand() % (10 + 1 - 1) + 1;
			num = rand() % (10 + 1 - 1) + 1;
			if (plr[num][ltr] == 6 || plr[num][ltr] == 7) goto cycle;
		}
		Sleep(500);
		//Secondly it searches for another ship part whether vertical or horizontal
		if (btmp[2] == 0) {
		botcycle:
			switch (rand() % (3 + 1 - 0) + 0) {
			case 0: {
				num = btmp[0] + 1;
				ltr = btmp[1];
				if (plr[num][ltr] == 7 || plr[num][ltr] == 6) {
					goto botcycle;
				}
				BotCoordinatesHandler(num);
				shiptmp[0] = 'v';
				break;
			}
			case 1: {
				num = btmp[0] - 1;
				ltr = btmp[1];
				if (plr[num][ltr] == 7 || plr[num][ltr] == 6) {
					goto botcycle;
				}
				BotCoordinatesHandler(num);
				shiptmp[0] = 'v';
				break;
			}
			case 2: {
				num = btmp[0];
				ltr = btmp[1] + 1;
				if (plr[num][ltr] == 7 || plr[num][ltr] == 6) {
					goto botcycle;
				}
				BotCoordinatesHandler(ltr);
				shiptmp[0] = 'h';
				break;
			}
			case 3: {
				num = btmp[0];
				ltr = btmp[1] - 1;
				if (plr[num][ltr] == 7 || plr[num][ltr] == 6) {
					goto botcycle;
				}
				BotCoordinatesHandler(ltr);
				shiptmp[0] = 'h';
				break;
			}
			}
		}
		//And finally, it uses BotCoordinatesHandler, to get coordinates according to ship orientation
		if (btmp[2] == -2) {
			switch (shiptmp[0]) {
			case 'v': {
				if ((plr[shiptmp[q]][ltr] == 6 || plr[shiptmp[q]][ltr] == 0) && q < 4) q = 4;
				if ((plr[shiptmp[q]][ltr] == 6 || plr[shiptmp[q]][ltr] == 0) && q > 4) btmp[2] = -1;
				else {
					num = shiptmp[q];
					q++;
				}
				break;
			}
			case 'h': {
				if ((plr[num][shiptmp[q]] == 6 || plr[num][shiptmp[q]] == 0) && q < 4) q = 4;
				if ((plr[num][shiptmp[q]] == 6 || plr[num][shiptmp[q]] == 0) && q > 4) btmp[2] = -1;
				else {
					ltr = shiptmp[q];
					q++;
				}
				break;
			}
			}
		}
	}
	else {
		printf("                           Input coordinates: ");
		static char pos[2]; scanf("%s", pos);
		ltr = pos[0] - 96;
		num = pos[1] - 48;
		if (ltr > 10 || ltr < 1 || num > 10 || num < 0) { goto cycle; }
	}
	num == 0 ? num = 10 : false;
	//this switch case is for defining what to do if meets following value
	switch (plr[num][ltr]) {
		// 0 is for empty cell
	case 0: { PlaySound(MAKEINTRESOURCE(IDR_WAVE7), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);  plr[num][ltr] = 6; break; }
		  // 6 is for empty cell that has been shoot already
	case 6: { btmp[2] != -2 ? btmp[2] = -1 : false;  goto cycle; }
		  // 7 is for ship part that was destroyed already
	case 7: { btmp[2] != -2 ? btmp[2] = -1 : false;  goto cycle;  }
		  // 1 is for ship part that was never touched
	case 1: {
		plr[num][ltr] = 7;
		if (isBot == true) {
			if (btmp[2] == -1) {
				btmp[0] = num;
				btmp[1] = ltr;
			}
			btmp[2] == 0 ? btmp[2] = -2 : false;
			btmp[2] == -1 ? btmp[2] = 0 : false;
		}
		//vertical
		if (plr[num + 1][ltr] == 1 || plr[num - 1][ltr] == 1 || plr[num + 1][ltr] == 7 || plr[num - 1][ltr] == 7) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE5), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			int sh = 0, tmp = 0;
			//these two cycles are counting how much ship parts remaining
			for (int i = 0; i < 4; i++) {
				if (plr[num + i][ltr] == 0 || plr[num + i][ltr] == 6) { break; }
				plr[num + i][ltr] == 1 ? sh++ : false;
			}
			for (int i = 1; i < 5; i++) {
				if (plr[num - i][ltr] == 0 || plr[num - i][ltr] == 6) { tmp = num - i + 1; break; }
				plr[num - i][ltr] == 1 ? sh++ : false;
			}
			//if no ship parts remaining, start drawing a zone around the whole ship
			if (sh == 0) {
				PlaySound(MAKEINTRESOURCE(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				int j = 0;
				for (int i = -1; i < 5; i++) {
					if (j == 2) {
						dstr++;
						if (isBot == true) {
							btmp[2] = -1;
							q = 1;
						}
						goto cycle;
					}
					if (plr[tmp + i][ltr] == 7) {
						if (tmp + i > -1 && tmp + i < 12 && ltr - 1 > -1 && ltr - 1 < 12 && plr[tmp + i][ltr - 1] != 1) plr[tmp + i][ltr - 1] = 6;
						if (tmp + i > -1 && tmp + i < 12 && ltr + 1 > -1 && ltr + 1 < 12 && plr[tmp + i][ltr + 1] != 1) plr[tmp + i][ltr + 1] = 6;
					}
					else if (tmp + i > -1 && tmp + i < 12) {
						for (int j = -1; j < 2; j++) {
							ltr + j > -1 && ltr + j < 12 && plr[tmp + i][ltr + j] != 1 ? plr[tmp + i][ltr + j] = 6 : false;
						}
						j++;
					}
					else j++;
				}
			}
		}
		//horizontal
		else if (plr[num][ltr + 1] == 1 || plr[num][ltr - 1] == 1 || plr[num][ltr + 1] == 7 || plr[num][ltr - 1] == 7) {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE5), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			int sh = 0, tmp = 0;
			for (int i = 0; i < 4; i++) {
				if (plr[num][ltr + i] == 0 || plr[num][ltr + i] == 6) { break; }
				plr[num][ltr + i] == 1 ? sh++ : false;
			}
			for (int i = 1; i < 5; i++) {
				if (plr[num][ltr - i] == 0 || plr[num][ltr - i] == 6) { tmp = ltr - i + 1; break; }
				plr[num][ltr - i] == 1 ? sh++ : false;
			}
			if (sh == 0) {
				PlaySound(MAKEINTRESOURCE(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
				int j = 0;
				for (int i = -1; i < 5; i++) {
					if (j == 2) {
						dstr++;
						if (isBot == true) {
							btmp[2] = -1;
							q = 1;
						}
						goto cycle;
					}
					if (plr[num][tmp + i] == 7) {
						if (tmp + i > -1 && tmp + i < 12 && ltr - 1 > -1 && ltr - 1 < 12 && plr[num - 1][tmp + i] != 1) plr[num - 1][tmp + i] = 6;
						if (tmp + i > -1 && tmp + i < 12 && ltr + 1 > -1 && ltr + 1 < 12 && plr[num + 1][tmp + i] != 1) plr[num + 1][tmp + i] = 6;
					}
					else if (tmp + i > -1 && tmp + i < 12) {
						for (int j = -1; j < 2; j++) {
							ltr + j > -1 && ltr + j < 12 && plr[num + j][tmp + i] != 1 ? plr[num + j][tmp + i] = 6 : false;
						}
						j++;
					}
					else j++;
				}
			}
		}
		else {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE6), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) plr[num + j][ltr + i] = 6;
			plr[num][ltr] = 7;
			isBot == true ? btmp[2] = -1 : false;
		}
		dstr++;
		goto cycle;
	}
	}
	GameRender(plr, false);
	Sleep(2000);
	return dstr;
}
//Game() manages the game whether PvP or PvE according to isBot value.
void Game(int plr1[12][12], int plr2[12][12], bool isBot) {
	srand(time(NULL));
	//replacing all 5 with 0
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			plr1[i][j] == 5 ? plr1[i][j] = 0 : false;
			plr2[i][j] == 5 ? plr2[i][j] = 0 : false;
		}
	}
	// starts a game with random player turn
	bool turn = rand() % (1 + 1 - 0) + 0;
	while (dstr1 < 20 || dstr2 < 20) {
		turn = !turn;
		if (turn) {
			SetConsoleTitleW((LPCWSTR)L"Player 1, attack!");
			dstr1 += Attack(plr2, false);
		}
		else {
			if (isBot == false) {

				SetConsoleTitleW((LPCWSTR)L"Player 2, attack!");
				dstr2 += Attack(plr1, false);
			}
			else {
				SetConsoleTitleW((LPCWSTR)L"Bot, attack!");
				Sleep(500);
				dstr2 += Attack(plr1, true);
			}
		}
		//checks for win condition
		if (dstr1 >= 20) {
			Sleep(10);
			PlaySound(MAKEINTRESOURCE(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			printf("                           Player 1 wins!\n");
			system("pause");
			switch (rand() % (2 + 1 - 0) + 0) {
			case 0: { PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 1: { PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 2: { PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			}
			return;

		}
		if (dstr2 >= 20) {
			Sleep(10);
			PlaySound(MAKEINTRESOURCE(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
			isBot == true ? printf("                           Bot wins!\n") : printf("                           Player 2 wins!\n");
			system("pause");
			switch (rand() % (2 + 1 - 0) + 0) {
			case 0: { PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 1: { PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			case 2: { PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
			}
			return;
		}

	}
}

