//
// prog1.asm -- an assembler example with global variables
//

// global Integer x;
// global Integer y;
// x = 2;
// y = x + 3;
// x = 7 * y + x;
// writeInteger(x + -33);
// writeCharacter('\n');

	pushc	2
	popg	0
	pushg	0
	pushc	3
	add
	popg	1
	pushc	7
	pushg	1
	mul
	pushg	0
	add
	popg	0
	pushg	0
	pushc	-33
	add
	wrint
	pushc	'\n'
	wrchr
	halt

