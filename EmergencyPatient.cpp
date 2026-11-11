// EmergencyPatient.cpp
#include "EmergencyPatient.h"
#include <iostream>

namespace scapms {
namespace model {

EmergencyPatient::EmergencyPatient(std::string id, std::string n, int a, std::string contact, std::string severity)
    : PatientRecord(std::move(id), std::move(n), a, std::move(contact)), severityLevel(std::move(severity)) {}

void EmergencyPatient::displayPatientCategory() const {
    std::cout << "[Emergency Patient] - HIGH PRIORITY. Severity: " << severityLevel << "\n";
}

bool EmergencyPatient::scheduleAppointment(const std::string& date, const std::string& time) {
    // Emergency patients might override standard scheduling rules
    std::cout << "URGENT: Emergency slot allocated for " << date << " at " << time << "\n";
    return true;
}

bool EmergencyPatient::cancelAppointment() {
    std::cout << "Emergency appointment cancelled. (Warning: Ensure patient stability)\n";
    return true;
}

} // namespace model
} // namespace scapms