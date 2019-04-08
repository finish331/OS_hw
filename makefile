all: producer_consumer.x

producer_consumer.x: producer_consumer.o
	gcc -o producer_consumer.x producer_consumer.o -lpthread

producer_consumer.o: producer_consumer.c buffer.h
	gcc -c producer_consumer.c -lpthread

clean:
	rm -f *.o *.x
