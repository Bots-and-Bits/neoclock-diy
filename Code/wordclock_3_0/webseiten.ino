
void Webserver_Start()
{
  server.begin();     // Start TCP/IP-Server on ESP32
}



String WebRequestHostAddress;     // global variable used to store Server IP-Address of HTTP-Request


//  Call this function regularly to look for client requests
//  template see https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/SimpleWiFiServer/SimpleWiFiServer.ino
//  returns empty string if no request from any client
//  returns GET Parameter: everything after the "/?" if ADDRESS/?xxxx was entered by the user in the webbrowser
//  returns "-" if ADDRESS but no GET Parameter was entered by the user in the webbrowser
//  remark: client connection stays open after return
String Webserver_GetRequestGETParameter()
{
  String GETParameter = "";
  boolean newpage = true;

  myclient = server.available();   // listen for incoming clients

  //Serial.print(".");

  if (myclient) {                            // if you get a client,
 //   Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                 // make a String to hold incoming data from the client

    while (myclient.available()) {            // if there's bytes to read from the client,

      //      if (myclient.available()) {            // if there's bytes to read from the client,

      char c = myclient.read();            // read a byte, then
 //     Serial.write(c);                     // print it out the serial monitor

      if (c == '\n') {                     // if the byte is a newline character

        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request
        if (currentLine.length() == 0) {
          if (newpage == true)
          {
    
            if (GETParameter.length() > 1)      // request contains some GET parameter
            {
              DecodeGETParameterAndSetConfigValues(GETParameter);     // decode the GET parameter and set ConfigValues
              ProcessAndValidateConfigValues(numbervalues);
            }
            EncodeFormHTMLFromConfigValuesnew();
            Webserver_SendHTMLPage(HTMLPageWithConfigForm);
          }
          if (GETParameter == "") {
            GETParameter = "-";
          }    // if no "GET /?" was found so far in the request bytes, return "-"

          // break out of the while loop:
          break;

        } else {    // if you got a newline, then clear currentLine:
          currentLine = "";
        }

      } else if (c != '\r') {  // if you got anything else but a carriage return character,
        currentLine += c;      // add it to the end of the currentLine
      }

      if (c == '\r' && currentLine.startsWith("GET /?"))
      {
        GETParameter = currentLine.substring(currentLine.indexOf('?') + 1, currentLine.indexOf(' ', 6));    // extract everything behind the ? and before a space
        newpage = false;
      }

      if (c == '\r' && currentLine.startsWith("GET /generate_204?"))
      {

        GETParameter = currentLine.substring(currentLine.indexOf('?') + 1, currentLine.indexOf(' ', 18));    // extract everything behind the ? and before a space
        newpage = false;
      }

      if (c == '\r' && currentLine.startsWith("Host:"))
        // we see a "Host:" in the HTTP data of the client request
        // user entered ADDRESS or ADDRESS/... in webbrowser, ADDRESS = Server IP-Address of HTTP-Request
      {
        int IndexOfBlank = currentLine.indexOf(' ');
        WebRequestHostAddress = currentLine.substring(IndexOfBlank + 1, currentLine.length());    // extract everything behind the space character and store Server IP-Address of HTTP-Request
      }

    }

 //   Serial.println("get parameter");
 //   Serial.println(GETParameter);
    return GETParameter;
  }


}


void Wifireconnect()
{
  if (reconnecttimer - millis() > 60000)
  {
 //   Serial.println("Attempting to reconnect");
    String strSSID = preferences.getString("SSID", "");
    String strPassword = preferences.getString("Password", "");

    char* txtSSID = const_cast<char*>(strSSID.c_str());
    char* txtPassword = const_cast<char*>(strPassword.c_str());

    WiFi.begin(txtSSID, txtPassword);
    WiFi.setHostname(HOSTNAME);
    reconnecttimer = millis();
  }
}

