void setminutes(int m, int h)  //minuten setzen
{
  FastLED.clear ();



  //ES IST


  leds[103] = CRGB(redval, greenval, blueval);
  leds[101] = CRGB(redval, greenval, blueval);
  leds[61] = CRGB(redval, greenval, blueval);
  leds[81] = CRGB(redval, greenval, blueval);
  leds[62] = CRGB(redval, greenval, blueval);


  int e = 0;
  e = m % 10;


  if ((m >= 0 && m < 5) || m == 60)
  {
    sethour(h);
    if (h == 1)
    {
      leds[56] = CRGB::Black;
    }
    leds[31] = CRGB(redval, greenval, blueval);
    leds[12] = CRGB(redval, greenval, blueval);
    leds[10] = CRGB(redval, greenval, blueval);


  }

  if (m >= 5 && m < 10)
  {
    sethour(h);
    fuenf();
    nach();
  }

  if (m >= 10 && m < 15)
  {
    sethour(h);
    zehn();
    nach();
  }

  if (m >= 15 && m < 20)
  {
    sethour(h);
    viertel();
    nach();
  }

  if (m >= 20 && m < 25)
  {
    sethour(h);
    zwanzig();
    nach();
  }

  if (m >= 25 && m < 30)
  {
    sethour(h);
    fuenf();
    zwanzig();
    nach();
  }

  if (m >= 30 && m < 35)
  {

    sethour(h + 1);

    //HALB
    leds[107] = CRGB(redval, greenval, blueval);
    leds[97] = CRGB(redval, greenval, blueval);
    leds[86] = CRGB(redval, greenval, blueval);
    leds[77] = CRGB(redval, greenval, blueval);
  }

  if (m >= 35 && m < 40)
  {
    sethour(h + 1);
    fuenf();
    zwanzig();

    vor();
  }

  if (m >= 40 && m < 45)
  {
    sethour(h + 1);
    zwanzig();

    vor();
  }

  if (m >= 45 && m < 50)
  {
    sethour(h + 1);

    viertel();
    vor();
  }

  if (m >= 50 && m < 55)
  {
    sethour(h + 1);
    zehn();
    vor();
  }

  if (m >= 55 && m < 60)
  {
    sethour(h + 1);
    fuenf();
    vor();
  }


  if (e >= 5)
  {
    e = e - 5;
  }

  switch (e) {   //ecken setzten

    case 1:
      leds[102] = CRGB(redval, greenval, blueval);
      break;
    case 2:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      break;
    case 3:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      break;
    case 4:
      leds[102] = CRGB(redval, greenval, blueval);
      leds[0] = CRGB(redval, greenval, blueval);
      leds[113] = CRGB(redval, greenval, blueval);
      leds[11] = CRGB(redval, greenval, blueval);
      break;
  }
//if(zeroclear==true)
//{
//  FastLED.clear ();
//}
  FastLED.show();
  delay(50);

}


