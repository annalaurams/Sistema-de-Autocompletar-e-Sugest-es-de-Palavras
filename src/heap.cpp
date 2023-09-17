#include "./include/document.hpp"

// insere primeiros k elementos

void insertK(unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i) {

    removeErro(glossary);

    WordInfo info;
    int aux = 0;

    for (const auto &entry : glossary) {

        if (aux >= K)  break;

        info.word = entry.first;
        info.occurrences = entry.second.occurrences;

        aux_heap.push_back(info);

        aux++;
    }

    heapify(aux_heap, lenght, i);
    finaleHash(glossary, aux_heap, lenght, i);
}

void heapify(vector<WordInfo> &aux_heap, int &lenght, int i) {

    int left = 2 * i + 1; // nó esquedo
    int right = 2 * i + 2; // nó direito

    int aux = i;

    lenght = aux_heap.size();

    if (left < lenght && aux_heap[left].occurrences < aux_heap[aux].occurrences)
        aux = left;

    if (right < lenght && aux_heap[right].occurrences < aux_heap[aux].occurrences)
        aux = right;

    if (aux != i) {
        swap(aux_heap[i], aux_heap[aux]);
        heapify(aux_heap, lenght, aux);
    }
}

// compara o restante dos elementos da hash com o heap

void finaleHash(const unordered_map<string, WordInfo> &glossary, vector<WordInfo> &aux_heap, int &lenght, int i) {

    int position = 0;
    int start = K;

    auto it = glossary.begin();

    for (; it != glossary.end() && position < start + 1; ++it, ++position) {} // Começar a partir de K

    for (; it != glossary.end(); ++it) {

        int current = it->second.occurrences;

        WordInfo info;

        info.word = it->first;
        info.occurrences = it->second.occurrences;

        if (current > aux_heap[0].occurrences) {
            aux_heap[0] = info;
            heapify(aux_heap, lenght, i);
        }
    }
}

void printHeap(vector<WordInfo> &aux_heap) {

    cout << "\n-------------- HEAP --------------\n\n";

    for (const WordInfo &info : aux_heap) {
        cout << info.word << ": " << info.occurrences << endl;
    }
}

// verifica se a palavra exise no heap

void existsInHeap(vector<WordInfo> &heap, string &input, int lenght, int i, vector<WordInfo> &aux_heap) {

    int controle = 1;

    heap = aux_heap;

    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].word == input) {

            heap.erase(heap.begin() + i);
            controle = 2;
        }
    }

    if (controle == 1) heap.erase(heap.begin());

    heapify(heap, lenght, i);
}