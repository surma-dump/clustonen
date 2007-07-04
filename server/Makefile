MAINVERSION=0
RELEASEVERSION=0
PATCHVERSION=1
NAME=clustonenserver

CC := gcc
CXX := g++
LD := g++

CCFLAGS := -Wall
CXXFLAGS := -Wall
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

clean: binary-clean backup-clean object-clean

binary-clean:
	-@rm $(NAME) 2> /dev/null


backup-clean:
	find . -name "*~" -exec rm {} \;


object-clean:
	find . -name "*.o" -exec rm {} \;

run:
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PWD)/../lib ./$(NAME) $(PARAM)