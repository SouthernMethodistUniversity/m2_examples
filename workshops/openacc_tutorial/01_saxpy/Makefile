CC=pgcc
CFLAGS=-acc

saxpy_openacc : saxpy_openacc.c
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf saxpy_openacc

