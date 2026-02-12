void MotorInit() {
  // Linear Motor Init]
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  // ledcSetup(MOTOR_PWM_PIN, MotorFreq, MotorResolution);
  // ledcAttachPin(MOTOR_PWM_PIN, MotorLedChannel);
  // ledcWrite(MotorLedChannel, 0);
  MotorUp();
}
void MotorUp() {
  Serial.println("MOTOR UP");
  // ledcWrite(MotorLedChannel, 200);
  digitalWrite(MOTOR_DIR_PIN, LOW);
  digitalWrite(MOTOR_PWM_PIN, HIGH);
}

void MotorDown() {
  Serial.println("MOTOR DOWN");
  // ledcWrite(MotorLedChannel, 80);
  digitalWrite(MOTOR_DIR_PIN, HIGH);
  digitalWrite(MOTOR_PWM_PIN, HIGH);
}

void MotorStop() {
  Serial.println("모터 스탑");
  digitalWrite(MOTOR_DIR_PIN, LOW);
  ledcWrite(MotorLedChannel, 0);
}