// Send HTML page to client, as HTTP response
// client connection must be open (call Webserver_GetRequestGETParameter() first)
void Webserver_SendHTMLPage(String HTMLPage)
{
  String httpResponse = "";

  // begin with HTTP response header
  httpResponse += "HTTP/1.1 200 OK\r\n";
  httpResponse += "Content-type:text/html\r\n\r\n";

  // then the HTML page
  httpResponse += HTMLPage;

  // The HTTP response ends with a blank line:
  httpResponse += "\r\n";

  // send it out to TCP/IP client = webbrowser
  myclient.println(httpResponse);

  // close the connection
  myclient.stop();

//  Serial.println("Client Disconnected.");

};



// +++++++++++++++++++ End of Webserver library +++++++++++++++++++++




// +++++++++++++++++++ Start of WiFi Library ++++++++++++++++++++++++


// Connect to router network and return 1 (success) or -1 (no success)
int WiFi_RouterNetworkConnect(char* txtSSID, char* txtPassword)
{
  int success = 1;
  // connect to WiFi network
  // see https://www.arduino.cc/en/Reference/WiFiBegin
//  Serial.print("trying to connect to wifi with ssid:");
 // Serial.print(txtSSID);
 // Serial.print(" and password:");
//  Serial.println(txtPassword);

  WiFi.begin(txtSSID, txtPassword);
  WiFi.setHostname(HOSTNAME);

  // we wait until connection is established
  // or 10 seconds are gone

  int WiFiConnectTimeOut = 0;
  while ((WiFi.status() != WL_CONNECTED) && (WiFiConnectTimeOut < 10))
  {
    delay(1000);
    WiFiConnectTimeOut++;
  }

  // not connected
  if (WiFi.status() != WL_CONNECTED)
  {
    success = -1;
    wificonnected = false;
  }
  else
  {
    wificonnected = true;
    updatertc();
    setminutes(minuten, stunden);
  }
  // print out local address of ESP32 in Router network (LAN)
//Serial.println(WiFi.localIP());

//  Serial.print("Wificonnected boolean: ");
//  Serial.println(wificonnected);
  return success;
}

// Disconnect from router network and return 1 (success) or -1 (no success)
int WiFi_RouterNetworkDisconnect()
{
  int success = -1;

  WiFi.disconnect();

  int WiFiConnectTimeOut = 0;
  while ((WiFi.status() == WL_CONNECTED) && (WiFiConnectTimeOut < 10))
  {
//    Serial.println("in DC Loop");
    delay(1000);
    WiFiConnectTimeOut++;
  }

  // not connected
  if (WiFi.status() != WL_CONNECTED)
  {
    success = 1;
    Serial.println("Disconnected.");
  }

  return success;
}


// Initialize Soft Access Point with ESP32
// ESP32 establishes its own WiFi network, one can choose the SSID
void WiFi_AccessPointStart()
{

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Wordclock", passwordap);
  dnsServer.start(DNS_PORT, "*", apIP);
  WiFi.setHostname(HOSTNAME);
//  Serial.println(WiFi.softAPIP());
}


// Put ESP32 in both modes in parallel: Soft Access Point and station in router network (LAN)
void WiFi_SetBothModesNetworkStationAndAccessPoint()
{
  WiFi.mode(WIFI_AP_STA);
}


// Get IP-Address of ESP32 in Router network (LAN), in String-format
String WiFi_GetOwnIPAddressInRouterNetwork()
{
  return WiFi.localIP().toString();
}



// +++++++++++++++++++ End of WiFi Library +++++++++++++++++++



