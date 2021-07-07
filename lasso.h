#ifndef __LASSO_H__
#define __LASSO_H__

#include "MovingObject.h"
#include "coin.h"

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 1400
#define WINDOW_Y 800

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1
#define BOMB_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90
#define BOMB_SPEED 100
#define BOMB_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30
#define BOMB_G 40

#define LASSO_SIZE 15
#define LASSO_RADIUS 50
#define COIN_SIZE 10
#define BOMB_SIZE 12

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  int num_coins;
  int life;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin(Coin *coin);
  void check_for_bomb(Bomb *bomb);
  int getNumCoins() { return num_coins; }
  int getLife(){
    if(life<1) {

      closeCanvas();
    initCanvas("Out of lives!", WINDOW_X, WINDOW_Y);

    //interesting output to no lives left

    Turtle pen;
    Circle smiley(700,300,250);

    smiley.setColor(COLOR("red"));
    smiley.setFill(true);

    Circle smiley1(700,300,251);

    smiley1.setColor(COLOR("black"));

    Circle eye1(600,190,40),eye2(800,190,40);
    eye1.setColor(COLOR("white"));
    eye1.setFill(true);
    eye2.setColor(COLOR("white"));
    eye2.setFill(true);

    Circle eyeo1(600,190,41),eyeo2(800,190,41);
    eyeo1.setColor(COLOR("black"));
    eyeo2.setColor(COLOR("black"));


    
    Circle facemaker1(700,400,20);
    facemaker1.setColor(COLOR("white"));
    facemaker1.setFill(true);

    Circle facemaker2(730,405,20);
    facemaker2.setColor(COLOR("white"));
    facemaker2.setFill(true);

    Circle facemaker3(670,405,20);
    facemaker3.setColor(COLOR("white"));
    facemaker3.setFill(true);

    Circle facemaker4(760,415,20);
    facemaker4.setColor(COLOR("white"));
    facemaker4.setFill(true);

    Circle facemaker5(640,415,20);
    facemaker5.setColor(COLOR("white"));
    facemaker5.setFill(true);

    Circle facemaker6(790,430,20);
    facemaker6.setColor(COLOR("white"));
    facemaker6.setFill(true);

    Circle facemaker7(610,430,20);
    facemaker7.setColor(COLOR("white"));
    facemaker7.setFill(true);

    Text Bomb1(700,600,"OOPS! You are out of lives and so,");
    Text Bomb2(700,630,"your game has ended!");
    Text Bomb3(700,660,"Better luck next time..");
    Text Bomb5(700,690,"Thank you for playing!");
    Text Bomb4(700,720,"Please wait. Auto-close in 10 seconds.");

    Text Fancy1(350,150,"NO");
    Text Fancy2(1050,150,"NO");
    Text Fancy3(350,250,"MORE");
    Text Fancy4(1050,250,"MORE");
    Text Fancy5(350,350,"LIVES");
    Text Fancy6(1050,350,"LIVES");
    Text Fancy7(350,450,"LEFT");
    Text Fancy8(1050,450,"LEFT");

    hide();
    wait(10);


 
    cout<<"All lives lost and game ended"<<endl;
    exit(0);}

    if(life==1) {
      Text lastLife1(PLAY_X_START+200, 350, "WARNING!!");
      lastLife1.setColor(COLOR("red"));
      Text lastLife2(PLAY_X_START+200, 380, "LAST LIFE!!");
      lastLife2.setColor(COLOR("red"));

    }
    return life;

  }

  

}; // End class Lasso

#endif
