#include "eepromi2c.h"

void e2pext_init(void)
{
  TRISA=0xC3;
  TRISB=0x01;
  TRISC=0x01;
  TRISD=0x00;
  TRISE=0x00;
}

void delay(void)
{
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
  __asm  NOP __endasm;
}

void i2c_init(void)
{
  TIDAT=0;
  ICLK=1;
  IDAT=1;
}

void i2c_start(void)
{
  ICLK=1;
  IDAT=1;
  delay();
  IDAT=0;
  delay();
}

void i2c_stop(void)
{
  ICLK=1;
  IDAT=0;
  delay();
  IDAT=1;
  delay();
}

void i2c_wb(unsigned char val)
{
  char i;
  ICLK=0;
  for(i=7;i>=0;i--)
  {
    IDAT=((val>>i)& 0x01);
    ICLK=1;
    delay();
    ICLK=0;
  }
  IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;
}

unsigned char i2c_rb(unsigned char ack)
{
  char i;
  unsigned char ret=0;

  ICLK=0;
  TIDAT=1;
  IDAT=1;
  for(i=7;i>=0;i--)
  {
    ICLK=1;
    delay();
    ret|=(IDAT<<i);
    ICLK=0;
  }
  TIDAT=0;
  if(ack)
    IDAT=0;
  else
    IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;

  return ret;
}




unsigned char e2pext_r(unsigned int addr)
{
  unsigned char ret;
  unsigned char ah;
  unsigned char al;

  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA2);
  }
  else
  {
    i2c_wb(0xA0);
  }
  i2c_wb(al);

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA3);
  }
  else
  {
    i2c_wb(0xA1);
  }
  ret=i2c_rb(1);
  i2c_stop();

  return ret;
}


void e2pext_w(unsigned int addr, unsigned char val)
{
  unsigned int tmp;
  unsigned char ah;
  unsigned char al;
  unsigned char nt;

  tmp=val;
  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;
  nt=0;

  do
  {
    i2c_start();
    if(ah)
    {
      i2c_wb(0xA2);
    }
    else
    {
      i2c_wb(0xA0);
    }
    i2c_wb(al);
    i2c_wb(tmp);
    i2c_stop();

    nt++;
  }
  while((tmp != e2pext_r(addr))&&(nt < 10));
}





