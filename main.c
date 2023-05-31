#include <REGX52.H>

void UartInit()  //9600bps@11.0592MHz
{
 PCON &= 0x80;  
 SCON = 0x50; 
 TMOD &= 0x0F;  
 TMOD |= 0x20;  
 TL1 = 0xFD; 
 TH1 = 0xFD;  
 ET1 = 0;  
 TR1 = 1;  
 EA = 1;
 ES = 1;
}


void UART_SendByte(unsigned char Byte)
{
 SBUF=Byte;
 while(TI==0);
 TI=0;
}

void UART_routine() interrupt 4
{  
  if(RI==1){
  
  if(SBUF==0x02){
  UART_SendByte(SBUF);
  P0=0xFF;
  P0=0xAA;
  RI=0;
  }
  else if(SBUF==0x04){
		
  UART_SendByte(SBUF);
  P0_0=0;
  P0_1=1;
  P0_2=1;
  P0_3=0;
  RI=0;
  }
  else if(SBUF==0x06){
  UART_SendByte(SBUF);
  
  P0_0=1;
  P0_1=0;
  P0_2=0;
  P0_3=1;
  RI=0;
  }
  else if(SBUF==0x08){
  UART_SendByte(SBUF);
  P0=0xFF;
  P0=~0xAA;
  RI=0;
  }
  else{
  P0=0xFF;
  RI=0;
  }
  
  }

}


void main()
{
 UartInit();
 while(1){

 }
}