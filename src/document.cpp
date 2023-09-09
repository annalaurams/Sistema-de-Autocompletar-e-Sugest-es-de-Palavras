#include "tree.hpp"
#include "document.hpp"

using namespace std;

int Frequy = 0;

// stop words

void addStopWord(unordered_map<string, WordInfo> &glossaryStopWords, string &s){

  WordInfo newWord;
  newWord.occurrences = 1;

  if (s != ""){
    if (glossaryStopWords.find(s) != glossaryStopWords.end()){}
    
    else glossaryStopWords[s] = newWord;
  }
  s = "";
}

void existentWord(unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords){

  for (const auto& entry : glossaryStopWords) {
      const string& stopWord = entry.first;
      
      if (glossary.find(stopWord) != glossary.end()) 
        glossary.erase(stopWord);
  }
}

// processa os textos 

void processingFiles(unordered_map<string, WordInfo> &glossary, string &text){

  string str;
  ifstream file; 

  file.open(text, ios::in);

  if (file.is_open()){

    char c = '\0';
    str = "";

    while (file.get(c))
      fileReading(c, str, glossary);

    file.close();
  }
  else cout << "\nErro ao abrir o arquivo.\n";
}

void fileReading(char c, string &str, unordered_map<string, WordInfo> &glossary){

  switch (c){

    case ' ':
      cases(str, glossary);
      break;

    case '\n':
      cases(str, glossary);
      break;

    case '.':
      cases(str, glossary);
      break;

    case '!':
      cases(str, glossary);
      break;

    case '?':
      cases(str, glossary);
      break;

    case ',':
      cases(str, glossary);
      break;

    case ':':
      cases(str, glossary);
      break;

    case ';':
      cases(str, glossary);
      break;

    case '[':
      cases(str, glossary);
      break;

    case ']':
      cases(str, glossary);
      break;

    case '(':
      cases(str, glossary);
      break;

    case ')':
      cases(str, glossary);
      break;

    case '"':
      cases(str, glossary);
      break;

    case '+':
      cases(str, glossary);
      break;

    case '/':
      cases(str, glossary);
      break;

      case '\x9D':
        break;

      default:
      if(str == "--" || str == "^" || str == " — " || str == " —" || str == "—" || str == "”" || str == "“" || str == "-”" || str == "——")
        str = "";

      if((c != '-') && (c != '"') && (c != '\xE2') && (c != '\x80') && (c != '\x9D') && (c != '\x9C') && (c != '\x94'))
        str+=tolower(c);

      break;
    }
}

void removeErro(unordered_map<string, WordInfo> &glossary){

  for (auto it = glossary.begin(); it != glossary.end();) {
        if (it->first.empty() || it->first == "-") {
            
            it = glossary.erase(it);
            it->second.occurrences;
            it = glossary.erase(it);

        } else {
            ++it;
        }
    }
}

string accentuation(const string &word){

  string result = word;
  int cont = 0;

  string acentos = "áàâãäéèêëíìîïóòôõöúùûüç"; 

  for (int i = 0; i < (int)result.length(); ++i){

    char c = result[i];
    int aux = acentos.find(c);

    if (aux) cont++;
  }

  return result;
}

// identifica as palavras e conta as ocorrências

void cases(string &str, unordered_map<string, WordInfo> &glossary){

  WordInfo newWord;
  newWord.occurrences = 1;
  
  string element;

  if(glossary.find(str) != glossary.end()) 
    glossary[str].occurrences++;

  else if (str != ""){
    element = accentuation(str);
    glossary[element] = newWord;
  }

  str = "";
}

// imprimi o glossário

void printGlossary(unordered_map<string,WordInfo> &glossary){

  for(auto& [key, word] : glossary){
    cout << key << ": " << word.occurrences << endl;
  }
}

//  heap

void insertK(unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i){

  removeErro(glossary);

  WordInfo info;
  int aux = 0;

  for (const auto& entry : glossary){

      if(aux >= K)  break;
      
      info.word = entry.first;
      info.occurrences = entry.second.occurrences;

      aux_heap.push_back(info);

      aux++;
  }

  heapify(aux_heap, lenght, i);
  finaleHash(glossary, aux_heap, lenght, i);
  //printHeap(heap);
}

