CC = gcc
# -g : allows use of GNU Debugger
# -Wall : show all warnings
FLAGS = -g -Wall
LIBS = # None yet...
COMMON = common.c
SERVER = server.o
CLIENT = client.o

all: $(SERVER) $(CLIENT)

%.o: %.c $(COMMON)
	@# Call the compiler with source & output arguments
	$(CC) $(LIBS) $(FLAGS) -o $@ $^
	@# Make the output file executable
	chmod 755 $@

clean:
	@# Using the '@' sign suppresses echoing
	@# the line while the command is run
	@rm -f $(SERVER) $(CLIENT)

CLEAN_MSG = "All resources closed/removed."
UNCLEAN_MSG = "Please clean resources using 'ipcrm'"
test-clean:
	@echo "Checking for open resources..."
	@ipcs | grep -q -w $(USER); if [ $$? = 1 ] ; then echo $(CLEAN_MSG); else ipcs && echo $(UNCLEAN_MSG); fi
