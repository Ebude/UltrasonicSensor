


//#include <LiquidCrystal.h>

/********************************************************************/
/*                                                                  */
/*                                                                  */
/* PROJECT: Refueling Device using Ultrasonic sensor                             */
/* AUTHOR:  Ebude                              */
/* DATE:    16/08/2018                                              */
/********************************************************************/


/*********************************************************************
        INITIAL CONFIG
*********************************************************************/

const int pingPin = 7;
const int echoPin = 6;
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long vol1=0; //initialising the volume value

/*********************************************************************
        SETUP - FUNCTION
*********************************************************************/

void setup() 
{
   //pinMode(pingPin, OUTPUT);
   //pinMode(echoPin, INPUT);


  // initialize serial communication:
  Serial.begin(9600);
  Serial.print("Measures volume of water in a tank every 1000 seconds");
  //lcd.begin(16, 2);
  //lcd.print("Hello, World!");
 
 

}


/*********************************************************************
        LOOP - FUNCTION
*********************************************************************/

void loop()
{
// establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  // using the characteristic of the tank: length, width and height.
  // dif represent the different between new volume and initial volume
  long duration, inches, cm, vol, len, wid, height,voltank, dif;




  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);



 
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);



  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  // Characteristic of the tank: case study is a regtangular tank (SI Unit meters)
  len = 50;
  wid = 40;
  height = 50;
  //Volume of the tank
  voltank = len * wid * height;  
  // Volume of water = height in meters * length * width. (SI Unit meters cube)
  vol= cm * len * wid /100 ;
  // initialise dif
  dif=0;


  // SERIAL DEBUG, printing results on Virtual Environment
  
  Serial.println();
  Serial.print("level of water: ");
  Serial.print(inches);
  Serial.print(" in, ");
  Serial.print("Volume: ");
  Serial.print(vol);
  Serial.print(" l");
  Serial.println();

  //lcd.println();
  //lcd.print("level of water: ");
  //lcd.print(inches);
  //lcd.print("Volume: ");
  //lcd.print(vol);
  //lcd.println();
  
  delay(100);
  //when a change of volume occur, signal
  
  // Start by  checking if the water exceeds the tank  to give an alarm
  // Check if there has been a refuel or consumption
  if (voltank < vol){
    Serial.print("Alert!!! tank capacity exceeded ");
    Serial.println();}
   //lcd.print("Alert!!! tank capacity exceeded ");
   //lcd.println();}
  else {if (vol != vol1) {
  dif= vol-vol1;
  if (dif<0){
    dif= abs(dif);
  Serial.print("Volume used: ");
  Serial.print(dif);
  Serial.print(" l");
  Serial.println();}
  
  else{
  Serial.print("New volume added: ");
  Serial.print(dif);
  Serial.print(" l");
  Serial.println();}

  }
} 
  
  // assign value of volume to global volume variable to compare with next value
  vol1 = vol;
  
  
  delay(500);  
}




/*********************************************************************
        SUBROTINES
*********************************************************************/

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}



//-------------------------------------------------------------------
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}




/*********************************************************************
        END
*********************************************************************/