void sethour(int h)  //Stunden setzen
{
  if (h == 13)
  {
    h = 1;
  }
  if (h == 0)
  {
    h = 12;
  }

  switch (h) {
    case 1:
      leds[87] = CRGB(redval, greenval, blueval);
      leds[76] = CRGB(redval, greenval, blueval);
      leds[67] = CRGB(redval, greenval, blueval);
      leds[56] = CRGB(redval, greenval, blueval);
      break;

    case 2:
      leds[108] = CRGB(redval, greenval, blueval);
      leds[96] = CRGB(redval, greenval, blueval);
      leds[87] = CRGB(redval, greenval, blueval);
      leds[76] = CRGB(redval, greenval, blueval);

      break;

    case 3:

      leds[95] = CRGB(redval, greenval, blueval);
      leds[88] = CRGB(redval, greenval, blueval);
      leds[75] = CRGB(redval, greenval, blueval);
      leds[68] = CRGB(redval, greenval, blueval);

      break;

    case 4:
      leds[34] = CRGB(redval, greenval, blueval);
      leds[29] = CRGB(redval, greenval, blueval);
      leds[14] = CRGB(redval, greenval, blueval);
      leds[8] = CRGB(redval, greenval, blueval);

      break;
    case 5:
      leds[35] = CRGB(redval, greenval, blueval);
      leds[28] = CRGB(redval, greenval, blueval);
      leds[15] = CRGB(redval, greenval, blueval);
      leds[7] = CRGB(redval, greenval, blueval);

      break;
    case 6:
      leds[92] = CRGB(redval, greenval, blueval);
      leds[91] = CRGB(redval, greenval, blueval);
      leds[72] = CRGB(redval, greenval, blueval);
      leds[71] = CRGB(redval, greenval, blueval);
      leds[52] = CRGB(redval, greenval, blueval);

      break;
    case 7:
      leds[56] = CRGB(redval, greenval, blueval);
      leds[47] = CRGB(redval, greenval, blueval);
      leds[36] = CRGB(redval, greenval, blueval);
      leds[27] = CRGB(redval, greenval, blueval);
      leds[16] = CRGB(redval, greenval, blueval);
      leds[6] = CRGB(redval, greenval, blueval);

      break;
    case 8:

      leds[93] = CRGB(redval, greenval, blueval);
      leds[90] = CRGB(redval, greenval, blueval);
      leds[73] = CRGB(redval, greenval, blueval);
      leds[70] = CRGB(redval, greenval, blueval);

      break;
    case 9:
      leds[74] = CRGB(redval, greenval, blueval);
      leds[69] = CRGB(redval, greenval, blueval);
      leds[54] = CRGB(redval, greenval, blueval);
      leds[49] = CRGB(redval, greenval, blueval);

      break;
    case 10:
      leds[53] = CRGB(redval, greenval, blueval);
      leds[50] = CRGB(redval, greenval, blueval);
      leds[33] = CRGB(redval, greenval, blueval);
      leds[30] = CRGB(redval, greenval, blueval);

      break;
    case 11:
      leds[110] = CRGB(redval, greenval, blueval);
      leds[94] = CRGB(redval, greenval, blueval);
      leds[89] = CRGB(redval, greenval, blueval);

      break;
    case 12:
      leds[57] = CRGB(redval, greenval, blueval);
      leds[46] = CRGB(redval, greenval, blueval);
      leds[37] = CRGB(redval, greenval, blueval);
      leds[26] = CRGB(redval, greenval, blueval);
      leds[17] = CRGB(redval, greenval, blueval);

      break;

  }

}

void fuenf()
{
  //Fünf
  leds[41] = CRGB(redval, greenval, blueval);
  leds[22] = CRGB(redval, greenval, blueval);
  leds[21] = CRGB(redval, greenval, blueval);
  leds[1] = CRGB(redval, greenval, blueval);

}

void zehn()
{
  //ZEHN
  leds[104] = CRGB(redval, greenval, blueval);
  leds[100] = CRGB(redval, greenval, blueval);
  leds[83] = CRGB(redval, greenval, blueval);
  leds[80] = CRGB(redval, greenval, blueval);
}
void viertel()
{
  //Viertel
  leds[64] = CRGB(redval, greenval, blueval);
  leds[59] = CRGB(redval, greenval, blueval);
  leds[44] = CRGB(redval, greenval, blueval);
  leds[39] = CRGB(redval, greenval, blueval);
  leds[24] = CRGB(redval, greenval, blueval);
  leds[19] = CRGB(redval, greenval, blueval);
  leds[3] = CRGB(redval, greenval, blueval);

}

void zwanzig()
{
  //ZWANZIG
  leds[63] = CRGB(redval, greenval, blueval);
  leds[60] = CRGB(redval, greenval, blueval);
  leds[43] = CRGB(redval, greenval, blueval);
  leds[40] = CRGB(redval, greenval, blueval);
  leds[23] = CRGB(redval, greenval, blueval);
  leds[20] = CRGB(redval, greenval, blueval);
  leds[2] = CRGB(redval, greenval, blueval);
}

void vor()
{

  //VOR

  leds[45] = CRGB(redval, greenval, blueval);
  leds[38] = CRGB(redval, greenval, blueval);
  leds[25] = CRGB(redval, greenval, blueval);
}

void nach()
{
  //NACH
  leds[85] = CRGB(redval, greenval, blueval);
  leds[78] = CRGB(redval, greenval, blueval);
  leds[65] = CRGB(redval, greenval, blueval);
  leds[58] = CRGB(redval, greenval, blueval);
}


