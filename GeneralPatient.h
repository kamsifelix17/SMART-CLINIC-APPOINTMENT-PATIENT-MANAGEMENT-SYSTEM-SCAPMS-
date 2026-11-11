// GeneralPatient.h
#pragma once
#include "PatientRecord.h"
#include "Appointable.h"

namespace scapms {
namespace model {

class GeneralPatient : public PatientRecord, public Appointable {
public:
    GeneralPatient(std::string id, std::string n, int a, std::string contact);

    void displayPatientCategory() const override;
    bool scheduleAppointment(const std::string& date, const std::string& time) override;
    bool cancelAppointment() override;
};

} // namespace model
} // namespace scapms