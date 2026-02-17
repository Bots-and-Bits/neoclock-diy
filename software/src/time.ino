void setMinutes(int m, int h)  // Set minutes and display time
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
    setHour(h);
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
    setHour(h);
    displayFive();
    displayPast();
  }

  if (m >= 10 && m < 15)
  {
    setHour(h);
    displayTen();
    displayPast();
  }

  if (m >= 15 && m < 20)
  {
    setHour(h);
    displayQuarter();
    displayPast();
  }

  if (m >= 20 && m < 25)
  {
    setHour(h);
    displayTwenty();
    displayPast();
  }

  if (m >= 25 && m < 30)
  {
    setHour(h);
    displayFive();
    displayTwenty();
    displayPast();
  }

  if (m >= 30 && m < 35)
  {

    setHour(h + 1);

    //HALB (half past)
    leds[107] = CRGB(redval, greenval, blueval);
    leds[97] = CRGB(redval, greenval, blueval);
    leds[86] = CRGB(redval, greenval, blueval);
    leds[77] = CRGB(redval, greenval, blueval);
  }

  if (m >= 35 && m < 40)
  {
    setHour(h + 1);
    displayFive();
    displayTwenty();

    displayTo();
  }

  if (m >= 40 && m < 45)
  {
    setHour(h + 1);
    displayTwenty();

    displayTo();
  }

  if (m >= 45 && m < 50)
  {
    setHour(h + 1);

    displayQuarter();
    displayTo();
  }

  if (m >= 50 && m < 55)
  {
    setHour(h + 1);
    displayTen();
    displayTo();
  }

  if (m >= 55 && m < 60)
  {
    setHour(h + 1);
    displayFive();
    displayTo();
  }


  if (e >= 5)
  {
    e = e - 5;
  }

  switch (e) {   // Set corner LEDs (minute indicators)

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
  FastLED.show();
  delay(50);

}

// Same as setMinutes() but without FastLED.show() or delay
// Used for rainbow mode to avoid flickering
void setMinutesNoShow(int m, int h)
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
    setHour(h);
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
    setHour(h);
    displayFive();
    displayPast();
  }

  if (m >= 10 && m < 15)
  {
    setHour(h);
    displayTen();
    displayPast();
  }

  if (m >= 15 && m < 20)
  {
    setHour(h);
    displayQuarter();
    displayPast();
  }

  if (m >= 20 && m < 25)
  {
    setHour(h);
    displayTwenty();
    displayPast();
  }

  if (m >= 25 && m < 30)
  {
    setHour(h);
    displayFive();
    displayTwenty();
    displayPast();
  }

  if (m >= 30 && m < 35)
  {
    setHour(h + 1);
    //HALB (half past)
    leds[107] = CRGB(redval, greenval, blueval);
    leds[97] = CRGB(redval, greenval, blueval);
    leds[86] = CRGB(redval, greenval, blueval);
    leds[77] = CRGB(redval, greenval, blueval);
  }

  if (m >= 35 && m < 40)
  {
    setHour(h + 1);
    displayFive();
    displayTwenty();
    displayTo();
  }

  if (m >= 40 && m < 45)
  {
    setHour(h + 1);
    displayTwenty();
    displayTo();
  }

  if (m >= 45 && m < 50)
  {
    setHour(h + 1);
    displayQuarter();
    displayTo();
  }

  if (m >= 50 && m < 55)
  {
    setHour(h + 1);
    displayTen();
    displayTo();
  }

  if (m >= 55 && m < 60)
  {
    setHour(h + 1);
    displayFive();
    displayTo();
  }

  if (e >= 5)
  {
    e = e - 5;
  }

  switch (e) {   // Set corner LEDs (minute indicators)
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
  // No FastLED.show() or delay() - caller will show after applying effects
}


void setHour(int h)  // Set hours (convert 24h to 12h format)
{
  // Convert 24-hour to 12-hour format
  if (h == 0) {
    h = 12;
  } else if (h > 12) {
    h = h - 12;
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

void displayFive()  // "FÜNF" (five minutes)
{
  // 'FÜNF' (five) — German word used in display mapping
  leds[41] = CRGB(redval, greenval, blueval);
  leds[22] = CRGB(redval, greenval, blueval);
  leds[21] = CRGB(redval, greenval, blueval);
  leds[1] = CRGB(redval, greenval, blueval);

}

void displayTen()  // "ZEHN" (ten minutes)
{
  //ZEHN
  leds[104] = CRGB(redval, greenval, blueval);
  leds[100] = CRGB(redval, greenval, blueval);
  leds[83] = CRGB(redval, greenval, blueval);
  leds[80] = CRGB(redval, greenval, blueval);
}
void displayQuarter()  // "VIERTEL" (quarter)
{
  // 'VIERTEL' (quarter) — German word used in display mapping
  leds[64] = CRGB(redval, greenval, blueval);
  leds[59] = CRGB(redval, greenval, blueval);
  leds[44] = CRGB(redval, greenval, blueval);
  leds[39] = CRGB(redval, greenval, blueval);
  leds[24] = CRGB(redval, greenval, blueval);
  leds[19] = CRGB(redval, greenval, blueval);
  leds[3] = CRGB(redval, greenval, blueval);

}

void displayTwenty()  // "ZWANZIG" (twenty minutes)
{
  // 'ZWANZIG' (twenty) — German word used in display mapping
  leds[63] = CRGB(redval, greenval, blueval);
  leds[60] = CRGB(redval, greenval, blueval);
  leds[43] = CRGB(redval, greenval, blueval);
  leds[40] = CRGB(redval, greenval, blueval);
  leds[23] = CRGB(redval, greenval, blueval);
  leds[20] = CRGB(redval, greenval, blueval);
  leds[2] = CRGB(redval, greenval, blueval);
}

void displayTo()  // "VOR" (to/before the hour)
{

  // 'VOR' (to/before) — German word used in display mapping

  leds[45] = CRGB(redval, greenval, blueval);
  leds[38] = CRGB(redval, greenval, blueval);
  leds[25] = CRGB(redval, greenval, blueval);
}

void displayPast()  // "NACH" (past the hour)
{
  // 'NACH' (past/after) — German word used in display mapping
  leds[85] = CRGB(redval, greenval, blueval);
  leds[78] = CRGB(redval, greenval, blueval);
  leds[65] = CRGB(redval, greenval, blueval);
  leds[58] = CRGB(redval, greenval, blueval);
}

// updatertc() function moved to 00_main.ino (modernized with ezTime)

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
