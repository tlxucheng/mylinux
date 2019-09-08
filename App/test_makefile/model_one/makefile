CC = gcc
RM = rm

CFLAGS += -D FUN1

TARGETS := myapp

all:$(TARGETS)

$(TARGETS):print_fun.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -f *.o
	$(RM) -f $(TARGETS)


