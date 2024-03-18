# Lab 7: Mobile Robot II

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

<details>
  <summary>Table of Contents</summary>

- [0 (Prelab) Odometry Equations](#0-prelab-odometry-equations)
- [2 Controller](#2-controller)
  - [2.1 Microcontroller Validation](#21-microcontroller-validation)
  - [2.2 Joystick Wiring](#22-joystick-wiring)
  - [2.3 Joystick Validation](#23-joystick-validation)
- [3 Wireless Communications](#3-wireless-communications)
  - [3.1 Microcontroller Validation](#31-microcontroller-validation)
  - [3.2 Receiver MAC Address](#32-receiver-mac-address)
  - [3.3 ESP-NOW Validation](#33-esp-now-validation)
  - [3.4 Sending Joystick Data](#34-sending-joystick-data)
- [4 Mobile Robot](#4-mobile-robot)
  - [4.1 Motor Validation](#41-motor-validation)
  - [4.2 Encoder Validation](#42-encoder-validation)
  - [4.3 Driving Forward](#43-driving-forward)
  - [4.4 Driving via Joystick](#44-driving-via-joystick)
- [5 Competition](#5-competition)
- [6 Feedback Form](#6-feedback-form)

</details>

In this lab, you will be working together as a small team to drive a mobile robot! Some parts of this lab can be performed in parallel, so feel free to skim through the handout and delegate to get through the lab faster.

## 0 (Prelab) Odometry Equations

Estimated time of completion: 5 min

Clone this repository.

In past labs, we asked you to move files into the `robot/` directory in order to run them. This is because we have set the default environment in PlatformIO to be `robot`. Today, we will teach you how to change environments so that you can separate code for the mobile robot and the controller.

Click the button at the bottom of the screen that says `Default (lab6_2024)`. Then, select `env:joystick`. PlatformIO should reconfigure the project. Once it finishes, you can now click the upload button as usual and it should compile and upload code in the `joystick/` directory!

<p align="center">
<img src="./.images/robot_env1.png" alt="drawing" width="600"/>
</p>

To switch back, you can repeat the process above but select `env:robot`.

For this lab, we will **not** remind you to switch environments every time we switch between the controller and the mobile robot. You should do this automatically. Since you are working in a team, it may be easier to keep one laptop connected to the controller and the other connected to the mobile robot, so you don't have to switch environments.

## 2 Controller 
Estimated time of completion: 10 min

First, we need to wire and program a controller. **All wiring and code in this section should be on the controller.**. We have written this lab assuming you will use one joystick as the only input on your controller, but you are welcome to use other sensor/s as well. 

### 2.1 Microcontroller Validation

Run `test_basic/blink_test.cpp`. You should see the onboard LED change colors!

### 2.2 Joystick Wiring

If needed, wire the joystick and update `include/pinout.h`. We recommend you wire `U/D` to `Y_PIN` and `L/R` to `X_PIN`. 

### 2.3 Joystick Validation

Run `test_sensors/joystick_test.cpp` and open the Serial Monitor. You should see values in the range `[0, 4096)` print.

## 3 Wireless Communications

Estimated time of completion: 30 min

Now, we need to set up wireless communications between the controller (*sender*) and the mobile robot (*receiver*) so that the mobile robot can move using controller input. This section is inspired by the [tutorial](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/) in the prelab.

### 3.1 Microcontroller Validation

On the *receiver*, run `test_basic/blink_test.cpp`. You should see the onboard LED change colors! 

Tip: You can use the large `RST` and `BOOT` buttons on the PCB. 

### 3.2 Receiver MAC Address

In order to make sure your controller doesn't accidentally command the other mobile robots, the *sender* needs to broadcast to the MAC address of the *receiver*.  

On the *receiver*, run `test_wireless/get_mac.cpp`. Copy the MAC address to the `TODO` in `test_wireless/esp_now_sender.cpp`.

<details> <summary> <i> How exactly do I copy it? </i> </summary>

 In the curly brackets, type `0x` before each pair of characters and separate them with commas. For example, if the MAC address is `30:AE:A4:07:0D:64`, you should set
 ```
 uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x07, 0x0D, 0x64};
 ```
</details>

### 3.3 ESP-NOW Validation

We will then use test code directly copied from the [tutorial](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/) to send and receive some data. 

On the *receiver*, run `test_wireless/esp_now_receiver.cpp`.

On the *sender*, run `test_wireless/esp_now_sender.cpp`.

On the machine connected to the *receiver*, open the Serial Monitor. You should see received messages in the form
```
THIS IS A CHAR
3
1.2
false
```
where `3` is a random integer that changes every message.

### 3.4 Sending Joystick Data

Now that we can send data wirelessly, we can change the data we send to be the controller inputs. 

Using `test_wireless/esp_now_sender.cpp` and `test_sensors/joystick_test.cpp` as references, fill in `joystick/joystick_wireless.cpp`. `struct joystickData` is defined in `wireless.h`.

On the *sender*, run `joystick/joystick_wireless.cpp`. 

To validate that your code works, we have provided code to receive and print messages. On the *receiver*, run `robot/robot_drive.cpp` and `robot/robot_wireless.cpp`. Open the Serial Monitor and confirm that joystick data is received correctly.

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Show your Serial Monitor with joystick data printing to a TA or LA. |

## 4 Mobile Robot

Estimated time of completion: 30 min

With wireless communications set up, we can now focus on using controller inputs to command the mobile robot. We have already assembled and wired the mobile robots. **All the code in this section should be on the mobile robot.**

### 4.1 Motor Validation

**Make sure the wheels of the mobile robot are all elevated off any surface.** We don't want the mobile robot to drive away! 

Run `test_basic/motor_drive_test.cpp`. You should see each motor drive at two different speeds, in two different directions, one-by-one. Confirm that the wheels spin in the following order: front-left, front-right, back-left, and back-right. 

<details> <summary> <i> Wheels not spinning? </i> </summary> 

Try changing `Serial.begin();` to `Serial.begin(115200);`. Serial may have trouble initializing without an explicit baud rate.

</details>

### 4.2 Encoder Validation

Run `test_basic/encoder_test.cpp` and open the Serial Monitor. You should see each motor's position and velocity printed. Make sure that E1 is front-left, E2 is front-right, E3 is back-left, and E4 is back-right. It is very important that the motors and encoders are in the same order!

### 4.3 Driving Forward

Fill in `robot/robot_drive.cpp` to implement velocity control on all motors. Define the setpoints to all be `2` rad/s. Remember, each motor needs its own PID controller! You may use `test_basic/motor_drive_test.cpp`, `test_basic/encoder_test.cpp`, and `test_basic/motor_velocity_control.cpp` as references.

Hint: You may have to input the negative of `controlEffort` to `motor.drive()` for some motors since they are wired in the opposite way to motor 1.

Run `robot/robot_drive.cpp` and `robot/robot_wireless.cpp` and confirm that all wheels spin at about `2` rad/s and in the direction that would make the mobile robot go forward.

### 4.4 Driving via Joystick

Modify `robot/robot_drive.cpp` so that the setpoints are depedent on `joystick.x` and `joystick.y` instead of just being `2`. Think carefully about how you want to map joystick readings to the individual velocities of the motors.

**While you have not confirmed that your code works, make sure the wheels of the mobile robot stay elevated off any surface.** Run `robot/robot_drive.cpp` and `robot/robot_wireless.cpp`. Confirm that the wheels spin reasonably with respect to the joystick.

You should not need to upload new code on the joystick. Just supply power via the USB-C port of the microcontroller by plugging it into your laptop or a power brick.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your mobile robot in action to a TA or LA. |

## 5 Competition

Estimated time of completion: 15 min

At this point, you should be able to use your joystick to drive your mobile robot around! Feel free to make modifications and/or practice driving. We will have a friendly competition during the last 15 minutes of lab.

## 6 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback. 

| :white_check_mark: CHECKOFF 3 :white_check_mark:   |
|:---------------------------------------------------|
| Show the feedback form completion screen to a TA or LA. |

[^1]: Version 1 - 2016: Peter Yu, Ryan Fish and Kamal Youcef-Toumi  
  Version 2 - 2017: Yingnan Cui and Kamal Youcef-Toumi  
  Version 3 - 2019: Jerry Ng  
  Version 4 - 2023: Joseph Ntaimo, Kentaro Barhydt, Ravi Tejwani, Kamal Youcef-Toumi and Harrison Chin  
  Version 5 - 2024: Jinger Chong, Josh Sohn
