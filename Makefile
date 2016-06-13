CC=g++
FLAGS=-Wall -g

INCLUDE=-I.
LIBS=-lGL -lglut -lGLU -lGLEW -lassimp

TARGET=IN55.exe

SOURCES=main.cpp \
		scene.cpp \
		camera.cpp \
		bone.cpp \
		mesh.cpp \
		utils.cpp

OBJECTS=$(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS) *.h
	@echo "Builing the whole project"
	$(CC) $(OBJECTS) $(LIBS) -o $(TARGET)

%.o: %.cpp
	@echo "Compiling .cpp files"
	$(CC) -c $(INCLUDE) $(FLAGS) $< -o $@

clean:
	@echo "Cleaning"
	rm -rf *.o $(TARGET)

