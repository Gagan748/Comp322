Lab7: Asynchronous Elephant

matrix_gen - program that generates matrix of size given in argv[1]
matrix_add- this adds scalar to matrix and save it to matrix_file2.size
it reads the input from file matrix_file1.size using aio_read using redirection operator and writes to another file matrix_file2.size using aio_write after performing matrix addition.

make matrix_gen - compiles program matrix_gen
./matrix_gen size > matrix_file1.size - generates a matrix of size= size*size in file matrix_file1.size
make matrix_add - compiles program matrix_add
./matrix_add size blocks < matrix_file1.size > matrix_file2.size - generates a new matrix with adding scalar value in matrix_file2.size to matrix stored in matrix_file1.size
