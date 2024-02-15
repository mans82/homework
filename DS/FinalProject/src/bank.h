#pragma once

#include <string>
#include <iostream>

#include "trie.h"
#include "twodtree.h"
#include "shapes.h"
#include "vector.h"

namespace bank {
    
    struct Neighborhood {
        std::string name;
        containers::Rectangle boundry;
    };
    
    enum class BuildingType {
        BANK,
        BRANCH,
    };

    struct Building {
        virtual void printInfo() = 0;
        virtual BuildingType buildingType() = 0;
    };


    struct Branch : public Building {
        std::string name;
        std::string bankName;
        containers::Point loc;

        void printInfo() {
            std::cout << "Bank " << bankName << ", branch " << name << " at (" << loc.x << ", " << loc.y << ')' << std::endl;
        }

        BuildingType buildingType() {
            return BuildingType::BRANCH;
        }
    };

    struct Bank : public Building {
        std::string name;
        containers::Point loc;
        containers::TwoDTree<Branch> branches;

        void printInfo() {
            std::cout << "Bank " << name << " at (" << loc.x << ", " << loc.y << ") (main office)" << std::endl;
        }

        BuildingType buildingType() {
            return BuildingType::BANK;
        }
    };

    class BankManager {
    private:
        containers::Vector<Bank> banks;
        containers::Trie banksTrie;
        containers::TwoDTree<Bank> banksTree;
        containers::Vector<Neighborhood> neighborhoods;
        containers::Trie neighborhoodsTrie;
        containers::TwoDTree<Building> allbuildings;
    public:
        void addNeighborhood(Neighborhood);
        void addBank(Bank*);
        void addBranch(Branch*);
        void removeBranch(containers::Point);
        void printBanksInNeighborhood(const std::string&);
        void listBranches(const std::string&);
        Building* nearestBank(containers::Point);
        Branch* nearestBranchOfBank(containers::Point, const std::string&);
        containers::Vector<Building*> availableBanks(containers::Circle);
    };
}