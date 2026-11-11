#include "SortEngine.h"

namespace scapms {
namespace controller {

void SortEngine::selectionSortByName(std::vector<model::PatientRecord*>& records) {
    int n = records.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (records[j]->getName() < records[minIndex]->getName()) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // Swap the pointers without using std::swap
            model::PatientRecord* temp = records[i];
            records[i] = records[minIndex];
            records[minIndex] = temp;
        }
    }
}

void SortEngine::insertionSortByID(std::vector<model::PatientRecord*>& records) {
    int n = records.size();
    for (int i = 1; i < n; ++i) {
        model::PatientRecord* key = records[i];
        int j = i - 1;

        while (j >= 0 && records[j]->getPatientID() > key->getPatientID()) {
            records[j + 1] = records[j];
            j = j - 1;
        }
        records[j + 1] = key;
    }
}

} // namespace controller
} // namespace scapms