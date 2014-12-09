CC=gcc
SRCS=test.c cstr.c
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -pedantic -std=c99 -O2 -D_GNU_SOURCE
CPPFLAGS+= -MMD -MP
TARGET=test

all: $(TARGET)

debug: $(TARGET)
debug: CFLAGS+= -DDEBUG -g

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $^

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

-include $(OBJS:.o=.d)

clean:
	rm -f test *.o *.d

