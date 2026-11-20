#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <ostream>
#include <string>

class InventoryItem {
 private:
  std::string id;
  std::string itemName;

 protected:
  const std::string& getStoredId() const {
    return id;
  }

  const std::string& getStoredName() const {
    return itemName;
  }

 public:
  InventoryItem(const std::string& itemId, const std::string& name)
      : id(itemId), itemName(name) {}

  virtual ~InventoryItem() = default;

  virtual const std::string& inventoryId() const = 0;
  virtual const std::string& name() const = 0;
  virtual std::string describe() const = 0;

  virtual bool isRental() const {
    return false;
  }

  virtual int beginnerLevel() const {
    return 0;
  }

  bool operator<(const InventoryItem& other) const {
    return inventoryId() < other.inventoryId();
  }
};

inline std::ostream& operator<<(std::ostream& out,
                                const InventoryItem& item) {
  out << item.inventoryId() << ' ' << item.name();
  return out;
}

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double dailyEnergy() const = 0;
};

#endif
