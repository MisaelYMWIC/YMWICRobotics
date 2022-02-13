#include <kipr/botball.h>
void go_straight(int dist)
{
  create_connect();
  create_drive_direct(100,100);
  msleep(dist);
  create_stop();
  create_disconnect();
}

void L_Turn(int degree)
{
  create_connect();
  set_create_total_angle(0);
  while (get_create_total_angle() < degree)
  {
    create_drive_direct(-200,200);
    msleep(20);
  }
  create_stop();
  create_disconnect();
}

void R_Turn(int degree)
{
  create_connect();
  set_create_total_angle(0);
  while (get_create_total_angle() > -degree)
  {
    create_drive_direct(200,-200);

  }
  create_stop();
  create_disconnect();
}

void go_back(int dist)
{
  create_connect();
  create_drive_direct(-100,-100);
  msleep(dist);
  create_stop();
  create_disconnect();
}