#include "./include/huffman.hpp"

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