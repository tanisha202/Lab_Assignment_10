#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHAR_SIZE 26

struct Trie {
    int occurrences;
    struct Trie *children[CHAR_SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL) {
        *ppTrie = (struct Trie *)malloc(sizeof(struct Trie));
        (*ppTrie)->occurrences = 0;
        for (int i = 0; i < CHAR_SIZE; i++){
            (*ppTrie)->children[i] = NULL;
        }
    }

    struct Trie *t = *ppTrie;
    int n = strlen(word);
    for (int i = 0; i < n; i++) {
        int index = tolower(word[i]) - 'a';
        if (t->children[index] == NULL) {
            t->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            t->children[index]->occurrences = 0;
            for (int j = 0; j < CHAR_SIZE; j++){
                t->children[index]->children[j] = NULL;
            }
        }

        t = t->children[index];
    }

    t->occurrences++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    if (pTrie == NULL){
        return 0;
    }

    int n = strlen(word);
    struct Trie *t = pTrie;
    for (int i = 0; i < n; i++) {
        int index = tolower(word[i]) - 'a';
        if (t->children[index] == NULL){
            return 0;
        }
        t = t->children[index];
    }

    return t->occurrences;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }

    for (int i = 0; i < CHAR_SIZE; i++){
        deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    // Insert each word from the dictionary
    char *pWords[] = {"notaword", "UCF", "no", "Note", "Corg"};
    int numWords = sizeof(pWords) / sizeof(char *);
    for (int i = 0; i < numWords; i++){
        insert(&trie, pWords[i]);
    }

    // Check the number of occurrences of each word
    for (int i = 0; i < numWords; i++){
        printf("\t%s : %d", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    // Deallocate the trie data structure
    trie = deallocateTrie(trie);

    if (trie != NULL){
        printf("There is an error in this program");
    }

    return 0;
}
