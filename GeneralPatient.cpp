// GeneralPatient.cpp
#include "GeneralPatient.h"
#include <iostream>

namespace scapms {
namespace model {

GeneralPatient::GeneralPatient(std::string id, std::string n, int a, std::string contact)
    : PatientRecord(std::move(id), std::move(n), a, std::move(contact)) {}

void GeneralPatient::displayPatientCategory() const {
    std::cout << "[General Patient] - Standard Priority\n";
}

bool GeneralPatient::scheduleAppointment(const std::string& date, const std::string& time) {
    // Logic for scheduling a standard appointment
    std::cout << "General appointment scheduled for " << date << " at " << time << "\n";
    return true;
}

bool GeneralPatient::cancelAppointment() {
    std::cout << "General appointment cancelled.\n";
    return true;
}

} // namespace model
} // namespace scapms