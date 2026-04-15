#include <MotorWebUI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

const char* ssid     = "Kobryn";
const char* password = "password123";

#define IN1 5   
#define IN2 4   
#define IN3 14  
#define IN4 13  

AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);
const float STEPS_PER_DEGREE = 2048.0 / 360.0;

ESP8266WebServer server(80);

void disableCoils() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void onMove(int deg, bool dir) {
  long steps = (long)(deg * STEPS_PER_DEGREE);
  if (dir) stepper.move(steps);
  else stepper.move(-steps);
}

void onStop() {
  stepper.stop();
  stepper.setCurrentPosition(stepper.currentPosition());
  disableCoils();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  disableCoils();

  stepper.setMaxSpeed(500);
  stepper.setAcceleration(200);

  WiFi.softAP(ssid, password);
  Serial.println("\nAP started!");
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  initWeb(server);
}

void loop() {
  handleWeb();

  if (stepper.distanceToGo() != 0) {
    stepper.run();
  } else {
    disableCoils();
  }
}