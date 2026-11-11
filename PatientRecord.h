#pragma once
#include <string>
#include <iostream>

namespace scapms {
namespace model {

class PatientRecord {
protected:
    std::string patientID;
    std::string name;
    int age;
    std::string contactInfo;

public:
    PatientRecord(std::string id, std::string n, int a, std::string contact);
    virtual ~PatientRecord() = default;

    // Getters
    std::string getPatientID() const { return patientID; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getContactInfo() const { return contactInfo; }

    // Pure virtual function making this an abstract class
    virtual void displayPatientCategory() const = 0;
};

} // namespace model
} // namespace scapms