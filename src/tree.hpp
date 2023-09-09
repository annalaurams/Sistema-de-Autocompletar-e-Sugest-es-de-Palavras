#ifndef tree_HPP
#define tree_HPP
#include "document.hpp"
#define MAX 100

typedef struct No{

    WordInfo *key;
    
    No* left;
    No* right;

}No;


class Huffman{
    
    public:
        WordInfo* keyHuff;

        Huffman* leftH;
        Huffman* rightH;

        Huffman(WordInfo* wordInfo) : keyHuff(wordInfo), leftH(nullptr), rightH(nullptr) {}
};

class Compare {
public:
    bool operator()(Huffman* a, Huffman* b) {
        return a->keyHuff->occurrences > b->keyHuff->occurrences;
    }
};


// Àrvore binária

void createNo(No *&newNo, WordInfo *wordInfo);
void insertTree(No *&node, WordInfo *wordInfo);
void insert(vector<WordInfo> &heap, No *&root);

void printTree(No* raiz);
void outTree(No* root);
void outPrintTree(No *root, ofstream& outT);

void deleteTree(No *&node);

void binaryTree(vector<WordInfo> &heap, No *&root);


// Huffman

void HuffmanCodes(vector<WordInfo>& heap) ;
Huffman* generateHuffman(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff);
void printPriorityQueue(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff);
void printCodes(Huffman* rootH, int arr[], int top);
void clearHuffmanTree(Huffman* rootH);

void outHuffPrint(Huffman* rootH, int arr[], int top, ofstream& outT);
void outHuff(Huffman* rootH, int arr[], int top);

#endif