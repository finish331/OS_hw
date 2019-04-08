all: producer_consumer.x

producer_consumer.x: producer_consumer.o
	gcc -o producer_consumer.x producer_consumer.o

producer_consumer.o: producer_consumer.c buffer.h
	gcc -c producer_consumer.c

clean:
	rm -f *.o *.x
