#include "../src/arkanoid.h"

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

int rightBorderIncorrectTest(double platform_position)
{
    tests++;
    if(!isRightBorder(platform_position))
    {
        passed++;
        return 0;
    }
    printf("Right border test doesn't pass!\n");
    return 1;
}

int ballCollapsingCorrectTest(block b)
{
    tests++;
    b.setPos(330, 420);
    
    if(collapse(b))
    {
        passed++;
        return 0;
    }
    printf("Ball collapsing test doesn't pass!\n");
    return 1;
}

int ballCollapsingIncorrectTest(block b)
{
    tests++;
    b.setPos(300, 300);
    if(!collapse(b))
    {
        passed++;
        return 0;
    }
    printf("Ball collapsing test doesn't pass!\n");
    return 1;
}

int main()
{
    leftBorderCorrectTest(-5);
    leftBorderIncorrectTest(100);
    rightBorderCorrectTest(600);
    rightBorderIncorrectTest(300);
    ballCollapsingCorrectTest(b);
    ballCollapsingIncorrectTest(b);
    printf("\n%d tests passed out of %d\n", passed, tests);
    return 0;
}
