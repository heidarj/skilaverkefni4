//******Robot Functions  ************
#include <Servo.h> //Servo er innbyggður í Arduino en það þarf að stofna servoMain sem er þá eintak af Servo
Servo servoMain;   //ServoMain hefur t.d. fallið write(int stefna)
//******************* Skilgreining á tengjum og breytum **************
int motorVpwm_ = 5;
int motorVgir_ = 9;
int motorVpwm; //Geymir stöðu motorV  (analogWrite(motorVpwm_,motorVpwm);)

int motorHpwm_ = 6;
int motorHgir_ = 12;
int motorHpwm;   //Geymir stöðu motorH  (analogWrite(motorHpwm_,motorHpwm);)
int servo_ = 10; //Geymir númer servo tengis

/*
int VgrunnV=125;   //Upphafsgildi mótoranna
int VgrunnH=125;
*/
int VgrunnV = 150; //Upphafsgildi mótoranna
int VgrunnH = 150;

int TXspilari_ = 4; //Sendir skipanir til mp3 spilarans
int RXspilari_ = 2; //Tekur við skipunum frá mp3 spilara

int sonarTrigger_ = 7; //Sendir 10us breiðan 40kHz sónarpúls
int sonarEcho_ = 8;	//Tekur á móti SONAR púlsinum
int lagNr;			   //Synir hvaða lag er spilad
int randomTurn = 1;
//****************************Lengdir og Tímar
unsigned int lengdV;
unsigned int lengdH;
unsigned int lengdMax = 0;
int lengdX = 0;
unsigned long time; //Notuð með millis() fallinu til að ákveða spilatíma laga
unsigned long timeX;

int maelingar[3] = {};

//******** Reikna púlsbreidd frá gráðum og kalla síðan á servoMain.write(stefna) *******
void reiknaPulsBreidd(int gradur, int snunAtt) //réttsaelis=1 rangsaelis=-1
{
	int stefna;
	if (snunAtt >= 0)
		stefna = gradur + 90;
	else
		stefna = -1 * gradur + 90;

	if (stefna < 0)
		stefna = 0;
	if (stefna > 180)
		stefna = 180;
	servoMain.write(stefna);
}

//******************** unsigned int lengd() Reiknar fjarlaegd ad endurvarpi ***************
//Athugid ad nota Tetta fall ekki nema SONAR se tengdur annars bídur tolvan endalaust

unsigned int lengd() //Reikna lengd ad endurvarpi
{
	unsigned int tmp;
	digitalWrite(sonarTrigger_, HIGH); //Setja trigger utgang í hastoðu (Byrja StartPuls)
	delayMicroseconds(10);			   //bíða í 10 us  (Start púls er 10us breiður)
	digitalWrite(sonarTrigger_, LOW);  //Setja trigger útgang í lastodu (enda startpuls)
	tmp = pulseIn(sonarEcho_, HIGH);

	tmp = tmp * 0.01715; //tmp*34300cm/s /2 =tmp*0,01715cm/us
	return tmp;			 //Skila lengdinni til baka til þess sem kallaði á fall
}

void geymaLengdir(int(listi[3]), int nyttgildi)
{
	listi[0] = listi[1];
	listi[1] = listi[2];
	listi[2] = nyttgildi;
}

bool allarLengdirEins(int listi[3])
{
	if (listi[0] == listi[1] && listi[0] == listi[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startCar()
{
	digitalWrite(motorVgir_, HIGH);
	digitalWrite(motorHgir_, LOW);
	analogWrite(motorVpwm_, VgrunnV);
	analogWrite(motorHpwm_, VgrunnH);
}
void breakCar()
{
	analogWrite(motorVpwm_, 0);
	analogWrite(motorHpwm_, 0);
}
void stopCar()
{
  digitalWrite(motorVgir_, HIGH);
  digitalWrite(motorHgir_, LOW);
  
  for (int i = 150; i > 0; i--)
  {
    analogWrite(motorVpwm_, i);
    analogWrite(motorHpwm_, i);
  }
}
void backCar()
{
	digitalWrite(motorVgir_, LOW);
	digitalWrite(motorHgir_, HIGH);
	analogWrite(motorVpwm_, VgrunnV);
	analogWrite(motorHpwm_, VgrunnH);
}

void driveLeft()
{
	digitalWrite(motorVgir_, LOW);
	digitalWrite(motorHgir_, LOW);
	analogWrite(motorVpwm_, VgrunnV);
	analogWrite(motorHpwm_, VgrunnH);
}
void driveRight()
{
	digitalWrite(motorVgir_, HIGH);
	digitalWrite(motorHgir_, HIGH);
	analogWrite(motorVpwm_, VgrunnV);
	analogWrite(motorHpwm_, VgrunnH);
}

// Vinstri = true, hægri = false;
bool beygja()
{
  int skanna35gradur;
  int skanna125gradur;
  
  servoMain.write(35);
  skanna35gradur = lengd();
  
  delay(300);
  
  servoMain.write(125);
  skanna125gradur = lengd();
  
  
  servoMain.write(80);
  
  return skanna35gradur > skanna125gradur;
}
