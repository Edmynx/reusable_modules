CFLAGS			=	-Wall -pedantic -std=c11 -L. -g

all				:	put-empty put-non-empty get-empty get-non-empty app-empty app-non-empty rem-empty rem-non-empty

list.o 			:	list.c list.h
					gcc $(CFLAGS) -c list.c 

make-car.o		:	make-car.c list.h
					gcc $(CFLAGS) -c make-car.c

function.o		:	function.c list.h
					gcc $(CFLAGS) -c function.c				

put-empty.o		:	put-empty.c list.h
					gcc $(CFLAGS) -c put-empty.c 

put-non-empty.o	:	put-non-empty.c list.h
					gcc $(CFLAGS) -c put-non-empty.c 

get-empty.o		:	get-empty.c list.h
					gcc $(CFLAGS) -c get-empty.c

get-non-empty.o	:	get-non-empty.c list.h
					gcc $(CFLAGS) -c get-non-empty.c

app-empty.o		:	app-empty.c list.h
					gcc $(CFLAGS) -c app-empty.c

app-non-empty.o:	app-non-empty.c list.h
					gcc $(CFLAGS) -c app-non-empty.c

rem-empty.o		:	rem-empty.c list.h
					gcc $(CFLAGS) -c rem-empty.c

rem-non-empty.o	:	rem-non-empty.c list.h
					gcc $(CFLAGS) -c rem-non-empty.c

put-empty		:	put-empty.o list.o make-car.o list.h
					gcc $(CFLAGS) put-empty.o list.o make-car.o -o put-empty

put-non-empty	:	put-non-empty.o list.o make-car.o list.h
					gcc $(CFLAGS) put-non-empty.o list.o make-car.o -o put-non-empty

get-empty		:	get-empty.o list.o list.h
					gcc $(CFLAGS) get-empty.o list.o -o get-empty

get-non-empty	:	get-non-empty.o list.o make-car.o list.h
					gcc $(CFLAGS) get-non-empty.o list.o make-car.o -o get-non-empty

app-empty		:	app-empty.o list.o function.o list.h
					gcc $(CFLAGS) app-empty.o list.o function.o -o app-empty

app-non-empty	:	app-non-empty.o list.o make-car.o function.o list.h
					gcc $(CFLAGS) app-non-empty.o list.o make-car.o function.o -o app-non-empty

rem-empty		:	rem-empty.o list.o list.h
					gcc $(CFLAGS) rem-empty.o list.o -o rem-empty

rem-non-empty	:	rem-non-empty.o list.o make-car.o list.h
					gcc $(CFLAGS) rem-non-empty.o list.o make-car.o -o rem-non-empty

clean			:	
					rm -f *.o put-empty put-non-empty get-empty get-non-empty app-empty app-non-empty rem-empty rem-non-empty

