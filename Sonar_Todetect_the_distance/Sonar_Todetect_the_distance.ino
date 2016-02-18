

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 6;
const int pingInPin = 7;
///const int ledgreenPin = 13;

const int ledredPin = 8;
const int input2Pin = 9; //motor driver input2
const int input7Pin = 10; //motor driver input7
const int input3Pin = 11;
const int ledINPUTyellowPin = 12;  //acts as an input 4

long duration, inches, cm;
void setup() {
// initialize serial communication:
Serial.begin(9600);
pinMode(input3Pin,OUTPUT);
pinMode(ledINPUTyellowPin,OUTPUT);
pinMode(ledredPin,OUTPUT); //Definindo pino digital 11 como saída.
pinMode(input2Pin,OUTPUT);
pinMode(input7Pin,OUTPUT);

}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingInPin, INPUT);
  duration = pulseIn(pingInPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
//Apagando todos os leds
//digitalWrite(ledgreenPin,LOW);
//digitalWrite(ledyellowPin,LOW);
digitalWrite(ledredPin,LOW);

//inputpins are to forward in yhis time
digitalWrite(input2Pin,LOW);
digitalWrite(input7Pin,HIGH);
digitalWrite(input3Pin,LOW);
digitalWrite(ledINPUTyellowPin,HIGH);

//Acendendo o led adequado para a distância lida no sensor
/*if (cm > 20) {
digitalWrite(ledgreenPin,HIGH);
Serial.print("ledgreenPin is glown the distance is now >20 cm");
}*/

/*if (cm <20 and cm > 10) {
digitalWrite(ledyellowPin,HIGH);
Serial.print("ledyellowPin is glown the distance is now >10 cm but <=20 cm");
}*/
//now for controlling car
if(cm<=15)
{
  //first stop the car
  digitalWrite(input2Pin,LOW);
  digitalWrite(input7Pin,LOW);
  digitalWrite(input3Pin,LOW);
  digitalWrite(ledINPUTyellowPin,LOW);
  Serial.print("StopCar");
  //glowing red led
  digitalWrite(ledredPin,HIGH);
  Serial.print("ledredPin is glown the distance is now <=15 cm");
  delay(1000);
  digitalWrite(ledredPin,LOW);
  //moving reverse
  Serial.print("Now moving Reverse");
  digitalWrite(input2Pin,HIGH);
  digitalWrite(input7Pin,LOW);
  digitalWrite(input3Pin,HIGH);
  digitalWrite(ledINPUTyellowPin,LOW);
  delay(10000);
  //turning right
  Serial.print("Turning right");
  digitalWrite(input2Pin,LOW);
  digitalWrite(input7Pin,HIGH);
  digitalWrite(input3Pin,HIGH);
  digitalWrite(ledINPUTyellowPin,LOW);
  delay(1000);
  //now moving forward
  Serial.print("StopCar and move forward");
  digitalWrite(input2Pin,LOW);
  digitalWrite(input7Pin,HIGH);
  digitalWrite(input3Pin,LOW);
  digitalWrite(ledINPUTyellowPin,HIGH);
}
/*if (cm < 10) {
digitalWrite(ledredPin,HIGH);
Serial.print("ledredPin is glown the distance is now <10 cm");
}*/
  //delay(1000);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

