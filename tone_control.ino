
void setup() {
 Serial.begin(19200);
 pinMode(A0, INPUT);
 pinMode(13, OUTPUT);
}

void loop() {
 int value;
 value = analogRead(A0);
 Serial.print(value);
 Serial.println(" 0 1023");
 tone(13, value);

}


