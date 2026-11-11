#pragma once
#include <string>

namespace scapms {
namespace model {

class Appointable {
public:
    virtual ~Appointable() = default;
    
    // Pure virtual functions acting as interface methods
    virtual bool scheduleAppointment(const std::string& date, const std::string& time) = 0;
    virtual bool cancelAppointment() = 0;
};

} // namespace model
} // namespace scapms