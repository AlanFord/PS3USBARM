# PS3USBARM
## PS3 joystick control for a 6-axis killer robot arm

The sketch requires the use of the **USB Host Shield Library Version 2.0**.  It can be downloaded and installed from the 
Arduino IDE menu by selecting "Sketch", "Include Library", "Manage Libraries...".  Scroll down the list of libraries until you find the USB Host Shield Library 2.0, select it, and click on the "Install" button.


This is a simple arduino sketch to read a PS3 basic controller connected to a USB host shield.  Control of 6 axes is accomplished by using the two joysticks and the "front" buttons.  The axes and buttons are mapped as follows:

Robot arm axes are mapped as follows:  
 * LeftHatX  -> wrist joint rotation -> B axis  
 * LeftHatY  -> elbow                -> Y axis  
 * RightHatX -> base                 -> X axis  
 * RightHatY -> shoulder             -> Z axis  
 * Button2   -> wrist joint pivot    -> A axis  
 * Button1   -> gripper              -> C axis  

Optional bottons on top of the controller can be used for other features on the robot arm (lights, sound, activate laser, activate machine gun, etc.).  These are mapped as follows:  
 * Square button -> Opt1  
 * Circle button -> Opt2  
 * Cross Button -> Opt3  
 * Triangle Button -> Opt4  

The control data is transmitted out the serial port using a two-byte data structure that is mapped as follows:  

 
 ```
 MSB                                                                                        LSB   
 Bit:   | 15   | 14   | 13   | 12   | 11 | 10 | 9  | 8  | 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0   
 Event: | Opt4 | Opt3 | Opt2 | Opt1 | C+ | C- | B+ | B- | A+ | A- | Z+ | Z- | Y+ | Y- | X+ | X-   
```
If reading the control data one byte at a time, remember that the least-significant byte will be sent first, followed by the most significant byte.  In otherwords, bits 0-7 are sent first followed by bits 8-15.

If the control data is all zeros, this means the joystick controls are idle.  No further control data will be transmitted until the joystick is active again.
