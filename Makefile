CC = gcc
CFLAGS ?= -std=gnu11 -Wall -Wextra -g
CFLAGS += -pthread
LDLIBS += -pthread

TARGET = sync_car
OBJECTS = sync_car.o sync_car-runner.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

%.o: %.c sync_car.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
