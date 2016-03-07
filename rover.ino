// ---------------------------------------------------------------------------
// Rover control code, ported from trinket rover @
// http://learn.adafruit.com/trinket-powered-rover/source-code
// for the Victoria Makerspace by Thomas Gray
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h> 

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define RIGHT_SERVO 2
#define LEFT_SERVO 3
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define OBSTACLE 10
#define SPEED 50  // adjust speed so that this value moves the rover 1 cm
#define AVOID_TIME 1000  // time to run the avoid process, in ms

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo leftServo;
Servo rightServo;

void setup() {
  // To rotate the servo you just write a value to it, 90 is stop, a value lower then 90 is counterclockwise a value bigger then 90 is clockwise.
  leftServo.attach(LEFT_SERVO);
  rightServo.attach(RIGHT_SERVO);
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int distance = (uS / US_ROUNDTRIP_CM);

  if(distance < 10) {
    leftServo.write(SPEED);
    rightServo.write(SPEED);
    delay(AVOID_TIME);
  }
  
  leftServo.write(90+SPEED);
  rightServo.write(90-SPEED);
}

