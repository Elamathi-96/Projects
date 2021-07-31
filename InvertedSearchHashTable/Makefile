SRC:= $(wildcard *.c)
OBJ:= $(patsubst %.c, %.o, $(SRC))

list.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe

run:
	make && ./list.exe
