#include "ClinicDatabase.h"
#include <iostream>

namespace scapms {
namespace model {

ClinicDatabase::ClinicDatabase() : cacheIndex(0) {
    // Initialize the fixed array with null pointers
    for (int i = 0; i < 10; ++i) {
        recentPatients[i] = nullptr;
    }
}

ClinicDatabase::~ClinicDatabase() {
    // Clean up memory to prevent leaks
    for (auto* patient : patientRecords) {
        delete patient;
    }
}

// --- std::vector Logic ---
void ClinicDatabase::addPatientRecord(PatientRecord* patient) {
    patientRecords.push_back(patient);
    recordAdminOperation(AdminAction::ADD, patient->getPatientID());
}

// --- std::queue Logic ---
void ClinicDatabase::addPatientToQueue(PatientRecord* patient) {
    waitingQueue.push(patient);
    std::cout << patient->getName() << " added to the waiting queue.\n";
}

PatientRecord* ClinicDatabase::callNextPatient() {
    if (waitingQueue.empty()) {
        std::cout << "The waiting queue is empty.\n";
        return nullptr;
    }
    // Retrieve the first patient in line, then remove them from the queue
    PatientRecord* nextPatient = waitingQueue.front();
    waitingQueue.pop();
    return nextPatient;
}

// --- std::stack Logic ---
void ClinicDatabase::recordAdminOperation(AdminAction action, const std::string& patientId) {
    AdminOperation op = {action, patientId};
    undoStack.push(op);
}

void ClinicDatabase::undoLastOperation() {
    if (undoStack.empty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }
    
    AdminOperation lastOp = undoStack.top();
    undoStack.pop();
    
    std::cout << "Undoing last operation on Patient ID: " << lastOp.targetPatientId << "\n";
    // Detailed reversal logic (like restoring a deleted record) will be connected here later
}

// --- Fixed Array Logic ---
void ClinicDatabase::accessPatient(PatientRecord* patient) {
    // Add to cache, overriding oldest entry if the array is full (circular array logic)
    recentPatients[cacheIndex] = patient;
    cacheIndex = (cacheIndex + 1) % 10; 
}

const std::vector<PatientRecord*>& ClinicDatabase::getPatients() const {
    return patientRecords;
}

std::vector<PatientRecord*>& ClinicDatabase::getPatientsMutable() {
    return patientRecords;
}

} // namespace model
} // namespace scapms