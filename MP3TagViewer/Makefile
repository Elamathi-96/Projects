SRC:= $(wildcard *.c)
OBJ:= $(patsubst %.c, %.o, $(SRC))

mp3tag.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe

run:
	make && ./mp3tag.exe

