#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

//вынести в отдельный файл

typedef struct BstNode BstNode;
struct BstNode {
    int key;
    BstNode *left;  // < key
    BstNode *right; // >= key
    BstNode *parent;
    char *string;
};

typedef struct TrieNode TrieNode;
struct TrieNode {
    char key;
    TrieNode **kids;
    int len;
    int capacity;
    BstNode *link;
};

//gi

int trieDestroy(TrieNode *root) {
    for (int x = 0; x < root->len; x++) {
        trieDestroy(root->kids[x]);
    }
    freeAll(2, root->kids, root);
}

