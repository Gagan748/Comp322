
EXEC=part1 dining-p launch-philosophers
SRC1=part1.c
SRC2=dining-p.c

all:$(EXEC)

part1: $(SRC1)
	gcc -c part1.c -lpthread -lrt -Wall -Wextra
	gcc -o part1 part1.o -lpthread -lrt

dining-p: $(SRC2)
	gcc -c dining-p.c -lpthread -lrt -Wall -Wextra
	gcc -o dining-p dining-p.o -lpthread -lrt
launch-philosophers:
	chmod +x launch-philosophers.sh
clean:
	rm dining-p dining-p.o part1 part1.o 
