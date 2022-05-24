#include <Servo.h>

#define servoPin 2


Servo myServo;
int angle = 0;

void setup() {

  myServo.attach(servoPin);

}

void loop() {
  myServo.write(90);
  delay(1000);
  myServo.write(180);
  delay(1000);
  myServo.write(0);
  delay(1000);

  for(angle = 0; angle <= 180; angle += 1 ){
    myServo.write(angle);
    delay(15);
  }
  for(angle = 180; angle >= 0; angle -= 1 ){
    myServo.write(angle);
    delay(30);
  }
  delay(1000);
}
