// FollowUpPatient.h
#pragma once
#include "PatientRecord.h"
#include "Appointable.h"

namespace scapms {
namespace model {

class FollowUpPatient : public PatientRecord, public Appointable {
private:
    std::string previousDoctorId; // Specific attribute for follow-ups

public:
    FollowUpPatient(std::string id, std::string n, int a, std::string contact, std::string prevDocId);

    void displayPatientCategory() const override;
    bool scheduleAppointment(const std::string& date, const std::string& time) override;
    bool cancelAppointment() override;
};

} // namespace model
} // namespace scapms