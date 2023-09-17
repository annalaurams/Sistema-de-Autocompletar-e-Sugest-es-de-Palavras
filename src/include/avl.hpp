#ifndef avl_hpp
#define avl_hpp

#include "shared.hpp"

typedef struct AVL{

    WordInfo keyAVL;
     vector<  string>vetor;
    
    AVL* leftAVL;
    AVL* rightAVL;

    int height;
}AVL;


int height(AVL* rootAvl);
int max(int a, int b);
AVL* rightRotate(AVL* y);
AVL* leftRotate(AVL* x);
int getBalance(AVL* N);
AVL* insertAvl(AVL* node, WordInfo data);
void printAVL(AVL* rootAvl);
void removeAllAVL(AVL *&t);

void avl(vector<WordInfo>heap);

void outPrintAVL(AVL *rootAVL, ofstream& outT);
void outAVL(AVL* rootAVL);


#endif