//Request decodieren und ConfigValue setzen
int DecodeGETParameterAndSetConfigValues(String GETParameter)
{

  int posFirstCharToSearch = 1;
  int count = 0;

  // while a "&" is in the expression, after a start position to search
  while (GETParameter.indexOf('&', posFirstCharToSearch) > -1)
  {
    int posOfSeparatorChar = GETParameter.indexOf('&', posFirstCharToSearch);  // position of & after start position
    int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);      // position of = after start position

    ConfigValue[count] = GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar);  // extract everything between = and & and enter it in the ConfigValue

    posFirstCharToSearch = posOfSeparatorChar + 1;  // shift the start position to search after the &-char
    count++;
  }

  // no more & chars found

  int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);       // search for =

  ConfigValue[count] = GETParameter.substring(posOfValueChar + 1, GETParameter.length());  // extract everything between = and end of string
  count++;

  return count;  // number of values found in GET parameter
}



//Datenverarbeitung
void ProcessAndValidateConfigValues(int countValues)
{
  if (ConfigValue[4] == "Summertime")
  {
    ConfigValue[3] = "1";
    ConfigValue[4] = ConfigValue[5];
    ConfigValue[5] = ConfigValue[6];
    ConfigValue[6] = ConfigValue[7];
    ConfigValue[7] = ConfigValue[8];
    ConfigValue[8] = ConfigValue[9];
    ConfigValue[9] = ConfigValue[10];
    ConfigValue[10] = ConfigValue[11];
    ConfigValue[11] = ConfigValue[12];
  }

  if (ConfigValue[5] == "nighttime")
  {
    ConfigValue[4] = "1";
    ConfigValue[5] = ConfigValue[6];
    ConfigValue[6] = ConfigValue[7];
    ConfigValue[7] = ConfigValue[8];
    ConfigValue[8] = ConfigValue[9];
    ConfigValue[9] = ConfigValue[10];
    ConfigValue[10] = ConfigValue[11];
    ConfigValue[11] = ConfigValue[12];
  }

  for (int i = 0; i < numbervalues; i++)
  {
    ConfigValue[i] = GetRidOfurlCharacters(ConfigValue[i]);
    Serial.print(ConfigName[i]);
    Serial.print("\t ");
    Serial.println(ConfigValue[i]);
  }

  //Hexstring zu RGB
  String hexstring = ConfigValue[0];
  // Get rid of '#' and convert it to integer
  int number = (int) strtol( &hexstring[1], NULL, 16);

  // Split them up into r, g, b values
  redval = map(number >> 16, 0, 255, 0, 255 / 2);
  greenval = map(number >> 8 & 0xFF, 0, 255, 0, 255 / 2);
  blueval = map(number & 0xFF, 0, 255, 0, 255 / 2);

  String tempssid = preferences.getString("SSID", "");
  String temppw = preferences.getString("Password", "");


  if (ConfigValue[10] == "RESET")
  {
//    Serial.println("Reset all values");
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
  }


  preferences.putString("Color", ConfigValue[0]);
  preferences.putString("Helligkeit", ConfigValue[1]);
  preferences.putString("Zeitzone", ConfigValue[2]);
  preferences.putString("Sommerzeit", ConfigValue[3]);
  preferences.putString("Ruhestart", ConfigValue[5]);
  preferences.putString("Ruheende", ConfigValue[6]);
  preferences.putString("Ruhean", ConfigValue[4]);
  preferences.putString("Ruhehelligkeit", ConfigValue[7]);
  preferences.putString("SSID", ConfigValue[8]);
  preferences.putString("Password", ConfigValue[9]);

  if (tempssid.equals(ConfigValue[8]) && temppw.equals(ConfigValue[9]))
  {
    newnetwork = false;
  }
  else {
    newnetwork = true;
  }
}



