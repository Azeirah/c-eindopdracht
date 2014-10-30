#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "dictionary.h"
#include "console.h"

#define STRINGBUFFER 512

Dictionary createDictionary() {
    Dictionary *dictionary   = malloc(sizeof(Dictionary));
    dictionary->length       = 0;
    dictionary->memorySize   = 0;
    dictionary->translations = malloc(0);
    return *dictionary;
}

void addTranslation(char* word, char* translation, Dictionary* dictionary) {
    Relation* translations;
    int    newMemorySize  = 0;
    Relation* newRelation = malloc(sizeof(Relation));

    // allocating space for the strings
    newRelation->word        = malloc(STRLEN(word));
    newRelation->translation = malloc(STRLEN(translation));
    // copying the strings into the translation structure
    strcpy(newRelation->word, word);
    strcpy(newRelation->translation, translation);

    // resizing the memory block for the array of translations
    newMemorySize = sizeof(*newRelation) + dictionary->memorySize;
    translations  = realloc(dictionary->translations, newMemorySize);
    if (translations != NULL) {
        dictionary->translations = translations;
    }

    // updating the array of translations with metadata and adds the new translation
    dictionary->translations[dictionary->length] = *newRelation;
    dictionary->memorySize                       = newMemorySize;
    dictionary->length                           += 1;
}

void printTranslation(Relation* rl) {
    printf("\nThe translation of %s is %s.", rl->word, rl->translation);
}

void printAllTranslations(Dictionary* dictionary) {
    for (size_t i = 0; i < dictionary->length; i++) {
        printTranslation(&dictionary->translations[i]);
    }
}

void createDictionaryFile(char* filePath) {
    FILE* fp = fopen(filePath, "w");
    fclose(fp);
}

Dictionary loadDictionaryFromFile(char* filePath) {
    FILE* fp = fopen(filePath, "r");
    char word[STRINGBUFFER];
    char translation[STRINGBUFFER];
    Dictionary dictionary = createDictionary();

    if (fp == NULL) {
        // The file doesn't exist, create it
        createDictionaryFile(filePath);
    } else {
        while(fscanf(fp, "%s %s", word, translation) != EOF) {
            addTranslation(word, translation, &dictionary);
        }
    }
    fclose(fp);
    return dictionary;
}

void saveDictionaryToFile(char* filePath, Dictionary* dictionary) {
    // this is an inefficient way to save, it simply removes the old file, and completely overwrites it with the updated in-memory dictionary.
    // a more efficient way would be to diff the in-memory dictionary with the file. But I won't go into that :D
    FILE* fp = fopen(filePath, "w");
    for (size_t i = 0; i < dictionary->length; i++) {
        fprintf(fp, "%s %s\n", dictionary->translations[i].word, dictionary->translations[i].translation);
    }
    fclose(fp);
}