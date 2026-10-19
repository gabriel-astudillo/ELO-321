CC=gcc
CXX=g++
RM=rm -f

TARGET=example


INCLUDES=-I./include -I.
LDFLAGS=-L/usr/local/lib 
LDLIBS=

CXXFLAGS=-std=c++17 -Wall -O2

SRCS=$(wildcard *.cc)

OBJS=$(patsubst %.cc,%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) 

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

clean:
	@$(RM) $(OBJS)
	@$(RM) *~ core

distclean: clean
	@$(RM) $(TARGET)

.PHONY: all clean distclean
	