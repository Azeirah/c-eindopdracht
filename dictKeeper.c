// clear && gcc -std=c99 -g -Wall -Wextra -pedantic dictKeeper.c console.c dictionary.c -o dictKeeper

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "dictKeeper.h"
#include "console.h"

void promptNewTranslation(Dictionary* dictionary) {
    printf("Type your English word to be translated: ");
    char* word = getLine();
    printf("Type \"%s\"'s Dutch translation: ", word);
    char* translation = getLine();

    addTranslation(word, translation, dictionary);

    printf("Translation %s - %s has been added to the dictionary", word, translation);
}

void promptDeletion(Dictionary* dictionary) {
    printf("Type the word to be deleted: ");
    char* word = getLine();

    if (deleteTranslation(word, dictionary)) {
        printf("The dictionary entry \"%s\" has been deleted", word);
    } else {
        printf("The dictionary entry \"%s\" could not be found", word);
    }
}

void promptLookup(Dictionary* dictionary) {
    printf("Type the (English) word you want to look up: ");
    char* word = getLine();
    int index = indexOfDict(word, dictionary);

    if (index >= 0) {
        printf("The translation of the English word \"%s\" is \"%s\".", dictionary->translations[index].word, dictionary->translations[index].translation);
    }
}

void promptChange(Dictionary* dictionary) {
    printf("Type the (English) word you want to change the translation of: ");
    char* word           = getLine();
    int translationIndex = indexOfDict(word, dictionary);
    if (translationIndex >= 0) {
        char* translation      = dictionary->translations[translationIndex].translation;
        printf("What do you want to change \"%s\"'s translation \"%s\" to? ", word, translation);
        char* newTranslation   = getLine();
        if (changeTranslation(word, newTranslation, dictionary) != -1) {
            printf("\"%s\" now means \"%s\".", word, newTranslation);
        } else {
            printf("1The dictionary entry \"%s\" could not be found", word);
        }
    } else {
        printf("2The dictionary entry \"%s\" could not be found", word);
    }
}

void exitProgram(Dictionary* dictionary) {
    printf("Goodbye! <3");
    saveDictionaryToFile(DICTIONARYFILEPATH, dictionary);
    exit(1);
}

void executeTask(int choice, Dictionary* dictionary) {
    switch(choice) {
        // notice how the operations are once again, CRUD operations...
        case 1:
            promptNewTranslation(dictionary);
            break;
        case 2:
            promptLookup(dictionary);
            break;
        case 3:
            promptChange(dictionary);
            break;
        case 4:
           promptDeletion(dictionary);
            break;
        case 5:
            // Quit program
            saveDictionaryToFile(DICTIONARYFILEPATH, dictionary);
            exit(1);
            break;
    }
}

int displayMenu() {
    int choice;
    printf("Press the corresponding number to select a task\n\n");

    printf("1: Add a word\n");
    printf("2: Look up a word\n");
    printf("3: Change a word\n");
    printf("4: Delete a word\n");
    printf("5: Quit\n\n");

    while (true) {
        choice = getSingleDigit();
        if (choice >= 1 AND choice <= 5) { // 1..5
            return choice;
        }
        printf("Press 1, 2, 3 or 4\n");
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    Dictionary dictionary = loadDictionaryFromFile(DICTIONARYFILEPATH);

    while (true) {
        int choice = displayMenu();
        executeTask(choice, &dictionary);
        waitForKeypress();
    }

    return 0;
}
