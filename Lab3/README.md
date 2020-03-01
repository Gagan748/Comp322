Lab3 project is about signals.

In this project I wrote a command line tool to catch any signal and 
print the signal and the time when it is caught on the console. 
After catching the signals whose names are given as command line arguments,
the program terminates after catching 3 SIGTERM signals. 
At the end it prints the total number of signals caught which is counted in the signal handler whenever there is a signal.
