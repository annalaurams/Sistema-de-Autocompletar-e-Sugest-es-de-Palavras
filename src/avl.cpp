#include "./include/avl.hpp"

int cont = 0;

// AVL

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
  // node->vetor.push_back(data.word);
  node->leftAVL = nullptr;
  node->rightAVL = nullptr;
  node->height = 0;

  return (node);
}

AVL *rightRotate(AVL *y) {

  AVL *LR = y->leftAVL;
  AVL *T2 = LR->rightAVL;

  y->leftAVL = T2;

  LR->rightAVL = y;

  y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;
  LR->height = max(height(LR->leftAVL), y->height) + 1;

  return LR;
}


AVL *leftRotate(AVL *y) {

  AVL *LR = y->rightAVL;
  AVL *T2 = LR->leftAVL;

  y->rightAVL = T2;

  LR->leftAVL = y;

  y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;
  LR->height = max(height(LR->rightAVL), y->height) + 1;

  return LR;
}

int getBalance(AVL *alt) {

  if (alt == nullptr) return 0;

  return height(alt->leftAVL) - height(alt->rightAVL);
}

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

void printAVL(AVL *rootAVL) {

  if (rootAVL == nullptr)
    return;

  cout << endl << endl;

  int height = 0;
  queue<AVL *> x;
  x.push(rootAVL);

  while (!x.empty()) {
    int levelSize = x.size();

    while (levelSize > 0) {
      AVL *current = x.front();
      x.pop();

      //cout << current->keyAVL.word << ": " << current->keyAVL.occurrences << " ";

      cout << current->keyAVL.word << ": " << current->keyAVL.occurrences;

      if (current->leftAVL != nullptr)
        x.push(current->leftAVL);

      if (current->rightAVL != nullptr)
        x.push(current->rightAVL);

      levelSize--;
    }
    cout << endl;

    height++;
  }

  // cout << endl;

}

void posordemAVL(AVL *rootAVL) {

  if (rootAVL != nullptr) {

    posordemAVL(rootAVL->leftAVL);
    posordemAVL(rootAVL->rightAVL);
    cout << rootAVL->keyAVL.word << ": " << rootAVL->keyAVL.occurrences << endl;
  }
}

void avl(vector<WordInfo>heap){

  auto startA = chrono::steady_clock::now();
  
  AVL *rootAVL = nullptr;

  for (const auto &wordInfo : heap) {

    rootAVL = insertAvl(rootAVL, wordInfo);
  }
  cont++;
  //printAVL(rootAVL);
  outAVL(rootAVL);

  removeAllAVL(rootAVL);
  auto endA = chrono::steady_clock::now();
  cout << "\nTEMPO AVL: " << chrono::duration_cast<chrono::nanoseconds>(endA - startA).count() << " ns" << endl << endl;

}

void removeAllAVL(AVL *&rootAVL) {

  if (rootAVL == NULL) return;

  removeAllAVL(rootAVL->leftAVL);
  removeAllAVL(rootAVL->rightAVL);

  delete rootAVL;
}

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
