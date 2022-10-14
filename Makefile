default:
	gcc rm.c -o rm
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc term.c 
	./a.out

preprocessor:
	gcc -E ls.c -o ls.i
	gcc -E cat.c -o cat.i
	gcc -E date.c -o date.i
	gcc -E mkdir.c -o mkdir.i
	gcc -E term.c -o term.i

compiler:
	gcc -S ls.c
	gcc -S cat.c
	gcc -S date.c
	gcc -S mkdir.c
	gcc -S term.c 

assembler:
	gcc -c ls.c
	gcc -c cat.c
	gcc -c date.c
	gcc -c mkdir.c
	gcc -c term.c 

linker:
	gcc rm.c -o rm
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc term.c 