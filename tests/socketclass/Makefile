MAINVERSION=0
RELEASEVERSION=0
PATCHVERSION=1
NAME=client server

CC := gcc
CXX := g++
LD := g++

CCFLAGS := -Wall
CXXFLAGS := -Wall
LDFLAGS := 

CPPS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPPS) )
LIBS := stdc++ clustonen c dl

LIBPATHS := ../../lib 
INCLUDES := ../../include

PWD := $(shell pwd)

all: objects server client
objects:
	$(CXX) $(CXXFLAGS) -c $(CPPS) $(addprefix -I, $(INCLUDES)) 
server:
	$(LD) $(LDFLAGS) server.o $(ADDITIONALOBJS) -o server $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

client:
	$(LD) $(LDFLAGS) client.o $(ADDITIONALOBJS) -o client $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

clean: binary-clean backup-clean object-clean

binary-clean:
	-@rm client server 2> /dev/null

backup-clean:
	find . -name "*~" -exec rm {} \;

object-clean:
	find . -name "*.o" -exec rm {} \;

run-client:
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PWD)/../../lib ./client $(PARAM)

run-server:
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PWD)/../../lib ./server $(PARAM)