/*
 Test of a joystick controller sending serial command data to a 6-axis robotic arm.
 
 Robot arm axes are mapped as follows:
 LeftHatX  -> wrist joint rotation -> B
 LeftHatY  -> elbow                -> Y
 RightHatX -> base                 -> X
 RightHatY -> shoulder             -> Z
 Button2   -> wrist joint pivot    -> A
 Button1   -> gripper              -> C

 The 2 byte output data buffer is mapped as follows:
        MSB                                                  LSB
 Bit:   15   14   13   12   11 10 9  8  7  6  5  4  3  2  1  0 
 Event: Opt4 Opt3 Opt2 Opt1 C+ C- B+ B- A+ A- Z+ Z- Y+ Y- X+ X-
*/


// these #define statements will make bit masking statements easier to read 
#define XMINUS 0
#define XPLUS  1
#define YMINUS 2
#define YPLUS  3
#define ZMINUS 4
#define ZPLUS  5
#define AMINUS 6
#define APLUS  7
#define BMINUS 8
#define BPLUS  9
#define CMINUS 10
#define CPLUS  11
#define OPT1   12
#define OPT2   13
#define OPT3   14
#define OPT4   15


#include <PS3USB.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
PS3USB PS3(&Usb);

//////////////////////////////////////////////////////////////////////////////
// Here we are defining a 2 byte variable called "output" that is of type
// "Output_Packet_t".  This allows us to access these 2 bytes as either an
// unsigned integer "output.outputData" or as an array of bytes "output.byteArray".

typedef union Output_Packet_t {
 unsigned int outputData;
 char  byteArray[2];
};

Output_Packet_t output;
//////////////////////////////////////////////////////////////////////////////

bool buttonsWerePressed = true;   // flag indicating previous joystick activity

void setup() 
{
  // initialize the serial connection
  Serial.begin(115200);

  // verify the USB port (i.e. joystick) has initialized correctly
  if (Usb.Init() == -1) {
    while (1); //halt
  }
  // Make sure the serial buffer is clear
  //while (Serial.availableForWrite() !=0) {
    //Serial.println("waiting");
    //; // wait for serial output buffer to clear
  //}   
}

void loop() {
  Usb.Task();

  if (PS3.PS3Connected) {
    // Serial.println("we are connected");
    readJoystick();
    sendTheBytes();  
  }
}

void readJoystick() {
  output.outputData = 0;  // clear the output data buffer;
  if (PS3.getAnalogHat(LeftHatX) > 137) {
    output.outputData = output.outputData | (0x0001<<BPLUS);
  }
  else if (PS3.getAnalogHat(LeftHatX) < 117) {
    output.outputData = output.outputData | (0x0001<<BMINUS);
  }
  if (PS3.getAnalogHat(LeftHatY) > 137) {
    output.outputData = output.outputData | (0x0001<<YMINUS);
  }
  else if (PS3.getAnalogHat(LeftHatY) < 117) {
    output.outputData = output.outputData | (0x0001<<YPLUS);
  }
  if (PS3.getAnalogHat(RightHatX) > 137) {
    output.outputData = output.outputData | (0x0001<<XPLUS);
  }
  else if (PS3.getAnalogHat(RightHatX) < 117) {
    output.outputData = output.outputData | (0x0001<<XMINUS);
  }
  if (PS3.getAnalogHat(RightHatY) > 137) {
    output.outputData = output.outputData | (0x0001<<ZMINUS);
  }
  else if (PS3.getAnalogHat(RightHatY) < 117) {
    output.outputData = output.outputData | (0x0001<<ZPLUS);
  }
  if (PS3.getButtonPress(L1)) {
    output.outputData = output.outputData | (0x0001<<CMINUS);
  }
  else if (PS3.getButtonPress(R1)) {
    output.outputData = output.outputData | (0x0001<<CPLUS);
  }
  if (PS3.getButtonPress(L2)) {
    output.outputData = output.outputData | (0x0001<<AMINUS);
  }
  else if (PS3.getButtonPress(R2)) {
    output.outputData = output.outputData | (0x0001<<APLUS);
  }  
  if (PS3.getButtonClick(CIRCLE)) {
    output.outputData = output.outputData | (0x0001<<OPT2);
  }
  if (PS3.getButtonClick(SQUARE)) {
    output.outputData = output.outputData | (0x0001<<OPT1);
  }
  if (PS3.getButtonClick(TRIANGLE)) {
    output.outputData = output.outputData | (0x0001<<OPT4);
  }
  if (PS3.getButtonClick(CROSS)) {
    output.outputData = output.outputData | (0x0001<<OPT3);
  }
}

void sendTheBytes() {
  if (output.outputData != 0) {
    //we have data to send
    Serial.write(output.byteArray,2); 
    buttonsWerePressed = true; 
    delay(10);
  } 
  else {
    if (buttonsWerePressed == true) {
      // send a wait state
      Serial.write(output.byteArray,2);
      buttonsWerePressed = false; 
    }
    delay(10);
  }        
}


