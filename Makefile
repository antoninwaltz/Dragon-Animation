CC=clang++-3.6
FLAGS=-Wall -g

INCLUDE=-I.

TARGET=IN55.exe

SOURCES=main.cpp\
		model.cpp

OBJECTS=$(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS) *.h
	@echo "Builing the whole project"
	$(CC) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	@echo "Compiling .cpp files"
	$(CC) -c $(INCLUDE) $(FLAGS) $< -o $@

clean:
	@echo "Cleaning"
	rm -rf *.o

