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
LIBS := argtable2 c 

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

clean:
	-@rm *.o 2> /dev/null
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION).$(PATCHVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION).$(RELEASEVERSION) 2> /dev/null
	-@rm $(NAME).$(MAINVERSION) 2> /dev/null
	-@rm $(NAME) 2> /dev/null
	-@rm *~ 2> /dev/null

post-clean:
	-@rm *.o 2 >/dev/null
	-@rm *~ 2> /dev/null
