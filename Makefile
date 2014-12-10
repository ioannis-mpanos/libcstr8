CC=gcc
SRCS=test.c cstr.c
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -pedantic -std=c99 -O2 -D_GNU_SOURCE
CPPFLAGS+= -MMD -MP
TARGET=test

.PHONY: all doxy


all: $(TARGET)

debug: $(TARGET)
debug: CFLAGS+= -DDEBUG -g

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

-include $(OBJS:.o=.d)

doxy:
	doxygen doxy.conf
clean:
	rm -f test *.o *.d

