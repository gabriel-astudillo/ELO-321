CC=gcc
CXX=g++
RM=rm -f

TARGET=./example

CXXFLAGS=-std=c++17 -Wall -O3 

#######DEFINICIONES PARA MPI#########
MPICXX=$(HOME)/mpi/bin/mpicxx 

INCLUDES=
LDFLAGS=
LDLIBS=

CXX=$(MPICXX)

SRCS=$(wildcard *.cc)

OBJS=$(patsubst %.cc,%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS) $(LDFLAGS) 

%.o: %.cc
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

clean:
	$(RM) $(OBJS)
	$(RM) *~

distclean: clean
	$(RM) $(TARGET)

.PHONY: all clean distclean
	

