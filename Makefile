# compiles everything
all: library-target server-target

# compiles just the library
library-target: 
	make -C lib

# compiles just the server
server-target:
	make -C server

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

# delete all backupfiles
backup-clean:
	find . -name "*~" -exec rm {} \;

me:
	@echo -n "do "
a:
	@echo -n "it "
sandwich:
	@echo yourself!

