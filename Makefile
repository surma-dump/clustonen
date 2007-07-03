#compiles everything
all: library-target server-target modules-target tests-target

#compiles just the library
library-target: 
	make lib

#compiles just the server
server-target:
	make server

modules-target:
	@cd modules; \
	sh pseudo-make

#compiles test programs
tests-target:
	make tests

#deletes all modules, librarys, executables and backup files
clean:
	-@rm *~ 2> /dev/null
	-@cd include; \
	rm *~ 2> /dev/null
	-@cd modules; \
	rm *~ 2> /dev/null; \
	sh pseudo-make clean
	-@cd lib; \
	make clean
	-@cd server; \
	make clean
	-@cd tests; \
	make clean

#like clean, but leaves the library and executables 
post-clean:
	-@rm *~ 2> /dev/null
	-@cd include; \
	rm *~ 2> /dev/null
	-@cd modules; \
	rm *~ 2> /dev/null; \
	sh ./pseudo-make post-clean
	-@cd lib; \
	make post-clean
	-@cd server; \
	make post-clean
	-@cd modules; \
	make post-clean
	-@cd tests; \
	make post-clean
run:
	@cd server; \
	make run

me:
	@echo -n "do "
a:
	@echo -n "it "
sandwich:
	@echo yourself!

