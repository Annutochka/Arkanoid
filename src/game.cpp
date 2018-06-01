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

bool collapse(block bl) // проверка на столкновение шарика с блоком
{
	if ((ball_x > bl.cx1 && ball_x < bl.cx2) && (ball_y > bl.cy1 && ball_y < bl.cy2))
		return true;
	else return false;
}

