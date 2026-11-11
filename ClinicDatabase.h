#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include "PatientRecord.h"

namespace scapms {
namespace model {

// Represents an action that can be undone
enum class AdminAction { ADD, DELETE, MODIFY };

struct AdminOperation {
    AdminAction action;
    std::string targetPatientId;
};

class ClinicDatabase {
private:
    // 1. Vector: Stores all registered patients in the system
    std::vector<PatientRecord*> patientRecords;

    // 2. Queue: Manages the First-In-First-Out (FIFO) waiting room
    std::queue<PatientRecord*> waitingQueue;

    // 3. Stack: Manages the Last-In-First-Out (LIFO) undo history
    std::stack<AdminOperation> undoStack;

    // 4. Fixed Array: Caches the 10 most recently accessed records
    PatientRecord* recentPatients[10];
    int cacheIndex;

public:
    ClinicDatabase();
    ~ClinicDatabase();
    const std::vector<PatientRecord*>& getPatients() const;
    std::vector<PatientRecord*>& getPatientsMutable();

    // Vector operations
    void addPatientRecord(PatientRecord* patient);
    
    // Queue operations
    void addPatientToQueue(PatientRecord* patient);
    PatientRecord* callNextPatient();

    // Stack operations
    void recordAdminOperation(AdminAction action, const std::string& patientId);
    void undoLastOperation();

    // Array operations
    void accessPatient(PatientRecord* patient);
};

} // namespace model
} // namespace scapms