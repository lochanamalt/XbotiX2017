#include <QuickStats.h>

#include <Servo.h>
#include <QTRSensors.h>

Servo servo1;
Servo servo2;

#define Kp 0.1 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 1 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd)
//#define Ki 0.01
#define rightMaxSpeed 250 // max speed of the robot
#define leftMaxSpeed 250 // max speed of the robot
#define rightMinSpeed 20 // min speed of the robot
#define leftMinSpeed 20 // min speed of the robot


int rightBaseSpeed = 200; // this is the speed at which the motors should spin when the robot is perfectly on the line
int leftBaseSpeed = 200; // this is the speed at which the motors should spin when the robot is perfectly on the line


#define NUM_SENSORS  8    // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN
#define buzzer 35

//================= ultra sonic==================================

const int trigPin1 = 25;
const int echoPin1 = 23;
const int trigPin2 = 33;
const int echoPin2 = 27; 
const int trigPin3 = 53;
const int echoPin3 = 34;


int object1,object2;
//***************MOTORS********************


#define motorL_enb 48
#define motorL_dirP 4
#define motorL_dirN 5
#define motorL_PWM 6

#define motorR_enb 50
#define motorR_dirP 9
#define motorR_dirN 10
#define motorR_PWM 11
//***************IR sensors  ******************
//#define IR_left 20
//#define IR_right 21
//#define IR_top 49



int lastError = 0;
int position;
int error;

//---------------------- buttons ------------------------------------------

int button1 = 29;
int button2 = 31;
//int button3 = 27;
int btnstate1 = 0, btnstate2 = 0, btnstate3 = 0;

//QTR Sensor

QTRSensorsRC qtrrc((unsigned char[]) { 51, 49, 47, 45, 43, 41, 39, 37} , NUM_SENSORS, TIMEOUT, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];
bool dval[NUM_SENSORS];
//Digital Sensor Values

void qtrRead()
{
  position = qtrrc.readLine(sensorValues);
  for (int i = 0; i < NUM_SENSORS ; i++ )
  {
    if (sensorValues[i] > 500) dval[i] = 1;
    else dval[i] = 0;
    //
    //    Serial.print(dval[i]);
    //    Serial.print('\t');
    //    Serial.print(sensorValues[i]);
    //    Serial.print('\t');
  }
}

//  Encoders functions ------------------------------------------

volatile long leftCount = 0, rightCount = 0;

void leftISR() //ISR for left motor count
{
  leftCount++;
}
void rightISR() //ISR for right motor count
{
  rightCount++;
}


//===================================================



void setup()
{

  Serial.begin(9600);
  delay(500);

  pinMode(motorR_dirP, OUTPUT);
  pinMode(motorR_dirN, OUTPUT);

  pinMode(motorL_dirP, OUTPUT);
  pinMode(motorL_dirN, OUTPUT);

  pinMode(motorR_PWM, OUTPUT);
  pinMode(motorL_PWM, OUTPUT);

  pinMode(motorL_enb, OUTPUT);
  pinMode(motorR_enb, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
//  pinMode(button3, INPUT);

  digitalWrite(motorR_enb, HIGH);
  digitalWrite(motorL_enb, HIGH);


  attachInterrupt(digitalPinToInterrupt(2), leftISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rightISR, CHANGE);

  pinMode(buzzer, OUTPUT);

  //--------------Servos------------------------
  servo1.attach(52);
  servo2.attach(28);
  servo1.write(0);
  servo2.write(68);
  delay(1000);

  //-------------CALIBRATE---------------------------
  tone(buzzer, 200, 1000);
  for (int i = 0; i < 200; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrc.calibrate();

  tone(buzzer, 200, 1000);
  delay(1000);

  //------------------------------------------------
  btnstate1 = digitalRead(button1);
  btnstate2 = digitalRead(button2);
  int lastError = 0;
  int errorSum = 0;
}


int n = 0;

void loop()
{
  //if(btnstate1==HIGH)
  //{
  while (n == 0)
  {
   forward();
   PID(200);
  }
}
//}



//PID Algorithm -------------------------------------------------------------------------------------------------------------------------------------------------------------------

void PID(int pidspeed)
{

  position = qtrrc.readLine(sensorValues); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  error = position - 3500;

  int motorSpeed = (Kp * error + Kd * (error - lastError));
  lastError = error;

  rightBaseSpeed = pidspeed;
  leftBaseSpeed = pidspeed;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;

  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = rightMinSpeed; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = leftMinSpeed; // keep the motor speed positive
  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
}


void PIDB(int pidspeed)
{
  position = qtrrc.readLine(sensorValues); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  error = position - 3500;

  int motorSpeed = (Kp * error + Kd * (error - lastError));
  lastError = error;


  rightBaseSpeed = pidspeed;
  leftBaseSpeed = pidspeed;

  int rightMotorSpeed = rightBaseSpeed - motorSpeed;
  int leftMotorSpeed = leftBaseSpeed + motorSpeed;


  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = rightMinSpeed; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = leftMinSpeed; // keep the motor speed positive
  analogWrite(motorR_PWM, rightMotorSpeed);
  analogWrite(motorL_PWM, leftMotorSpeed);
}



//=====================================================================================================================================================================================
