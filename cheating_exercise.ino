/*
   INTELLIGENCE EXERCISE: 200 Digits of Phi
   Method: Batch Mode (20 Digits/Block) + Logic (1-5 Left, 6-0 Right)
   Hardware: Arduino Nano, Battery, 2x Motors (D3, D5), 2x Buttons (for redundancy)
   Input: DUAL BUTTONS (D7 and A5)
*/

// --- DATA ---
const byte digits[] = {
  1,6,1,8,0,3,3,9,8,8,7,4,9,8,9,4,8,4,8,2,
  0,4,5,8,6,8,3,4,3,6,5,6,3,8,1,1,7,7,2,0,
  3,0,9,1,7,9,8,0,5,7,6,2,8,6,2,1,3,5,4,4,
  8,6,2,2,7,0,5,2,6,0,4,6,2,8,1,8,9,0,2,4,
  4,9,7,0,7,2,0,7,2,0,4,1,8,9,3,9,1,1,3,7,
  4,8,4,7,5,4,0,8,8,0,7,5,3,8,6,8,9,1,7,5,
  2,1,2,6,6,3,3,8,6,2,2,2,3,5,3,6,9,3,1,7,
  9,3,1,8,0,0,6,0,7,6,6,7,2,6,3,5,4,4,3,3,
  3,8,9,0,8,6,5,9,5,9,3,9,5,8,2,9,0,5,6,3,
  8,3,2,2,6,6,1,3,1,9,9,2,8,2,9,0,2,6,7,8,8
};

// --- PIN CONFIGURATION ---
const int MOTOR_LEFT = 3;   
const int MOTOR_RIGHT = 5;  

// --- DUAL BUTTON SETUP ---
const int BTN_PRIMARY = 7;  
const int BTN_SECONDARY = A5;

// --- SENSITIVITY TUNING (CRITICAL) ---
// From experimentation: Pressed (~20), Idle (~55), 35 should be perfect
const int ANALOG_THRESHOLD = 35; 

// --- TIMING ---
const int MOTOR_STRENGTH = 150; 
const int PULSE_LEN = 130;      
const int GAP_LEN = 130;        
const int DIGIT_GAP = 2000;     
const int CLICK_TIMEOUT = 600;  


int currentBlock = 0; 
const int DIGITS_PER_BLOCK = 20; 
const int TOTAL_BLOCKS = 10;     

void setup() {
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  
  //internal resistors for buttons
  pinMode(BTN_PRIMARY, INPUT_PULLUP);
  pinMode(BTN_SECONDARY, INPUT_PULLUP);

  //STARTUP
  buzz(true, false, 100); delay(100);
  buzz(false, true, 100); delay(100);
  buzz(true, false, 100);
  
  // Wait for any button to start
  while(isAnyButtonPressed() == false) {}
  delay(1000); 
}

void loop() {
  playBlock(currentBlock);

  int command = getClicks();

  if (command == 1) {
    currentBlock++;
    if (currentBlock >= TOTAL_BLOCKS) currentBlock = 0; 
  }
  else if (command == 2) {
    // REPEAT
  }
  else if (command == 3) {
    currentBlock--;
    if (currentBlock < 0) currentBlock = TOTAL_BLOCKS - 1; 
  }
  
  delay(1000); 
}

// --- HELPER: CHECKS BOTH BUTTONS ---
bool isAnyButtonPressed() {
  // Check 1: D7
  if (digitalRead(BTN_PRIMARY) == LOW) return true;

  // Check 2: A5
  if (analogRead(BTN_SECONDARY) < ANALOG_THRESHOLD) return true;

  return false;
}

// --- LOGIC FUNCTIONS ---
void playBlock(int blockIndex) {
  int startDigit = blockIndex * DIGITS_PER_BLOCK;
  for (int i = 0; i < DIGITS_PER_BLOCK; i++) {
    playDigit(digits[startDigit + i]);
    if (i < DIGITS_PER_BLOCK - 1) delay(DIGIT_GAP); 
  }
}

void playDigit(byte d) {
  if (d >= 1 && d <= 5) {
    pulseSequence(true, false, d);
  } 
  else {
    int pulses = 0;
    if (d == 0) pulses = 5;       
    else pulses = d - 5;          
    pulseSequence(false, true, pulses);
  }
}

int getClicks() {
  int clicks = 0;
  unsigned long lastClickTime = 0;
  bool waiting = true;

  while (isAnyButtonPressed() == false); // Wait for press
  
  clicks++;
  lastClickTime = millis();
  while(isAnyButtonPressed() == true); // Wait for release
  delay(50); 

  while (waiting) {
    if (isAnyButtonPressed() == true) {
      clicks++;
      lastClickTime = millis();
      while(isAnyButtonPressed() == true);
      delay(50);
    }
    
    if (millis() - lastClickTime > CLICK_TIMEOUT) waiting = false;
    if (clicks >= 3) waiting = false;
  }
  return clicks;
}

void pulseSequence(bool useLeft, bool useRight, int count) {
  for (int i = 0; i < count; i++) {
    buzz(useLeft, useRight, PULSE_LEN);
    if (i < count - 1) delay(GAP_LEN);
  }
}

void buzz(bool left, bool right, int duration) {
  if (left) analogWrite(MOTOR_LEFT, MOTOR_STRENGTH);
  if (right) analogWrite(MOTOR_RIGHT, MOTOR_STRENGTH);
  delay(duration);
  digitalWrite(MOTOR_LEFT, LOW);
  digitalWrite(MOTOR_RIGHT, LOW);
}