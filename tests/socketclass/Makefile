#/**
# * Copyright (C) 2007  Alexander Surma <crock@drebesium.org>
# * 
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License version 2 as published
# * by the Free Software Foundation.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program; if not, write to the Free Software
# * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# */

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

all: $(OBJS) server client

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< $(addprefix -I, $(INCLUDES) ) -o $@

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