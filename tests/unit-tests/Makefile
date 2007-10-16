#/**
# * Copyright (C) 2007  Andi Drebes <hackbert@drebesium.org>
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

CC := gcc
CXX := g++
LD := g++
NAME=testsuite

CCFLAGS := -Wall -pthread -pedantic
CXXFLAGS := -Wall -pthread -pedantic
LDFLAGS := 
LIBS := cppunit stdc++ clustonen c dl

ifdef DEBUG
	CCFLAGS := $(CCFLAGS) -g
	CXXFLAGS := $(CXXFLAGS) -g
endif

ifdef PROFILING
	CCFLAGS := $(CCFLAGS) -fprofile-arcs -ftest-coverage
	CXXFLAGS := $(CXXFLAGS) -fprofile-arcs -ftest-coverage
	LIBS := $(LIBS) gcov
endif

CPPS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPPS) )

LIBPATHS := ../../lib 
INCLUDES := ../../include

PWD := $(shell pwd)

all: $(OBJS) executable
	@echo 
	@echo 
	@echo "**********************************************************"
	@echo "* I AM NOW GOING TO RUN THE TEST-SUITES FOR UNIT-TESTING *"
	@echo "**********************************************************"
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../lib ./$(NAME)
	@echo 
	@echo 
	@echo 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< $(addprefix -I, $(INCLUDES) ) -o $@

executable:
	$(LD) $(LDFLAGS) $(OBJS) $(ADDITIONALOBJS) -o $(NAME) $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

clean: binary-clean backup-clean object-clean

binary-clean:
	-@rm $(NAME) 2> /dev/null

backup-clean:
	find . -name "*~" -exec rm {} \;

object-clean:
	find . -name "*.o" -exec rm {} \;

run:
	@LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PWD)/../../lib ./$(NAME) $(PARAM)