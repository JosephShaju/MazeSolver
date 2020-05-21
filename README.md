# Maze Solver Robot

Re-engineered a six-degree of freedom Stewart-Gough platform to solve a marble maze.The robot was designed and developed to solve any given maze by controlling the maze platform using a phone via Bluetooth.
The maze platform’s tilt and pan angles are determined by the phone’s tilt and pan angles that are obtained via the accelerometer and the gyroscope on the phone. 


![image1](https://user-images.githubusercontent.com/26580185/82514827-b51cb580-9ae4-11ea-8773-6b667e06c22c.jpg)


The platform was controlled using an Arduino Board and a Bluetooth module that was plugged in to the Arduino.

The file FinalCode.ino contains the complete Inverse Kinematics calculations that can be changed according to the dimensions of your model and if you map the values to a PS4/Xbox Joystick you should be able to control the platform accurately.

(Here is a video of our initial prototype: https://drive.google.com/file/d/1CEXkzg-nl-BIN54GoGaWJMK97bvith1F/view )
