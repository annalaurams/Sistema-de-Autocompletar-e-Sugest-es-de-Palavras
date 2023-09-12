#ifndef huffman_hpp
#define huffman_hpp


#include "shared.hpp"
#define MAX 100

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

// Huffman

void HuffmanCodes(vector<WordInfo>& heap) ;
Huffman* generateHuffman(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff);
void printPriorityQueue(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff);
void printCodes(Huffman* rootH, int array[], int top);
void clearHuffmanTree(Huffman* rootH);

void outHuffPrint(Huffman* rootH, int array[], int top, ofstream& outT);
void outHuff(Huffman* rootH, int array[], int top);




#endif