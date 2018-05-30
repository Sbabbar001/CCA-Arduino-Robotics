#include <IRremote.h>

int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
int led = 13;
int AIN1 = 8;
int AIN2 = 7;
int BIN1 = 2;
int BIN2 = 4;

void setup()
{
  Serial.begin(19200);
  irrecv.enableIRIn(); // Start the receiver
   pinMode(led, OUTPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);
 pinMode(BIN1, OUTPUT);
 pinMode(BIN2, OUTPUT);
}

void forward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, HIGH);
 digitalWrite(AIN2, LOW);
 digitalWrite(BIN1, HIGH);
 digitalWrite(BIN2, LOW);
}

void backward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, HIGH);
 digitalWrite(BIN1, LOW);
 digitalWrite(BIN2, HIGH);
}

void stop() {
 digitalWrite(led, LOW);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, LOW);
 digitalWrite(BIN1, LOW);
 digitalWrite(BIN2, LOW);
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
 if (results.value == 0x90) {
 Serial.println("Button Up");
 forward();
 delay(200);
 stop();
 }
 else if (results.value == 0x890) {
 Serial.println("Button Down");
 backward();
 delay(200);
 stop();
 }
 else {
 Serial.print("Unrecognized: ");
 Serial.print(results.value, HEX);
 Serial.println();
 }
 irrecv.resume(); 
  }
}
