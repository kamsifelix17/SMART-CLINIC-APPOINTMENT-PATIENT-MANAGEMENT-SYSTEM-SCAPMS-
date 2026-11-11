#include "./SearchEngine.h"
#include "../PatientRecord.h"

namespace scapms {
namespace controller {

model::PatientRecord* SearchEngine::linearSearchByID(const std::vector<model::PatientRecord*>& records, const std::string& targetID) {
    for (size_t i = 0; i < records.size(); ++i) {
        if (records[i]->getPatientID() == targetID) {
            return records[i];
        }
    }
    return nullptr; // Patient not found
}

model::PatientRecord* SearchEngine::binarySearchByID(const std::vector<model::PatientRecord*>& records, const std::string& targetID) {
    int left = 0;
    int right = records.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        std::string midID = records[mid]->getPatientID();

        if (midID == targetID) {
            return records[mid];
        }
        
        if (midID < targetID) {
            left = mid + 1; // Search the right half
        } else {
            right = mid - 1; // Search the left half
        }
    }
    return nullptr; // Patient not found
}

model::PatientRecord* SearchEngine::recursiveSearchByName(const std::vector<model::PatientRecord*>& records, const std::string& targetName, int index) {
    // Base case 1: Reached the end of the vector without finding a match
    if (index >= records.size()) {
        return nullptr;
    }
    
    // Base case 2: Match found at the current index
    if (records[index]->getName() == targetName) {
        return records[index];
    }
    
    // Recursive step: Call the function again, advancing to the next index
    return recursiveSearchByName(records, targetName, index + 1);
}

} // namespace controller
} // namespace scapms