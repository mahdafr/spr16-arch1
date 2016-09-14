//Exercise 1-15: Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.

#include <stdio.h>

void toCelsius(int i) {
  double fahr = i + 0.00;
  double cels = 5*(fahr-32)/9; //formula from fahrenheit to celsius
  printf("Fahrenheit: %.2f, Celsius: %.2f\n",fahr,cels); //output
}

void main(void) {
  for ( int i=0 ; i<=300 ; i+=50 ) { //do every 50-th measurement of F-C conversion
   toCelsius(i); //call to method: solve and print
  }
}
