CC=gcc
CFLAGS=-c -lc -Wall -g
LDFLAGS=
SOURCES= main.c function.c menu.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=output

all: $(SOURCES) $(EXECUTABLE)

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
