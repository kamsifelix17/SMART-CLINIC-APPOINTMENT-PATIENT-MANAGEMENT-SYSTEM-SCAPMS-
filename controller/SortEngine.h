#pragma once
#include <vector>
#include "../PatientRecord.h"

namespace scapms {
namespace controller {

class SortEngine {
public:
    // Sorts patients alphabetically by Name
    static void selectionSortByName(std::vector<model::PatientRecord*>& records);

    // Sorts patients numerically/alphabetically by ID
    static void insertionSortByID(std::vector<model::PatientRecord*>& records);
};

} // namespace controller
} // namespace scapms