CC=g++
CFLAGS=-c -std=c++14 -Werror -pedantic -Wall -Wextra -O2
LDFLAGS=
LIBS=-lm
SOURCES=suffix_tree.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lab5

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -frd $(OBJECTS) $(EXECUTABLE)
