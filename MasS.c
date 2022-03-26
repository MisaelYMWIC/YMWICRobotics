#include <kipr/botball.h>
void movearm(int distance)
    //int distance for the amount of ticks you want to move
{
    //there are a total of 1800 ticks for a full rotation of 360 degrees
    //should be between 0 and 2250 ticks for  degrees of arm movement
    cmpc(0);
    while (gmpc(0) < distance)
    {
        motor(0, 50);
    }
    ao();
}
