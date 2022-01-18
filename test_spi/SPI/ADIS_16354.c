/*
 * ADIS16354.c
 *
 *  Created on: Jan 17, 2022
 *      Author: Stergios
 */

#include "ADIS_16354.h"

void RegisterRead(uint16_t reg)
{
    /*
  uint8_t CMD[2]{};
  CMD[0] = ((static_cast<uint16_t>(reg)) & 0x00FF);
  CMD[1] = 0x00;

  // ADIS 16354 has 16 bits that we need to read, remembering to discard 1st return

  digitalWrite(SS, LOW);
  SPI.transfer(CMD[0]);
  delayMicroseconds(9);
  SPI.transfer(CMD[1]);
  delayMicroseconds(9);
  CMD[0] = SPI.transfer(reg);
  delayMicroseconds(9);
  CMD[1] = SPI.transfer(reg);
  delayMicroseconds(9);
  digitalWrite(SS, HIGH);

  int16_t reg_data = combine(CMD[0], CMD[1]);
  return reg_data;*/
}


uint16_t TwosComplement(float32_t rawdata)
{
    uint16_t tc_rawdata = 0x0000;
    (rawdata > 0) ? (tc_rawdata = (uint16_t)rawdata) : (tc_rawdata = ~((uint16_t)(-rawdata) - 1));
    return tc_rawdata;
}
