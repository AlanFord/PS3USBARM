# PS3USBARM
PS3 joystick control for a 6-axis killer robot arm

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
MSB  |                                                LSB   
 Bit: |     15   |  14   |   13  |   12   |  11 | 10 | 9  | 8  | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0   
 Event: | Opt4 | Opt3 | Opt2 | Opt1 | C+ | C- | B+ | B- | A+ | A- | Z+ | Z- | Y+ | Y- | X+ | X-   

