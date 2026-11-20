#include "Errors.hpp"
#include "Fleet.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace {

std::string readWord(std::istringstream& input) {
  std::string value;
  if (!(input >> value)) {
    throw CommandError("not enough arguments");
  }
  return value;
}

void checkNoExtra(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw CommandError("too many arguments");
  }
}

double parseEnergy(const std::string& text) {
  std::size_t used = 0;
  double value = 0.0;

  try {
    value = std::stod(text, &used);
  } catch (const std::exception&) {
    throw CommandError("invalid energy");
  }

  if (used != text.size() || !std::isfinite(value) || value < 0.0) {
    throw CommandError("energy must be a non-negative number");
  }

  return value;
}

int parseLevel(const std::string& text) {
  std::size_t used = 0;
  int value = 0;

  try {
    value = std::stoi(text, &used);
  } catch (const std::exception&) {
    throw CommandError("invalid beginner level");
  }

  if (used != text.size() || value < 1 || value > 10) {
    throw CommandError("beginner level must be from 1 to 10");
  }

  return value;
}

void runCommand(const std::string& line, Fleet& fleet, bool& shouldQuit) {
  std::istringstream input(line);
  std::string command;

  if (!(input >> command)) {
    return;
  }

  if (command == "add") {
    std::string type = readWord(input);
    std::string id = readWord(input);
    std::string name = readWord(input);

    if (type == "scooter") {
      double energy = parseEnergy(readWord(input));
      int level = parseLevel(readWord(input));
      checkNoExtra(input);
      fleet.addScooter(id, name, energy, level);
    } else if (type == "bike") {
      int level = parseLevel(readWord(input));
      checkNoExtra(input);
      fleet.addBike(id, name, level);
    } else if (type == "ebike") {
      double energy = parseEnergy(readWord(input));
      int level = parseLevel(readWord(input));
      checkNoExtra(input);
      fleet.addElectricBike(id, name, energy, level);
    } else if (type == "helmet") {
      checkNoExtra(input);
      fleet.addHelmet(id, name);
    } else if (type == "dock") {
      double energy = parseEnergy(readWord(input));
      checkNoExtra(input);
      fleet.addDock(id, name, energy);
    } else if (type == "cargo_bike") {
      double energy = parseEnergy(readWord(input));
      int level = parseLevel(readWord(input));
      checkNoExtra(input);
      fleet.addCargoBike(id, name, energy, level);
    } else {
      throw CommandError("unknown item type");
    }
  } else if (command == "list") {
    checkNoExtra(input);
    fleet.printList();
  } else if (command == "novice") {
    checkNoExtra(input);
    fleet.printNovice();
  } else if (command == "energy") {
    checkNoExtra(input);
    fleet.printEnergy();
  } else if (command == "report") {
    checkNoExtra(input);
    fleet.printReport();
  } else if (command == "max_energy") {
    checkNoExtra(input);
    fleet.printMaxEnergy();
  } else if (command == "focus") {
    std::string id = readWord(input);
    checkNoExtra(input);
    fleet.setFocus(id);
  } else if (command == "show_focus") {
    checkNoExtra(input);
    fleet.showFocus();
  } else if (command == "remove") {
    std::string id = readWord(input);
    checkNoExtra(input);
    fleet.remove(id);
  } else if (command == "info") {
    std::string id = readWord(input);
    checkNoExtra(input);
    fleet.printInfo(id);
  } else if (command == "ids") {
    checkNoExtra(input);
    fleet.printIds();
  } else if (command == "quit") {
    checkNoExtra(input);
    shouldQuit = true;
  } else {
    throw CommandError("unknown command");
  }
}

}  // namespace

int main() {
  Fleet fleet;
  std::string line;
  bool shouldQuit = false;

  while (!shouldQuit && std::getline(std::cin, line)) {
    try {
      runCommand(line, fleet, shouldQuit);
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }

  return 0;
}
