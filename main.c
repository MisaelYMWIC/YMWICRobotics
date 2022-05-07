#include <kipr/wombat.h>
//2022 Create Code by Misael Ventura & Xavier McClanahan
/*
This code will succesfully grab bot guy, 2 red cubes,and 2 green cubes along with placing them on the airlock in
the correct color orientation. If time allows the create bot will also push all the poms off the black line.


Create Code: 6 Main steps that the create will go throught 

Step 1: Go straigth out of the starting box until perpendicular to bot guy
		Once perpendicular to bot guy, turn 90 degrees to the left and move
        towards bot guy untill bump and grab bot guy and put him in the containers 

Step 2: Turn 90 degrees to the right facing the cubes, Move x distance untill the
		front of the create bot is next to the first cube, grab first cube and 
        place into correct container. Repeat same steps for all cube until they
        are gathered and put into their correct container.

Step 3: Begin to move towards the airlock with all items on the back of the create
		bot. 

Step 4: Place bot guy onto red side of airlock along with the red cubes.

Step 5: Turn the airlock 180 degrees so that the green side is facing the create bot.

Step 6: Place all of the green cubs onto airlock.

optional Step 7: move all the poms off the black line.

*/

/*
Void statement and their descriptions

void go_straight: move forwards for x distance

void L_turn: turn exactly x degrees to the left

void R_turn: turn exactly x degrees to the right

void go_back: move backwards for x amount of distance

void MasS_movearm: Move the moter as a servor for x distance

void go_Straight_till_bump: the create will move forwards until one of its bumps sensors is touched
*/
void go_straight(int dist);
void L_turn(int degree);
void R_turn(int degree);
void go_back(int dist);
void MasS_movearm(int dist);
void go_Straight_till_bump();
void arm_down();
void mas_armdown(int dist);
void square_up(int gray);
void start_go_back(int dist);
void start();
void linefollow(int dist);
void botguy_square_up(int gray);
int main()
{
    shut_down_in(119);
    create_connect();
    enable_servos();// start by connecting create
    arm_down();
    set_servo_position(0,2045);
    MasS_movearm(19500);
    
    //step 1
            

    //go_straight(715);
    //printf("Value: %d\n", get_create_distance());
    //printf("went straight\n");
    //L_turn(87);
    //printf("turned left\n");
    start(); 
    go_straight(500);
    botguy_square_up(2100);
    go_straight(50);
    linefollow(200);
    printf("went till bump\n");
    set_servo_position(0,1100);
    msleep(1000);
    go_back(-100);
    printf("went backward\n");
    
    printf("botguy is grabbed\n");
    printf("Angle Value %d\n", get_create_total_angle());
    //grab_botguy; code yet to be implimented.
   

  //  step 2
		//	steps to be implemented */
   if (digital(2)==1)
    {
    R_turn(130);
    go_straight(950);
    printf("Angle Value %d\n", get_create_total_angle());
    printf("does step 2\n");
	mas_armdown(11500);
    set_servo_position(0,2045);
    go_back(-300);
    }
    if (digital(2)==0)
    {
	set_servo_position(0,2045);
    ao();
        create_disconnect();
   } 
    //step 3
		//	steps to be implemented*/
    /*printf("does step 3\n");
    
    L_turn(179);
    printf("Angle Value %d\n", get_create_total_angle());
    go_straight(1000);
    R_turn(90);
    printf("Angle Value %d\n", get_create_total_angle());

    */
    /*step 4
			steps to be implemented */
    printf("does step 4\n");
    /*
    step 5
			steps to be implemented */
    printf("does step 5\n");
    /*
    step 6
			steps to be implemented */
    printf("does step 6\n");
    /*

    if time allows Step 7
    		steps to be implemented 

   */
    return 0;
}


void go_straight(int dist)
{
    //create_connect();
    set_create_distance(0);
    while(get_create_distance() < dist)
    {
        create_drive_direct(300,300);
        msleep(50);
    }
    create_stop();
    //create_disconnect();
}

void L_turn(int degree)
{
    //create_connect();
    set_create_total_angle(0);
    while (get_create_total_angle() < degree)
    {
        create_drive_direct(-100,100);
        msleep(50);
    }
    create_stop();
}

void R_turn(int degree)
{
    //create_connect();
    set_create_total_angle(0);
    while(get_create_total_angle() > -degree)
    {
        create_drive_direct(200,-200);
    }
    create_stop();
}

void go_back(int dist)
{
    //create_connect();
    set_create_distance(0);
    while(get_create_distance() > dist) //need to have negative distance 
    {
        create_drive_direct(-200,-200);
        msleep(10);
    }
    create_stop(); 
}

void MasS_movearm(int dist)
{
    cmpc(0);
    while(gmpc(0) < dist)
    {
        mav(0,1500);
    }
    ao();
}

void go_Straight_till_bump()
{

    //create_connect();


    while((get_create_rbump() == 0) && (get_create_lbump() == 0))
    {
        create_drive_direct(100,100);
        msleep(50);
    }
    create_stop();
    //create_disconnect();
}

//void Claw_code
void arm_down()
{
    while (digital(0)==0)
    {
    mav(0,-1500);
    }
    ao();
    while (digital(0)==1)
    {
    mav(0,1000);
    msleep(500);
    ao();
    }
}
void mas_armdown(int dist)
{
while(gmpc(0) > dist )
    {
        motor(0,-100);
    }
    ao();
}
  void square_up(int gray)
{
    while (1){
        if(get_create_lcliff_amt()> gray && get_create_rcliff_amt()> gray)
        {
            create_drive_direct(-200,-200);
        }
        if(get_create_rcliff_amt()< gray)
        {
            create_drive_direct(-200,0);
        }
         if(get_create_lcliff_amt()< gray)
        {
            create_drive_direct(0,-200);
        }
         if(get_create_lcliff_amt()< gray && get_create_rcliff_amt()< gray)
        {
            create_drive_direct(0,0);
              break;
         }
    }
}
void start_go_back(int dist)
{
    set_create_distance(0);
    while (get_create_distance()>dist)
    {
    	create_drive_direct(-200,-200);
        
    }
    create_stop();
}

void start()
{
    square_up(2100);
    create_drive_direct(-200,-200);
    msleep(500);
    start_go_back(-445);
    R_turn(92);
}
void linefollow(int dist)
{
    int threshold = 2300;
    int speed = 150;
    
    printf("Follow the non-yellow brick road!\n");
    set_create_distance(0);
 while(get_create_distance() < dist)
 {
         printf("Following the non-yellow brick road!\n");

		if (get_create_lfcliff_amt() < threshold)
        {
            create_drive_direct(0.5*speed, speed);
        }
        else
        {
            create_drive_direct(speed, 0.5*speed);
        }
    }
    ao();
}

 void botguy_square_up(int gray)
{
    while (1){
        if(get_create_lcliff_amt()> gray && get_create_rcliff_amt()> gray)
        {
            create_drive_direct(200,200);
        }
        if(get_create_rcliff_amt()< gray)
        {
            create_drive_direct(200,0);
        }
         if(get_create_lcliff_amt()< gray)
        {
            create_drive_direct(0,200);
        }
         if(get_create_lcliff_amt()< gray && get_create_rcliff_amt()< gray)
        {
            create_drive_direct(0,0);
              break;
         }
    }
 }


