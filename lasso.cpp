#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

using namespace simplecpp;

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("brown"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;
  life=3;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("brown"));

  lasso_band.setColor(COLOR("BlueViolet"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin != NULL) {
    num_coins++;
    the_coin->resetCoin();
  }
} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin(Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    cout<<"A stone was caught "<<endl;
    the_coin = coinPtr;
    the_coin->getAttachedTo(this);
  }
  else{
    life--;
    cout<<"Oops! A life was lost. "" Remaining lives are "<<life<<endl;
    the_coin=NULL;}
  }

void Lasso::check_for_bomb(Bomb *bombPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    cout<<"A bomb was caught, ending the game"<<endl;
    closeCanvas();
    initCanvas("You Caught a Bomb!", WINDOW_X, WINDOW_Y);

    //interesting output to bomb catching

    Turtle pen;
    Circle smiley(700,300,250);

    smiley.setColor(COLOR("yellow"));
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
    facemaker1.setColor(COLOR("red"));
    facemaker1.setFill(true);

    Circle facemaker2(730,405,20);
    facemaker2.setColor(COLOR("red"));
    facemaker2.setFill(true);

    Circle facemaker3(670,405,20);
    facemaker3.setColor(COLOR("red"));
    facemaker3.setFill(true);

    Circle facemaker4(760,415,20);
    facemaker4.setColor(COLOR("red"));
    facemaker4.setFill(true);

    Circle facemaker5(640,415,20);
    facemaker5.setColor(COLOR("red"));
    facemaker5.setFill(true);

    Circle facemaker6(790,430,20);
    facemaker6.setColor(COLOR("red"));
    facemaker6.setFill(true);

    Circle facemaker7(610,430,20);
    facemaker7.setColor(COLOR("red"));
    facemaker7.setFill(true);

    Text Bomb1(700,600,"OOPS! You caught a bomb and so,");
    Text Bomb2(700,630,"your game has ended!");
    Text Bomb3(700,660,"Better luck next time..");
    Text Bomb5(700,690,"Thank you for playing!");
    Text Bomb4(700,720,"Please wait. Auto-close in 10 seconds.");

    Text Fancy1(350,150,"B");
    Text Fancy2(1050,150,"B");
    Text Fancy3(350,250,"O");
    Text Fancy4(1050,250,"O");
    Text Fancy5(350,350,"M");
    Text Fancy6(1050,350,"M");
    Text Fancy7(350,450,"B!");
    Text Fancy8(1050,450,"B!");

    hide();
    wait(10);


 
   
    exit(0);
  }
  

  
} // End Lasso::check_for_coin and bomb ()

