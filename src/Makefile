# Definitions
EXEC = main.out
IMGUI_DIR = vendor/imgui
OBJ_DIR = object_files
CC = g++
CFLAGS = -Wall -Werror -Ivendor -Ivendor/imgui
GLFLAGS = -ldl -lglfw3 -lGL
DEL = rm


all: $(EXEC)


# creating object files from C source files

$(OBJ_DIR)/main.o: main.cpp index_buffer.h vertex_array.h shader.h \
		$(IMGUI_DIR)/imgui.h $(IMGUI_DIR)/imgui_impl_glfw.h $(IMGUI_DIR)/imgui_impl_opengl3.h \
		tests/test_clear_colour.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/glad.o: glad.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/renderer.o: renderer.cpp renderer.h vertex_buffer.h index_buffer.h vertex_array.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/vertex_buffer.o: vertex_buffer.cpp vertex_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/index_buffer.o: index_buffer.cpp index_buffer.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/vertex_array.o: vertex_array.cpp vertex_array.h vertex_buffer_layout.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/shader.o: shader.cpp shader.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/test.o: tests/test.cpp tests/test.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/test_clear_colour.o: tests/test_clear_colour.cpp tests/test_clear_colour.h tests/test.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/test_square.o: tests/test_square.cpp tests/test_square.h tests/test.h renderer.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/test_square_batch.o: tests/test_square_batch.cpp tests/test_square_batch.h tests/test.h renderer.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/batch_render.o: batch_render.cpp batch_render.h vertex_buffer_layout.h
	$(CC) -c $(CFLAGS) $< -o $@

# imgui stuff

$(OBJ_DIR)/imgui.o: $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/imgui_impl_glfw.o: $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_glfw.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/imgui_impl_opengl3.o: $(IMGUI_DIR)/imgui_impl_opengl3.cpp $(IMGUI_DIR)/imgui_impl_opengl3.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/imgui_draw.o: $(IMGUI_DIR)/imgui_draw.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/imgui_tables.o: $(IMGUI_DIR)/imgui_tables.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/imgui_widgets.o: $(IMGUI_DIR)/imgui_widgets.cpp
	$(CC) -c $(CFLAGS) $< -o $@


# creating output file from object files
$(EXEC): $(OBJ_DIR)/main.o $(OBJ_DIR)/glad.o $(OBJ_DIR)/renderer.o $(OBJ_DIR)/vertex_buffer.o $(OBJ_DIR)/index_buffer.o $(OBJ_DIR)/vertex_array.o $(OBJ_DIR)/shader.o \
		$(OBJ_DIR)/imgui.o $(OBJ_DIR)/imgui_impl_glfw.o $(OBJ_DIR)/imgui_impl_opengl3.o $(OBJ_DIR)/imgui_draw.o $(OBJ_DIR)/imgui_tables.o $(OBJ_DIR)/imgui_widgets.o \
		$(OBJ_DIR)/test.o $(OBJ_DIR)/test_clear_colour.o $(OBJ_DIR)/test_square.o $(OBJ_DIR)/test_square_batch.o $(OBJ_DIR)/batch_render.o
	$(CC) $(CFLAGS) $^ $(GLFLAGS) -o $@ -lm

# setting the run target
run: all
	./$(EXEC)


# cleaning the object and output file from directory
.PHONY: clean
clean:
	-$(DEL) $(OBJ_DIR)/*.o *.out

# compiling and then running the program
.PHONY: all run
