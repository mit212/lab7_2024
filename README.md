# Lab 7: Mobile Robot II

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

<details>
  <summary>Table of Contents</summary>

- [1 Controller](#1-controller)
  - [1.1 Get MAC Address](#11-get-mac-address)
  - [1.2 Validate Controller](#12-validate-controller)
  - [1.3 Run Controller](#13-run-controller)
- [2 Mobile Robot](#2-mobile-robot)
  - [2.1 Get MAC Address](#21-get-mac-address)
  - [2.2 Run Joystick Control](#22-run-joystick-control)
- [3 Trajectories](#3-trajectories)
  - [3.1 Understand Odometry](#31-understand-odometry)
  - [3.2 Circle](#32-circle)
  - [3.3 U-Turn](#33-u-turn)
  - [3.4 Custom Path](#34-custom-path)
- [4 Feedback Form](#4-feedback-form)

</details>

We have already written most of the code for this lab. We hope that you will use this free time to understand the mobile robot codebase and prepare for the final competition. Have a great Spring Break!

## 1 Controller
Connect to the microcontroller on your controller and change your PlatformIO environment to be `env:controller`.

<details> <summary> <i> Forget how to change environments? </i> </summary>

Please refer to the [instructions from Lab 6](
https://github.com/mit212/lab6_2024?tab=readme-ov-file#1-changing-platformio-environment).

</details>

### 1.1 Get MAC Address

Run `lib/Wireless/examples/get_mac.cpp` (you will have to move it to the `src/controller/` folder). Open `lib/Wireless/wireless.h` and change `controllerAddr` to this MAC address.

### 1.2 Validate Controller

Run `src/test_controller/controller_test.cpp`. You should see joystick readings being printed to your Serial monitor.

### 1.3 Run Controller

Run `src/controller/controller_main.cpp` and `src/controller/controller_wireless.cpp`. This will read the joystick and set up two-way wireless communication with the microcontoller on the mobile robot.

## 2 Mobile Robot

Connect to the microcontroller on your mobile robot and change your PlatformIO environment to be `env:robot`.

### 2.1 Get MAC Address

Run `lib/Wireless/examples/get_mac.cpp` (you will have to move it to the `src/robot/` folder). Open `lib/Wireless/wireless.h` and change `robotAddr` to this MAC address.

### 2.2 Run Joystick Control

Run `src/robot/robot_main.cpp`, `src/robot/robot_drive.cpp`, `src/robot/robot_motion_control.cpp`, and `src/robot/robot_wireless.cpp`. This will implement a PID controller to follow velocity setpoints based on either joystick or a given trajectory, calculate odometry data, and set up two-way wireless communication with the microcontoller on the controller.

At this point, you should be able to drive your mobile robot around with your joystick!

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Show your mobile robot in action to a TA or LA. |

## 3 Trajectories

### 3.1 Understand Odometry

Open `src/robot/robot_motion_control.cpp` and read through `updateOdometry()`. Make sure that you understand exactly how this function calculates odometry data.

### 3.2 Circle

In the same file, comment out `#define JOYSTICK` and uncomment `#define CIRCLE`. This will change the `followTrajectory()` function to follow a circle instead of the joystick setpoint. Your mobile robot should now autonomously follow a circle.

### 3.3 U-Turn

In the same file, comment out `#define CIRCLE` and uncomment `#define UTURN`. Your mobile robot should now autonomously follow a U-Turn.

### 3.4 Custom Path

In the same file, comment out `#define UTURN` and uncomment `#define YOUR_TRAJECTORY`. In the `followTrajectory()` function, make your own path using a state machine, taking `UTURN` as inspiration.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your mobile robot in action to a TA or LA. |


Estimated time of completion: 5 min

## 4 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback. 

| :white_check_mark: CHECKOFF 3 :white_check_mark:   |
|:---------------------------------------------------|
| Show the feedback form completion screen to a TA or LA. |

[^1]: Version 1 - 2016: Peter Yu, Ryan Fish and Kamal Youcef-Toumi  
  Version 2 - 2017: Yingnan Cui and Kamal Youcef-Toumi  
  Version 3 - 2019: Jerry Ng  
  Version 4 - 2023: Joseph Ntaimo, Kentaro Barhydt, Ravi Tejwani, Kamal Youcef-Toumi and Harrison Chin  
  Version 5 - 2024: Jinger Chong, Josh Sohn