void heapify(vector<WordInfo> &aux_heap, int &lenght, int i){
 
  int left = 2 * i + 1; // nó esquedo
  int right = 2 * i + 2; // nó direito

  int aux = i;
  
  lenght = aux_heap.size();

  if (left < lenght && aux_heap[left].occurrences < aux_heap[aux].occurrences)
      aux = left;

  if (right < lenght && aux_heap[right].occurrences < aux_heap[aux].occurrences)
      aux = right;

  if (aux != i){
      swap(aux_heap[i], aux_heap[aux]);
      heapify(aux_heap, lenght, aux);
  }
}

void finaleHash(const unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i){

    int position = 0;
    int start = K;
    
    auto it = glossary.begin(); 

    for (; it != glossary.end() && position < start + 1; ++it, ++position) {} // Começar a partir de K 

    for (; it != glossary.end(); ++it){

        int current = it->second.occurrences; 

         WordInfo info;

         info.word = it->first;
         info.occurrences = it->second.occurrences;

         if (current > aux_heap[0].occurrences){
          aux_heap[0] = info;
          heapify(aux_heap, lenght, i);
        }
    } 
}

void printHeap(vector<WordInfo> &aux_heap){

  cout << "\n-------------- HEAP --------------\n\n";

  for (const WordInfo& info : aux_heap) {
          cout << info.word << ": " << info.occurrences << endl;
  }
}

void existsInHeap(vector<WordInfo> &heap, string &input, int lenght, int i, vector<WordInfo> &aux_heap){

    int controle = 1;

    heap = aux_heap;

    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].word == input){

            heap.erase(heap.begin() + i);
            controle = 2;  
        }
    }

    if(controle == 1) heap.erase (heap.begin());
    
    heapify(heap, lenght, i);
}

void nameFile(list<string>&nameFiles){

    for (auto &t : filesystem::directory_iterator("data")){
        string text = t.path().string();

        if ((text == "data/stopwords.txt") || (text == "data/input.txt")) continue;

        nameFiles.push_back(text);
  }

//   cout << "\nTamanho Lista: " << nameFiles.size()  << endl;
//   for (const string& fileName : nameFiles) {
//         cout << fileName << " "; // Imprime cada elemento da lista
//     }
//     cout << endl;
}

void inputFile(string &input, list<string> &wordInput){

    ifstream inputFile("data/input.txt");

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo input.txt" << endl;
        return;
    }

    string line;

    while (getline(inputFile, line)) {
        wordInput.push_back(line);
    }

    inputFile.close();

    list<string> q = wordInput;

//   cout << "\nTamanho Fila: " << wordInput.size()  << endl;

//   while (!q.empty()) {
//         cout << q.front() << endl; // Imprime o elemento da frente da fila
//         q.pop(); 
//     }
    //cout << endl;
}

bool existGlossary(unordered_map<string, WordInfo> &glossary, string &input){

    auto it = glossary.find(input);

   if(it != glossary.end()) {
    
    Frequy = it->second.occurrences;

    if(Frequy > 0)
      return true; // Palavra encontrada
  }
  return false; // Palavra não encontrada
}


void search(int &lenght, int i, unordered_map<string, WordInfo> &glossaryStopWords){

  No* root = NULL;
  
  unordered_map<string, WordInfo> glossary;

  string str, text, input;

  vector<WordInfo> heap;
  vector<WordInfo> aux_heap;

  list<string>nameFiles;
  nameFile(nameFiles);

  list<string> wordInput;
  inputFile(input, wordInput);

  outputCreate();
  
  for(string name : nameFiles){

    string aux = name;

    processingFiles(glossary, aux);

    existentWord(glossary, glossaryStopWords);
    
    aux.erase(0, 5);
    outTheme(aux);

    insertK(glossary, aux_heap, lenght, i);

    for(string palavra : wordInput){

      string input = palavra;
    
      if(existGlossary(glossary, input)){

        existsInHeap(heap, input, lenght, i, aux_heap);

        output(input);

        binaryTree(heap, root);
        avl(heap);
        HuffmanCodes(heap);

        Frequy = 0;
    }

    }
    glossary.clear();
    aux_heap.clear();
  }

}

// AVL

