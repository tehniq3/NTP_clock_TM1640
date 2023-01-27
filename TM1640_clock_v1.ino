// https://wiki.keyestudio.com/Ks0357_Keyestudio_8x16_LED_Matrix_Panel
// NTP clock inspired by https://nicuflorica.blogspot.com/2022/10/ceas-ntp-pe-afisaj-cu-tm1637.html
// original sketch by Nicu FLORICA (niq_ro)
// v.1 - added hardware switch for DST (Daylight Saving Time) as at https://nicuflorica.blogspot.com/2022/12/ceas-ntp-pe-afisaj-oled-de-096-128x64.html


#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "niq_ro";
const char *password = "berelaburtica";

const long timezoneOffset = 2*3600; // GMT + seconds  (Romania)

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", timezoneOffset);

#define IIC_SCL  5  // GPIO5  = D1
#define IIC_SDA  4  // GPIO4  = D2
#define DSTpin   14 // GPIO14 = D5, see https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

unsigned char data_line = 0;
unsigned char delay_count = 0;

void IIC_start();
void IIC_send(unsigned char send_data);
void IIC_end();
//unsigned char table[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; 


unsigned char table[4][16] = {
 {0x0c,0xff,0x00,0x62,0x89,0x76,0x00,0x00,0x00,0x7e,0x81,0x7e,0x00,0x03,0xf1,0x0f},                           
 {0x0c,0xff,0x00,0x62,0x89,0x76,0x00,0x24,0x00,0x7e,0x81,0x7e,0x00,0x03,0xf1,0x0f},
 {0x0c,0xff,0x00,0x62,0x89,0x76,0x00,0x00,0x00,0x7e,0x81,0x7e,0x00,0x03,0xf1,0x0f},                           
 {0x0c,0xff,0x00,0x62,0x89,0x76,0x00,0x24,0x00,0x7e,0x81,0x7e,0x00,0x03,0xf1,0x0f}}; 

byte x = 0;

unsigned char caractere[10][3] = {
{0x7e,0x81,0x7e},  // 0
{0x0c,0xff,0x00},  // 1
{0xe6,0x91,0x8e},  // 2
{0x62,0x89,0x76},  // 3
{0x1c,0x13,0xf8},  // 4
{0x67,0x89,0x71},  // 5
{0x7e,0x89,0x72},  // 6
{0x03,0xf1,0x0f},  // 7
{0x76,0x89,0x76},  // 8
{0x66,0x89,0x7e}   // 9
};

unsigned char zeci[2][2] = {
{0x00,0x00},  // none  
{0x0c,0xff},  // 1  
};

unsigned char secunde[2] = {
0x00,0x24  // none, ;   
};

int ora, minut;
byte DST = 0;
byte DST0;

void setup() 
{
pinMode (DSTpin, INPUT);
   
Serial.begin(115200);
 Serial.println ( "." ); 

 
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  if (digitalRead(DSTpin) == LOW)
   DST = 0;
  else
   DST = 1;
  timeClient.setTimeOffset(timezoneOffset + DST*3600);
  timeClient.begin();
  DST0 = DST;
   
   
// display zone  
  pinMode(IIC_SCL,OUTPUT);
  pinMode(IIC_SDA,OUTPUT);
  digitalWrite(IIC_SCL,LOW);
  digitalWrite(IIC_SDA,LOW);

     /*************set the brightness display***************/ 
    IIC_start();
    IIC_send(0x88);  // brightness (0x88 - minimum ... 0x8F - maximum)
    IIC_end(); 
    /*************end the brightness display***************/ 
}
/*----------------------------------------------------------------*/
void loop() 
{

 if (digitalRead(DSTpin) == LOW)
   DST = 0;
  else
   DST = 1;
  
timeClient.update();
 ora = timeClient.getHours();
 minut = timeClient.getMinutes();

Serial.print(ora);
Serial.print(";");
Serial.println(minut);
 
 ora = ora%12;  // 12-hour format
 if (ora == 0) ora = 12;  // 12-hour format

unsigned char text [16];

table[0][0] = zeci[ora/10][0];
table[0][1] = zeci[ora/10][1];
table[0][2] = secunde[0];  // space
table[0][3] = caractere[ora%10][0];
table[0][4] = caractere[ora%10][1];
table[0][5] = caractere[ora%10][2];
table[0][6] = secunde[0]; // space
if (x%2 == 0)
table[0][7] = secunde[0]; // :
else
table[0][7] = secunde[1]; // :
table[0][8] = secunde[0]; // space
table[0][9] = caractere[minut/10][0];
table[0][10] = caractere[minut/10][1];
table[0][11] = caractere[minut/10][2];
table[0][12] = secunde[0]; // space
table[0][13] = caractere[minut%10][0];
table[0][14] = caractere[minut%10][1];
table[0][15] = caractere[minut%10][2];


  
    /**************set the address plus 1***************/
    IIC_start();
    IIC_send(0x40);// set the address plus 1 automatically
    IIC_end();
    /************end the process of address plus 1 *****************/
    /************set the data display*****************/ 
    IIC_start();
    IIC_send(0xc0);// set the initial address as 0
    for(char i = 0;i < 16;i++)
    {
       IIC_send(table[data_line][i]);// send the display data 
    }
    IIC_end();
    /************end the data display*****************/
    
    delay(500);
    x++;

if (DST != DST0)
{
  timeClient.setTimeOffset(timezoneOffset + DST*3600);
  timeClient.begin();
DST0 = DST;
}

    
} // end main loop

/*----------------------------------------------------------------*/
void IIC_start()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
}
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)
  {
      digitalWrite(IIC_SCL,LOW);
      delayMicroseconds(3); 
      if(send_data & 0x01)
      {
        digitalWrite(IIC_SDA,HIGH);
      }
      else
      {
        digitalWrite(IIC_SDA,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(IIC_SCL,HIGH); 
      delayMicroseconds(3);
      send_data = send_data >> 1;
  }
}
void IIC_end()
{
  digitalWrite(IIC_SCL,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,LOW);
  delayMicroseconds(3);
  digitalWrite(IIC_SCL,HIGH);
  delayMicroseconds(3);
  digitalWrite(IIC_SDA,HIGH);
  delayMicroseconds(3);
}
