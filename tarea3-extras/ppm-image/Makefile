################################################
# Cambiar nombre del ejecutable si es necesario
TARGET=./example

#######DEFINICIONES PARA C#########
CC=cc

#######DEFINICIONES PARA C++#########
CXX=g++
CXXFLAGS=-std=c++17 -Wall -O3

#######DEFINICIONES PARA MPI#########
MPICC=mpicc
MPICCFLAGS=-std=c++17 -Wall -O3 

RM=rm -f

INCLUDES=
LDFLAGS=
LDLIBS=

SRCS=$(wildcard *.cc)

OBJS=$(patsubst %.cc,%.o,$(SRCS))


all: $(TARGET)

$(TARGET): $(OBJS)
	$(MPICC) -o $@ $^ $(MPICCFLAGS) $(LDLIBS) $(LDFLAGS) 

%.o: %.cc
	$(MPICC) -c -o $@ $< $(MPICCFLAGS) $(INCLUDES)

clean:
	$(RM) $(OBJS)
	$(RM) *~

distclean: clean
	$(RM) $(TARGET)

.PHONY: all clean distclean
	

