// EmergencyPatient.h
#pragma once
#include "PatientRecord.h"
#include "Appointable.h"

namespace scapms {
namespace model {

class EmergencyPatient : public PatientRecord, public Appointable {
private:
    std::string severityLevel; // Specific behavior/attribute for emergency

public:
    EmergencyPatient(std::string id, std::string n, int a, std::string contact, std::string severity);

    void displayPatientCategory() const override;
    bool scheduleAppointment(const std::string& date, const std::string& time) override;
    bool cancelAppointment() override;
};

} // namespace model
} // namespace scapms