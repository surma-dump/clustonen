MAINVERSION=0
RELEASEVERSION=0
PATCHVERSION=1
NAME=clustonen-server

CC := gcc
CXX := g++
LD := g++

CCFLAGS := -Werror
CXXFLAGS := -Werror 
LDFLAGS := 

CPPS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPPS) )
LIBS := argtable2 stdc++ clustonen c dl

LIBPATHS := ../lib 
INCLUDES := ../include

PWD := $(shell pwd)

all: objects linking
objects:
	$(CXX) $(CXXFLAGS) -c $(CPPS) $(addprefix -I, $(INCLUDES)) 
linking:
	$(LD) $(LDFLAGS) $(OBJS) $(ADDITIONALOBJS) -o $(NAME) $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

clean:
	-@rm *.o 2> /dev/null
	-@rm $(NAME) 2> /dev/null
	-@rm *~ 2> /dev/null

post-clean:
	-@rm *.o 2> /dev/null
	-@rm *~ 2> /dev/null

run:
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PWD)/../lib ./clustonen-server $(PARAM)