#include <string>
#include <iostream>

#include "bank.h"
#include "shapes.h"

namespace bank {

    bool isRectangleValid(const containers::Rectangle r) {
        return r.topLeft.x <= r.bottomRight.x && r.topLeft.y >= r.bottomRight.y;
    }

    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }

    bool isStringValid(const std::string& s) {
        for (char c : s) if (!isAlphaNumeric(c)) return false;
        return true;
    }

    bool isCircleValid(containers::Circle c) {
        return c.radius >= 0;
    }

    void BankManager::addNeighborhood(Neighborhood n) {
        if (!isStringValid(n.name)) throw std::string("Invalid name. Neighborhood name should only contain letters and numbers.");
        if (!isRectangleValid(n.boundry)) throw std::string("Invalid boundry");
        if (neighborhoodsTrie.exists(n.name)) throw std::string("Neighborhood already exists");

        neighborhoods.pushBack(n);
        neighborhoodsTrie.insert(n.name, neighborhoods.size() - 1);
    }

    void BankManager::addBank(Bank* b) {
        if (!isStringValid(b->name)) throw std::string("Invalid name. Bank name should only contain letters and numbers.");
        if (banksTrie.exists(b->name)) throw std::string("Bank already exists");
        if (allbuildings.exists(b->loc)) throw std::string("A building already exists at this location");

        banks.pushBack(*b);
        banksTrie.insert(b->name, banks.size() - 1);
        banksTree.insert(b->loc, b);
        allbuildings.insert(b->loc, b);
    }

    void BankManager::addBranch(Branch* br) {
        if (!isStringValid(br->name)) throw std::string("Invalid branch name. Branch name should only contain letters and numbers.");
        if (!isStringValid(br->bankName)) throw std::string("Invalid bank name. Bank name should only contain letters and numbers.");
        if (!banksTrie.exists(br->bankName)) throw std::string("Bank does not exist");
        if (allbuildings.exists(br->loc)) throw std::string("A building already exists at this location");

        Bank& bankOfBranch = banks[banksTrie.find(br->bankName)];

        bankOfBranch.branches.insert(br->loc, br);
        allbuildings.insert(br->loc, br);
    }

    void BankManager::removeBranch(containers::Point p) {
        Building* foundBuilding = allbuildings.dataAt(p);

        if (foundBuilding == nullptr) throw std::string("No branch or main office exists at the specified point");
        if (foundBuilding->buildingType() != BuildingType::BRANCH) throw std::string("Specified building is not a branch");

        Branch* foundBranch = dynamic_cast<Branch*>(foundBuilding);
        Bank& bankOfBranch = banks[banksTrie.find(foundBranch->bankName)];
        bankOfBranch.branches.remove(p);
        allbuildings.remove(p);
    }

    void BankManager::printBanksInNeighborhood(const std::string& name) {
        if (!isStringValid(name)) throw std::string("Invalid neighborhood name. Neighborhood name should only contain letters and numbers.");
        if (!neighborhoodsTrie.exists(name)) throw std::string("Neighborhood does not exist");

        Neighborhood n = neighborhoods[neighborhoodsTrie.find(name)];
        containers::Vector<Building*> result = allbuildings.rangeSearch(n.boundry);
        
        if (result.size() == 0) std::cout << " - No banks exist in this neighborhood - ";
        else for (int i = 0; i < result.size(); i++) {
            result[i]->printInfo();
        }
    }

    void BankManager::listBranches(const std::string& bankName) {
        if (!isStringValid(bankName)) throw std::string("Invalid bank name. Bank name should only contain letters and numbers.");
        int bankIndex = banksTrie.find(bankName);
        if (bankIndex == -1) throw std::string("Bank does not exist");
        Bank& bankOfBranch = banks[bankIndex];
        bankOfBranch.branches.travereseAll([](Branch* b) {b->printInfo();});
    }

    Building* BankManager::nearestBank(containers::Point p) {
        return allbuildings.nearest(p);
    }

    Branch* BankManager::nearestBranchOfBank(containers::Point p, const std::string& bankName) {
        if (!isStringValid(bankName)) throw std::string("Invalid bank name. Bank name should only contain letters and numbers.");
        if (!banksTrie.exists(bankName)) throw std::string("Bank does not exist");
        Bank& bankOfBranch = banks[banksTrie.find(bankName)];
        return bankOfBranch.branches.nearest(p);
    }

    containers::Vector<Building*> BankManager::availableBanks(containers::Circle c) {
        if (!isCircleValid(c)) throw std::string("Range of search is not valid");
        return allbuildings.rangeSearch(c);
    }
}