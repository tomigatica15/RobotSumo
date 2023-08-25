/*
Tomas Gatica
Robot sumo
5 E

Negro > 500
Blanco < 500
*/

const int trig = 2;
const int echo = 3;

const int sensor_front_right = A0;
const int sensor_back_right = A1;
const int sensor_front_left = A2;
const int sensor_back_left = A3;

#define motor_right 8
#define motor_right2 9
#define motor_left 10
#define motor_left2 11

void setup()
{
  Serial.begin(9600);
  // Ultrasonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  // Optics
  pinMode(sensor_front_right, INPUT);
  pinMode(sensor_back_right, INPUT);
  pinMode(sensor_front_left, INPUT);
  pinMode(sensor_back_left, INPUT);
  // Motors
  pinMode(motor_right, OUTPUT);
  pinMode(motor_right2, OUTPUT);
  pinMode(motor_left, OUTPUT);
  pinMode(motor_left2, OUTPUT);
}

void sleep()
{
  delay(1000);
}

//            //
//  Movements //
//            //

void leftBack()
{
  digitalWrite(motor_left, LOW);
  digitalWrite(motor_left2, HIGH);
  delay(1);
}

void leftFront()
{
  digitalWrite(motor_left, HIGH);
  digitalWrite(motor_left2, LOW);
  delay(1);
}

void rightBack()
{
  digitalWrite(motor_right, LOW);
  digitalWrite(motor_right2, HIGH);
  delay(10);
}

void rightFront()
{
  digitalWrite(motor_right, HIGH);
  digitalWrite(motor_right2, LOW);
  delay(10);
}

//                //
//  Optic sensor  //
//                //

void sensor()
{
  int value_front_left = analogRead(sensor_front_left);
  int value_back_left = analogRead(sensor_back_left);

  int value_front_right = analogRead(sensor_front_right);
  int value_back_right = analogRead(sensor_back_right);

  /* 0000 */ /* All Black */
  if (value_front_left > 500 && value_front_right > 500 && value_back_left > 500 && value_back_right > 500)
  {
    rightFront();
    leftFront();
  }
  /* 0001 */ /*  Right Back White */
  else if (value_front_left > 500 && value_front_right > 500 && value_back_left > 500 && value_back_right < 500)
  {
    rightBack();
    sleep();
    rightBack();
    leftBack();
  }
  /* 0010 */ /* Left Back White */
  else if (value_front_left > 500 && value_front_right > 500 && value_back_left < 500 && value_back_right > 500)
  {
    leftBack();
    sleep();
    leftBack();
    rightBack();
  }
  /* 0011 */ /* Left & Right Back White */
  else if (value_front_left > 500 && value_front_right > 500 && value_back_left < 500 && value_back_right < 500)
  {
    rightBack();
    sleep();
    rightBack();
    leftBack();
  }
  /* 0100 */ /*  Front Right White */
  else if (value_front_left > 500 && value_front_right < 500 && value_back_left > 500 && value_back_right > 500)
  {
    leftFront();
    sleep();
    leftFront();
    rightFront();
  }
  /* 0101 */ /* Front & Back Right White */
  else if (value_front_left > 500 && value_front_right < 500 && value_back_left > 500 && value_back_right < 500)
  {
    leftBack();
    sleep();
    rightBack();
    leftBack();
  }
  /* 0110 */ /* Front Right & Back Left White */
  else if (value_front_left > 500 && value_front_right < 500 && value_back_left < 500 && value_back_right > 500)
  {
    rightBack();
    sleep();
    rightBack();
    leftBack();
  }
  /* 0111 */ /* Front Right & Back Left & Back Right White */
  else if (value_front_left > 500 && value_front_right < 500 && value_back_left < 500 && value_back_right < 500)
  {
  }
  /* 1000 */ /* Front Left White */
  else if (value_front_left < 500 && value_front_right > 500 && value_back_left > 500 && value_back_right > 500)
  {
  }
  /* 1001 */ /* Front Left & Back Right White */
  else if (value_front_left < 500 && value_front_right > 500 && value_back_left > 500 && value_back_right < 500)
  {
  }
  /* 1010 */ /*Front Left & Back Left White*/
  else if (value_front_left < 500 && value_front_right > 500 && value_back_left < 500 && value_back_right > 500)
  {
  }
  /* 1011 */ /* Front Left & Back Left & Back Right White */
  else if (value_front_left < 500 && value_front_right > 500 && value_back_left < 500 && value_back_right < 500)
  {
  }
  /* 1100 */ /* Front Left & Front Right White */
  else if (value_front_left < 500 && value_front_right < 500 && value_back_left > 500 && value_back_right > 500)
  {
  }
  /* 1101 */ /* Front Left & Front Right & Back Right White */
  else if (value_front_left < 500 && value_front_right < 500 && value_back_left > 500 && value_back_right < 500)
  {
  }
  /* 1110 */ /*Front Left & Front Right & Back Left White*/
  else if (value_front_left < 500 && value_front_right < 500 && value_back_left < 500 && value_back_right > 500)
  {
  }
  /* 1111 */ /* All White */
  else if (value_front_left < 500 && value_front_right < 500 && value_back_left < 500 && value_back_right < 500)
  {
  }
}

void sensorTest()
{
  float value_front_right = analogRead(sensor_front_right);
  if (value_front_right < 500)
  {
    Serial.println("< 500");
    delay(2000);
  }
  else if (value_front_right > 500)
  {
    Serial.println("> 500");
    delay(2000);
  }
}
//                    //
// Ultrasonic Sensor  //
//                    //

void ultrasonic()
{
  long distance;
  int duration;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  if (distance)
  {
    Serial.print("Distancia: ");
    Serial.println(distance);
    delay(1000);
  }
}

//        //
//  Bucle //
//        //

void loop()
{
  ultrasonic();
  sensor();
}