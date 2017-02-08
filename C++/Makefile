CC=g++
C++FLAGS=-std=c++11

SIM_OBJ=main.o
SIM_PROG= aq_simulation

%.o : %.cpp
	$(CC)  -c $< -o $@ $(C++FLAGS)

all:

	make $(SIM_PROG)


$(SIM_PROG): $(SIM_OBJ)
	$(CC) $(C++FLAG) -o $@ $(SIM_OBJ)



clean:
	(rm -f *.o;)

	rm -f $(SIM_PROG)s



