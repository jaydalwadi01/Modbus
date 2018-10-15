#include <Modbus.h>

#define Slave_Address 0x01 // Address of slave

#define SERIAL_NO 1 //here Serial1 will be used.

#define DE_RE_Pin 3 //DE RE Combine Pin

//Initialization 
Modbus mybus(Slave_Address, SERIAL_NO, DE_RE_Pin);

void setup() 
{
  Serial.begin(9600);
  
  delay(1000);
  
  // Write Data 
  mybus.WriteSingleRegister(0x2000, 0x0005);
  
  // Read Data
  uint16_t res = mybus.ReadSingleRegister(0x3000, 0x0001);
  
  Serial.println(res, DEC);
}

void loop() 
{

}