void handleserver()
{
  String GETParameter = Webserver_GetRequestGETParameter();   // look for client request

  if (GETParameter.length() > 0)        // we got a request, client connection stays open
  {
    if (GETParameter.length() > 1)      // request contains some GET parameter
    {
      int countValues = DecodeGETParameterAndSetConfigValues(GETParameter);     // decode the GET parameter and set ConfigValues
      ProcessAndValidateConfigValues(numbervalues);


      if (newnetwork == true)                   // the user entered this address in browser, with GET parameter values for configuration
      {

        String strSSID = preferences.getString("SSID", "");                 // takeout SSID and Password out of non-volatile storage
        String strPassword = preferences.getString("Password", "");

        char* txtSSID = const_cast<char*>(strSSID.c_str());                 // convert to char*
        char* txtPassword = const_cast<char*>(strPassword.c_str());         // https://coderwall.com/p/zfmwsg/arduino-string-to-char

        int successDisconnect = WiFi_RouterNetworkDisconnect();             // disconnect from router network
        int successConnect = WiFi_RouterNetworkConnect(txtSSID, txtPassword);   // then try to connect once new with new login-data

        if (successConnect == 1)
        {
//          Serial.println("Success to connect new WIFI ");

        }
        else
        {
 //         Serial.println("NO success to connect new WIFI ");

        }
      }
      EncodeFormHTMLFromConfigValuesnew();       // build a new Configuration webpage with form and new ConfigValues entered in textboxes

      Webserver_SendHTMLPage(HTMLPageWithConfigForm);    // send out the webpage to client = webbrowser and close client connection

    }
  }
}


void scanwifinetworks()
{
  WiFi.mode(WIFI_STA);
//  Serial.println("scan start");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  numberWlan = n;
//  Serial.println("scan done");
  if (n == 0) {
//    Serial.println("no networks found");
  } else {
//  Serial.print(n);
//    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Wlanssid[n-1-i] = WiFi.SSID(i);
      Wlanrssi[n-1-i] = WiFi.RSSI(i);
    }
  }
  WiFi.disconnect();
}

