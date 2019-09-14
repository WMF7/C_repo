CC=gcc
#CFLAGS=-I/usr/include/glib-2.0
#CFLAGS+=-I/usr/lib32/glib-2.0/include
#$CFLAGS+=-lglib-2.0

CFLAGS=-llua
result=res

build: 
	${CC} ${CFLAGS} main.c -o ${result}
	@echo "----------------"
run: build 
	@(./${result})
