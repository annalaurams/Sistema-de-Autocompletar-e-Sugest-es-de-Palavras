#ifndef tree_HPP
#define tree_HPP

#include "shared.hpp"

typedef struct No{

    WordInfo *key;
    
    No* left;
    No* right;

}No;


// Àrvore binária

void createNo(No *&newNo, WordInfo *wordInfo);
void insertTree(No *&node, WordInfo *wordInfo);
void insert(vector<WordInfo> &heap, No *&root);

void printTree(No* raiz);
void outTree(No* root);
void outPrintTree(No *root, ofstream& outT);

void deleteTree(No *&node);

void binaryTree(vector<WordInfo> &heap, No *&root);

#endif