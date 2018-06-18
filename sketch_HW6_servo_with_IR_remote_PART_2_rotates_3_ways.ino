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
    if (results.value == 0x10EFF807) { // button A on IR remote moves servo 90 deg
      Serial.println("Button A servo moves 90 deg"); // print "button A servo moves 90 deg"
      servo.write(90);
    }
    else if (results.value == 0x10EF7887) { // button B on IR remote moves servo 60 deg to reset
      Serial.println("Button A servo moves 60 deg"); // print "button b servo moves 60 deg to reset"
      servo.write(60);
    }
    else if (results.value == 0x10EF58A7) { // button C on IR remote moves servo 60 deg to reset
      Serial.println("Button C servo moves 60 deg"); // print "button C servo moves 60 deg to reset"
      servo.write(20);
    }
  }
}

