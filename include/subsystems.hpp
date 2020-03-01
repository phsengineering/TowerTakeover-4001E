#include "main.h"
using namespace pros;

extern Motor rightFrontDrive;
extern Motor rightBackDrive;
extern Motor leftFrontDrive;
extern Motor leftBackDrive;
extern Motor tray;
extern Motor rightIntake;
extern Motor leftIntake;
extern Motor lift;
void drive(int analogY, int analogX);
void intakeHandler(int speed);
void trayHandler(int speeed);
void liftHandler(int speed);
void autoDrive(int speed);
