#include "./include/avl.hpp"
#include "./include/tree.hpp"
#include "./include/huffman.hpp"
#include "./include/document.hpp"

using namespace std;

int Frequy = 0;

// stop words

void addStopWord(unordered_map<string, WordInfo> &glossaryStopWords, string &s) {

  WordInfo newWord;
  newWord.occurrences = 1;

  if (s != "") {
    if (glossaryStopWords.find(s) != glossaryStopWords.end()) {}

    else glossaryStopWords[s] = newWord;
  }
  s = "";
}

void existentWord(unordered_map<string, WordInfo> &glossary, unordered_map<string, WordInfo> &glossaryStopWords) {

  for (const auto &entry : glossaryStopWords) {
    const string &stopWord = entry.first;

    if (glossary.find(stopWord) != glossary.end())
      glossary.erase(stopWord);
  }
}

// processa os textos

void processingFiles(unordered_map<string, WordInfo> &glossary, string &text) {

  string str;
  ifstream file;

  file.open(text, ios::in);

  if (file.is_open()) {

    char c = '\0';
    str = "";

    while (file.get(c))
      fileReading(c, str, glossary);

    file.close();
  } else cout << "\nErro ao abrir o arquivo.\n";
}

void fileReading(char c, string &str, unordered_map<string, WordInfo> &glossary) {

  switch (c) {

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
    if (str == "--" || str == "^" || str == " — " || str == " —" || str == "—" || str == "”" || str == "“" || str == "-”" || str == "——")
      str = "";

    if ((c != '-') && (c != '"') && (c != '\xE2') && (c != '\x80') && (c != '\x9D') && (c != '\x9C') && (c != '\x94'))
      str += tolower(c);

    break;
  }

}

void removeErro(unordered_map<string, WordInfo> &glossary) {

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

string accentuation(const string &word) {

  string result = word;
  int cont = 0;

  string acentos = "áàâãäéèêëíìîïóòôõöúùûüç";

  for (int i = 0; i < (int)result.length(); ++i) {

    char c = result[i];
    int aux = acentos.find(c);

    if (aux) cont++;
  }

  return result;
}

// identifica as palavras e conta as ocorrências

void cases(string &str, unordered_map<string, WordInfo> &glossary) {

  WordInfo newWord;
  newWord.occurrences = 1;

  string element;

  if (glossary.find(str) != glossary.end())
    glossary[str].occurrences++;

  else if (str != "") {
    element = accentuation(str);
    glossary[element] = newWord;
  }

  str = "";
}

// imprimi o glossário

void printGlossary(unordered_map<string, WordInfo> &glossary) {

  for (auto &[key, word] : glossary) {
    cout << key << ": " << word.occurrences << endl;
  }
}

// salva o nome dos arquivos em uma lista

void nameFile(list<string> &nameFiles) {

  for (auto &t : filesystem::directory_iterator("data")) {
    string text = t.path().string();

    if ((text == "data/stopwords.txt") || (text == "data/input.txt")) continue;

    nameFiles.push_back(text);
  }
}
// salva todas as palavras de busca em uma lista

void inputFile(string &input, list<string> &wordInput) {

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
}

// verifica se a palavra existe no glossário

bool existGlossary(unordered_map<string, WordInfo> &glossary, string &input) {

  auto it = glossary.find(input);

  if (it != glossary.end()) {

    Frequy = it->second.occurrences;

    if (Frequy > 0)
      return true; // Palavra encontrada
  }
  return false; // Palavra não encontrada
}

// coloca em ordem as funções para o funcionamento do programa

void search(int &lenght, int i, unordered_map<string, WordInfo> &glossaryStopWords) {

  No *root = NULL;

  unordered_map<string, WordInfo> glossary;

  string str, text, input;

  vector<WordInfo> heap;
  vector<WordInfo> aux_heap;

  list<string>nameFiles;
  nameFile(nameFiles);

  list<string> wordInput;
  inputFile(input, wordInput);

  outputCreate();

  for (string name : nameFiles) {

    string aux = name;

    //cout << "\n\nTEXTO: " << aux << endl;

    processingFiles(glossary, aux);

    existentWord(glossary, glossaryStopWords);

    aux.erase(0, 5);
    outTheme(aux);

    for (string palavra : wordInput) {

      string input = palavra;

      if (existGlossary(glossary, input)) {

        insertK(glossary, aux_heap, lenght, i);
        existsInHeap(heap, input, lenght, i, aux_heap);

        output(input);

        //printHeap(heap);

        //cout << "\n\n\tÁRVORE\n\n";
        binaryTree(heap, root);

        //cout << "\n\n\tAVL\n\n";
        avl(heap);

        //cout << "\n\n\tHUFFMAN\n\n";
        HuffmanCodes(heap);

        Frequy = 0;
      }

      aux_heap.clear();
      heap.clear();
    }
    glossary.clear();
  }
}

// funções de output

void outTheme(string &aux) {
  ofstream outFile("output.txt", ios::app);
  outFile << "================================================================================================================================================================================================================================================================================================================================" << endl;
  outFile << "> TEXTO " << setw(15) << aux << endl;
  outFile << "================================================================================================================================================================================================================================================================================================================================" << endl;
  outFile.close();
}

void output(string &firstWord) {

  ofstream outFile("output.txt", ios::app);
  outFile << "__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
  outFile << "| PALAVRA   " << setw(15) << firstWord << setw(10) << " | " << setw(10) << "FREQUÊNCIA   " << setw(15) << Frequy << endl;
  outFile << "__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________" << endl;
  outFile.close();
}

void outputCreate() {

  ofstream outFile;
  outFile.open("output.txt");
  outFile.close();

}

void outEnd() {

  ofstream outFile("output.txt", ios::app);
  outFile << "=====================================================================================================================================================================================================================================================================================================================================" << endl;
  outFile.close();
}