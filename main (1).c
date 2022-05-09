#include <kipr/wombat.h>
//2022 Create Code by Misael Ventura & Xavier McClanahan
/*
This code will succesfully grab bot guy and 1 red cube and place them onto the airlock with an addition 
to a failsafe where if botguy is not obtained it will proceed to grab 1 red cube and place ontop of the airlock.


Create Code: 6 Main steps that the create will go throught 

Step 1: move to where the robot is perpendicular to botguy.
step 2: move towards botguy using line follow to center the robot.
step 3: move backwards and follow the black line up then turn 90 degrees to the right, bump into the wall and turn
towards airlock and place botguy.
step 4: get red cube and place on airlock

failsafe: botguy is not grabbed proceed to red cube and place on airlock



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
void movetopar();
void botguy();
void awaybotguy();
void cube_grab();
void clawcount();
int main()
{
    // wait_for_light(0);
    shut_down_in(119);
    movetopar();//move until robot is perpendicular to botguy
    botguy();//move towards botguy and grab him then place onto airlock.

    create_disconnect();



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
    while(gmpc(2) < dist)
    {
        mav(2,2000);
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
        mav(2,-1500);
        ao();
    }
    while (digital(0)==1)
    {
        mav(2,1000);
        msleep(500);
        ao();
    }
    cmpc(2);
}
void mas_armdown(int dist)
{
    while(gmpc(2) > dist )
    {
        motor(2,-100);
    }
    ao();
}
void square_up(int gray)//squares up with the balck line to make sure robot is straight
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
void start_go_back(int dist)//go backwards.
{
    set_create_distance(0);
    while (get_create_distance()>dist)
    {
        create_drive_direct(-200,-200);

    }
    create_stop();
}

void start()// code for starting phase of the robot
{
    square_up(2100);
    create_drive_direct(-200,-200);
    msleep(500);
    start_go_back(-445);
    R_turn(92);
}
void linefollow(int dist)//follows line
{
    int threshold = 2300;
    int speed = 150;
    set_create_distance(0);
    while(get_create_distance() < dist)
    {


        if (get_create_lfcliff_amt() < threshold)
        {
            create_drive_direct(0.5*speed, speed);
        }
        else
        {
            create_drive_direct(speed,0.5*speed);
        }
    }
    ao();
}
void linefollow_bump()//follows line
{
    int threshold = 2300;
    int speed = 150;
    set_create_distance(0);
    while((get_create_rbump() == 0) && (get_create_lbump() == 0))
    {
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

void botguy_square_up(int gray)//squares up to be straight onto botguy.
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
void movetopar()//move parrallel to botguy
{
    create_connect();
    enable_servos();// start by connecting create


    start();//code to squareup at the beginning 
    arm_down();//put the arm down to have point 0
    set_servo_position(0,2045);//open claw
    MasS_movearm(18500);//move arm up
    go_straight(500);//move
    go_straight(50);//move
}
void botguy()
{
    /*Follow line up to botguy, grab botguy, back up and turn. then follow line, if botuy is in claw turn right, go straight 
    until bump, turn and place botguy on airlock. if botguy is not in claw, lower arm, turn left, go straight, grab box.  */
    linefollow_bump();//flows line to botguy
    create_drive_direct(0,0);//stops infront of botguy
    msleep(1000);
    set_servo_position(0,840);//close claw
    msleep(1000);
    go_back(-400);//go backwards from botguy
    R_turn(90);//turn towards the black line
    linefollow(600);//folow line for a certain distance
    if (digital(2)==1)//if claw is clicked proceed like noraml.
    {
        R_turn(90);
        printf("Angle Value %d\n", get_create_total_angle());
        while((get_create_rbump() == 0) && (get_create_lbump() == 0))
        {
            create_drive_direct(75,75);
        }
        awaybotguy();
    }
    if (digital(2)==0)//if switch is not clicked do fail safe.
    {
        set_servo_position(0,2045);
        create_drive_direct(0,0);
        msleep(500);
        cube_grab();
        ao();

    } 
}
void awaybotguy()//leaves botguy
{
    go_back(-100);// after bump move a bit back 
    L_turn(80);//turn slightly to the left to be close to the airlock
    go_straight(75);//move a bit forwards towards the airlock to get the claw in a better place
    mas_armdown(11500);//move the claw down to place botguy
    set_servo_position(0,2045);
}
void cube_arm()
{
    while (gmpc(2)<600)
    {
        mav(2,1000);
    }
    ao();
}
void cube_grab()
{
    set_servo_position(0,2450);
    arm_down();

    cube_arm();

    L_turn(87);

    go_straight(150);
    
    set_servo_position(0,840);
    
    go_back(150);
    create_drive_direct(0,0);
    msleep(500);
    R_turn(180);
    create_drive_direct(0,0);
    msleep(500);
    MasS_movearm(8500);
    botguy_square_up(2100);
    while((get_create_rbump() == 0) && (get_create_lbump() == 0))
        {
            create_drive_direct(75,75);
        }
    awaybotguy();
}

void clawcount()
{
    enable_servos();
    int count = 2000;
    while(count < 0)
    {
        msleep(100);
        count = count + 50;
        set_servo_position(0,count);
    }
}
    