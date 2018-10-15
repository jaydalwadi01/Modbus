#include "Modbus.h"

Modbus::Modbus(uint16_t SlaveAddress, uint8_t Ser_No, int Control_Pin)
{
  _Slave_Address = SlaveAddress;
  _DE_RE_Pin = Control_Pin;
  _Ser_No = Ser_No;
  pinMode(_DE_RE_Pin, OUTPUT);
  switch (_Ser_No)
  {
    case 0: Serial.begin(9600);
      break;
    case 1: Serial1.begin(9600);
      break;
    case 2: Serial2.begin(9600);
      break;
    case 3: Serial3.begin(9600);
      break;
  }
}

void Modbus::WriteSingleRegister(uint16_t u16Addrs, uint16_t u16Data)
{
  uint16_t crc = Modbus::CRC(WRITE_BYTE, ((u16Addrs >> 8) & 0xFF), (u16Addrs & 0xFF), ((u16Data >> 8) & 0xFF), (u16Data & 0xFF));
  byte request[] = {_Slave_Address, WRITE_BYTE, ((u16Addrs >> 8) & 0xFF), (u16Addrs & 0xFF), ((u16Data >> 8) & 0xFF), (u16Data & 0xFF), (crc & 0xFF), ((crc >> 8) & 0xFF)};
  digitalWrite(_DE_RE_Pin, 1);
  switch (_Ser_No)
  {
    case 0: time = millis();
			Serial.write(request, sizeof(request));
      break;
    case 1: time = millis();
			Serial1.write(request, sizeof(request));
      break;
    case 2: time = millis();
			Serial2.write(request, sizeof(request));
      break;
    case 3: time = millis();
			Serial3.write(request, sizeof(request));
      break;
  }
  while((millis()-time) <= 25);
  /*while((millis() - time) <= 10);
  digitalWrite(_DE_RE_Pin, 0);
  byte buf[8];
  switch (_Ser_No)
  {
    case 0: while(!Serial.available()); 
		while (Serial.available())
      {
        Serial.readBytes(buf, 8);
      }
      break;
    case 1: while(!Serial1.available());
		while (Serial1.available())
      {
        Serial1.readBytes(buf, 8);
      }
      break;
    case 2: while(!Serial2.available());
		while (Serial2.available())
      {
        Serial2.readBytes(buf, 8);
      }
      break;
    case 3: while(!Serial3.available()); 
		while (Serial3.available())
      {
        Serial3.readBytes(buf, 8);
      }
      break;
  }
  for(int i = 0; i<=7; i++)
  {
    Serial.println(buf[i], HEX);
  }
  for(int i = 0; i<=7; i++)
  {
	  buf[i] = 0;
  }*/
}

uint16_t Modbus::CRC_Cal_Value (uint16_t Data, unsigned char Length)
{
  int i = 0;
  while (Length--)
  {
    crc_value ^= Data;
    for (i = 0; i < 8; i++)
    {
      if (crc_value & 0x0001)
      {
        crc_value = (crc_value >> 1) ^ 0xA001;
      }
      else
      {
        crc_value = crc_value >> 1;
      }
    }
  }
  return (crc_value);
}

uint16_t Modbus::CRC(uint16_t addr2, uint16_t addr3, uint16_t addr4, uint16_t addr5, uint16_t addr6)
{
  crc_value = 0xFFFF;
  Modbus::CRC_Cal_Value(_Slave_Address, 1);
  Modbus::CRC_Cal_Value(addr2, 1);
  Modbus::CRC_Cal_Value(addr3, 1);
  Modbus::CRC_Cal_Value(addr4, 1);
  Modbus::CRC_Cal_Value(addr5, 1);
  return (Modbus::CRC_Cal_Value(addr6, 1));
}

uint16_t Modbus::ReadSingleRegister(uint16_t u16RegH, uint16_t u16RegL)
{
  uint16_t crc = Modbus::CRC(READ_BYTE, ((u16RegH >> 8) & 0xFF), (u16RegH   & 0xFF), ((u16RegL >> 8) & 0xFF), (u16RegL & 0xFF));
  byte request[] = {_Slave_Address, READ_BYTE, ((u16RegH >> 8) & 0xFF), (u16RegH & 0xFF), ((u16RegL >> 8) & 0xFF), (u16RegL & 0xFF), (crc & 0xFF), ((crc >> 8) & 0xFF)};
  digitalWrite(_DE_RE_Pin, 1);
  switch (_Ser_No)
  {
    case 0: time = millis();
			Serial.write(request, sizeof(request));
      break;
    case 1: time = millis();
			Serial1.write(request, sizeof(request));
      break;
    case 2: time = millis();
			Serial2.write(request, sizeof(request));
      break;
    case 3: time = millis();
			Serial3.write(request, sizeof(request));
      break;
  }

  while((millis()-time) <= 10);
  
  digitalWrite(_DE_RE_Pin, 0);
  
  byte buf[8];
  
  switch (_Ser_No)
  {
    case 0: while(!Serial.available()); 
		while (Serial.available())
      {
        Serial.readBytes(buf, 8);
      }
      break;
    case 1: while(!Serial1.available());
		while (Serial1.available())
      {
        Serial1.readBytes(buf, 8);
      }
      break;
    case 2: while(!Serial2.available());
		while (Serial2.available())
      {
        Serial2.readBytes(buf, 8);
      }
      break;
    case 3: while(!Serial3.available()); 
		while (Serial3.available())
      {
        Serial3.readBytes(buf, 8);
      }
      break;
  }
  /*for(int i = 0; i<=7; i++)
  {
    Serial.println(buf[i], HEX);
  }
  for(int i = 0; i<=7; i++)
  {
	  buf[i] = 0;
  }*/
  while((millis()-time) <= 15);
  if ((buf[0] == _Slave_Address) && (buf[1] == 0x03))
  {
    return ((buf[3] << 8) | buf[4]);
  }
  else
  {
    return ERR_CODE;
  }
}

/*
  uint16_t Modbus::CircuitDiagnosisAndSetting(uint16_t u16RegAddrs, uint16_t u16Regs)
  {
  byte request[]={_Slave_Address, CIRCUIT_DIAG_BYTE, ((u16RegAddrs >> 8) & 0xFF), (u16RegAddrs && 0xFF), ((u16Regs >> 8) & 0xFF), (u16Regs && 0xFF)};

  SoftwareSerial _MySerial(_Rx_Pin, _Tx_Pin);

  _MySerial.begin(9600);

  _MySerial.write(request, sizeof(request));
  }
*/




