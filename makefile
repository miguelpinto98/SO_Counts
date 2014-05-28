SRC1 = linkedlist/linkedlist.c struct.c utils.c server.c
SRC2 = cliente.c
FILE1 = SERVER
FILE2 = CLIENTE
CCFLAGS = -O2 -Wextra
CCC = gcc

$(FILE1): $(SRC1:.c=.o)
	$(CCC) -o $(FILE1) $(CCFLAGS) $(SRC1)

$(FILE2): $(SRC2:.c=.o)
	$(CCC) -o $(FILE2) $(CCFLAGS) $(SRC2)

clean:
	rm -f *.o SERVER CLIENTE