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

void starting()
{
		platform.loadFromFile("/home/realtura/workspace/kursach/images/platform.png");
		win.loadFromFile("/home/realtura/workspace/kursach/images/win.png");
		ball.loadFromFile("/home/realtura/workspace/kursach/images/ball.png");
		lose.loadFromFile("/home/realtura/workspace/kursach/images/lose.png");
		home_screen.loadFromFile("/home/realtura/workspace/kursach/images/start.png");
		rules.loadFromFile("/home/realtura/workspace/kursach/images/rules.png");
		rules_sprite.setTexture(rules);
		platform_sprite.setTexture(platform);
		ball_sprite.setTexture(ball);
		lose_sprite.setTexture(lose);
		win_sprite.setTexture(win);
		home_screen_sprite.setTexture(home_screen);
		lose_sprite.setPosition(0, 0);
		win_sprite.setPosition(0, 0);
		home_screen_sprite.setPosition(0, 0);
		rules_sprite.setPosition(0, 0);
		ball_sprite.setPosition(340, 430);
		platform_sprite.setPosition(300, 450);
		font.loadFromFile("/home/realtura/workspace/kursach/fonts/NotoSansCJK-Black.ttc");
		text.setColor(Color::Red);
}

int game()
{
	bool isStart = false;
	start:
		platform_position = 300;
		int flagi = 0;
		game_end = 0;
		int score = 0;
		ball_x = 340; ball_y = 430;
		double game_speed = 2;

		bool up = true;
		bool left = true;
		int flag = 0;
		block game[5][12];
		blocksInit(game);
		RenderWindow window(VideoMode(640, 480), "Arkanoid!");
		starting();
		while (window.isOpen())
		{
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f pos = window.mapPixelToCoords(pixelPos);
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			if(!isStart)
			{

				if (flagi == 1) window.draw(rules_sprite);
				else window.draw(home_screen_sprite);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						if (pos.x > 245 && pos.x < 395 && pos.y > 115 && pos.y < 150)
							isStart = true;
						if (pos.x > 250 && pos.x < 390 && pos.y > 230 && pos.y < 260)
							flagi = 1;
						if (pos.x > 270 && pos.x < 365 && pos.y > 340 && pos.y < 380)
							return 0;
						if (pos.x > 240 && pos.x < 400 && pos.y > 405 && pos.y < 445)
							flagi = 0;
					}
			}
			else
			{
				if (!isLeftBorder(platform_position) && Keyboard::isKeyPressed(Keyboard::Left)) { platform_sprite.move(-game_speed * 1.1, 0); platform_position -= game_speed * 1.1; }
				if (!isRightBorder(platform_position) && Keyboard::isKeyPressed(Keyboard::Right)) { platform_sprite.move(game_speed * 1.1, 0); platform_position += game_speed * 1.1; }
				window.clear();
				if(isGame(game_end))
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 12; j++)
						{
							if (collapse(game[i][j]) && game[i][j].isAlive)
							{
								if (game[i][j].isAlive)
								{
									if (up && left)
									{
										if ((game[i][j].cx2 - ball_x) >= (game[i][j].cy2 - ball_y))
											up = false;
										else left = false;
									}
									else if (left)
									{
										if ((game[i][j].cx2 - ball_x) >= (ball_y - game[i][j].cy1))
											up = true;
										else left = false;
									}
									else if (up)
									{
										if ((ball_x - game[i][j].cx1) >= (game[i][j].cy2 - ball_y))
											up = false;
										else left = true;
									}
									else
									{
										if ((ball_x - game[i][j].cx1) >= (ball_y - game[i][j].cy1))
											up = true;
										else left = true;
									}
								}
							}
							if (collapse(game[i][j]) && game[i][j].isAlive)
							{
								game[i][j].isDead();
								score += 10;
							}
							if (game[i][j].isAlive)
							{
								window.draw(game[i][j].block_skin_sprite);
								flag++;
							}

						}
					}
				if (flag == 0 && isGame(game_end))
				{
					game_end = 2;
					game_speed = 0;
				}
				else
				flag = 0;
				if (up && left)
				{
					if (ball_x < 0)
					{
						left = false;
						ball_sprite.move(game_speed, -1 * game_speed);
						ball_x += game_speed;
						ball_y -= game_speed;
					}
					else if (!(ball_y < 0))
					{
						ball_sprite.move(-1 * game_speed, -1 * game_speed);
						ball_x -= game_speed;
						ball_y -= game_speed;
					}
					if (ball_y <= 0)
					{
						up = false;
						ball_sprite.move(-1 * game_speed, game_speed);
						ball_x -= game_speed;
						ball_y += game_speed;
					}
				}
				else if (left)
				{
					if (ball_x < 0)
					{
						left = false;
						ball_sprite.move(game_speed, game_speed);
						ball_x += game_speed;
						ball_y += game_speed;
					}
					else if(!(ball_y >= 450))
					{
						ball_sprite.move(-1 * game_speed, game_speed);
						ball_x -= game_speed;
						ball_y += game_speed;
					}
					if (ball_y >= 448 && ball_y <= 450 && ball_x >= platform_position && ball_x <= platform_position + 100)
					{
						up = true;
						ball_sprite.move(-1 * game_speed, -1 * game_speed);
						ball_x -= game_speed;
						ball_y -= game_speed;
					}
					else if (ball_y > 448 && !(ball_x >= platform_position && ball_x <= platform_position + 100))
						game_end = 1;
				}
				else if (up)
				{
					if (ball_x > 640)
					{
						left = true;
						ball_sprite.move(-1 * game_speed, -1 * game_speed);
						ball_x -= game_speed;
						ball_y -= game_speed;
					}
					else if (!(ball_y < 0))
					{
						ball_sprite.move(game_speed, -1 * game_speed);
						ball_x += game_speed;
						ball_y -= game_speed;
					}
					if (ball_y <= 0)
					{
						up = false;
						ball_sprite.move(game_speed, game_speed);
						ball_x += game_speed;
						ball_y += game_speed;
					}
				}
				else
				{
					if (ball_x > 640)
					{
						left = true;
						ball_sprite.move(-1 * game_speed, game_speed);
						ball_x -= game_speed;
						ball_y += game_speed;
					}
					else if (!(ball_y >= 450))
					{
						ball_sprite.move(game_speed, game_speed);
						ball_x += game_speed;
						ball_y += game_speed;
					}
					if (ball_y >= 448 && ball_y <= 450 && ball_x >= platform_position && ball_x <= platform_position + 120)
					{
						up = true;
						ball_sprite.move(game_speed, -1 * game_speed);
						ball_x += game_speed;
						ball_y -= game_speed;
					}
					else if (ball_y > 448 && !(ball_x >= platform_position && ball_x <= platform_position + 120))
						game_end = 1;

				}
					window.draw(platform_sprite);
					window.draw(ball_sprite);
					if (!isGame(game_end))
					{
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							if (pos.x > 160 && pos.x < 500 && pos.y > 250 && pos.y < 320)
								goto start;
							if (pos.x > 230 && pos.x < 390 && pos.y > 380 && pos.y < 430)
								return 0;
						}
						if (game_end == 2)
							window.draw(win_sprite);
						else if (game_end == 1)
							window.draw(lose_sprite);
					}
				if(isGame(game_end))
					{
						text.setString("Score: " + std::to_string(score));
						text.setPosition(520, 0);
					}
				else
					{
						text.setString("Your score is: " + std::to_string(score));
						text.setPosition(250, 210);
					}
				window.draw(text);
			}
			window.display();
		}
        return 0;
}
