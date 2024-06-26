﻿#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "resource.h"
#include "SeaBattle.h"
int main() {
	srand(time(NULL));
	switch (rand() % (2 + 1 - 0) + 0) {
	case 0: { PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
	case 1: { PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
	case 2: { PlaySound(MAKEINTRESOURCE(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP); break; }
	}
	HWND hwnd = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleW((LPCWSTR)L"Welcome!");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	MoveWindow(hwnd, 10, 10, 550, 150, TRUE);
	system("cls");
	printf("      _           _     _     _           _           _         \n");
	printf("     | |         | |   | |   | |         | |         | |        \n");
	printf("     | |__  _   _| |__ | |__ | | ___  ___| |__  _   _| | __     \n");
	printf("     | '_ \\| | | | '_ \\| '_ \\| |/ _ \\/ __| '_ \\| | | | |/ /     \n");
	printf("     | |_) | |_| | |_) | |_) | |  __/ (__| | | | |_| |   <      \n");
	printf("     |_.__/ \\__,_|_.__/|_.__/|_|\\___|\\___|_| |_|\\__,_|_|\\_\\");
	Sleep(5000);
	while (true) {
		SetConsoleTextAttribute(hConsole, 7);
		SetConsoleTitleW((LPCWSTR)L"SeaBattle 1.0");
		ShowScrollBar(hwnd, SB_VERT, 0);
		MoveWindow(hwnd, 10, 10, 633, 471, TRUE);
		system("cls");
		printf("       _________            __________         __    __  .__          \n");
		printf("      /   _____/ ____ _____ \\______   \\_____ _/  |__/  |_|  |   ____  \n");
		printf("      \\_____  \\_/ __ \\\\__  \\ |    |  _/\\__  \\\\   __\\   __\\  | _/ __ \\ \n");
		printf("      /        \\  ___/ / __ \\|    |   \\ / __ \\|  |  |  | |  |_\\  ___/ \n");
		printf("     /_______  /\\___  >____  /______  /(____  /__|  |__| |____/\\___  >\n");
		printf("             \\/     \\/     \\/       \\/      \\/                     \\/ \n\n");
		printf("      __________________________\n");
		printf("     |                          |\n");
		printf("     |         PVP Mode         |         Play with your friend. (1)\n");
		printf("     |__________________________|\n");
		printf("\n");
		printf("      ___________________________\n");
		printf("     |                          |\n");
		printf("     |         PVE Mode         |         Play with a bot. (2)\n");
		printf("     |__________________________|\n");
		printf("\n");
		printf("      __________________________\n");
		printf("     |                          |\n");
		printf("     |        Report Bug        |         Found a bug? Report it! (3)\n");
		printf("     |__________________________|\n");
		printf("\n");
		printf("      __________________________\n");
		printf("     |                          |\n");
		printf("     |           Exit           |         Exit game. (4)\n");
		printf("     |__________________________|");
		static int plr1[12][12], plr2[12][12];
		int choice = _getch();
		for (int i = 1; i < 11; i++) for (int j = 1; j < 11; j++) plr1[i][j] = 0;
		switch (choice) {
		case '1': {
			system("cls");
			printf("       _________            __________         __    __  .__          \n");
			printf("      /   _____/ ____ _____ \\______   \\_____ _/  |__/  |_|  |   ____  \n");
			printf("      \\_____  \\_/ __ \\\\__  \\ |    |  _/\\__  \\\\   __\\   __\\  | _/ __ \\ \n");
			printf("      /        \\  ___/ / __ \\|    |   \\ / __ \\|  |  |  | |  |_\\  ___/ \n");
			printf("     /_______  /\\___  >____  /______  /(____  /__|  |__| |____/\\___  >\n");
			printf("             \\/     \\/     \\/       \\/      \\/                     \\/ \n\n");
			printf("           Welcome to SeaBattle! A small guide here how to play:\n");
			printf("\n");
			printf("                             Ship Placement\n\n");
			printf("        --> 1) Use 1, 2, 3, 4 keyboard buttons to select ship size\n");
			printf("               you would like to place. Notice that you can place\n");
			printf("               ships randomly by pressing \"r\".\n");
			printf("        --> 2) Input 3 characters. The first two are for coordinates.\n");
			printf("                The third one are for ship orientation. \n");
			printf("                \"v\" stands for vertical, \"h\" for horizontal.\n");
			printf("                For example, \"b2v\" is for place ship at B2 verticaly.\n");
			printf("\n");
			printf("                                Attack\n\n");
			printf("        --> Just input coordinates to shoot. If you'll hit, your turn\n");
			printf("            continues. Otherwise it will be another player turn.\n\n");
			printf("\n                      ");  system("pause");
			PlaySoundW(NULL, NULL, 0);
			SetConsoleTitleW((LPCWSTR)L"Player 1, place your ships! Press Esc to exit to main menu!");
			if (ShipManager(plr1) == 0) { break; }
			SetConsoleTitleW((LPCWSTR)L"Player 2, place your ships! Press Esc to exit to main menu!");
			if (ShipManager(plr2) == 0) { break; }
			Game(plr1, plr2, false);
			break;
		}
		case '2': {
			system("cls");
			printf("       _________            __________         __    __  .__          \n");
			printf("      /   _____/ ____ _____ \\______   \\_____ _/  |__/  |_|  |   ____  \n");
			printf("      \\_____  \\_/ __ \\\\__  \\ |    |  _/\\__  \\\\   __\\   __\\  | _/ __ \\ \n");
			printf("      /        \\  ___/ / __ \\|    |   \\ / __ \\|  |  |  | |  |_\\  ___/ \n");
			printf("     /_______  /\\___  >____  /______  /(____  /__|  |__| |____/\\___  >\n");
			printf("             \\/     \\/     \\/       \\/      \\/                     \\/ \n\n");
			printf("           Welcome to SeaBattle! A small guide here how to play:\n");
			printf("\n");
			printf("                             Ship Placement\n\n");
			printf("        --> 1) Use 1, 2, 3, 4 keyboard buttons to select ship size\n");
			printf("               you would like to place. Notice that you can place\n");
			printf("               ships randomly by pressing \"r\".\n");
			printf("        --> 2) Input 3 characters. The first two are for coordinates.\n");
			printf("                The third one are for ship orientation. \n");
			printf("                \"v\" stands for vertical, \"h\" for horizontal.\n");
			printf("                For example, \"b2v\" is for place ship at B2 verticaly.\n");
			printf("\n");
			printf("                                Attack\n\n");
			printf("        --> Just input coordinates to shoot. If you'll hit, your turn\n");
			printf("            continues. Otherwise it will be another player turn.\n\n");
			printf("\n                      ");  system("pause");
			PlaySoundW(NULL, NULL, 0);
			SetConsoleTitleW((LPCWSTR)L"Place your ships! Press Esc to exit to main menu!");
			if (ShipManager(plr1) == 0) { break; }
			int ships[4] = { 0, 0, 0, 0 };
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 12; j++) {
					plr2[i][j] = 0;
				}
			}
			for (int i = 4; i > 0; i--) {
				for (int j = i; j < 5; j++) {
					botship(plr2, i, ships[i - 1]);
				}
			}
			Game(plr1, plr2, true);
			break;
		}
		case '3': {
			system("start https://github.com/bubblechuk/SeaBattle/issues");
			break;
		}
		case '4': { exit(0); }
		}
	}
}