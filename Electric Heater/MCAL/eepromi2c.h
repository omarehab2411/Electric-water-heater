#ifndef __EEPROMI2C__H
#define __EEPROMI2C__H
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


unsigned char e2pext_r(unsigned int addr);
void e2pext_w(unsigned int addr, unsigned char val);
void e2pext_init(void);
#endif // __EEPROMI2C__H
