#include "arkanoid.h"

using namespace sf;

int passed = 0;
int tests = 0;
block b = block();

int leftBorderCorrectTest(double platform_position)
{
    tests++;
    if(isLeftBorder(platform_position))
    {
        passed++;
        return 0;
    }
    printf("Left border test doesn't pass!\n");
    return 1;
}

int leftBorderIncorrectTest(double platform_position)
{
    tests++;
    if(!isLeftBorder(platform_position))
    {
        passed++;
        return 0;
    }
    printf("Left border test doesn't pass!\n");
    return 1;
}

int rightBorderCorrectTest(double platform_position)
{
    tests++;
    if(isRightBorder(platform_position))
    {
        passed++;
        return 0;
    }
    printf("Right border test doesn't pass!\n");
    return 1;
}

