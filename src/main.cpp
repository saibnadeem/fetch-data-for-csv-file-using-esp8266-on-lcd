#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LittleFS.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void displayDataFromCSV();
void showError(const char* message);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  if (!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    showError("LittleFS Mount Error");
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Loading data...");
  displayDataFromCSV();
}

void loop() {
  displayDataFromCSV();
  delay(10000);
}

void displayDataFromCSV() {
  File file = LittleFS.open("/nemes.csv", "r");

  if (!file) {
    Serial.println("Failed to open file for reading");
    showError("File not found");
    return;
  }
  while (file.available()) {
    String line = file.readStringUntil('\n');
    if (line.length() > 0 && (line.charAt(line.length() - 1) == '\r' || line.charAt(line.length() - 1) == '\n')) {
      line.remove(line.length() - 1);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line);

    delay(2000);

    if (!file.available()) {
      break;
    }
  }

  file.close();
}

void showError(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error:");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(2000);  
}
// component requarted 
// esp8266
// lcd (16*2 )