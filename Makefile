

assemble: assembler2.c
	gcc -c assembler2.c
	gcc -o assembler assembler2.o
	./assembler $(FILENAME)

simulate:
	gcc simulator.c -g -Wall -o output_exe
	./output_exe

all:
	 gcc -c assembler2.c
	 gcc -o assembler assembler2.o
	 ./assembler $(FILENAME)
	 gcc simulator.c -g -Wall -o output_exe
	 ./output_exe

clean:
	rm *.o assembler output_exe


help:
	echo -e 'use "Make assemble FILENAME=(file.asm)" to assemble the instruction set\nUse "Make simulate" to run the simulator after assembly\nUse "make all FILENAME=(file.asm)" to run both assembler and simulator\nUse "make clean" to remove all compiled files\n'
