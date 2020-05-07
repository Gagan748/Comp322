EXEC=matrix_gen matrix_add 

all:$(EXEC)

matrix_gen:
	gcc -c matrix_gen.c -Wall -Wextra
	gcc -o matrix_gen matrix_gen.o -Wall -Wextra

matrix_add:
	gcc -c matrix_add.c -Wall -Wextra -lrt
	gcc -o matrix_add matrix_add.o -Wall -Wextra -lrt
clean:
	rm matrix_gen matrix_gen.o matrix_add matrix_add.o matrix_file1.size matrix_file2.size

