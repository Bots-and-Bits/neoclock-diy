byte calcDayOfWeek (byte y, byte m, byte d) {
  // Old mental arithmetic method for calculating day of week
  // adapted for Arduino, for years 2000~2099
  // returns 1 for Sunday, 2 for Monday, etc., up to 7 for Saturday
  // for "bad" dates (like Feb. 30), it returns 0
  // Note: input year (y) should be a number from 0~99
  if (y > 99) return 0; // we don't accept years after 2099
  // we take care of bad months later
  if (d < 1) return 0; // because there is no day 0
  byte w = 6; // this is a magic number (y2k fix for this method)
  // one ordinary year is 52 weeks + 1 day left over
  // a leap year has one more day than that
  // we add in these "leftover" days
  w += (y + (y >> 2));
  // correction for Jan. and Feb. of leap year
  if (((y & 3) == 0) && (m <= 2)) w--;
  // add in "magic number" for month
  switch (m) {
    case 1:  if (d > 31) return 0; w += 1; break;
    case 2:  if (d > ((y & 3) ? 28 : 29)) return 0; w += 4; break;
    case 3:  if (d > 31) return 0; w += 4; break;
    case 4:  if (d > 30) return 0; break;
    case 5:  if (d > 31) return 0; w += 2; break;
    case 6:  if (d > 30) return 0; w += 5; break;
    case 7:  if (d > 31) return 0; break;
    case 8:  if (d > 31) return 0; w += 3; break;
    case 9:  if (d > 30) return 0; w += 6; break;
    case 10: if (d > 31) return 0; w += 1; break;
    case 11: if (d > 30) return 0; w += 4; break;
    case 12: if (d > 31) return 0; w += 6; break;
    default: return 0;
  }
  // then add day of month
  w += d;
  // there are only 7 days in a week, so we "cast out" sevens
  while (w > 7) w = (w >> 3) + (w & 7);
  return w;
}

void clockGen() {
dow= calcDayOfWeek(years, months, days);
  if (months <= 2 || months >= 11)
    DST = false;                                   // Winter months
  if (months >= 4 && months <= 9)
    DST = true;                                    // Summer months
  //***  Detect the beginning of theU DST in March and set DST = 1
  if (months == 3 && days - dow >= 25) {           // Begin of summer time
    if (stunden >= 3 - 1) // MESZ – 1 hour
      DST = true;
  }

  //***  Still summer months time DST beginning of October, so easy to determine
  if (months == 10 && days - dow < 25)
    DST = true;
  if (months == 10 && days - dow >= 25) {
    if (stunden >= 3 - 1) {
      DST = false;
 //     Serial.println("We have winter time");
    }
    else {
      DST = true;
  //    Serial.println("A good day! We have summer time");
    }
  }
  if (DST == true)
    stunden += 1;                                    // Add 1 hour due to detected DST
}
