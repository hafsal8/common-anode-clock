#include <ESP8266WiFi.h>
#include <time.h>

// ================= WIFI =================

const char* ssid = "athikarath5G";
const char* password = "8590084515hafsal";

const char* ntpServer = "pool.ntp.org";

long gmtOffset_sec = 19800; // India UTC +5:30
int daylightOffset_sec = 0;

// ================= DISPLAY PINS =================

int dataPin  = D5;
int clockPin = D6;
int latchPin = D7;

int digitPins[4] = {D1, D2, D3, D4};

// ================= SEGMENT MAP =================

#define SEG_F  0
#define SEG_A  1
#define SEG_D  2
#define SEG_E  3
#define SEG_C  4
#define SEG_G  5
#define SEG_B  6
#define SEG_DP 7

// ================= MAKE DIGIT =================

byte makeDigit(bool a,bool b,bool c,bool d,bool e,bool f,bool g,bool dp=false){

  byte val = 0xFF;

  if(a) bitClear(val, SEG_A);
  if(b) bitClear(val, SEG_B);
  if(c) bitClear(val, SEG_C);
  if(d) bitClear(val, SEG_D);
  if(e) bitClear(val, SEG_E);
  if(f) bitClear(val, SEG_F);
  if(g) bitClear(val, SEG_G);
  if(dp) bitClear(val, SEG_DP);

  return val;
}

// ================= NUMBER TABLE =================

byte numbers[10];

// ================= DISPLAY FUNCTION =================

void displayDigit(int digit, byte value){

  // OFF all digits
  for(int i=0;i<4;i++) {

    digitalWrite(digitPins[i], HIGH);
  }

  // Send segment data
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, value);

  digitalWrite(latchPin, HIGH);

  // Enable selected digit
  digitalWrite(digitPins[digit], LOW);

  delay(2);

  // Disable again
  digitalWrite(digitPins[digit], HIGH);
}

// ================= CLOCK VARIABLES =================

int currentHour = 0;
int currentMinute = 0;

unsigned long lastUpdate = 0;

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  // Display pins
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  for(int i=0;i<4;i++) {

    pinMode(digitPins[i], OUTPUT);

    digitalWrite(digitPins[i], HIGH);
  }

  // Generate digits

  numbers[0] = makeDigit(1,1,1,1,1,1,0);
  numbers[1] = makeDigit(0,1,1,0,0,0,0);
  numbers[2] = makeDigit(1,1,0,1,1,0,1);
  numbers[3] = makeDigit(1,1,1,1,0,0,1);
  numbers[4] = makeDigit(0,1,1,0,0,1,1);
  numbers[5] = makeDigit(1,0,1,1,0,1,1);
  numbers[6] = makeDigit(1,0,1,1,1,1,1);
  numbers[7] = makeDigit(1,1,1,0,0,0,0);
  numbers[8] = makeDigit(1,1,1,1,1,1,1);
  numbers[9] = makeDigit(1,1,1,1,0,1,1);

  // ================= WIFI =================

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  // ================= NTP =================

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("Waiting for NTP sync...");

  while(time(nullptr) < 100000) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("\nTime Synced!");
}

// ================= LOOP =================

void loop() {

  // Update internet time every second

  if(millis() - lastUpdate > 1000) {

    lastUpdate = millis();

    time_t now = time(nullptr);

    struct tm* timeinfo = localtime(&now);

    currentHour = timeinfo->tm_hour;
    currentMinute = timeinfo->tm_min;

    Serial.print(currentHour);

    Serial.print(":");

    if(currentMinute < 10)
      Serial.print("0");

    Serial.println(currentMinute);
  }

  // Split digits

  int d1 = currentHour / 10;
  int d2 = currentHour % 10;

  int d3 = currentMinute / 10;
  int d4 = currentMinute % 10;

  // Add blinking decimal point

  byte secondDigit = numbers[d2];

  if((millis()/500)%2 == 0) {

    bitClear(secondDigit, SEG_DP);
  }

  // Display HH.MM

  displayDigit(0, numbers[d1]);
  displayDigit(1, secondDigit);
  displayDigit(2, numbers[d3]);
  displayDigit(3, numbers[d4]);
}