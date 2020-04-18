This is Comp322 Lab4

Dining Philosophers problem

Part1 - this program has N philosophers eating from the table. Here I have used counting semaphore with value initialized to N-1 which allows only N-1 philosophers to pick upthe chopsticks. 
It can be compiled using make part1 (included in makefile).
N- argument passed in command line


dining-p -
In this program I have tried to avoid the circular wait deadlock by separating the left handed and right handed philosophers. first N-1 philosophers are left handed and last philosopher is right handed which prevents the deadlock.

Makefile-
It contains execuatables - part1, dining-p , launch-philosopher and clean
command make- will run executables part1, dining-p and launch-philosopher
command make clean- will delete all the files exceppt .c files

launch-philosopher.sh- script that runs ./dining-p $@
