#ifndef Modbus_h
#define Modbus_h

#include <Arduino.h>

// Command Mode
#define READ_BYTE 0x03
#define WRITE_BYTE 0x06
#define CIRCUIT_DIAG_BYTE   0x08

#define ERR_CODE 0xEEEE

class Modbus
{
  public:
    Modbus(uint16_t SlaveAddress, uint8_t Ser_No, int Control_Pin);
    void WriteSingleRegister(uint16_t u16Addrs, uint16_t u16Data);
    void WriteSingleRegister(uint16_t u16Addrs, uint16_t u16Data, bool WantToRead);
    uint16_t ReadSingleRegister(uint16_t u16RegHiByte, uint16_t u16RegLWByte);
    //uint16_t CircuitDiagnosisAndSetting(uint16_t u16RegAddrs, uint16_t u16Regs);

  private:
	unsigned long time;
    uint8_t _Ser_No; 
    uint16_t _Slave_Address;
    int _DE_RE_Pin;
    uint16_t CRC(uint16_t addr2, uint16_t addr3, uint16_t addr4, uint16_t addr5, uint16_t addr6);
    uint16_t CRC_Cal_Value (uint16_t Data, unsigned char Length);
    uint16_t crc_value = 0xFFFF;
};

#endif

