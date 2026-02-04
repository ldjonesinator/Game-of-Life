# Definitions
CC = g++
CFLAGS = -Wall -Werror
GLFLAGS = -ldl -lglfw
EXEC = main.out
DEL = rm


all: $(EXEC)

# creating object files from C source files

main.o: main.cpp glad.c index_buffer.h vertex_array.h shader.h
	$(CC) -c $(CFLAGS) $< -o $@

glad.o: glad.c
	$(CC) -c $(CFLAGS) $< -o $@

index_buffer.o: index_buffer.cpp index_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

vertex_buffer.o: vertex_buffer.cpp vertex_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

vertex_array.o: vertex_array.cpp vertex_array.h vertex_buffer_layout.h
	$(CC) -c $(CFLAGS) $< -o $@

shader.o: shader.cpp shader.h
	$(CC) -c $(CFLAGS) $< -o $@


# creating output file from object files
$(EXEC): main.o glad.o index_buffer.o vertex_buffer.o vertex_array.o shader.o
	$(CC) $(CFLAGS) $^ $(GLFLAGS) -o $@ -lm

# setting the run target
run: all
	./$(EXEC)


# cleaning the object and output file from directory
.PHONY: clean
clean:
	-$(DEL) *.o *.out

# compiling and then running the program
.PHONY: all run
