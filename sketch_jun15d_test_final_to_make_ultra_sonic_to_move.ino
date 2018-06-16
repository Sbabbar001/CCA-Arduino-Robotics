/*
  #include <IRremote.h>  // IR remote library resource uploaded

  int RECV_PIN = 12;  // IR sensor is on pin 12
  IRrecv irrecv(RECV_PIN); // IR receiver
  decode_results results;
*/

// motor
int AIN1 = 8; // motor A (pin 8)
int AIN2 = 7; // motor A (pin 7)
int BIN1 = 2; // motor B (pin 2)
int BIN2 = 4; // motor B (pin 4)

// ultra sonic sensor
int triggerPin = 18; // pin A4 (pin 18) trig pin
int echoPin = 19; // pin A5 (pin 19) echo pin

void setup()
{
  /*
    Serial.begin(19200);
    // IR sensor
    irrecv.enableIRIn(); // Start the IR receiver
  */

  // motor
  pinMode(AIN1, OUTPUT); // motor A (pin 8 set as output)
  pinMode(AIN2, OUTPUT); // motor A (pin 7 set as output)
  pinMode(BIN1, OUTPUT); // motor B (pin 2 set as output)
  pinMode(BIN2, OUTPUT); // motor B (pin 4 set as output)

  // ultra sonic sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
}

// ultra sonic sensor
float ping() {
  unsigned long maxTime = 20000;
  unsigned long us;
  float inches;
  // Hold triggerPin high for at least 10us
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Measure length of high pulse on echoPin
  us = pulseIn(echoPin, HIGH, maxTime);
  // pulseIn returns 0 on timeout. Assume worst case.
  if (us == 0) {
    us = maxTime;
  }
  // Convert roundtrip microseconds to inches
  inches = us * 0.013504 / 2;
  return inches;
}

// motor functions
void forward() { // move wheels forward
  digitalWrite(AIN1, HIGH); // motor A high on (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, HIGH); // motor B high on (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
}

void backward() { // move wheels backward
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, HIGH); // motor A high on (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, HIGH); // motor B high on (pin 7 set as output)
}

void left() { // move wheels left
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, HIGH); // motor B high on (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
}

void right() { // move wheels right
  digitalWrite(AIN1, HIGH); // motor A high on (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
}

void stop() { // stop all wheels from moving
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
}

void loop()
{
  /*
    if (irrecv.decode(&results)) {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
  */
  float inches = ping();
  Serial.println(inches);
  delay(60);
  if (inches > 45) { // hand on ultra sonic moves forward
    //Serial.println("Hand Up"); // print "hand up"
    forward(); // function to move forward
    // delay(1000); // delay 1 second
    // stop();   // stop
  }
  else if (inches <= 45) {
    backward();
    delay(1000);
    right();
  }
}
/*
  else if (results.value == 0x10EF00FF) { // button down on IR remote moves backward
  Serial.println("Button Down"); // print "button down"
  backward(); // function to move backward
  delay(1000); // delay 1 second
  stop(); // stop
  }
  else if (results.value == 0x10EF10EF) { // button left on IR remote moves left
  Serial.println("Button left"); // print "button left"
  left(); // function to move left
  delay(1000); // delay 1 second
  stop(); // stop
  }
  else if (results.value == 0x10EF807F) { // button right on IR remote moves right
  Serial.println("Button right"); // print "button right"
  right(); // function to move right
  delay(1000); // delay 1 second
  stop(); // stop
  }
  else {
  Serial.print("Unrecognized: ");
  Serial.print(results.value, HEX);
  Serial.println();
  }
*/


/* void loop()
  {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    if (results.value == 0x10EFA05F) { // button up on IR remote moves forward
      Serial.println("Button Up"); // print "button up"
      forward(); // function to move forward
      delay(1000); // delay 1 second
      stop();   // stop
    }
    else if (results.value == 0x10EF00FF) { // button down on IR remote moves backward
      Serial.println("Button Down"); // print "button down"
      backward(); // function to move backward
      delay(1000); // delay 1 second
      stop(); // stop
    }
    else if (results.value == 0x10EF10EF) { // button left on IR remote moves left
      Serial.println("Button left"); // print "button left"
      left(); // function to move left
      delay(1000); // delay 1 second
      stop(); // stop
    }
    else if (results.value == 0x10EF807F) { // button right on IR remote moves right
      Serial.println("Button right"); // print "button right"
      right(); // function to move right
      delay(1000); // delay 1 second
      stop(); // stop
    }
    else {
      Serial.print("Unrecognized: ");
      Serial.print(results.value, HEX);
      Serial.println();
    }
    irrecv.resume();
  }
  }
*/
