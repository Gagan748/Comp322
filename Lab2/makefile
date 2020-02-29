EXECUTABLES=launch tube
SRC1=launch.c
SRC2=tube.c

ALL: $(EXECUTABLES)

launch: $(SRC1)
	gcc -c launch.c -Wall -Wextra
	gcc -o launch launch.o 
tube: $(SRC2)
	gcc -c tube.c -Wall -Wextra
	gcc -o tube tube.o
clean:
	-rm launch.o tube.o launch tube
