
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

.PHONY: tests doc

# compiles everything
all: library-target server-target client-target

# generates the documentation using doxygen
# requires graphviz
doc:
	doxygen

# compiles just the library
library-target: 
	make -C lib

# compiles just the server
server-target: modules
	make -C server

# compiles just the client
client-target:
	make -C client

# compiles the testsuites
tests: library-target
	make -C ./tests
	
modules: library-target
	make -C ./modules

# deletes all modules, librarys, executables and backup files
clean: object-clean binary-clean backup-clean

# delete all object files
# FIXME: add modules and test
object-clean:
	find . -name "*.o" -exec rm {} \;

# just delete binaries
binary-clean:
	make -C lib binary-clean
	make -C server binary-clean
	make -C tests binary-clean
	make -C modules binary-clean

# delete all backupfiles
backup-clean:
	find . -name "*~" -exec rm {} \;

me:
	@echo -n "do "
a:
	@echo -n "it "
sandwich:
	@echo yourself!

