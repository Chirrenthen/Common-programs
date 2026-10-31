/*Line following robot.
  created by SriTu Tech team.
  Read the code below and use it for any of your creation
*/
//motor one
#define ENA 5
#define IN1 2
#define IN2 3
 
//motor two
#define ENB 6
#define IN3 7
#define IN4 8
 
//sensor pins
#define SL 10
#define SR 9
 
int mSpeed = 130;//motor speed
 
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
  pinMode(SL, INPUT);
  pinMode(SR, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  bool LValue = digitalRead(SL);//get sensor value one 
  bool RValue = digitalRead(SR);//get sensor value two 
 
  Serial.print(LValue);
  Serial.println(RValue);
 
  if (RValue == 1 && LValue == 0 ) {
    turnRight();
    Serial.println("turnRight");
  } else if (LValue == 1 && RValue == 0) {
    turnLeft();
    Serial.println("turnLeft");
  } else if (LValue == 0 && RValue == 0) {
    forward();
    Serial.println("forward");
  } else if (LValue == 1 && RValue == 1) {
    Stop();
    Serial.println("stop");
  }
 
 
}
void turnRight() {
  analogWrite(ENA, mSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
 
}
void turnLeft() {
  analogWrite(ENB, mSpeed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void forward() {
  analogWrite(ENA, mSpeed);
  analogWrite(ENB, mSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}