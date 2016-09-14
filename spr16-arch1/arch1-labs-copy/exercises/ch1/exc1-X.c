//Exercise 1-X: Write a program that performs one of the following temperature conversions:
//   - converts from Celsius to Rankine: the formula is R = (C+273.15)*9/5
//   - converts from Rankine to Celsius: the formula is C = (R*5/9)-273.15
//   - converts from Fahrenheit to Kelvin: the formula is K = (F+459.67)*5/9
//   - converts from Kelvin to Fahrenheit: the formula is F = (K*9/5)-459.67
//   You should print out a short list of conversions.

#include <stdio.h>

void celsiusToRankine(int i) {
  double cels = i + 0.00;
  double ran = (cels+273.15)*9/5; //formula: convert Rankine to Celsius
  printf("Celsius: %.2f, Rankine: %.2f\n",cels,ran); //output
}

int main(void) {
  for ( int i=0 ; i<=300 ; i+=50 ) {
    celsiusToRankine(i); //call to method to calculate this degree in Rankine
  }
  return 0;
}
