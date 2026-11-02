const int trigPin = 9;    
const int echoPin = 10;   
#define one 7
#define two 8
#define led 2 

void setup() {
  Serial.begin(9600);         
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //motor
  digitalWrite(one, LOW);
  digitalWrite(two, LOW);
  digitalWrite(led, LOW);

  // sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);   
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.0343 / 2;
 
  if(distance < 20 && distance > 10){
    Serial.println("\n LED ON");
    digitalWrite(led, HIGH);
  }else if(distance < 10 && distance > 0){
    Serial.println("\n Motor ON");
    digitalWrite(one, HIGH);
    digitalWrite(two, LOW);
  }else{
    Serial.println("\n No object");
  }
  delay(500);
}
