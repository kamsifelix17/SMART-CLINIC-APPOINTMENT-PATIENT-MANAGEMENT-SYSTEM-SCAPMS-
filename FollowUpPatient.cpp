// FollowUpPatient.cpp
#include "FollowUpPatient.h"
#include <iostream>

namespace scapms {
namespace model {

FollowUpPatient::FollowUpPatient(std::string id, std::string n, int a, std::string contact, std::string prevDocId)
    : PatientRecord(std::move(id), std::move(n), a, std::move(contact)), previousDoctorId(std::move(prevDocId)) {}

void FollowUpPatient::displayPatientCategory() const {
    std::cout << "[Follow-Up Patient] - Returning to Dr. " << previousDoctorId << "\n";
}

bool FollowUpPatient::scheduleAppointment(const std::string& date, const std::string& time) {
    std::cout << "Follow-up appointment scheduled with Dr. " << previousDoctorId << " on " << date << " at " << time << "\n";
    return true;
}

bool FollowUpPatient::cancelAppointment() {
    std::cout << "Follow-up appointment cancelled.\n";
    return true;
}

} // namespace model
} // namespace scapms