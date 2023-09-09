#ifndef topk_HPP
#define topk_HPP
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <ctype.h>
#include <cctype>
#include <filesystem>
#include <time.h>
#include <list>

#include "tree.hpp"

#define K 21

using namespace std;

typedef struct WordInfo{

  string word;
  int occurrences;

}WordInfo;

typedef struct AVL{

    WordInfo keyAVL;
    
    AVL* leftAVL;
    AVL* rightAVL;

    int height;
}AVL;

void addStopWord(unordered_map<string, WordInfo> &glossaryStopWords, string &s);
void existentWord(unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords);

void printGlossary(unordered_map<string,WordInfo> &glossary);
void fileReading(char c, string &str, unordered_map<string, WordInfo> &glossary);
void processingFiles(unordered_map<string, WordInfo> &glossary, string &text);
void cases(string &str, unordered_map<string, WordInfo> &glossary);

string accentuation(const string &word);
void removeErro(unordered_map<string, WordInfo> &glossary);

void insertK(unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i);
void printHeap(vector<WordInfo> &aux_heap);
void heapify(vector<WordInfo> &aux_heap, int &lenght, int i);
void finaleHash(const unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &length, int i);

void nameFile(list<string>&nameFiles);
void inputFile(string &input, list<string> &wordInput);

void existsInHeap(vector<WordInfo> &heap, string &input, int lenght, int i, vector<WordInfo> &aux_heap);
bool existGlossary(unordered_map<string, WordInfo> &glossary, string &input);

void search(int &lenght, int i, unordered_map<string, WordInfo> &glossaryStopWords);

// AVL


int height(AVL* rootAvl);
int max(int a, int b);
AVL* newNode(WordInfo data);
AVL* rightRotate(AVL* y);
AVL* leftRotate(AVL* x);
int getBalance(AVL* N);
AVL* insertAvl(AVL* node, WordInfo data);
void printAVL(AVL* rootAvl);
void removeAllAVL(AVL *&t);

void avl(vector<WordInfo>heap);

void outPrintAVL(AVL *rootAVL, ofstream& outT);

void outAVL(AVL* rootAVL);

void outTheme(string &aux);
void output(string &firstWord);
void outputCreate();
void outEnd();


#endif
