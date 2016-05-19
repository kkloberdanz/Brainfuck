/*
 * Programmer: Kyle Kloberdanz
 * Description: Takes brainfuck code, and transpiles it to c
 *              and prints the c code to stdout
 *              (Use the '>' symbol to direct the output to a file,
 *               example './brainfuck-to-c program.bf > out.c'     )
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *input_file; 

    if (argv[1]) {
        input_file = fopen(argv[1], "r");
    } else {
        puts("bftoc: no input file specified");
        exit(EXIT_FAILURE);
    }

    int tape_size = 200;
    if (argv[2]) {
        tape_size = atoi(argv[2]);
    }

    puts("#include <stdio.h>");
    puts("#include <stdlib.h>");
    puts("#define TAPE_SIZE 200");

    printf("char a[%d] = {0};\n", tape_size);
    puts("char* ptr = a;"); 

    puts("void saftey_check() {");
    puts("  // Saftey, end if atempt to write outside of bounds");
    puts("  if ((ptr < a) || (ptr >= a + TAPE_SIZE)) {");
    puts("       puts(\"brainfuck: quit to avoid overwritting system memory\");");
    puts("       exit(EXIT_FAILURE);");
    puts("  }");
    puts("}");

    puts("int main(void) {");

    char symbol = 'a';
    while (symbol != EOF) {
        symbol = fgetc(input_file);
        switch (symbol) {
            case '+':
                puts("saftey_check();");
                puts("++*ptr;");
                break;
                
            case '-':
                puts("saftey_check();");
                puts("--*ptr;");
                break;

            case '>':
                puts("saftey_check();");
                puts("++ptr;"); 
                break;

            case '<':
                puts("saftey_check();");
                puts("--ptr;"); 
                break;

            case '[':
                puts("saftey_check();");
                puts("while (*ptr) {");
                break;

            case ']':
                puts("saftey_check();");
                puts("}");
                break;

            case '.':
                puts("putchar(*ptr);");
                break;

            case ',':
                puts("*ptr = getchar();");
                puts("saftey_check();");
                break;

        }
    } 

    puts("return 0;");
    puts("}");
    return 0;
}
