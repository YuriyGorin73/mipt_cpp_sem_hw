#ifndef FLEET_HPP
#define FLEET_HPP

#include "Errors.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Fleet {
 private:
  static const int capacity = 100;
  static const int noviceLevel = 6;

  std::vector<std::unique_ptr<InventoryItem>> items;
  Registry<std::string, 100> ids;

  // Эти указатели не владеют объектами. Они нужны только для weak_ptr.
  std::vector<std::shared_ptr<InventoryItem>> focusLinks;
  std::weak_ptr<InventoryItem> focus;
  bool focusWasSet = false;

  std::map<std::string, std::shared_ptr<const ModelSpec>> models;
  ServiceCenter serviceCenter;

  std::shared_ptr<const ModelSpec> getModel(const std::string& type) const {
    auto found = models.find(type);
    if (found == models.end()) {
      throw CommandError("unknown transport model");
    }
    return found->second;
  }

  void addItem(std::unique_ptr<InventoryItem> item) {
    std::string id = item->inventoryId();

    if (ids.contains(id)) {
      throw CommandError("duplicate inventory id");
    }
    if (items.size() >= static_cast<std::size_t>(capacity)) {
      throw CommandError("park is full");
    }

    // Объектом владеет unique_ptr, shared_ptr нужен только для weak_ptr.
    std::shared_ptr<InventoryItem> link(item.get(), [](InventoryItem*) {});

    if (!ids.add(id)) {
      throw CommandError("park is full");
    }

    items.push_back(std::move(item));
    focusLinks.push_back(std::move(link));
  }

  std::size_t findIndex(const std::string& id) const {
    for (std::size_t i = 0; i < ids.size(); ++i) {
      if (ids[i] == id) {
        return i;
      }
    }
    return ids.size();
  }

 public:
  Fleet() {
    items.reserve(capacity);
    focusLinks.reserve(capacity);

    models["scooter"] = std::make_shared<ModelSpec>(
        ModelSpec{"Electric scooter"});
    models["bike"] = std::make_shared<ModelSpec>(ModelSpec{"Bicycle"});
    models["ebike"] = std::make_shared<ModelSpec>(
        ModelSpec{"Electric bicycle"});
    models["cargo_bike"] = std::make_shared<ModelSpec>(
        ModelSpec{"Cargo bicycle"});
  }

  void addScooter(const std::string& id, const std::string& name,
                  double energy, int level) {
    auto item = std::make_unique<ElectricScooter>(
        id, name, energy, level, getModel("scooter"));
    serviceCenter.inspect(*item);
    addItem(std::move(item));
  }

  void addBike(const std::string& id, const std::string& name, int level) {
    auto item = std::make_unique<Bicycle>(id, name, level, getModel("bike"));
    serviceCenter.inspect(*item);
    addItem(std::move(item));
  }

  void addElectricBike(const std::string& id, const std::string& name,
                       double energy, int level) {
    auto item = std::make_unique<ElectricBike>(
        id, name, energy, level, getModel("ebike"));
    serviceCenter.inspect(*item);
    addItem(std::move(item));
  }

  void addCargoBike(const std::string& id, const std::string& name,
                    double energy, int level) {
    auto item = std::make_unique<CargoBike>(
        id, name, energy, level, getModel("cargo_bike"));
    serviceCenter.inspect(*item);
    addItem(std::move(item));
  }

  void addHelmet(const std::string& id, const std::string& name) {
    addItem(std::make_unique<Helmet>(id, name));
  }

  void addDock(const std::string& id, const std::string& name, double energy) {
    addItem(std::make_unique<DockStation>(id, name, energy));
  }

  void printList() const {
    std::vector<const InventoryItem*> sorted;

    for (const auto& item : items) {
      sorted.push_back(item.get());
    }

    // Сортировка простым обменом по инвентарному номеру.
    for (std::size_t i = 0; i < sorted.size(); ++i) {
      for (std::size_t j = i + 1; j < sorted.size(); ++j) {
        if (*sorted[j] < *sorted[i]) {
          const InventoryItem* temp = sorted[i];
          sorted[i] = sorted[j];
          sorted[j] = temp;
        }
      }
    }

    for (const InventoryItem* item : sorted) {
      std::cout << *item << '\n';
    }
  }

  double totalEnergy() const {
    double total = 0.0;

    for (const auto& item : items) {
      const EnergyConsumer* consumer =
          dynamic_cast<const EnergyConsumer*>(item.get());
      if (consumer != nullptr) {
        total += consumer->dailyEnergy();
      }
    }

    return total;
  }

  void printEnergy() const {
    std::cout << std::fixed << std::setprecision(1) << totalEnergy() << '\n';
  }

  void printReport() const {
    std::cout << "items: " << items.size() << '\n';
    std::cout << "energy: " << std::fixed << std::setprecision(1)
              << totalEnergy() << '\n';
  }

  void printNovice() const {
    for (const auto& item : items) {
      const InventoryItem* base = item.get();
      if (base->isRental() && base->beginnerLevel() >= noviceLevel) {
        std::cout << *base << '\n';
      }
    }
  }

  void printMaxEnergy() const {
    const InventoryItem* bestItem = nullptr;
    double bestEnergy = -1.0;

    for (const auto& item : items) {
      const EnergyConsumer* consumer =
          dynamic_cast<const EnergyConsumer*>(item.get());
      if (consumer != nullptr && consumer->dailyEnergy() > bestEnergy) {
        bestEnergy = consumer->dailyEnergy();
        bestItem = item.get();
      }
    }

    if (bestItem == nullptr) {
      std::cout << "none\n";
      return;
    }

    std::cout << *bestItem << ' ' << std::fixed << std::setprecision(1)
              << bestEnergy << '\n';
  }

  void printInfo(const std::string& id) const {
    std::size_t index = findIndex(id);
    if (index == ids.size()) {
      throw CommandError("unknown inventory id");
    }

    std::cout << items[index]->describe() << '\n';
  }

  void setFocus(const std::string& id) {
    std::size_t index = findIndex(id);
    if (index == ids.size()) {
      throw CommandError("unknown inventory id");
    }

    focus = focusLinks[index];
    focusWasSet = true;
  }

  void showFocus() const {
    if (!focusWasSet) {
      std::cout << "no focus\n";
      return;
    }

    std::shared_ptr<InventoryItem> item = focus.lock();
    if (!item) {
      std::cout << "removed\n";
      return;
    }

    std::cout << *item << '\n';
  }

  void remove(const std::string& id) {
    std::size_t index = findIndex(id);
    if (index == ids.size()) {
      throw CommandError("unknown inventory id");
    }

    focusLinks[index].reset();
    focusLinks.erase(focusLinks.begin() +
                     static_cast<std::ptrdiff_t>(index));
    items.erase(items.begin() + static_cast<std::ptrdiff_t>(index));
    ids.eraseAt(index);
  }

  void printIds() const {
    std::cout << ids << '\n';
  }
};

#endif
