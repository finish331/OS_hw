.PHONY:clean
all:DiskScheduling.o

DiskScheduling.o: DiskScheduling.c
	gcc DiskScheduling.c -o DiskScheduling.o

clean:
	rm -rf DiskScheduling.o
