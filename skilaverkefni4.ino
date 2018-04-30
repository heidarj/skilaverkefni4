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
	reiknaPulsBreidd(0 - 10, -1);	 //SONAR beint framm, í þessum bíl er leiðrétt um -10°
	if (digitalRead(RXspilari_) == 1) //Ef Spilari upptekinn þá er RXspilari==0
	{								  //RXspilari (D2) tengist BUSY tengi á spilara sjá mynd 17
		if (lagNr == 17)
			lagNr = 1;
		mp3_play_track(lagNr);
	}
	delay(100);
	startCar(); // Bíll keyrir áfram

	geymaLengdir(maelingar, lengd());

	while (lengd() < 40)
	{
		stopCar();

		backCar();

		delay(500);

		stopCar();

   newDirection = scanForNewDirection();

		switch (newDirection)
		{
		case 0:
			driveLeft();
			delay(500);
			stopCar();
			break;
		case 1:
			driveLeft();
			delay(250);
			stopCar();
			break;
		case 2:
			driveRight();
			delay(250);
			stopCar();
			break;
		case 3:
			driveRight();
			delay(500);
			stopCar();
			break;

    default:
      driveRight();
      delay(1000);
      stopCar();
      break;
		}
   
		startCar();
	}
} //End of loop *********************
