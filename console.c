#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

char getch() {
    // this code is very much stolen from the internet.
    // it's a unix reimplementation of the windows only getch function.
    char buf           = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) {
        perror("tcsetattr()");
    }
    old.c_lflag    &= ~ICANON;
    old.c_lflag    &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) {
        perror("tcsetattr ICANON");
    }
    if (read(0, &buf, 1) < 0) {
        perror("read()");
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) {
        perror("tcsetattr ~ICANON");
    }
    return buf;
}

char getSingleCharacter() {
    return getch();
}

char* getWord() {
    char* word = malloc(50 * sizeof(char));
    fgets(word, 50, stdin);
    return word;
}

char* getLine() {
    int c;
    char* line    = malloc(100);
    char* linep   = line;
    size_t lenmax = 100;
    size_t len    = lenmax;

    if (line == NULL) {
        return NULL;
    }

    while(1) {
        // read the source character by character
        c = fgetc(stdin);
        if (c == EOF) {
            // when the source has reached END OF FILE, return
            break;
        }

        if (--len == 0) {
            // when the length of the message is greater than lenmax, reallocate space for the line buffer
            len         = lenmax;
            char* linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }
            line  = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n') {
            // when the source has reached END OF FILE, return
            break;
        }
    }
    *line = '\0';
    // replace the last character in the string (always a \n), with a null terminator
    linep[strlen(linep) - 1] = 0;
    return linep;
}

void waitForKeypress() {
    printf("\n\nPress any key to continue...\n\n");
    getch();
}

int getSingleDigit() {
    // gets a single digit represented as an integer, limited to 0..9 only!
    return getSingleCharacter() - '0';
}
