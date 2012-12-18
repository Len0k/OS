To compile and link these files do (on x84_64)
`yasm -f elf64 g.asm`
`gcc -c m.c`
`gcc m.o g.o -lpthread -o main`
And run:
`./main`

