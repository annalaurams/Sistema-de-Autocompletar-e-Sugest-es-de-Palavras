#include "./include/huffman.hpp"

// HUFFMAN

// soma os elementos e insere de volta na fila

Huffman *generateHuffman(priority_queue<Huffman *, vector<Huffman *>, Compare> &huff) {

    while (huff.size() != 1) {

        Huffman *leftH = huff.top();
        huff.pop();

        Huffman *rightH = huff.top();
        huff.pop();

        WordInfo *h = new WordInfo { "", leftH->keyHuff->occurrences + rightH->keyHuff->occurrences };
        Huffman *node = new Huffman(h);
        node->leftH = leftH;
        node->rightH = rightH;

        huff.push(node);
    }

    return huff.top();
}

// imprimi as palavras e seus respectivos códigos

void printCodes(Huffman *rootH, int array[], int top) {

    if (rootH->leftH) {
        array[top] = 0;
        printCodes(rootH->leftH, array, top + 1);
    }

    if (rootH->rightH) {
        array[top] = 1;
        printCodes(rootH->rightH, array, top + 1);
    }

    if (!rootH->leftH && !rootH->rightH) {

        cout << rootH->keyHuff->word << " ";

        for (int i = 0; i < top; i++)
            cout << array[i];

        cout << endl;
    }
}

void HuffmanCodes(vector<WordInfo> &heap) {

    //auto startH = chrono::steady_clock::now();

    priority_queue<Huffman *, vector<Huffman *>, Compare> huff;

    for (const WordInfo &wordInfo : heap) {
        Huffman *newNode = new Huffman(new WordInfo(wordInfo));
        huff.push(newNode);
    }

    Huffman *rootH = generateHuffman(huff);

    int array[MAX], top = 0;

    //printCodes(rootH, array, top);
    outHuff(rootH, array, top);
    clearHuffmanTree(rootH);

    //auto endH = chrono::steady_clock::now();
    //cout << "\nTEMPO HUFFMAN: " << chrono::duration_cast<chrono::nanoseconds>(endH - startH).count() << " ns" << endl << endl;
}

// imprimi a fila

void printPriorityQueue(priority_queue<Huffman *, vector<Huffman *>, Compare> &huff) {

    cout << "\nPriority Queue: ";
    priority_queue<Huffman *, vector<Huffman *>, Compare> temphuff = huff;

    while (!temphuff.empty()) {
        cout << temphuff.top()->keyHuff->word << "(" << temphuff.top()->keyHuff->occurrences << ") ";
        temphuff.pop();
    }
    cout << endl << endl;
}

// esvazia a árvore

void clearHuffmanTree(Huffman *rootH) {

    if (rootH) {
        clearHuffmanTree(rootH->leftH);
        clearHuffmanTree(rootH->rightH);
        delete rootH;
    }
}

// funções de output

void outHuffPrint(Huffman *rootH, int array[], int top, ofstream &outT) {

    if (rootH->leftH) {
        array[top] = 0;
        outHuffPrint(rootH->leftH, array, top + 1, outT);
    }

    if (rootH->rightH) {
        array[top] = 1;
        outHuffPrint(rootH->rightH, array, top + 1, outT);
    }

    if (!rootH->leftH && !rootH->rightH) {

        outT << rootH->keyHuff->word << " ";

        for (int i = 0; i < top; i++)
            outT << array[i];
        outT << ", ";
    }
}

void outHuff(Huffman *rootH, int array[], int top) {

    if (rootH == nullptr) return;

    ofstream outT;
    outT.open("output.txt", ios::app);

    outT << endl << "HUFFMAN" << endl;
    outT << "[ ";

    outHuffPrint(rootH, array, top, outT);

    outT << "]" << endl << endl;

    outT.close();
}