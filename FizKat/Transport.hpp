#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include "Inventory.hpp"

#include <memory>
#include <string>

struct ModelSpec {
  std::string typeName;
};

class Transport : public InventoryItem {
 private:
  int level;
  std::shared_ptr<const ModelSpec> model;

 public:
  Transport(const std::string& id, const std::string& name, int beginnerLevel,
            const std::shared_ptr<const ModelSpec>& modelInfo)
      : InventoryItem(id, name), level(beginnerLevel), model(modelInfo) {}

  const std::string& inventoryId() const override {
    return getStoredId();
  }

  const std::string& name() const override {
    return getStoredName();
  }

  bool isRental() const override {
    return true;
  }

  int beginnerLevel() const override {
    return level;
  }

 protected:
  const std::string& modelName() const {
    return model->typeName;
  }
};

class ElectricScooter : public Transport, public EnergyConsumer {
 private:
  double energy;

 public:
  ElectricScooter(const std::string& id, const std::string& name,
                  double dailyEnergy, int level,
                  const std::shared_ptr<const ModelSpec>& modelInfo)
      : Transport(id, name, level, modelInfo), energy(dailyEnergy) {}

  double dailyEnergy() const override {
    return energy;
  }

  std::string describe() const override {
    return modelName() + ": " + inventoryId() + " " + name() +
           ", energy " + std::to_string(energy) +
           " kWh/day, level " + std::to_string(beginnerLevel());
  }
};

class Bicycle : public Transport {
 public:
  Bicycle(const std::string& id, const std::string& name, int level,
          const std::shared_ptr<const ModelSpec>& modelInfo)
      : Transport(id, name, level, modelInfo) {}

  std::string describe() const override {
    return modelName() + ": " + inventoryId() + " " + name() +
           ", no daily energy use, level " +
           std::to_string(beginnerLevel());
  }
};

class ElectricBike : public Transport, public EnergyConsumer {
 private:
  double energy;

 public:
  ElectricBike(const std::string& id, const std::string& name,
               double dailyEnergy, int level,
               const std::shared_ptr<const ModelSpec>& modelInfo)
      : Transport(id, name, level, modelInfo), energy(dailyEnergy) {}

  double dailyEnergy() const override {
    return energy;
  }

  std::string describe() const override {
    return modelName() + ": " + inventoryId() + " " + name() +
           ", energy " + std::to_string(energy) +
           " kWh/day, level " + std::to_string(beginnerLevel());
  }
};

class CargoBike : public Transport, public EnergyConsumer {
 private:
  double energy;
  int loadLimit;

 public:
  CargoBike(const std::string& id, const std::string& name,
            double dailyEnergy, int level,
            const std::shared_ptr<const ModelSpec>& modelInfo)
      : Transport(id, name, level, modelInfo), energy(dailyEnergy),
        loadLimit(25) {}

  double dailyEnergy() const override {
    return energy;
  }

  std::string describe() const override {
    return modelName() + ": " + inventoryId() + " " + name() +
           ", energy " + std::to_string(energy) +
           " kWh/day, load limit " + std::to_string(loadLimit) +
           " kg, level " + std::to_string(beginnerLevel());
  }
};

#endif
