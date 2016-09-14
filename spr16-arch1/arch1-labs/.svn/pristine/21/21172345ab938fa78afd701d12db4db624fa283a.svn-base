#include <stdio.h>
#include "calendar_utils.h"

int main(void)
{
  int year = 2004;
  int month = 15;
  int day = 31;

  //this should produce -1 for the month
  int yearday = day_of_year(year, month, day);
  printf("Date: %d-%d-%d\nYearday from date: %d\n", month, day, year, yearday);
  
  month_day(year, &yearday, &month, &day);
  printf("Date from yearday: %d-%d-%d\n", month, day, year);

  
  //this should produce -1 for the day
  year = 2019, month = 2, day = 0, yearday = day_of_year(year, month, day);
  printf("Date: %d-%d-%d\nYearday from date: %d\n", month, day, year, yearday);
  
  month_day(year, &yearday, &month, &day);
  printf("Date from yearday: %d-%d-%d\n", month, day, year);

  
  //this should produce no erroneous result
  year = 1316, month = 12, day = 31, yearday = day_of_year(year, month, day);
  printf("Date: %d-%d-%d\nYearday from date: %d\n", month, day, year, yearday);
  
  month_day(year, &yearday, &month, &day);
  printf("Date from yearday: %d-%d-%d\n", month, day, year);
  return 0;
}