int height(AVL* alt) {
    if (alt == nullptr)
        return 0;
    return alt->height;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

AVL* newNode(WordInfo data){

    AVL* node = new AVL();

    node->keyAVL = data;
    node->leftAVL = nullptr;
    node->rightAVL = nullptr;
    node->height = 1; 

    return (node);
}

AVL* rightRotate(AVL* y){

    AVL* LR = y->leftAVL;
    AVL* T2 = LR->rightAVL;

    LR->rightAVL = y;
    y->leftAVL = T2;

    y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;
    LR->height = max(height(LR->leftAVL), height(LR->rightAVL)) + 1;

    return LR;
}

AVL* leftRotate(AVL* LR){

    AVL* y = LR->rightAVL;
    AVL* T2 = y->leftAVL;

    y->leftAVL = LR;
    LR->rightAVL = T2;

    LR->height = max(height(LR->leftAVL), height(LR->rightAVL)) + 1;
    y->height = max(height(y->leftAVL), height(y->rightAVL)) + 1;

    return y;
}

int getBalance(AVL* alt){

    if (alt == nullptr) return 0;

    return height(alt->leftAVL) - height(alt->rightAVL);
}

AVL* insertAvl(AVL* node, WordInfo data){

    if (node == nullptr) return (newNode(data));

    if (data.occurrences < node->keyAVL.occurrences)
        node->leftAVL = insertAvl(node->leftAVL, data);

    else if (data.occurrences > node->keyAVL.occurrences)
        node->rightAVL = insertAvl(node->rightAVL, data);

    else
        node->leftAVL = insertAvl(node->leftAVL, data);


    if(node->leftAVL == nullptr || node->rightAVL == nullptr) return node;

    node->height = 1 + max(height(node->leftAVL), height(node->rightAVL));

    int balance = getBalance(node);

    if (balance > 1 && data.occurrences < node->leftAVL->keyAVL.occurrences)
        return rightRotate(node);

    if (balance < -1 && data.occurrences > node->rightAVL->keyAVL.occurrences)
        return leftRotate(node);

    if (balance > 1 && data.occurrences > node->leftAVL->keyAVL.occurrences) {
        node->leftAVL = leftRotate(node->leftAVL);
        return rightRotate(node);
    }

    if (balance < -1 && data.occurrences < node->rightAVL->keyAVL.occurrences) {
        node->rightAVL = rightRotate(node->rightAVL);
        return leftRotate(node);
    }

    return node;
}

void printAVL(AVL* rootAVL){

    if (rootAVL != nullptr){
        
      printAVL(rootAVL->leftAVL);
      cout << rootAVL->keyAVL.word << ": " << rootAVL->keyAVL.occurrences << endl;
      printAVL(rootAVL->rightAVL);

    }
}

void avl(vector<WordInfo>heap){

    AVL *rootAVL = NULL;

    for (const WordInfo& wordInfo : heap) {
        rootAVL = insertAvl(rootAVL, wordInfo);
    }

    outAVL(rootAVL);
    removeAllAVL(rootAVL);
}

void removeAllAVL(AVL *&rootAVL){

  if (rootAVL == NULL) return;

  removeAllAVL(rootAVL->leftAVL);
  removeAllAVL(rootAVL->rightAVL);

  delete rootAVL;
}

void outPrintAVL(AVL *rootAVL, ofstream& outT){

   if (rootAVL == nullptr) return;

  outPrintAVL(rootAVL->leftAVL, outT);

  outT << rootAVL->keyAVL.word << ": " << rootAVL->keyAVL.occurrences << ", ";

  outPrintAVL(rootAVL->rightAVL, outT);
}

void outAVL(AVL* rootAVL){

    if (rootAVL == nullptr) return;

    ofstream outT;
    outT.open("output.txt", ios::app);

    outT  << endl << "AVL" << endl;
    outT  << "[ ";

    outPrintAVL(rootAVL, outT);

    outT << "]" << endl;

    outT.close();
}

void outTheme(string &aux){
  ofstream outFile("output.txt", ios::app);
  outFile << "================================================================================================================================================================================================================================================================================================================================" << endl;                            
  outFile << "> TEXTO " << setw(15)	<< aux << endl;
  outFile << "================================================================================================================================================================================================================================================================================================================================" << endl;                            
  outFile.close();
}

void output(string &firstWord){

  ofstream outFile("output.txt", ios::app);
  outFile << "__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;                                 
  outFile << "| PALAVRA   "<< setw(15) << firstWord << setw(10) << " | " << setw(10) <<  "FREQUÊNCIA   " << setw(15) << Frequy << endl;
  outFile << "__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;                            
  outFile.close();
}

void outputCreate(){

  ofstream outFile;
  outFile.open("output.txt");
  outFile.close();

}

void outEnd(){

  ofstream outFile("output.txt", ios::app);
  outFile << "=====================================================================================================================================================================================================================================================================================================================================" << endl;                            
  outFile.close();
}