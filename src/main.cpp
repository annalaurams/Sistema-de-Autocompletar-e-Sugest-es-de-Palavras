#include "./include/tree.hpp"
#include "./include/document.hpp"


using namespace std;
using namespace std::chrono;

int main() {

    auto start = chrono::steady_clock::now();

    unordered_map<string, WordInfo> glossaryStopWords;

    string s;
    int lenght = 0, i = 0;

    ifstream fileStopWords;
    fileStopWords.open("data/stopwords.txt", ios::in);

    while (fileStopWords) {
        getline(fileStopWords, s, '\n');
        addStopWord(glossaryStopWords, s);
    }

    fileStopWords.close();

    search(lenght, i, glossaryStopWords);
    outEnd();

    auto end = chrono::steady_clock::now();


    cout << "\nTEMPO DE EXECUÇÃO TOTAL DO PROGRAMA: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl << endl;

    return 0;
}
