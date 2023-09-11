#include "./include/tree.hpp"
#include "./include/document.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {


    clock_t startTime, endTime;
    startTime = clock();

    unordered_map<string, WordInfo> glossaryStopWords;

    string s;
    int lenght = 0, i = 0;

    ifstream fileStopWords;
    fileStopWords.open("data/stopwords.txt", ios::in);

    while (fileStopWords){
        getline(fileStopWords, s, '\n');
        addStopWord(glossaryStopWords, s);
    }

    fileStopWords.close();

    search(lenght, i, glossaryStopWords);
    outEnd();



 
    endTime = clock();
    clock_t elapsedTime = endTime - startTime;
    double elapsedTimeMs = ((double)elapsedTime/CLOCKS_PER_SEC)*1000;
    cout << "\nTEMPO DE EXECUÇÃO TIME.H: " << elapsedTimeMs << " ms " << endl;
    cout << endl;

    return 0;
}
