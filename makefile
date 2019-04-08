.PHONY: clean

CC:= gcc
SRC:= producer_consumer.c buffer.h

all: producer_consumer.o producer_consumer

producer_consumer: producer_consumer.o
	$(CC) $< -o $@ -lpthread

producer_consumer.o: $(SRC)
	$(CC) -c $< -o $@ -lpthread

clean:
	rm -f *.o
