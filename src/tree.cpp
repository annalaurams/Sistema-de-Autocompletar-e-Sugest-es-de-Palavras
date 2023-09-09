#include "tree.hpp"

// ÁRVORE BINÁRIA

void insert(vector<WordInfo> &heap, No *&root){

  for (const WordInfo &wordInfo : heap){
    WordInfo *wordInfoPtr = new WordInfo{wordInfo};
    insertTree(root, wordInfoPtr);
  }
}

void createNo(No *&newNo, WordInfo *wordInfo){

  newNo = new No;

  if (newNo == nullptr) return;

  newNo->key = wordInfo;
  newNo->left = nullptr;
  newNo->right = nullptr;
}

void insertTree(No *&no, WordInfo *wordInfo){

  if (no == nullptr){
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

void deleteTree(No *&node){

  if (node == nullptr) return;

  deleteTree(node->left);
  deleteTree(node->right);

  delete node->key; 
  delete node;
  
  node = nullptr; 
}

void printTree(No *root){

  if(!(root == NULL)){
    printTree(root->left); 
    cout << root->key->word << ": " << root->key->occurrences << " | ";
    printTree(root->right); 
  }     
}

void outPrintTree(No *root, ofstream& outT){

   if (root == nullptr) return;

  outPrintTree(root->left, outT);
  
  outT  << root->key->word << ": " << root->key->occurrences <<  ", ";

  outPrintTree(root->right, outT);
}

void outTree(No* root){

    if (root == nullptr) return;

    ofstream outT;
    outT.open("output.txt", ios::app);
    outT << endl << "ÁRVORE BINÁRIA" << endl;
    outT << "[ ";

    outPrintTree(root, outT);

    outT << "]" << endl;

    outT.close();
}

void binaryTree(vector<WordInfo> &heap, No *&root){

  insert(heap, root);
  outTree(root);
  deleteTree(root);
}


// HUFFMAN

Huffman* generateHuffman(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff){

    while (huff.size() != 1){

      //printPriorityQueue(huff);
      Huffman* leftH = huff.top();
      huff.pop();

      Huffman* rightH = huff.top();
      huff.pop();

      WordInfo* h = new WordInfo{"", leftH->keyHuff->occurrences + rightH->keyHuff->occurrences};
      Huffman * node = new Huffman(h);
      node->leftH = leftH;
      node->rightH = rightH;

      huff.push(node);
    }
    
    return huff.top();
}

void printCodes(Huffman* rootH, int arr[], int top){

    if (rootH->leftH) {
        arr[top] = 0;
        printCodes(rootH->leftH, arr, top + 1); 
    }

    if (rootH->rightH){
        arr[top] = 1;
        printCodes(rootH->rightH, arr, top + 1);
    }

    if (!rootH->leftH && !rootH->rightH){

        cout << rootH->keyHuff->word << " ";

        for (int i = 0; i < top; i++) 
            cout << arr[i];
        
        cout << endl;
    }
}

void HuffmanCodes(vector<WordInfo>& heap){

    priority_queue<Huffman*, vector<Huffman*>, Compare> huff;

    for (const WordInfo& wordInfo : heap) {
        Huffman* newNode = new Huffman(new WordInfo(wordInfo));
        huff.push(newNode);
    }

   Huffman* rootH = generateHuffman(huff);

   int arr[MAX], top = 0;

   //printCodes(rootH, arr, top);
   outHuff(rootH, arr, top);
   clearHuffmanTree(rootH);
}

void printPriorityQueue(priority_queue<Huffman*, vector<Huffman*>, Compare>& huff){

    cout << "\nPriority Queue: ";
    priority_queue<Huffman*, vector<Huffman*>, Compare> temphuff = huff;

    while (!temphuff.empty()) {
        cout << temphuff.top()->keyHuff->word << "(" << temphuff.top()->keyHuff->occurrences << ") ";
        temphuff.pop();
    }
    cout << endl << endl;
}

void clearHuffmanTree(Huffman* rootH){

    if (rootH) {
        clearHuffmanTree(rootH->leftH);
        clearHuffmanTree(rootH->rightH);
        delete rootH;
    }
}

void outHuffPrint(Huffman* rootH, int arr[], int top, ofstream& outT){

    if (rootH->leftH) {
        arr[top] = 0;
        outHuffPrint(rootH->leftH, arr, top + 1, outT); 
    }

    if (rootH->rightH){
        arr[top] = 1;
        outHuffPrint(rootH->rightH, arr, top + 1, outT);
    }

    if (!rootH->leftH && !rootH->rightH){

        outT << rootH->keyHuff->word << " ";

        for (int i = 0; i < top; i++) 
            outT << arr[i];
           outT << ", ";
    }
}

void outHuff(Huffman* rootH, int arr[], int top){

    if (rootH == nullptr) return;

    ofstream outT;
    outT.open("output.txt", ios::app);

    outT << endl << "HUFFMAN" << endl;
    outT << "[ ";

    outHuffPrint(rootH, arr, top, outT);

    outT << "]" << endl << endl;

    outT.close();
}