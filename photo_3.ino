void setup() {
 Serial.begin(19200);
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
}

void loop() {
 int value;
 int value1;
 int value2;
 
 value = analogRead(A0);
 Serial.print(value);
 Serial.print(" ");
  value1 = analogRead(A1);
 Serial.print(value1);
 Serial.print(" ");
  value2 = analogRead(A2);
 Serial.print(value2);
 Serial.println(" 0 1023 ");

}
