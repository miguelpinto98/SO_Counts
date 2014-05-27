SRC = linkedlist/linkedlist.c struct.c mainServer.c
CCFLAGS = -O2 -Wextra
CCC = gcc
FILE = TESTE

$(FILE): $(SRC:.c=.o)
	$(CCC) -o $(FILE) $(CCFLAGS) $(SRC)

clean:
	rm -f *.o