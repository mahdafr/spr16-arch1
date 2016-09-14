//Exercise 3-2: Write a function excape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.

#include <stdio.h>

void escapeF(char s[],char t[]) {
  //we will traverse the the string t with i and s with j, as j!=i always
  int i, j=0;
  for ( i=0 ; t[i]!='\0' ; i++ ) {
    //printf("%d",j); //debugging
    switch ( t[i] ) {
    case '\n':
      //if it is the new line character
      s[j] = '\\';
      s[++j] = 'n';
      break;
    case '\t':
      //if it is the horizontal tab character
      s[j] = '\\';
      s[++j] = 't';
      break;
    case '\a':
      //if it is the alert(bell) character
      s[j] = '\\';
      s[++j] = 'a';
      break;
    case '\b':
      //if it is the backspace character
      s[j] = '\\';
      s[++j] = 'b';
      break;
    case '\f':
      //if it is the formfeed character
      s[j] = '\\';
      s[++j] = 'f';
      break;
    case '\r':
      //if it is the carriage return character
      s[j] = '\\';
      s[++j] = 'r';
      break;
    case '\v':
      //if it is the vertical tab character
      s[j] = '\\';
      s[++j] = 'v';
      break;
    case '\\':
      //if it is the backslash character
      s[j] = '\\';
      j++;
      break;
    case '\?':
      //if it is the question mark character
      s[j] = '\\';
      s[++j] = '\?';
      break;
    case '\'':
      //if it is the single quote character
      s[j] = '\\';
      s[++j] = '\'';
      break;
    case '\"':
      //if it is quotation mark character (double quote)
      s[j] = '\\';
      s[++j] = '\"';
      break;
    default:
      //if it is not an escape sequence
      s[j] = t[i];
      j++;
      break;
    } //end switch
    j++; //move to next character
  } //end for: traversing s
  s[j] = s[i];
}

void escapeR(char s[],char t[]) {
  //again, traversing t with i and s with j as j!=i always
  int i, j=0;
  for ( i=0 ; t[i]!='\0' ; i++ ) {
    switch ( t[i] ) {
    case '\\':
      //if the character will be an escape sequence
      switch ( t[++i] ) {
      case 'n':
	//if it is a newline
	s[j] = '\n';
	break;
      case 't':
	//if it is a horizontal tab
	s[j] = '\t';
	break;
      case '\\':
	//if it is a backslash
	s[j] = '\\';
	break;
      case '\?':
	//if it is a question mark
	s[j] = '\?';
	break;
      case '\'':
	//if it is a single quote
	s[j] = '\'';
	break;
      case '\"':
	//if it is a quotation mark
	s[j] = '\"';
	break;
      case 'v':
	//if it is a vertical tab
	s[j] = '\v';
	break;
      case 'r':
	//if it is a carriage return
	s[j] = '\r';
	break;
      case 'f':
	//if it is a formfeed
	s[j] = '\f';
	break;
      case 'b':
	//if it is a backspace
	s[j] = '\b';
	break;
      case 'a':
	//if it is an alert(bell) character
	s[j] = '\a';
	break;
      } //end switch: escape sequence
      break;
    default:
      //it is not an escape sequence, so copy directly
      s[j] = t[i];
      break;
    } //end switch
    j++; //move to next character
  } //end for: traversing t
  s[j] = s[i];
}

int main(void) {
  char s[100];
  char t[100];
  int c; int i=0;
  while ( (c=getchar())!=EOF )
    t[i++] = c;

  //testing t
  printf("Escape forward, s=");
  escapeF(s,t);
  for ( i=0 ; s[i]!='\0' ; i++ )
    putchar(s[i]);

  //resetting s to convert again
  i=0;
  while ( s[i]!='\0' ) {
    t[i] = s[i];
    s[i++] = '\0';
  }

  //testing with the formed s
  printf("\nEscape reverse, s=");
  escapeR(s,t);
  for ( i=0 ; s[i]!='\0' ; i++ )
    putchar(s[i]);

  printf("\n");
  return 0;
}
