CC = gcc
CFLAGS = -I. -lm
OBJ = cpu.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cpu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
