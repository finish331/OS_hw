all: producer_consumer.o

producer_consumer.o: producer_consumer.c buffer.h
	gcc -c producer_consumer.c -lpthread

clean:
	rm -f *.o
