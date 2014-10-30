#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "dictKeeper.h"
#include "console.h"

void promptNewTranslation(Dictionary* dictionary) {
    printf("Type your Dutch word to be translated: ");
    char* word = getLine();
    printf("Type %s's English translation: ", word);
    char* translation = getLine();

    addTranslation(word, translation, dictionary);

    printf("Translation %s - %s has been added to the dictionary", word, translation);
}

void executeTask(int choice, Dictionary* dictionary) {
    switch(choice) {
        // notice how the operations are once again, CRUD operations...
        case 1:
            promptNewTranslation(dictionary);
            break;
        case 2:
            // Look up word
            break;
        case 3:
            // Change word
            break;
        case 4:
            // Delete word
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
    printAllTranslations(&dictionary);

    while (true) {
        int choice = displayMenu();
        executeTask(choice, &dictionary);
        waitForKeypress();
    }

    return 0;
}
