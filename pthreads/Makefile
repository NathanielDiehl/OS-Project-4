CC        = gcc
CFLAGS    = -Wall -pthread
LDFLAGS   = -pthread

#
# Modify TOPDIR if you use your own include files and library files
#

PROGRAM   = main	# name of the binary
SRCS      = pthread_main.c		# source file
OBJS      = $(SRCS:.c=.o)		# object file

#
# Targets
#

default: all

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(CFLAGS) $(LDFLAGS)

# Ensure that the program is recompiled when source files are modified
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)


clean:
	/bin/rm -f $(OBJS) $(PROGRAM)
