#ifndef __I2C__H
#define __I2C__H

#include "Main.h"

#define ICLK RC3
#define IDAT RC4
#define TIDAT TRISC4

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_wb(unsigned char val);
unsigned char i2c_rb(unsigned char ack);
void i2c_acktst(unsigned char val);
#endif // __I2C__H
