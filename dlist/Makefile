CC = gcc
CFLAGS = -g -Wall
LIBS =
TARGETS = dlist
OBJS = main.o\
	   dlist.o

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.swp *.o $(TARGETS)
