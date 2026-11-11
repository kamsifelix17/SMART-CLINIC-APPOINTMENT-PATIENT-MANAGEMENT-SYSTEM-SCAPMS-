#pragma once
#include <vector>
#include <string>

namespace scapms {
namespace model {
class PatientRecord;
}

namespace controller {

class SearchEngine {
public:
    // Linear search by exact Patient ID (Used when data is unsorted)
    static model::PatientRecord* linearSearchByID(const std::vector<model::PatientRecord*>& records, const std::string& targetID);

    // Binary search by Patient ID (Used only after records are sorted)
    static model::PatientRecord* binarySearchByID(const std::vector<model::PatientRecord*>& records, const std::string& targetID);

    // Recursive search by Patient Name (Used when data is unsorted)
    static model::PatientRecord* recursiveSearchByName(const std::vector<model::PatientRecord*>& records, const std::string& targetName, int index = 0);
};

} // namespace controller
} // namespace scapms