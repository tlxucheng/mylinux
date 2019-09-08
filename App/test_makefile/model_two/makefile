CC = gcc
RM = rm

#CFLAGS += -D FUN1

TARGETS := myapp2

all:$(TARGETS)

$(TARGETS):../model_one/print_fun.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -f *.o
	$(RM) -f $(TARGETS)


