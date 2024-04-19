#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
};

// Creates a new Trie node
struct TrieNode* createNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (newNode) {
        newNode->isEndOfWord = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

// Inserts a word into the trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* current = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}

// Searches for a word in the trie and returns the number of occurrences
int numberOfOccurrences(struct TrieNode* root, char* word) {
    struct TrieNode* current = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->isEndOfWord;
}

// Deallocates memory used by the trie
void deallocateTrie(struct TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        deallocateTrie(root->children[i]);
    }
    free(root);
}

// Reads dictionary from file and stores words in array
int readDictionary(char* filename, char** pInWords) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    int count = 0;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }
    fclose(file);
    return count;
}

int main(void) {
    char* inWords[256];
    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }
    // Initialize the trie
    struct TrieNode* root = createNode();
    // Insert each word from dictionary into the trie
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    // Test cases
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    // Deallocate memory used by the trie
    deallocateTrie(root);
    return 0;
}