# Definitions
EXEC = main.out
IMGUI_DIR = vendor/imgui
CC = g++
CFLAGS = -Wall -Werror -Ivendor -Ivendor/imgui
GLFLAGS = -ldl -lglfw3 -lGL
DEL = rm


all: $(EXEC)


# creating object files from C source files

main.o: main.cpp index_buffer.h vertex_array.h shader.h $(IMGUI_DIR)/imgui.h $(IMGUI_DIR)/imgui_impl_glfw.h $(IMGUI_DIR)/imgui_impl_opengl3.h
	$(CC) -c $(CFLAGS) $< -o $@

glad.o: glad.c
	$(CC) -c $(CFLAGS) $< -o $@

renderer.o: renderer.cpp renderer.h vertex_buffer.h index_buffer.h vertex_array.h
	$(CC) -c $(CFLAGS) $< -o $@

vertex_buffer.o: vertex_buffer.cpp vertex_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

index_buffer.o: index_buffer.cpp index_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

vertex_array.o: vertex_array.cpp vertex_array.h vertex_buffer_layout.h
	$(CC) -c $(CFLAGS) $< -o $@

shader.o: shader.cpp shader.h
	$(CC) -c $(CFLAGS) $< -o $@

# imgui stuff

imgui.o: $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui.h
	$(CC) -c $(CFLAGS) $< -o $@

imgui_impl_glfw.o: $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_glfw.h
	$(CC) -c $(CFLAGS) $< -o $@

imgui_impl_opengl3.o: $(IMGUI_DIR)/imgui_impl_opengl3.cpp $(IMGUI_DIR)/imgui_impl_opengl3.h
	$(CC) -c $(CFLAGS) $< -o $@

imgui_draw.o: $(IMGUI_DIR)/imgui_draw.cpp
	$(CC) -c $(CFLAGS) $< -o $@

imgui_tables.o: $(IMGUI_DIR)/imgui_tables.cpp
	$(CC) -c $(CFLAGS) $< -o $@

imgui_widgets.o: $(IMGUI_DIR)/imgui_widgets.cpp
	$(CC) -c $(CFLAGS) $< -o $@


# creating output file from object files
$(EXEC): main.o glad.o renderer.o vertex_buffer.o index_buffer.o vertex_array.o shader.o imgui.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_draw.o imgui_tables.o imgui_widgets.o
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
