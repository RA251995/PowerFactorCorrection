#define PI 3.14

//LCD Module Connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;
sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
//End LCD Module Connections

char str[12];
float wt;

void findPF(void);

void main()
{
  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off
  Lcd_Out(1,3,"MINI PROJECT"); // Ouput text
  Delay_ms(500);

  ADCON1 = 0x06;
  TRISA0_bit = 1; //Set RA0 & RA1 pins as input
  TRISA1_bit = 1;
  
  TRISC0_bit = 0;

  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,"PF Angle");
  
  while(1){
    findPF();
    
    floatToStr(wt,str);
    Lcd_Out(2,6,str);
    
    if(wt>0.45){
      RC0_bit = 1;
    }
    Delay_ms(1000);
  }

}

void findPF(void){
  float t,pf;
  float a,b;
  int i;

  TMR1L=0;
  TMR1H=0;
  while(RA0_bit == 1);
  while(RA0_bit == 0);
  T1CON.TMR1ON = 1;
  while(1){
    if(RA0_bit == 0)
    {
      T1CON.TMR1ON = 0;
      break;
    }
  }
  a = (TMR1L | (TMR1H<<8));

  TMR1L=0;
  TMR1H=0;
  while(RA0_bit == 1);
  while(RA0_bit == 0);
  if(RA1_bit == 1){
     RC0_bit = 0;
  }
  do
  {
    if(RA0_bit == 1)
    {
      T1CON.TMR1ON=1;
      if(RA1_bit==1)
      {
        T1CON.TMR1ON=0;
        break;
      }
    }
  }while(1);
  b =  (TMR1L | (TMR1H<<8));
  
  wt = PI * b / a;
  
}