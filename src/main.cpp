#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START IQ MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END IQ MACROS


// Robot configuration code.
inertial BrainInertial = inertial();
controller Controller = controller();



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

#pragma endregion VEXcode Generated Robot Configuration

//----------------------------------------------------------------------------
//                                                                            
//    Module:       main.cpp                                                  
//    Author:       {author}                                                  
//    Created:      {date}                                                    
//    Description:  IQ project                                                
//                                                                            
//----------------------------------------------------------------------------

// Include the IQ Library
#include "iq_cpp.h"

// Allows for easier use of the VEX Library
using namespace vex;

int lf[4] = {20, 33, 20, 73};
int rt[4] = {139, 33, 139, 73};
int speed1 = 2;
int speed2 = 2;

void draw(int a[4]) {
  Brain.Screen.drawLine(a[0], a[1], a[2], a[3]);
}

int main() {
  // Begin project code
  srand(Brain.Timer.system());
  int ball[2] = {79, rand() % 106};
  Brain.Screen.setFillColor(yellow);
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.drawLine(79, 0, 79, 106);
    if(Controller.ButtonEUp.pressing() && lf[1] >= 0) {
      lf[1] -= 2;
      lf[3] -= 2;
    }
    if(Controller.ButtonEDown.pressing() && lf[3] <= 106) {
      lf[1] += 2;
      lf[3] += 2;
    }
    if(Controller.ButtonFUp.pressing() && rt[1] >= 0) {
      rt[1] -= 2;
      rt[3] -= 2;
    }
    if(Controller.ButtonFDown.pressing() && rt[3] <= 106) {
      rt[1] += 2;
      rt[3] += 2;
    }
    draw(lf);
    draw(rt);
    Brain.Screen.drawCircle(ball[0], ball[1], 3);
    ball[0] += speed1;
    ball[1] += speed2;
    if(ball[0] > 158) {
      Brain.Screen.clearScreen();
      Brain.Screen.setFillColor(black);
      Brain.Screen.print("Left Win");
      break;
    }
    if(ball[0] >= 138 && ball[0] <= 140 && rt[1] <= ball[1] && ball[1] <= rt[3]) {
      speed1 = -2;
      if(rand() % 2 == 0) {
        speed2 = -2;
      } else {
        speed2 = 2;
      }
    }
    if(ball[1] > 106) {
      ball[1] = 106;
      speed2 = -2;
    }
    if(ball[0] < 0) {
      Brain.Screen.clearScreen();
      Brain.Screen.setFillColor(black);
      Brain.Screen.print("Right Win");
      break;
    }
    if(ball[0] >= 19 && ball[0] <= 21 && lf[1] <= ball[1] && ball[1] <= lf[3]) {
      speed1 = 2;
      if(rand() % 2 == 0) {
        speed2 = -2;
      } else {
        speed2 = 2;
      }
    }
    if(ball[1] < 0) {
      ball[1] = 0;
      speed2 = 2;
    }

    wait(50, msec);
  }
  while (!Brain.buttonCheck.pressing()) {
    wait(20, msec);
  }
}
