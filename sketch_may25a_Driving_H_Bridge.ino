int led = 13;
int AIN1 = 7;
int AIN2 = 8;

void setup() {
 pinMode(led, OUTPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);
}

void forward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, HIGH);
 digitalWrite(AIN2, LOW);
}

void backward() {
 digitalWrite(led, HIGH);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, HIGH);
}

void stop() {
 digitalWrite(led, LOW);
 digitalWrite(AIN1, LOW);
 digitalWrite(AIN2, LOW);
}

void loop() {
 forward();
 delay(2000);
 backward();
 delay(2000);
 stop();
 delay(1000);
}