void updatertc()
{
  const char* ntpServer = "pool.ntp.org";

  const long  gmtOffset_sec = 0;
  const int   daylightOffset_sec = 0;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  stunden = timeinfo.tm_hour;
  minuten = timeinfo.tm_min;
  sekunden = timeinfo.tm_sec;
  years = timeinfo.tm_year + 1900;
  months = timeinfo.tm_mon + 1;
  days = timeinfo.tm_mday;

  if (rtcpresent == 0)
  {

    if (ConfigValue[3].toInt() == 1)
    {
      clockGen();
    }

    stunden = stunden + ConfigValue[2].toInt();


    if (stunden < 12)
    {
      stunden = stunden + 24;
    }
    if (stunden > 24)
    {
      stunden = stunden - 24;
    }

    dealwithnighttime();

    if (stunden > 12)
    {
      stunden = stunden - 12;
    }
  }
  else
  {
    rtc.adjust(DateTime(years - 48, months, days, stunden, minuten, sekunden));
  }

}


String split(String s, char parser, int index) {
  String rs = "";
  int parserIndex = index;
  int parserCnt = 0;
  int rFromIndex = 0, rToIndex = -1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex + 1;
    rToIndex = s.indexOf(parser, rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex, rToIndex);
    } else parserCnt++;
  }
  return rs;
}


void dealwithnighttime()
{
  boolean nighttime = false;

  String temphstart = ConfigValue[5];
  String temphend = ConfigValue[6];
  String tempmstart = ConfigValue[5];
  String tempmend = ConfigValue[6];

  int temphourstart = split(temphstart, ':', 0).toInt();
  int temphourend = split(temphend, ':', 0).toInt();
  int tempminstart = ConfigValue[5].substring(3, 5).toInt();
  int tempminend = ConfigValue[6].substring(3, 5).toInt();

  if (ConfigValue[4].toInt() == 1)
  {
    if (temphourstart > temphourend)
    {
      if (stunden >= temphourstart || stunden <= temphourend )
      {
        //nachthelligkeit
        if (stunden != temphourstart && stunden != temphourend)
        {
          nighttime = true;
        }

        if (stunden == temphourstart && minuten >= tempminstart)
        {
          nighttime = true;
        }
        if (stunden == temphourend && minuten <= tempminend)
        {
          nighttime = true;
        }
      }
    }

    if (temphourstart == temphourend)
    {
      if (stunden == temphourstart && stunden == temphourend)
      {

        if (minuten >= tempminstart && minuten <= tempminend)
        {
          nighttime = true;
        }
      }
    }

    if (temphourstart < temphourend)
    {

      if (stunden >= temphourstart && stunden <= temphourend)
      {
        //Nacht
        if (stunden != temphourstart && stunden != temphourend)
        {
          nighttime = true;
        }
        if (stunden == temphourstart && minuten >= tempminstart)
        {
          nighttime = true;
        }
        if (stunden == temphourend && minuten <= tempminend)
        {
          nighttime = true;
        }
      }
    }
  }


  if (nighttime == true)
  {
    FastLED.setBrightness(map(ConfigValue[7].toInt(), 0, 100, 0, 255));
//    zeroclear = false;
//    if (ConfigValue[7].toInt() == 0)
//    {
//      zeroclear = true;
//    }
  }
  else {
    FastLED.setBrightness(map(ConfigValue[1].toInt(), 0, 100, 0, 255));
//    zeroclear = false;
//    if (ConfigValue[1].toInt() == 0)
//    {
//      zeroclear = true;
//    }
  }

}

void updatetime()
{
  DateTime now = rtc.now();
  stunden = now.hour();
  minuten = now.minute();
  months = now.month();
  days = now.day();
  years   = now.year();

  if (ConfigValue[3].toInt() == 1)
  {
    clockGen();
  }

  stunden = stunden + ConfigValue[2].toInt();


  if (stunden < 12)
  {
    stunden = stunden + 24;
  }
  if (stunden > 24)
  {
    stunden = stunden - 24;
  }

  dealwithnighttime();

  if (stunden > 12)
  {
    stunden = stunden - 12;
  }

  //  Serial.print(years);
  //  Serial.print('/');
  //  Serial.print(months, DEC);
  //  Serial.print('/');
  //  Serial.print(days, DEC);
  //  Serial.print(" (");
  //  Serial.print(stunden);
  //  Serial.print(':');
  //  Serial.print(minuten);
  //  Serial.print(':');
  //  Serial.print(now.second(), DEC);
  //  Serial.print(")");
  //  Serial.println();

}
