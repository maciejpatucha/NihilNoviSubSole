CC=clang
CFLAGS=-g -c -Wall
LDFLAGS=
SOURCES=main.c options_parsing.c logging.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=DMServer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
.PHONY: clean run

clean: 
	-rm -rf *.o $(EXECUTABLE)

run:
	./$(EXECUTABLE) --no-fork

