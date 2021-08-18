build:
	gcc -g -Wall -c -fPIC fault.c -o fault.o -std=c99
	gcc -g -Wall -c -fPIC state_machine.c -o state_machine.o -std=c99
	gcc -g -Wall -c -fPIC motor.c -o motor.o -std=c99
	gcc -shared fault.o state_machine.o motor.o -o libstate-machine.so