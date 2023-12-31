#include "./include/tree.hpp"

// ÁRVORE BINÁRIA

void insert(vector<WordInfo> &heap, No *&root) {

  for (const WordInfo &wordInfo : heap) {
    WordInfo *wordInfoPtr = new WordInfo { wordInfo };
    insertTree(root, wordInfoPtr);
  }
}

void createNo(No *&newNo, WordInfo *wordInfo) {

  newNo = new No;

  if (newNo == nullptr) return;

  newNo->key = wordInfo;
  newNo->left = nullptr;
  newNo->right = nullptr;
}

// insere os elementos na árvore

void insertTree(No *&no, WordInfo *wordInfo) {

  if (no == nullptr) {
    createNo(no, wordInfo);
    return;
  }

  if (wordInfo->occurrences < no->key->occurrences)
    insertTree(no->left, wordInfo);

  else if (wordInfo->occurrences > no->key->occurrences)
    insertTree(no->right, wordInfo);

  else
    insertTree(no->left, wordInfo);
}

// esvazia a árvore

void deleteTree(No *&node) {

  if (node == nullptr) return;

  deleteTree(node->left);
  deleteTree(node->right);

  delete node->key;
  delete node;

  node = nullptr;
}

// imprimi a árvore

void printTree(No *root) {

  if (!(root == NULL)) {
    printTree(root->left);
    cout << root->key->word << ": " << root->key->occurrences << " | ";
    printTree(root->right);
  }
}

// funções de output

void outPrintTree(No *root, ofstream &outT) {

  if (root == nullptr) return;

  outPrintTree(root->left, outT);
  outPrintTree(root->right, outT);
  outT << root->key->word << ": " << root->key->occurrences << " ";
}

void outTree(No *root) {

  if (root == nullptr) return;

  ofstream outT;
  outT.open("output.txt", ios::app);
  outT << endl << "ÁRVORE BINÁRIA" << endl;
  outT << "[ ";

  outPrintTree(root, outT);

  outT << "]" << endl;

  outT.close();
}

void binaryTree(vector<WordInfo> &heap, No *&root) {

  //auto startT = chrono::steady_clock::now();

  insert(heap, root);
  outTree(root);
  deleteTree(root);
  
  //auto endT = chrono::steady_clock::now();
 // cout << "\nTEMPO TREE: " << chrono::duration_cast<chrono::nanoseconds>(endT - startT).count() << " ns" << endl << endl;
}

