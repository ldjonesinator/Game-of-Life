EXEC = main.out

GLM_DIR = vendor/glm
IMGUI_DIR = vendor/imgui
TEST_DIR = tests

CODEDIRS = . $(IMGUI_DIR) $(TEST_DIR)
INCDIRS = . $(IMGUI_DIR) $(TEST_DIR)

CC = g++
OPT = -O0
# generate files that encode make rules for the .h dependencies
DEPFLAGS = -MP -MD
CFLAGS = -Wall -Werror -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)
GLFLAGS = -ldl -lglfw3 -lGL

CPPFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.cpp))
CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))

OBJECTS = $(patsubst %.cpp, %.o, $(CPPFILES)) $(patsubst %.c, %.o, $(CFILES))
DEPFILES = $(patsubst %.cpp, %.d, $(CPPFILES)) $(patsubst %.c, %.d, $(CFILES))

DEL = rm


all: $(EXEC)


$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(GLFLAGS) -lm

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	-$(DEL) $(EXEC) $(OBJECTS) $(DEPFILES)


# setting the run target
run: all
	./$(EXEC)

# compiling and then running the program
.PHONY: all run
