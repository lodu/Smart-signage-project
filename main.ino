#include <Adafruit_LiquidCrystal.h>
#include <SPI.h>
#include <WiFi.h>
#include <aREST.h>

#define ARROW_LEFT "<-"
#define ARROW_RIGHT "->"
#define ARROW_UP "^"
#define ARROW_DOWN "v"

char ssid[] = "<INSERT SSID>"; 
char pass[] = "<INSERT PASSWORD>";   
int status = WL_IDLE_STATUS;

const int rs = 33, en = 25, d4 = 26, d5 = 27, d6 = 14, d7 = 12; // LCD
int buttonPin = 15;

String arrow;

bool previousButtonValue = false;
bool isToggled = false; // true when Grote Markt is 'full'

Adafruit_LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
WiFiServer server(80);
aREST rest = aREST();


void setup() {

  // used by aREST web-dashboard
  rest.set_id("001");
  rest.set_name("dotjes_machine");

  // functions to be exposed
  rest.function("flip", updateLcd);


  // connect to WIFI
  while (status != WL_CONNECTED)
  {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid, pass);
      delay(10000);
  }

  server.begin();

  lcd.begin(16, 2);
  updateLcd(""); // LCD is blank initially
}

void loop() {
  WiFiClient client = server.available();
  rest.handle(client);
  // readButton();
}

int updateLcd(String text) {  
  isToggled = !isToggled;  

  if (isToggled) {
    arrow = ARROW_LEFT;
    lcdPrintToLine("Vermijd drukte!  ", 0);
    lcdPrintToLine(generateDestinationText("Aa-kerk"), 1);
  } else {
    arrow = ARROW_RIGHT;
    lcdPrintToLine(generateDestinationText("Grote markt"), 0);
    arrow = ARROW_LEFT;
    lcdPrintToLine(generateDestinationText("Aa-kerk"), 1);
  }
  return 1;
}

void lcdPrintToLine(String text, int line) {
  lcd.setCursor(0, line);
  lcd.print(text); 
}

// format text for LCD
String generateDestinationText(String destination) {
  String displayString = destination;
  int amountOfWhiteSpace = 16 - destination.length() - arrow.length();
  for (int i = 0; i < amountOfWhiteSpace; i++) {
    displayString += " ";
  }
  
  displayString += arrow;

  return displayString; 
}

void readButton() {  
  bool buttonValue = digitalRead(buttonPin);
  if (previousButtonValue == 0 && buttonValue == 1) {
    isToggled = !isToggled;
    updateLcd();
  }
  previousButtonValue = buttonValue; 
}