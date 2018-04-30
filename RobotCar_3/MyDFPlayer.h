//*********************** MyDFPlayer.h ***************************
#include "Arduino.h"

//Athugið að TX (4)á Arduino tengist við RX (2) a DFPlayer
//og að RX (2) á Arduino tengist BUSY (16) a DFPlayer
//Busy á DFPlayer er í lástöðu meðan lag er spilað en hástöðu annars
SoftwareSerial mySerial(2, 4); // RX, TX á arduino
 

void mp3_play_track(unsigned char fileNum)  //Spilar skrana fileNum
{
    unsigned char pakki[8] = { 0X7E, 0XFF, 0X06, 0X03, 00, 00, fileNum, 0XEF};
    for (int i=0; i<8; i++) 
    { 
       mySerial.write( pakki[i] ); 
    }
}
void mp3_play_next()  //Spilar naestu skra a sd kortinu
{
    unsigned char pakki[8] = { 0X7E, 0XFF, 0X06, 0X01, 00, 00, 00, 0XEF};
    for (int i=0; i<8; i++) 
    { 
       mySerial.write( pakki[i] ); 
    }
}
void mp3_play_previous()  //Spilar skrana er sidast var spilud
{
   unsigned char pakki[8] = { 0X7E, 0XFF, 0X06, 0X02, 00, 00, 00, 0XEF};
   for (int i=0; i<8; i++) 
   { 
      mySerial.write( pakki[i] ); 
   }
}
void mp3_set_volume(unsigned char volume)   //Setur hljodstyrkinn a volume 0..30
{
    unsigned char pakki[8] = { 0X7E, 0XFF, 0X06, 0X06, 00, 00, volume, 0XEF};
    for (int i=0; i<8; i++) 
    { 
       mySerial.write( pakki[i] );
    }
}
void mp3_play() //Spilar fyrstu skrana a sd kortinu an hindrana
{
    unsigned char pakki[8] = { 0X7E, 0XFF, 0X06, 0X0D, 00, 00, 00, 0XEF};
    for (int i=0; i<8; i++) 
    { 
       mySerial.write( pakki[i] );
    }
}
