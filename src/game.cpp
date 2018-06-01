#include "arkanoid.h"

using namespace sf;

double ball_x = 340, ball_y = 430;
int game_end;
int x, y = 20;
double platform_position;
Texture platform;
Texture ball;
Texture rules;
Texture home_screen;
Texture win;
Texture lose;
Sprite rules_sprite;
Sprite platform_sprite;
Sprite home_screen_sprite;
Sprite ball_sprite;
Sprite lose_sprite;
Sprite win_sprite;
Font font;
Text text("", font, 20);

bool isLeftBorder(double platform_position)
{
	if(platform_position < 0)
		return true;
	return false;
}

bool isRightBorder(double platform_position)
{
	if(platform_position + 100 > 640)
		return true;
	return false;
}

bool collapse(block bl) // проверка на столкновение шара с блоком
{
	if ((ball_x > bl.cx1 && ball_x < bl.cx2) && (ball_y > bl.cy1 && ball_y < bl.cy2))
		return true;
	else return false;
}

bool isGame(int game_end)
{
	if(game_end != 0) return false;
	else return true;
}

void blocksInit(block game[5][12]) // Заполняет блоками игровую область 
{
	for (int i = 0; i < 5; i++)
		{
			x = 20;
			for (int j = 0; j < 12; j++)
			{
				game[i][j] = block();
				game[i][j].setTexture();
				game[i][j].setSprite();
				game[i][j].setPos(x, y);
				x += 50;
			}
			y += 30;
		}
	y = 20;
} 
