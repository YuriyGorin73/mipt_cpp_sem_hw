#ifndef SERVICE_CENTER_HPP
#define SERVICE_CENTER_HPP

#include "Errors.hpp"
#include "Transport.hpp"

#include <cctype>
#include <string>

class ServiceCenter {
 public:
  void inspect(const Transport& vehicle) const {
    std::string name = vehicle.name();

    for (char& symbol : name) {
      symbol = static_cast<char>(
          std::tolower(static_cast<unsigned char>(symbol)));
    }

    if (name.find("broken") != std::string::npos) {
      throw InspectionError("inspection rejected");
    }
  }
};

#endif
