#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>
#include <string>

class FleetError : public std::exception {
 private:
  std::string message;

 public:
  explicit FleetError(const std::string& text) : message(text) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};

class InspectionError : public FleetError {
 public:
  explicit InspectionError(const std::string& text) : FleetError(text) {}
};

class CommandError : public FleetError {
 public:
  explicit CommandError(const std::string& text) : FleetError(text) {}
};

#endif
