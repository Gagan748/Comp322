EXEC= mole spiritd 

all:$(EXEC)

mole:
	gcc -c mole.c -Wall -Wextra -lrt 
	gcc -o mole mole.o -lpthread -lrt
spiritd:
	gcc -c spiritd.c -Wall -Wextra
	gcc -o spiritd spiritd.o -Wall -Wextra
clean:
	rm mole mole.o spiritd spiritd.o
