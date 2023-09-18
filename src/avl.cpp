#include "./include/avl.hpp"

int cont = 0;

// AVL

// calcula a altura da subárvore

int height(AVL *alt) {
  if (alt == nullptr)
    return 0;
  return alt->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

AVL *newNode(WordInfo data) {

  AVL *node = new AVL();

  node->keyAVL = data;
  node->leftAVL = nullptr;
  node->rightAVL = nullptr;
  node->height = 0;

  return (node);
}

// rotação simples para direita

AVL *rightRotate(AVL *y) {

  AVL *LR = y->leftAVL;
  AVL *T2 = LR->rightAVL;

  y->leftAVL = T2;

  LR->rightAVL = y;

  y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;
  LR->height = max(height(LR->leftAVL), y->height) + 1;

  return LR;
}

// rotação simples para esquerda


AVL *leftRotate(AVL *y) {

  AVL *LR = y->rightAVL;
  AVL *T2 = LR->leftAVL;

  y->rightAVL = T2;

  LR->leftAVL = y;

  y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;
  LR->height = max(height(LR->rightAVL), y->height) + 1;

  return LR;
}

// calcula a diferença de altura

int getBalance(AVL *alt) {

  if (alt == nullptr) return 0;

  return height(alt->leftAVL) - height(alt->rightAVL);
}

// insere os elemenos na árvore

AVL *insertAvl(AVL *node, WordInfo data) {

  if (node == nullptr) {
    return (newNode(data));
  }

  if (data.word != node->keyAVL.word) {

    if (data.occurrences <= node->keyAVL.occurrences) {

      node->leftAVL = insertAvl(node->leftAVL, data);

      if (height(node->leftAVL) - height(node->rightAVL) == 2) {
        if (data.occurrences <= node->leftAVL->keyAVL.occurrences) {
          node = rightRotate(node);
        } else {
          node->leftAVL = leftRotate(node->leftAVL);
          node = rightRotate(node);
        }
      }
    }

    if (data.occurrences > node->keyAVL.occurrences) {
      node->rightAVL = insertAvl(node->rightAVL, data);

      if (height(node->rightAVL) - height(node->leftAVL) == 2) {
        if (data.occurrences > node->rightAVL->keyAVL.occurrences) {
          node = leftRotate(node);
        } else {
          node->rightAVL = rightRotate(node->rightAVL);
          node = leftRotate(node);
        }
      }
    }
  }

  node->height = max(height(node->leftAVL), height(node->rightAVL)) + 1;

  return node;
}

// imprimi a árvore

void printAVL(AVL *rootAVL) {

  if (rootAVL != nullptr) {

    printAVL(rootAVL->leftAVL);
    printAVL(rootAVL->rightAVL);
    cout << rootAVL->keyAVL.word << ": " << rootAVL->keyAVL.occurrences << endl;
  }

}


void avl(vector<WordInfo>heap) {

  //auto startA = chrono::steady_clock::now();

  AVL *rootAVL = nullptr;

  for (const auto &wordInfo : heap) {

    rootAVL = insertAvl(rootAVL, wordInfo);
  }
  cont++;
  //printAVL(rootAVL);
  outAVL(rootAVL);

  removeAllAVL(rootAVL);
 // auto endA = chrono::steady_clock::now();
  // cout << "\nTEMPO AVL: " << chrono::duration_cast<chrono::nanoseconds>(endA - startA).count() << " ns" << endl << endl;

}

// esvazia a árvore

void removeAllAVL(AVL *&rootAVL) {

  if (rootAVL == NULL) return;

  removeAllAVL(rootAVL->leftAVL);
  removeAllAVL(rootAVL->rightAVL);

  delete rootAVL;
}

// funções de output

void outPrintAVL(AVL *rootAVL, ofstream &outT) {

  if (rootAVL == nullptr) return;

  outPrintAVL(rootAVL->leftAVL, outT);
  outPrintAVL(rootAVL->rightAVL, outT);
  outT << rootAVL->keyAVL.word << ": " << rootAVL->keyAVL.occurrences << " ";

}

void outAVL(AVL *rootAVL) {

  if (rootAVL == nullptr) return;

  ofstream outT;
  outT.open("output.txt", ios::app);

  outT << endl << "AVL" << endl;
  outT << "[ ";

  outPrintAVL(rootAVL, outT);

  outT << "]" << endl;

  outT.close();
}
