/* 
   -- ECE590 - Robot Design --
   David Gregory - Homerwork 4
   OpenCM9.04 - Motor Control & USB Interface
   
   Controls 2 Dynamixel motors
*/

 /* Serial device defines for DXL1 bus */ 
#define DXL_BUS_ID 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04

/* Dynamixel Motor IDs */
#define RGT_MOTOR 1
#define LFT_MOTOR 2

#define FWD_SPEED  200
#define TRN_SPEED  100
#define RVS_SPEED  200

#define STOP_SPEED  0
#define CW_BIT 0x400 //10th bit


Dynamixel Dxl(DXL_BUS_ID);



void setup(){
  //You can attach your serialUSB interrupt
  //or, also detach the interrupt by detachInterrupt(void) method
  SerialUSB.attachInterrupt(usbInterrupt);
  
  pinMode(BOARD_LED_PIN, OUTPUT);  //toggleLED_Pin_Out; For FUN!!
  
  // Initialize the dynamixel bus:
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.wheelMode(DXL_BUS_ID); //wheelMode() is to use wheel mode
  
  //STOP on RESET
  Dxl.goalSpeed(RGT_MOTOR, STOP_SPEED); 
  Dxl.goalSpeed(LFT_MOTOR, STOP_SPEED);
  
}//End setup()

//USB max packet data is maximum 64byte, so nCount can not exceeds 64 bytes
void usbInterrupt(byte* buffer, byte nCount){
  //SerialUSB.print("nCount =");
  //SerialUSB.println(nCount);
  
  for(unsigned int i=0; i < nCount;i++){  //printf_SerialUSB_Buffer[N]_receive_Data
    SerialUSB.println((char)buffer[i]);
  }
  //FORWARD
  if(buffer[0] == 119){         //ASCII w: FWD
    SerialUSB.println("CMD_FWD RCVD");
    /* MOVE Forward */
    Dxl.goalSpeed(RGT_MOTOR, FWD_SPEED | CW_BIT); //CW
    Dxl.goalSpeed(LFT_MOTOR, FWD_SPEED); //CCW 
  }
  //LEFT  
  else if(buffer[0] == 97){       //ASCII a:LFT
    SerialUSB.println("CMD_LFT RCVD");
    /* Turn LEFT */
    Dxl.goalSpeed(RGT_MOTOR, TRN_SPEED | CW_BIT); //CW
    Dxl.goalSpeed(LFT_MOTOR, TRN_SPEED | CW_BIT); //CW  
  }
  //RIGHT  
  else if(buffer[0] == 100){       //ASCII d:RGT
    SerialUSB.println("CMD_RGT RCVD");
    /* Turn RIGHT */
    Dxl.goalSpeed(RGT_MOTOR, TRN_SPEED); //CCW
    Dxl.goalSpeed(LFT_MOTOR, TRN_SPEED); //CCW
  }
  //REVERSE 
  else if(buffer[0] == 120){       //ASCII x:RVS
    SerialUSB.println("CMD_RVS RCVD");
    /* Reverse */
    Dxl.goalSpeed(RGT_MOTOR, RVS_SPEED); //CCW
    Dxl.goalSpeed(LFT_MOTOR, RVS_SPEED | CW_BIT); //CW
  }
  //STOP
  else if(buffer[0] == 115){       //ASCII s:STOP
    SerialUSB.println("CMD_STOP RCVD");
   /*ALL STOP*/
    Dxl.goalSpeed(RGT_MOTOR, STOP_SPEED); 
    Dxl.goalSpeed(LFT_MOTOR, STOP_SPEED);    
  }
    
  else    //CMD not received correctly!
    SerialUSB.println("ERROR: INCORRECT CMD RX");
    
  SerialUSB.println(""); //print new line when done printing buffer
}


void loop(){
  //Flash the led
  toggleLED();
  delay(100);

}

