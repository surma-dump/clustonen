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
NAME=libclustonen.so

CC := gcc
CXX := g++
LD := g++
LN := ln

CCFLAGS := -Werror
CXXFLAGS := -Werror -fPIC
LDFLAGS := --shared

CPPS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(CPPS) )
LIBS := argtable2 c pthread

LIBPATHS :=

INCLUDES := ../include

all: objects linking symlinks
objects:
	$(CXX) $(CXXFLAGS) -c $(CPPS) $(addprefix -I, $(INCLUDES) ) 
linking:
	$(LD) $(LDFLAGS) $(OBJS) -o $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(addprefix -L, $(LIBPATHS) ) $(addprefix -l, $(LIBS) ) 

symlinks:
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME).$(MAINVERSION).$(RELEASEVERSION)
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME).$(MAINVERSION)
	-@ln -fs $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) $(NAME)

clean: binary-clean backup-clean object-clean

binary-clean:
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION) 2> /dev/null
	-@rm $(NAME) 2> /dev/null

backup-clean:
	find . -name "*~" -exec rm {} \;

object-clean:
	find . -name "*.o" -exec rm {} \;