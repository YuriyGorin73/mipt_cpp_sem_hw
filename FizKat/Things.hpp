#ifndef THINGS_HPP
#define THINGS_HPP

#include "Inventory.hpp"

#include <string>

class Helmet : public InventoryItem {
 public:
  Helmet(const std::string& id, const std::string& name)
      : InventoryItem(id, name) {}

  const std::string& inventoryId() const override {
    return getStoredId();
  }

  const std::string& name() const override {
    return getStoredName();
  }

  std::string describe() const override {
    return "Helmet: " + inventoryId() + " " + name();
  }
};

class DockStation : public InventoryItem, public EnergyConsumer {
 private:
  double energy;

 public:
  DockStation(const std::string& id, const std::string& name,
              double dailyEnergy)
      : InventoryItem(id, name), energy(dailyEnergy) {}

  const std::string& inventoryId() const override {
    return getStoredId();
  }

  const std::string& name() const override {
    return getStoredName();
  }

  double dailyEnergy() const override {
    return energy;
  }

  std::string describe() const override {
    return "Dock station: " + inventoryId() + " " + name() +
           ", energy " + std::to_string(energy) + " kWh/day";
  }
};

#endif
