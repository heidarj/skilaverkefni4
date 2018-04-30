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
	pinMode(ledPin12, OUTPUT);
  pinMode(ledPin13, OUTPUT);
	
	pinMode(TXspilari_, OUTPUT);
	pinMode(RXspilari_, INPUT_PULLUP); //Notum aftur Internal pullup vidnam

	Serial.begin(9600);
	//******************** Setja upp MDFPlayer *************************
	mySerial.begin(9600);
	delay(500);
	//mp3_set_volume(25);
	mp3_set_volume(20);
	delay(100);

	mp3_play_track(17); // 17. Bíll í gang (gamli bíllinn)
	delay(5000);
	mp3_play_track(1); // 1. Riding along in my automobile
	lagNr = 2;
	//Timar
	time = millis(); //Setur time breytuna á tíma liðinn frá starti
	timeX = time;
	reiknaPulsBreidd(0 - 10, -1); //SONAR beint framm, í þessum bíl er leiðrétt um -10°
	lengdX = lengd();
} //End of setup *********

//*************************** Keyrslulykkjan **********************
void loop()
{
	reiknaPulsBreidd(0 - 10, -1); //SONAR beint framm, í þessum bíl er leiðrétt um -10°
	delay(100);
	startCar(); // Bíll keyrir áfram
	delay(100);
	if (digitalRead(RXspilari_) == 1) //Ef Spilari upptekinn þá er RXspilari==0
	{								  //RXspilari (D2) tengist BUSY tengi á spilara sjá mynd 17
		if (lagNr == 17)
			lagNr = 1;
		mp3_play_track(lagNr++);
	}

  if (lengd() == lengdB() && lengd() < 40)
  {
    stopCar();

    backCar();

    delay(500);

    stopCar();

    scanForNewDirection();
    if (scanForNewDirection() < 90)
      driveRight(); // bíll snýst til hægri
    else if (scanForNewDirection() < 90)
      driveLeft(); // bíll snýst til vinstri
    else 
      startCar();
    delay(300);    // Gefa tíma til að beygja ca +/- 90°
    startCar();
    
  }

  
	while (lengd() < 40)
	{
		stopCar();
    
		scanForNewDirection();

    if (scanForNewDirection() < 90)
    {
      digitalWrite(ledPin12, HIGH);
      delay(1000);
      digitalWrite(ledPin12, LOW);
      delay(1000);
      driveRight(); // bíll snýst til hægri
    }
    else if (scanForNewDirection() < 90)
    {
      digitalWrite(ledPin13, HIGH);
      delay(1000);
      digitalWrite(ledPin13, LOW);
      delay(1000);
      driveLeft(); // bíll snýst til vinstri
    }
    else 
      startCar();
    delay(300);    // Gefa tíma til að beygja ca +/- 90°
    startCar();
    delay(1000);
	}
} //End of loop *********************
