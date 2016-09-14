# !/bin/bash
# This script clears the terminal, displays a greeting, asks for the user's name, displays the user's name, gives a list of connected users, illustrates the setting of a local shell variable and gives the date and time.

echo
echo This is the beginning of the script
echo
# The echo command displays on the terminal the text following the command

sleep 3
# sleeps for 3 seconds

echo Lets clear the screen
echo

sleep 3

clear
# This command clears the terminal window

sleep 3

echo "Hello World!"
echo
sleep 3

echo "Please enter your first name"
read NAME
# the read command will read input from the terminal.
# NAME is defined now as a variable. we couldjust have easily used another variable, for example:
echo
sleep 3

echo "Please enter your last name"
read LN
echo
sleep 3

echo "Hi $NAME $LN!"
# the dollar sign is used to get the content of the variable
echo
sleep 3

echo "Now I will display a list of connected users:"
echo
sleep 3

w
#command that displays who is logged on and what they are doing
echo
sleep 3

echo -n "The current time and date are: "
# the -n means echo should not print the newline character
sleep 3

date
# the date command prints the date and time
echo
sleep 3

echo "This is the end of the script"
echo
sleep 3

echo "Returning to the command prompt."
echo
