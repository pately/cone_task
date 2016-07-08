CC=g++
CFLAGS=-Wall -O0 -g3 -std=c++11 
LDFLAGS=
LIBS=

CFLAGS+=$(shell pkg-config --cflags $(LIBS))
LDFLAGS+=$(shell pkg-config --libs $(LIBS))
SOURCES=$(wildcard *.cc) $(wildcard ../*.cc)
HEADERS=$(wildcard *.h) $(wildcard ../*.h) $(wildcard *.inc) $(wildcard ../*.inc)
RESULT=$(notdir $(CURDIR))
OBJS=$(SOURCES:.cc=.o)

SOURCES+= 
OBJS+= 

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(RESULT): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(RESULT)
	./$(RESULT)

clean:
	rm $(RESULT) $(OBJS) $(COVLOGS)

.PHONY: all clean
