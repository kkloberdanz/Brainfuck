/* Programmer  : Kyle Kloberdanz
 * File        : brainfuck.cpp
 * Notes       : Must be compiled with c++11 std
 *
 * Description : A brainfuck interpreter in c++
 */

#include <vector>
#include <stack>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TAPE_SIZE 32000 

FILE* input_file;
char  a[TAPE_SIZE] = {0};
char* ptr = a; 

/*
// Used for debugging 
template <typename T>
void print_vector(std::vector<T> v) {
    if (!v.empty()) {
        for (auto element : v) {
            //std::cout << element << ", ";
            std::cout << element;
        }
        std::cout << std::endl;
    }
}
*/

/*
// Used for debugging 
void print_tape() {
    // An 'x' marks where the head currently is
    puts("\n*** Start of tape ***");
    int i;
    for (i = 0; i < TAPE_SIZE; i++) {
        if (ptr == a + i) { 
            printf("%dx, ", a[i]);
        } else {
            printf("%d, ", a[i]);
        }
    }
    puts("\n***  End of tape  ***");
}
*/

/* put switch in here, call recursively? */
void run_code(char symbol) { 

    // Saftey, end if atempt to write outside of bounds
    if ((ptr < a) || (ptr >= a + TAPE_SIZE)) {
        puts("brainfuck: quit to avoid overwritting system memory");
        exit(EXIT_FAILURE);
    } 

    switch (symbol) { 

        // move 1 cell to the right
        case '>':
            ++ptr;
            break;
            
        // move 1 cell to the left
        case '<':
            --ptr;
            break;

        // increment cell
        case '+':
            ++*ptr;
            break;

        // decrement cell
        case '-':
            --*ptr;
            break;

        // print cell to screen as ascii
        case '.':
            putchar(*ptr);
            break;

        // read in char
        case ',':
            *ptr = getchar();
            break;

        // everything else is ignored (loops are handled elsewhere)
        default:
            break; 
    }
} // end func run_code 

int main(int argc, char* argv[]) { 
    std::vector<char> code;

    if (argv[1]) {
        input_file = fopen(argv[1], "r");
    } else {
        puts("brainfuck: no input file specified");
        exit(EXIT_FAILURE);
    }

    if (!input_file) {
        puts("brainfuck: unable to open file"); 
        exit(EXIT_FAILURE);
    }

    /* Pull all of code into memory */
    char symbol = 'a'; 
    while (symbol != EOF) { 
        symbol = fgetc(input_file); 
        code.push_back(symbol); 
    }

    int i = 0;

    // contains indeces of where to loop back to
    std::stack<int> repeat_s;

    // contains index of where to go after loop
    int end_repeat;

    int code_length = code.size();
                              
    /* Handles looping */
    do {
        if (code[i] == '[') {
            repeat_s.push(i);
        } else if (code[i] == ']') {
            end_repeat = i;
            i = repeat_s.top();
        } 
        if (!repeat_s.empty()) { 
            // condition to stop loop 
            if ((i == repeat_s.top()) && (!*ptr)) { 
                i = end_repeat; 
                repeat_s.pop();
            }
        }
        if ((code[i] != '[') && (code[i] != ']')) {
            run_code(code[i]);
        }
        i++;
    } while (i < code_length);

    fclose(input_file);
    return 0;
}
