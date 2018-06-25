
#include <IRremote.h>  // IR remote library resource uploaded

#include <Servo.h>      // servo library resource uploaded

#include <Adafruit_NeoPixel.h> // neoPixel
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 15 // neoPixel is on pin 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_RGBW + NEO_KHZ800); // neoPixel


// IR sensor
int RECV_PIN = 12;  // IR sensor is on pin 12
IRrecv irrecv(RECV_PIN); // IR receiver
decode_results results;

// motor
int AIN1 = 8; // motor A (pin 8)
int AIN2 = 7; // motor A (pin 7)
int BIN1 = 2; // motor B (pin 2)
int BIN2 = 4; // motor B (pin 4)

// color brightness
int colorBrightness = 255;

// servo
int servoPin = 14;    // servo is on pin 14

// for neoPixel
int i;


// ultra sonic sensor
int triggerPin = 18; // pin A4 (pin 18) trig pin
int echoPin = 19; // pin A5 (pin 19) echo pin


Servo servo;

void setup()
{
  servo.attach(servoPin); // servo
  Serial.begin(19200);
  // IR sensor
  irrecv.enableIRIn(); // Start the IR receiver


  // motor
  pinMode(AIN1, OUTPUT); // motor A (pin 8 set as output)
  pinMode(AIN2, OUTPUT); // motor A (pin 7 set as output)
  pinMode(BIN1, OUTPUT); // motor B (pin 2 set as output)
  pinMode(BIN2, OUTPUT); // motor B (pin 4 set as output)

  // neoPixel
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


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
void forward(int howlong, bool Stop) { // move wheels forward
  digitalWrite(AIN1, HIGH); // motor A high on (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, HIGH); // motor B high on (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
  if(Stop == true){
    delay(howlong);
    stop();
  }
}

void backward(int howlong, bool Stop) { // move wheels backward
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, HIGH); // motor A high on (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, HIGH); // motor B high on (pin 7 set as output)
  if(Stop == true){
    delay(howlong);
    stop();
  }
}

void left(int howlong, bool Stop) { // move wheels left
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, HIGH); // motor B high on (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
  if(Stop == true){
    delay(howlong);
    stop();
  }
}

void right(int howlong, bool Stop) { // move wheels right
  digitalWrite(AIN1, HIGH); // motor A high on (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
  if(Stop == true){
    delay(howlong);
    stop();
  }
}

void stop() { // stop all wheels from moving
  digitalWrite(AIN1, LOW); // motor A low off (pin 8 set as output)
  digitalWrite(AIN2, LOW); // motor A low off (pin 7 set as output)
  digitalWrite(BIN1, LOW); // motor B low off (pin 8 set as output)
  digitalWrite(BIN2, LOW); // motor B low off (pin 7 set as output)
}


void loop()
{
  //float inches = ping();
  
  if (irrecv.decode(&results)) {
    //remote button codes
    //-------------------
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    if (results.value == 0x10EFA05F) { // button up on IR remote moves forward
      Serial.println("Button Up"); // print "button up"
      forward(2000, true); // function to move forward
    }
    // motor backward | Button down
    else if (results.value == 0x10EF00FF) { // button down on IR remote moves backward
      Serial.println("Button Down"); // print "button down"
      backward(2000, true); // function to move backward
    }
    // motor left | Button left
    else if (results.value == 0x10EF10EF) { // button left on IR remote moves left
      Serial.println("Button left"); // print "button left"
      left(1000, true); // function to move left
    }
    // motor right | Button right
    else if (results.value == 0x10EF807F) { // button right on IR remote moves right
      Serial.println("Button right"); // print "button right"
      right(1000, true); // function to move right
    }
    // servo arm controller | Button A | neoPixel blue
    // Button A blue color for drawing
    else if (results.value == 0x10EFF807) { // button A on IR remote moves servo 90 deg (color 1 for drawing)
      Serial.println("Button A servo moves 90 deg"); // print "button A servo moves 90 deg"
      colorChange(87, 0, 0, 255, 0);
    }
    else if (results.value == 0x10EF7887) { // button B on IR remote moves servo 60 deg (to reset color for no drawing)
      Serial.println("Button B servo moves 60 deg"); // print "button B servo moves 60 deg to reset"
      colorChange(60, 0, 0, 0, 255);
    }
    else if (results.value == 0x10EF58A7) { // button C on IR remote moves servo 20 deg (color 2 for drawing)
      Serial.println("Button C servo moves 20 deg"); // print "button C servo moves 20 deg"
      colorChange(20, 0, 255, 0, 0);
      servo.write(20);
    }
    // power button | neoPixel white animation
    // neoPixel power button on IR remote makes a white light show / power on effect
    else if (results.value == 0x10EFD827) { // button power on IR remote turns neoPixel on white
      Serial.println("Button power neoPixel turns white on"); // print "button power turns neoPixel turns white on"
      colorChange(0, 0, 0, 0, 255);
    }
    else {
      Serial.print("Unrecognized: ");
      Serial.print(results.value, HEX);
      Serial.println();
    }
    irrecv.resume();
  } else{
   //Serial.println(inches);
  rangeMove();
  }
}


void rangeMove() {
  float inches = ping();
  Serial.println(inches);
  delay(100);
  if (inches > 14 && inches <120) { // hand on ultra sonic moves forward
    //Serial.println("Hand Up"); // print "hand up"
    stop(); // function to move forward
  }
  else if (inches >= 5 && inches <= 8) {
    backward(200, false);
  }
  else if (inches > 8 && inches <= 13) {
    forward(200, false);
  }
}

void colorChange(int deg, int r, int g, int b, int w){
      servo.write(deg);
      for (i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(r, g, b, w)); // neoPixel turns red
        strip.setBrightness(colorBrightness);
      }
      strip.show();

  
}













