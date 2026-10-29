CC=gcc
CXX=mpicc
RM=rm -f

TARGET=./example

CXXFLAGS=-std=c++17 -Wall -O3 

#######DEFINICIONES PARA MPI#########
MPICC=mpicc 

INCLUDES=
LDFLAGS=
LDLIBS=

CXX=$(MPICC)

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
	

