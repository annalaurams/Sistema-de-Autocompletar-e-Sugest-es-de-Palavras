#ifndef document_hpp
#define document_hpp

#include <ctype.h>
#include <filesystem>
#include <time.h>
#include <list>

#include <unordered_map>
#include "shared.hpp"
#include "avl.hpp"

#define K 21

using namespace std;


void addStopWord(unordered_map<string, WordInfo> &glossaryStopWords, string &s);
void existentWord(unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords);

void printGlossary(unordered_map<string, WordInfo> &glossary);
void fileReading(char c, string &str, unordered_map<string, WordInfo> &glossary);
void processingFiles(unordered_map<string, WordInfo> &glossary, string &text);
void cases(string &str, unordered_map<string, WordInfo> &glossary);

string accentuation(const string &word);
void removeErro(unordered_map<string, WordInfo> &glossary);

void insertK(unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i);
void printHeap(vector<WordInfo> &aux_heap);
void heapify(vector<WordInfo> &aux_heap, int &lenght, int i);
void finaleHash(const unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &length, int i);

void nameFile(list<string> &nameFiles);
void inputFile(list<string> &wordInput);

void existsInHeap(vector<WordInfo> &heap, string &input, int lenght, int i, vector<WordInfo> &aux_heap);
bool existGlossary(unordered_map<string, WordInfo> &glossary, string &input);

void search(int &lenght, int i, unordered_map<string, WordInfo> &glossaryStopWords);

void outTheme(string &aux);
void output(string &firstWord);
void outputCreate();
void outEnd();


#endif
