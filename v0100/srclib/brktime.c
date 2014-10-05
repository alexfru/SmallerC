/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#include "itime.h"

#ifdef __SMALLER_C_32__
static unsigned short DaysSinceEpoch[]=
{
  /*1970*/             0u,  365u,  730u, 1096u, 1461u, 1826u, 2191u,
  /*1977*/   2557u, 2922u, 3287u, 3652u, 4018u, 4383u, 4748u, 5113u,
  /*1985*/   5479u, 5844u, 6209u, 6574u, 6940u, 7305u, 7670u, 8035u,
  /*1993*/   8401u, 8766u, 9131u, 9496u, 9862u,10227u,10592u,10957u,
  /*2001*/  11323u,11688u,12053u,12418u,12784u,13149u,13514u,13879u,
  /*2009*/  14245u,14610u,14975u,15340u,15706u,16071u,16436u,16801u,
  /*2017*/  17167u,17532u,17897u,18262u,18628u,18993u,19358u,19723u,
  /*2025*/  20089u,20454u,20819u,21184u,21550u,21915u,22280u,22645u,
  /*2033*/  23011u,23376u,23741u,24106u,24472u,24837u,25202u,25567u,
  /*2041*/  25933u,26298u,26663u,27028u,27394u,27759u,28124u,28489u,
  /*2049*/  28855u,29220u,29585u,29950u,30316u,30681u,31046u,31411u,
  /*2057*/  31777u,32142u,32507u,32872u,33238u,33603u,33968u,34333u,
  /*2065*/  34699u,35064u,35429u,35794u,36160u,36525u,36890u,37255u,
  /*2073*/  37621u,37986u,38351u,38716u,39082u,39447u,39812u,40177u,
  /*2081*/  40543u,40908u,41273u,41638u,42004u,42369u,42734u,43099u,
  /*2089*/  43465u,43830u,44195u,44560u,44926u,45291u,45656u,46021u,
  /*2097*/  46387u,46752u,47117u,47482u,47847u,48212u,48577u,48942u,
  /*2105*/  49308u,49673u
};

/*
// Used to generate DaysSinceEpoch[]
void mktab(void)
{
  unsigned y, d = 0;
  for (y = 1970; y <= 2106; d += 365 + __isleap(y), y++)
    printf ("%5uu,", d),
    (y%8) ? 0 : printf ("\n  /%c%u%c/  ", '*', y+1, '*');
  printf ("\n");
}
*/

struct tm* __breaktime(time_t* t)
{
  static struct tm tm;
  time_t trem = *t;
  unsigned daysPassed, lidx, ridx, idx, leap;

  if (trem == (time_t)-1)
    return NULL;

  daysPassed = trem / SECONDS_PER_DAY;
  trem -= daysPassed * SECONDS_PER_DAY;

  tm.tm_wday = (daysPassed + 4) % 7;

  tm.tm_hour = trem / SECONDS_PER_HOUR;
  trem -= tm.tm_hour * (time_t)SECONDS_PER_HOUR;

  tm.tm_min = trem / SECONDS_PER_MINUTE;
  trem -= tm.tm_min * SECONDS_PER_MINUTE;

  tm.tm_sec = trem;

  // Convert integral amount of days since 1970-Jan-01 to the year:
  if (daysPassed >= 
      DaysSinceEpoch[sizeof(DaysSinceEpoch)/sizeof(DaysSinceEpoch[0])-1])
    return NULL;
  for (lidx=0, ridx=sizeof(DaysSinceEpoch)/sizeof(DaysSinceEpoch[0])-1;;)
  {
    idx = (lidx + ridx) >> 1;
    if (daysPassed < DaysSinceEpoch[idx])
      ridx = idx;
    else if (daysPassed >= DaysSinceEpoch[idx+1])
      lidx = idx;
    else
      break;
  }
  tm.tm_year = 70 + idx;
  leap = __isleap(1970 + idx);
  daysPassed -= DaysSinceEpoch[idx];

  tm.tm_yday = daysPassed;

  // Convert integral amount of days since Jan-01 to the month:
  for (lidx=0, ridx=sizeof(__DaysSinceJan1st[0])/sizeof(__DaysSinceJan1st[0][0])-1;;)
  {
    idx = (lidx + ridx) >> 1;
    if (daysPassed < __DaysSinceJan1st[leap][idx])
      ridx = idx;
    else if (daysPassed >= __DaysSinceJan1st[leap][idx+1])
      lidx = idx;
    else
      break;
  }
  tm.tm_mon = idx;
  daysPassed -= __DaysSinceJan1st[leap][idx];

  tm.tm_mday = 1 + daysPassed;

  tm.tm_isdst = 0;  // no daylight saving time

  return &tm;
}
#endif
