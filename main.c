
#include <kipr/botball.h>
#include "Create_Movement.h"
int main()
{
  go_straight(2000);
  printf("went straight/n");
  L_Turn(90);
  printf("turned left/n");
  R_Turn(90);
  printf("turned right/n");
  go_back(2000);
  printf("went back/n");
  
  
  
  create_stop();
  return 0;
}
