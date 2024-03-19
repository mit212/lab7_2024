#ifndef ROBOT_DRIVE_H
#define ROBOT_DRIVE_H

#define NUM_MOTORS 4

#define Kp 0.5
#define Ki 0
#define Kd 0
#define pidTau 0.1

#define MAX_FORWARD 6
#define MAX_TURN 3

void setupDrive();
void updateSetpoints(double left, double right);
void updatePIDs();

#endif // ROBOT_DRIVE_H