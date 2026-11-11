#include "PatientRecord.h"

namespace scapms {
namespace model {

PatientRecord::PatientRecord(std::string id, std::string n, int a, std::string contact)
    : patientID(std::move(id)), name(std::move(n)), age(a), contactInfo(std::move(contact)) {}

} // namespace model
} // namespace scapms