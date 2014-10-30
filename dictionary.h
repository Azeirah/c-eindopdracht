typedef struct Relation {
    char* word;
    char* translation;
} Relation;

typedef struct Dictionary {
    size_t length;
    struct Relation *translations;
    int memorySize;
} Dictionary;

Dictionary createDictionary();
int indexOfDict(char* word, Dictionary* dictionary);
int deleteTranslation(char* word, Dictionary* dictionary);
int changeTranslation(char* word, char* newTranslation, Dictionary* dictionary);
void addTranslation(char* word, char* translation, Dictionary* dictionary);
void printTranslation(Relation* rl);
void printAllTranslations(Dictionary* dictionary);
Dictionary loadDictionaryFromFile(char* filePath);
void saveDictionaryToFile(char* filePath, Dictionary* dictionary);