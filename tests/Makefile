MAINVERSION=0
RELEASEVERSION=0
PATCHVERSION=1
NAME=tests

CC := gcc
CXX := g++
LD := g++

CCFLAGS := -Wall
CXXFLAGS := -Wall -pedantic
LDFLAGS := 

CPPS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPPS) )
LIBS := stdc++ clustonen c dl

LIBPATHS := ../lib 
INCLUDES := ../include

PWD := $(shell pwd)

all: objects linking
objects:
	$(CXX) $(CXXFLAGS) -c test.cpp $(addprefix -I, $(INCLUDES))
	$(CXX) $(CXXFLAGS) -c test2.cpp $(addprefix -I, $(INCLUDES))  
linking:
	$(LD) $(LDFLAGS) test.o $(ADDITIONALOBJS) -o test $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) )
	$(LD) $(LDFLAGS) test2.o $(ADDITIONALOBJS) -o test2 $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) )  

clean:
	-@rm *.o 2> /dev/null
	-@rm $(NAME) 2> /dev/null
	-@rm *~ 2> /dev/null

post-clean:
	-@rm *.o 2> /dev/null
	-@rm *~ 2> /dev/null

run:

	@LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PWD)/../lib:$(PWD)/../modules/testmodule ./tests