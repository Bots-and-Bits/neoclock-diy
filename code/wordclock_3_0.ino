#include <Wire.h>
#include <WiFi.h>
#include <Preferences.h>
#include <DNSServer.h>
#include <FastLED.h>
#include "time.h"
#include "RTClib.h"

//Webserver für OTA
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
const char* host = "wordclock";
WebServer webserver(8080);



//LED Kram

#define DATA_PIN    13
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    115
#define FRAMES_PER_SECOND  60
CRGB leds[NUM_LEDS];
long timetimer = millis();
long maintimer = millis();
long reconnecttimer = millis();
int redval = 255;
int greenval = 255;
int blueval = 255;
//boolean zeroclear=false;

//RTC
int rtcpresent = 0;
RTC_DS3231 rtc;
int stunden;
int minuten;
int sekunden;
String formattedDate;
String dayStamp;
String timeStamp;
char timestamp[9];
char datestamp[11];
byte dow;
byte days;            // Day (0 to 31)
byte months;            // Month (0 to 12)
byte years;
boolean DST                       =  false;
int summertime = 1;

//Webserver und Wlan
WiFiClient myclient;
Preferences preferences;
const char* HOSTNAME = "wordclock";
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
WiFiServer server(80);
int numbervalues = 15;
String ConfigName[16];     // name of the configuration value
String ConfigValue[16];    // the value itself (String)
String Wlanssid[50];
String Wlanrssi[50];
int numberWlan;
String HTMLPageWithConfigForm;
const char* passwordap = "mT3gH3Ex";
boolean wificonnected = false;
boolean newnetwork = false;


void setup()
{
  Serial.begin(19200);
  Serial.println("I updated");
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //  startanimation();
  scanwifinetworks();

  initvalues();
  if (rtcpresent == 1)
  {
    if (! rtc.begin()) {
      //    Serial.println("Couldn't find RTC");
    }

    if (rtc.lostPower()) {
      //    Serial.println("RTC lost power, lets set the time!");
    }
    else
    {
      //    Serial.println("RTC bereit");
    }
  }
  updatetime();

  //Hexstring zu RGB
  String hexstring = ConfigValue[0];
  // Get rid of '#' and convert it to integer
  int number = (int) strtol( &hexstring[1], NULL, 16);

  // Split them up into r, g, b values
  redval = map(number >> 16, 0, 255, 0, 255 / 2);
  greenval = map(number >> 8 & 0xFF, 0, 255, 0, 255 / 2);
  blueval = map(number & 0xFF, 0, 255, 0, 255 / 2);


  WiFi_SetBothModesNetworkStationAndAccessPoint();
  char* txtSSID = const_cast<char*>(ConfigValue[8].c_str());
  char* txtPassword = const_cast<char*>(ConfigValue[9].c_str());

  // Start access point with SSID
  WiFi_AccessPointStart();
  int success = WiFi_RouterNetworkConnect(txtSSID, txtPassword);
  Webserver_Start();
  otainit();
}



void loop() {

  if (millis() - maintimer > 5000)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Wifireconnect();
    }
    if (rtcpresent == 1)
    {
      updatetime();
    }
    else
    {
      updatertc();
    }
    setminutes(minuten, stunden);
    maintimer = millis();

    Serial.print(stunden);
    Serial.print(':');
    Serial.print(minuten);
    Serial.println();

  }

  if (millis() - timetimer > 60000 && WiFi.status() == WL_CONNECTED)
  {
    if (rtcpresent == 1)
    {
      updatertc();
    }
    timetimer = millis();
  }


  dnsServer.processNextRequest();
  webserver.handleClient();
  handleserver();
  delay(50);
}








void startanimation()
{
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    // Turn our current led on to white, then show the leds
    leds[whiteLed] = CRGB::White;

    // Show the leds (only one of which is set to white, from above)
    FastLED.show();

    // Wait a little bit
    delay(10);

    // Turn our current led back to black for the next loop around
    leds[whiteLed] = CRGB::Black;
  }
}




void initvalues()
{
  preferences.begin("MyJourney", false);

  // takeout 2 Strings out of the Non-volatile storage
  String strSSID = preferences.getString("SSID", "");
  String strPassword = preferences.getString("Password", "");
  String strZeitzone = preferences.getString("Zeitzone", "");
  String strSommerzeit = preferences.getString("Sommerzeit", "");
  String strColor = preferences.getString("Color", "");
  String strRuhean = preferences.getString("Ruhean", "");
  String strRuhestart = preferences.getString("Ruhestart", "");
  String strRuheende = preferences.getString("Ruheende", "");
  String strHelligkeit = preferences.getString("Helligkeit", "");
  String strRuhehelligkeit = preferences.getString("Ruhehelligkeit", "");

  // initialize config
  ConfigName[0] = "Farbe";
  ConfigName[1] = "Helligkeit";
  ConfigName[2] = "Zeitzone";
  ConfigName[3] = "Sommerzeit";
  ConfigName[5] = "Ruhestart";
  ConfigName[6] = "Ruheende";
  ConfigName[4] = "Ruhean";
  ConfigName[7] = "Ruhehelligkeit";
  ConfigName[8] = "SSID";
  ConfigName[9] = "Passwort";
  ConfigName[10] = "Reset";

  //Standardwerte
  ConfigValue[0] = "#FFFFFF";
  ConfigValue[1] = "50";
  ConfigValue[2] = "1";
  ConfigValue[3] = "1";
  ConfigValue[5] = "22:00";
  ConfigValue[6] = "07:00";
  ConfigValue[4] = "0";
  ConfigValue[7] = "10";
  ConfigValue[8] = "setup";
  ConfigValue[9] = "12345678";
  ConfigValue[10] = "";


  // put the NVS stored values in RAM for the program
  if (strColor != "")
  {
    ConfigValue[0] = strColor;
  }

  if (strHelligkeit != "")
  {
    ConfigValue[1] = strHelligkeit;
  }

  if (strZeitzone != "")
  {
    ConfigValue[2] = strZeitzone;
  }

  if (strSommerzeit != "")
  {
    ConfigValue[3] = strSommerzeit;
  }

  if (strRuhestart != "")
  {
    ConfigValue[5] = strRuhestart;
  }

  if (strRuheende != "")
  {
    ConfigValue[6] = strRuheende;
  }

  if (strRuhean != "")
  {
    ConfigValue[4] = strRuhean;
  }

  if (strRuhehelligkeit != "")
  {
    ConfigValue[7] = strRuhehelligkeit;
  }

  if (strSSID != "")
  {
    ConfigValue[8] = strSSID;
  }

  if (strPassword != "")
  {
    ConfigValue[9] = strPassword;
  }
}
