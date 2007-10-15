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

MAINVERSION=0
RELEASEVERSION=0
PATCHVERSION=1
NAME=libclustonen_testmodule.so

CC := gcc
CXX := g++
LD := g++
LN := ln

CCFLAGS := -Werror
CXXFLAGS := -Werror -fPIC
LDFLAGS := --shared
LIBS := stdc++ c 

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

LIBPATHS := 

INCLUDES := ../../include

all: $(OBJS) linking symlinks

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< $(addprefix -I, $(INCLUDES) ) -o $@

linking:
	$(LD) $(LDFLAGS) $(OBJS) -o $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

symlinks:
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME).$(MAINVERSION).$(RELEASEVERSION)
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME).$(MAINVERSION)
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME)

clean:
	-@rm *.o 2> /dev/null
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION) 2> /dev/null
	-@rm $(NAME) 2> /dev/null
	-@rm *~ 2> /dev/null
	
binary-clean:
	-@rm $(NAME) 2> /dev/null
	-@rm *.so.* 2> /dev/null

post-clean:
	-@rm *.o 2 >/dev/null
	-@rm *~ 2> /dev/null