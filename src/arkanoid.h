#ifndef ARKANOID_H
#define ARKANOID_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;

class  block
{
public:
	bool isAlive;
	Texture block_skin;
	Sprite block_skin_sprite;
	int cx1;
	int cy1;
	int cx2;
	int cy2;
	block()
	{
		isAlive = true;
	}
	void setTexture()
	{
		block_skin.loadFromFile("../images/block.png");
	}
	void setSprite()
	{
		block_skin_sprite.setTexture(block_skin);
	}
	void setPos(int x, int y)
	{
		block_skin_sprite.setPosition(x, y);
		cx1 = x;
		cy1 = y;
		cx2 = x + 50;
		cy2 = y + 30;
	}
	void isDead()
	{
		isAlive = false;
	}
};
bool isLeftBorder(double platform_position);
bool isRightBorder(double platform_position);
bool collapse(block bl);
bool isGame(int game_end);
void blocksInit(block game[5][12]);
void starting();
int game();
#endif
