#include <Servo.h>

#define trigPin 9
#define echoPin 10
#define in1 3
#define in2 4
#define in3 5
#define in4 6

Servo myServo; // Servo object
int distance;

// Function to measure distance using ultrasonic sensor
int getDistance() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2; // Convert to centimeters
}

// Motor control functions
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize servo
  myServo.attach(11); // Attach servo to pin 11
  myServo.write(90);  // Set initial position to 90 degrees

  Serial.begin(9600);
}

void loop() {
  // Sweep servo to scan environment
  int leftDistance, rightDistance;

  myServo.write(30); // Sweep left
  delay(500);
  leftDistance = getDistance();

  myServo.write(90); // Sweep center
  delay(500);
  distance = getDistance();

  myServo.write(150); // Sweep right
  delay(500);
  rightDistance = getDistance();

  // Print distances for debugging
  // Serial.print("Center: ");
  // Serial.print(distance);
  // Serial.print(" cm, Left: ");
  // Serial.print(leftDistance);
  // Serial.print(" cm, Right: ");
  // Serial.print(rightDistance);
  // Serial.println(" cm");

  // Obstacle avoidance logic
  if (distance < 30) { // Obstacle ahead
    Stop();
    delay(500);

    if (leftDistance > rightDistance) {
      turnLeft(); // Turn left if more space
      delay(500);
    } else {
      turnRight(); // Turn right otherwise
      delay(500);
    }
   else {
    moveForward();
    delay(500);// Move forward if path is clear
   } 
