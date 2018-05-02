//**************************** RobotCar_2018 ****************************
// Only files with the .ino extension are scanned for include files.     *
// This is by design, for simplicity for one thing and so that a         *
// library can't include another library that includes another library   *
// and so on.                                                            *
// Athugid ad setja snuningsAtt i RobotFunctions.h a -1 ef servomotor    *
// er orvhentur                                        *
//***********************************************************************/
#include "Arduino.h"
#include "RobotFunctions.h"
#include <SoftwareSerial.h>
#include "MyDFPlayer.h"

int ledPin12 = 12;
int ledPin13 = 13;

//************************** uppsetning á forritinu *****************
void setup()
{
	pinMode(motorVpwm_, OUTPUT);
	pinMode(motorVgir_, OUTPUT);
	pinMode(motorHpwm_, OUTPUT);
	pinMode(motorHgir_, OUTPUT);

	servoMain.attach(10); //Servo on digital pin ~10

	pinMode(sonarTrigger_, OUTPUT);
	pinMode(sonarEcho_, INPUT_PULLUP); //Allir inngangar verda að hafa pullup vidnam
									   //her notum við internal pullup (20kohm) orgjorvans
	pinMode(TXspilari_, OUTPUT);
	pinMode(RXspilari_, INPUT_PULLUP); //Notum aftur Internal pullup vidnam

	Serial.begin(9600);
	//******************** Setja upp MDFPlayer *************************
	mySerial.begin(9600);
	delay(500);
	//mp3_set_volume(25);
	mp3_set_volume(25);
	delay(100);

	mp3_play_track(1); // 17. Bíll í gang (gamli bíllinn)
	delay(3000);
  
	mp3_play_track(2); // 1. Riding along in my automobile
  lagNr = 2;
  
	//Timar
	time = millis(); //Setur time breytuna á tíma liðinn frá starti
	timeX = time;
	servoMain.write(95); //SONAR beint framm, í þessum bíl er leiðrétt um -10°
	lengdX = lengd();
} //End of setup *********

//*************************** Keyrslulykkjan **********************
void loop()
{
  if (digitalRead(RXspilari_) == 1 || lagNr != 2)
  {
    mp3_play_track(2);
    lagNr = 2;
  }
  
	delay(100);
	startCar(); // Bíll keyrir áfram

	while (lengd() < 40)
	{
    mp3_play_track(3);
    lagNr = 3;
		stopCar();

    mp3_play_track(4);
    lagNr = 4;
		backCar();

		breakCar();

		switch (beygja())
		{
  		case true:
        digitalWrite(ledPin13, HIGH);
        driveLeft();
        delay(350);
        digitalWrite(ledPin13, LOW);
  			breakCar();
  			break;
  		case false:
        digitalWrite(ledPin12, HIGH);
        driveRight();
        delay(350);
        digitalWrite(ledPin12, LOW);
  			breakCar();
  			break;
  
      default:
        backCar();
        delay(500);
        breakCar();
        break;
		}
	}
} //End of loop *********************
