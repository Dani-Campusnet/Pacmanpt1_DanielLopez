#include <iostream>
#define MAP_VERTICAL 29
#define MAP_HORIZONTAL 120
#define PERSONAJE 'O'
enum TILES { EMPTY = ' ', WALL = '#', POINT = '.' };
TILES map[MAP_VERTICAL][MAP_HORIZONTAL];
bool run = true;
bool win = false;

enum INPUT { QUIT, UP, DOWN, LEFT, RIGHT, UNKNOWN };
INPUT currentInput = INPUT::UNKNOWN;

int personaje_x;
int personaje_y;
int puntuacion_actual = 0;
int puntuacion_total;

void Setup() {
	personaje_x = MAP_HORIZONTAL / 2;
	personaje_y = MAP_VERTICAL / 2;
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == 0 || j == 0 || i == MAP_VERTICAL - 1 || j == MAP_HORIZONTAL - 1) {
				map[i][j] = TILES::WALL;
			}
			else {
				map[i][j] = TILES::EMPTY;
			}
		}
	}
	for (size_t i = MAP_VERTICAL-1; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 51; j < 59; j++)
		{
			map[i][j] = TILES::EMPTY;
		}
	}

	for (size_t i = 0; i < 1; i++)
	{
		for (size_t j = 51; j < 59; j++)
		{
			map[i][j] = TILES::EMPTY;
		}
	}

	map[10][50] = TILES::POINT;
	map[10][51] = TILES::POINT;
	map[10][52] = TILES::POINT;
	map[10][53] = TILES::POINT;
	map[26][50] = TILES::POINT;
	map[26][51] = TILES::POINT;
	map[26][52] = TILES::POINT;
	map[26][53] = TILES::POINT;

	map[10][0] = TILES::POINT;
	map[11][0] = TILES::POINT;
	map[12][0] = TILES::POINT;
	map[13][0] = TILES::POINT;

	map[10][MAP_HORIZONTAL - 1] = TILES::POINT;
	map[11][MAP_HORIZONTAL - 1] = TILES::POINT;
	map[12][MAP_HORIZONTAL - 1] = TILES::POINT;
	map[13][MAP_HORIZONTAL - 1] = TILES::POINT;

	map[MAP_VERTICAL-1][51] = TILES::EMPTY;
	map[MAP_VERTICAL-1][52] = TILES::EMPTY;
	map[MAP_VERTICAL-1][53] = TILES::EMPTY;
	map[MAP_VERTICAL-1][54] = TILES::EMPTY;

	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (map[i][j] == TILES::POINT) {
				puntuacion_total++;
			}
		}
	}
}


void Input() {
	char input;
	std::cin >> input;
	switch (input)
	{
	case 'w':
	case 'W':
		currentInput = INPUT::UP;
		break;
	case 's':
	case 'S':
		currentInput = INPUT::DOWN;
		break;
	case 'a':
	case 'A':
		currentInput = INPUT::LEFT;
		break;
	case 'd':
	case 'D':
		currentInput = INPUT::RIGHT;
		break;
	case 'q':
	case 'Q':
		currentInput = INPUT::QUIT;
		break;
	default:
		currentInput = INPUT::UNKNOWN;
		break;
	}
}
void Logic() {
	if (win)
	{
		switch (currentInput)
		{
		case QUIT:
			run = false;
			break;
		}
	}
	else {
		int personaje_y_new = personaje_y;
		int personaje_x_new = personaje_x;
		switch (currentInput)
		{
		case QUIT:
			run = false;
			break;
		case UP:
			personaje_y_new--;
			break;
		case DOWN:
			personaje_y_new++;
			break;
		case LEFT:
			personaje_x_new--;
			break;
		case RIGHT:
			personaje_x_new++;
			break;
		}
		if (personaje_x_new < 0) {
			personaje_x_new = MAP_HORIZONTAL - 1;
		}
		personaje_x_new = personaje_x_new % MAP_HORIZONTAL;
		if (personaje_y_new < 0) {
			personaje_y_new = MAP_VERTICAL - 1;
		}
		personaje_y_new = personaje_y_new % MAP_VERTICAL;

		switch (map[personaje_y_new][personaje_x_new])
		{
		case TILES::WALL:
			break;
		case TILES::POINT:
			puntuacion_actual++;
			map[personaje_y_new][personaje_x_new] = TILES::EMPTY;
		default:
			personaje_y = personaje_y_new;
			personaje_x = personaje_x_new;
			break;
		}
	}
	if (puntuacion_actual == puntuacion_total) {
		win = true;
	}

}
void Draw() {
	system("CLS");
	for (size_t i = 0; i < MAP_VERTICAL; i++)
	{
		for (size_t j = 0; j < MAP_HORIZONTAL; j++)
		{
			if (i == personaje_y && j == personaje_x) {
				std::cout << PERSONAJE;
			}
			else {
				std::cout << (char)map[i][j];
			}
		}
		std::cout << std::endl;
	}
	std::cout << puntuacion_actual << '/' << puntuacion_total;
	if (win)
	{
		std::cout << "Has ganado!" << std::endl;
		switch (currentInput)
		{
		case QUIT:
			run = false;
			break;
		}
	}
}

int main()
{
	Setup();
	Draw();
	while (run) {
		Input();
		Logic();
		Draw();
	}
}