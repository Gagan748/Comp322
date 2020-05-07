Lab6: Wack a mole!

mole.c- a program that outputs to logfile

spiritd.c- creates daemon(But as I was unable to access the root directory in my 
virtualbox , so I have commented the chdir("/") part and my log file is getting created in pwd where my program runs.
It gives out PID of running process. When we send kill -USR1 and -USR2 commands few times, it generates a random number which pops either child 1 or child 2 , printing in lab6.log.