String GetRidOfurlCharacters(String urlChars)
{
  urlChars.replace("%0D%0A", String('\n'));
  urlChars.replace("+",   " ");
  urlChars.replace("%20", " ");
  urlChars.replace("%21", "!");
  urlChars.replace("%22", String(char('\"')));
  urlChars.replace("%23", "#");
  urlChars.replace("%24", "$");
  urlChars.replace("%25", "%");
  urlChars.replace("%26", "&");
  urlChars.replace("%27", String(char(39)));
  urlChars.replace("%28", "(");
  urlChars.replace("%29", ")");
  urlChars.replace("%2A", "*");
  urlChars.replace("%2B", "+");
  urlChars.replace("%2C", ",");
  urlChars.replace("%2D", "-");
  urlChars.replace("%2E", ".");
  urlChars.replace("%2F", "/");
  urlChars.replace("%30", "0");
  urlChars.replace("%31", "1");
  urlChars.replace("%32", "2");
  urlChars.replace("%33", "3");
  urlChars.replace("%34", "4");
  urlChars.replace("%35", "5");
  urlChars.replace("%36", "6");
  urlChars.replace("%37", "7");
  urlChars.replace("%38", "8");
  urlChars.replace("%39", "9");
  urlChars.replace("%3A", ":");
  urlChars.replace("%3B", ";");
  urlChars.replace("%3C", "<");
  urlChars.replace("%3D", "=");
  urlChars.replace("%3E", ">");
  urlChars.replace("%3F", "?");
  urlChars.replace("%40", "@");
  urlChars.replace("%41", "A");
  urlChars.replace("%42", "B");
  urlChars.replace("%43", "C");
  urlChars.replace("%44", "D");
  urlChars.replace("%45", "E");
  urlChars.replace("%46", "F");
  urlChars.replace("%47", "G");
  urlChars.replace("%48", "H");
  urlChars.replace("%49", "I");
  urlChars.replace("%4A", "J");
  urlChars.replace("%4B", "K");
  urlChars.replace("%4C", "L");
  urlChars.replace("%4D", "M");
  urlChars.replace("%4E", "N");
  urlChars.replace("%4F", "O");
  urlChars.replace("%50", "P");
  urlChars.replace("%51", "Q");
  urlChars.replace("%52", "R");
  urlChars.replace("%53", "S");
  urlChars.replace("%54", "T");
  urlChars.replace("%55", "U");
  urlChars.replace("%56", "V");
  urlChars.replace("%57", "W");
  urlChars.replace("%58", "X");
  urlChars.replace("%59", "Y");
  urlChars.replace("%5A", "Z");
  urlChars.replace("%5B", "[");
  urlChars.replace("%5C", String(char(65)));
  urlChars.replace("%5D", "]");
  urlChars.replace("%5E", "^");
  urlChars.replace("%5F", "_");
  urlChars.replace("%60", "`");
  urlChars.replace("%61", "a");
  urlChars.replace("%62", "b");
  urlChars.replace("%63", "c");
  urlChars.replace("%64", "d");
  urlChars.replace("%65", "e");
  urlChars.replace("%66", "f");
  urlChars.replace("%67", "g");
  urlChars.replace("%68", "h");
  urlChars.replace("%69", "i");
  urlChars.replace("%6A", "j");
  urlChars.replace("%6B", "k");
  urlChars.replace("%6C", "l");
  urlChars.replace("%6D", "m");
  urlChars.replace("%6E", "n");
  urlChars.replace("%6F", "o");
  urlChars.replace("%70", "p");
  urlChars.replace("%71", "q");
  urlChars.replace("%72", "r");
  urlChars.replace("%73", "s");
  urlChars.replace("%74", "t");
  urlChars.replace("%75", "u");
  urlChars.replace("%76", "v");
  urlChars.replace("%77", "w");
  urlChars.replace("%78", "x");
  urlChars.replace("%79", "y");
  urlChars.replace("%7A", "z");
  urlChars.replace("%7B", String(char(123)));
  urlChars.replace("%7C", "|");
  urlChars.replace("%7D", String(char(125)));
  urlChars.replace("%7E", "~");
  urlChars.replace("%7F", "Â");
  urlChars.replace("%80", "`");
  urlChars.replace("%81", "Â");
  urlChars.replace("%82", "â");
  urlChars.replace("%83", "Æ");
  urlChars.replace("%84", "â");
  urlChars.replace("%85", "â¦");
  urlChars.replace("%86", "â");
  urlChars.replace("%87", "â¡");
  urlChars.replace("%88", "Ë");
  urlChars.replace("%89", "â°");
  urlChars.replace("%8A", "Å");
  urlChars.replace("%8B", "â¹");
  urlChars.replace("%8C", "Å");
  urlChars.replace("%8D", "Â");
  urlChars.replace("%8E", "Å½");
  urlChars.replace("%8F", "Â");
  urlChars.replace("%90", "Â");
  urlChars.replace("%91", "â");
  urlChars.replace("%92", "â");
  urlChars.replace("%93", "â");
  urlChars.replace("%94", "â");
  urlChars.replace("%95", "â¢");
  urlChars.replace("%96", "â");
  urlChars.replace("%97", "â");
  urlChars.replace("%98", "Ë");
  urlChars.replace("%99", "â¢");
  urlChars.replace("%9A", "Å¡");
  urlChars.replace("%9B", "âº");
  urlChars.replace("%9C", "Å");
  urlChars.replace("%9D", "Â");
  urlChars.replace("%9E", "Å¾");
  urlChars.replace("%9F", "Å¸");
  urlChars.replace("%A0", "Â");
  urlChars.replace("%A1", "Â¡");
  urlChars.replace("%A2", "Â¢");
  urlChars.replace("%A3", "Â£");
  urlChars.replace("%A4", "Â¤");
  urlChars.replace("%A5", "Â¥");
  urlChars.replace("%A6", "Â¦");
  urlChars.replace("%A7", "Â§");
  urlChars.replace("%A8", "Â¨");
  urlChars.replace("%A9", "Â©");
  urlChars.replace("%AA", "Âª");
  urlChars.replace("%AB", "Â«");
  urlChars.replace("%AC", "Â¬");
  urlChars.replace("%AE", "Â®");
  urlChars.replace("%AF", "Â¯");
  urlChars.replace("%B0", "Â°");
  urlChars.replace("%B1", "Â±");
  urlChars.replace("%B2", "Â²");
  urlChars.replace("%B3", "Â³");
  urlChars.replace("%B4", "Â´");
  urlChars.replace("%B5", "Âµ");
  urlChars.replace("%B6", "Â¶");
  urlChars.replace("%B7", "Â·");
  urlChars.replace("%B8", "Â¸");
  urlChars.replace("%B9", "Â¹");
  urlChars.replace("%BA", "Âº");
  urlChars.replace("%BB", "Â»");
  urlChars.replace("%BC", "Â¼");
  urlChars.replace("%BD", "Â½");
  urlChars.replace("%BE", "Â¾");
  urlChars.replace("%BF", "Â¿");
  urlChars.replace("%C0", "Ã");
  urlChars.replace("%C1", "Ã");
  urlChars.replace("%C2", "Ã");
  urlChars.replace("%C3", "Ã");
  urlChars.replace("%C4", "Ã");
  urlChars.replace("%C5", "Ã");
  urlChars.replace("%C6", "Ã");
  urlChars.replace("%C7", "Ã");
  urlChars.replace("%C8", "Ã");
  urlChars.replace("%C9", "Ã");
  urlChars.replace("%CA", "Ã");
  urlChars.replace("%CB", "Ã");
  urlChars.replace("%CC", "Ã");
  urlChars.replace("%CD", "Ã");
  urlChars.replace("%CE", "Ã");
  urlChars.replace("%CF", "Ã");
  urlChars.replace("%D0", "Ã");
  urlChars.replace("%D1", "Ã");
  urlChars.replace("%D2", "Ã");
  urlChars.replace("%D3", "Ã");
  urlChars.replace("%D4", "Ã");
  urlChars.replace("%D5", "Ã");
  urlChars.replace("%D6", "Ã");
  urlChars.replace("%D7", "Ã");
  urlChars.replace("%D8", "Ã");
  urlChars.replace("%D9", "Ã");
  urlChars.replace("%DA", "Ã");
  urlChars.replace("%DB", "Ã");
  urlChars.replace("%DC", "Ã");
  urlChars.replace("%DD", "Ã");
  urlChars.replace("%DE", "Ã");
  urlChars.replace("%DF", "Ã");
  urlChars.replace("%E0", "Ã");
  urlChars.replace("%E1", "Ã¡");
  urlChars.replace("%E2", "Ã¢");
  urlChars.replace("%E3", "Ã£");
  urlChars.replace("%E4", "Ã¤");
  urlChars.replace("%E5", "Ã¥");
  urlChars.replace("%E6", "Ã¦");
  urlChars.replace("%E7", "Ã§");
  urlChars.replace("%E8", "Ã¨");
  urlChars.replace("%E9", "Ã©");
  urlChars.replace("%EA", "Ãª");
  urlChars.replace("%EB", "Ã«");
  urlChars.replace("%EC", "Ã¬");
  urlChars.replace("%ED", "Ã­");
  urlChars.replace("%EE", "Ã®");
  urlChars.replace("%EF", "Ã¯");
  urlChars.replace("%F0", "Ã°");
  urlChars.replace("%F1", "Ã±");
  urlChars.replace("%F2", "Ã²");
  urlChars.replace("%F3", "Ã³");
  urlChars.replace("%F4", "Ã´");
  urlChars.replace("%F5", "Ãµ");
  urlChars.replace("%F6", "Ã¶");
  urlChars.replace("%F7", "Ã·");
  urlChars.replace("%F8", "Ã¸");
  urlChars.replace("%F9", "Ã¹");
  urlChars.replace("%FA", "Ãº");
  urlChars.replace("%FB", "Ã»");
  urlChars.replace("%FC", "Ã¼");
  urlChars.replace("%FD", "Ã½");
  urlChars.replace("%FE", "Ã¾");
  urlChars.replace("%FF", "Ã¿");

  return urlChars;
}
