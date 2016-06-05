CC=g++
FLAGS=-Wall -g

INCLUDE=-I.
LIBS=-lassimp

TARGET=IN55.exe

SOURCES=main.cpp\
		scene.cpp

OBJECTS=$(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS) *.h
	@echo "Builing the whole project"
	$(CC) $(OBJECTS) -lGL -lglut -lGLU $(LIBS) -o $(TARGET)

%.o: %.cpp
	@echo "Compiling .cpp files"
	$(CC) -c $(INCLUDE) $(FLAGS) $< -o $@

clean:
	@echo "Cleaning"
	rm -rf *.o $(TARGET)

