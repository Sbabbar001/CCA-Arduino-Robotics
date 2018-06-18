#include <Servo.h>
#include <IRremote.h>  // IR remote library resource uploaded

int RECV_PIN = 12;  // IR sensor is on pin 12
IRrecv irrecv(RECV_PIN); // IR receiver
decode_results results;

int servoPin = 14;

Servo servo;

void setup() {
  servo.attach(servoPin);
  Serial.begin(19200);
  // IR sensor
  irrecv.enableIRIn(); // Start the IR receiver

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    if (results.value == 0x10EFF807) { // button A on IR remote moves servo 180 deg
      Serial.println("Button A servo moves 180 deg"); // print "button A servo moves 180 deg"
      servo.write(90);
      delay(3000);
      servo.write(30);
    }
}
}
    
