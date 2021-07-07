#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

using namespace simplecpp;

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);



  //beginning of Enhancement -Helpbox


  Text helpboxHeader(950,90,"__________________CONTROLS__________________");
  Text helpbox1(950,127, "Press 't' to release Lasso.");
  Text helpbox2(950,154, "Press 'y' to retract released Lasso.");
  Text helpbox3(950,181, "Press 'l' to loop the Lasso, i.e. grab");
  Text helpbox4(950,208, "Press '[' to decrease release angle with horizontal");
  Text helpbox5(950,235, "Press ']' to increse release angle with horizontal");
  Text helpbox6(950,262, "Press '=' to increase release speed");
  Text helpbox7(950,289, "Press '-' to reduce release speed");
  Text helpbox8(950,316, "Press 'q' to exit the game");


  Rectangle helpboxOutline(950,198,800,316);


  helpboxHeader.setColor(COLOR("brown"));
  helpbox1.setColor(COLOR("violet"));
  helpbox2.setColor(COLOR("indigo"));
  helpbox3.setColor(COLOR("blue"));
  helpbox4.setColor(COLOR("green"));
  helpbox5.setColor(COLOR("gold"));
  helpbox6.setColor(COLOR("orange"));
  helpbox7.setColor(COLOR("red"));
  helpbox8.setColor(COLOR("violet"));


  //end of Enhancement -Helpbox


  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;


  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s

  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("green"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("green"));

  string msg("Key Pressed: _");
  Text charPressed(PLAY_X_START+100, PLAY_Y_HEIGHT+20, msg);


  //'life' feature main body 


  char life[10];
  sprintf(life, "Lives Remaining: %d", lasso.getLife());
  Text lifeCount(PLAY_X_START+200, 100, life);


  Text lifeInstructions1(PLAY_X_START+230, 150, "If your lasso is looped/yanked and");
  lifeInstructions1.setColor(COLOR("blue"));

  Text lifeInstructions2(PLAY_X_START+230, 180, "no stone is caught, you lose a life!");
  lifeInstructions2.setColor(COLOR("blue"));

  Text lifeWarning1(PLAY_X_START+200, 250, "Game will end when you");
  lifeWarning1.setColor(COLOR("red"));
  Text lifeWarning2(PLAY_X_START+200, 280, "lose all 3 lives!");
  lifeWarning2.setColor(COLOR("red"));

  Text bombWarning(PLAY_X_START+223, 320, "Catch a black bomb, and game ends!");
  bombWarning.setColor(COLOR("black"));


  //end of life feature main body


  char coinScoreStr[256];
  sprintf(coinScoreStr, "Score/Stones: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+100, PLAY_Y_HEIGHT+50, coinScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;

  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  //additional code for bomb

  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = BOMB_ANGLE_DEG;
  double bomb_ax = 0;
  double bomb_ay = BOMB_G;

  Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);

  //end additional code for bomb

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;
  double last_bomb_jump_end = 0;
  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit
  cout<<"Game transcript"<<endl;
  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
  cout<<"A lasso release at "<<currTime<<endl;
	lasso.unpause();

	break;
      case 'y':
  cout<<"A lasso yank at "<<currTime<<endl;
  lasso.check_for_coin(&coin);
	lasso.yank();
	break;
      case 'l':
  cout<<"A lasso looping at "<<currTime<<endl;
	lasso.loopit();
	lasso.check_for_coin(&coin);
  lasso.check_for_bomb(&bomb); //bomb check
  
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
  cout<<"Lasso release speed reduced at "<<currTime<<endl;
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
  cout<<"Lasso release speed increased at "<<currTime<<endl;
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
  cout<<"Game was quit by user at "<<currTime<<endl;
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    //bomb reset and unpause START

    bomb.nextStep(stepTime);

    if(bomb.isPaused()) {
      if((currTime-last_bomb_jump_end) >= BOMB_GAP) {
  bomb.unpause();
      }
    }

    if(bomb.getYPos() > PLAY_Y_HEIGHT) {
      bomb.resetBomb();
      last_bomb_jump_end = currTime;
    }

    //bomb reset and unpause END
    

    sprintf(life, "Lives Remaining: %d", lasso.getLife());
    lifeCount.setMessage(life);

    sprintf(coinScoreStr, "Score/Stones: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;

    wait(stepTime);
  } // End for(;;)

  wait(3);
} // End main_program
