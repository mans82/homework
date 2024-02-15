#include <iostream>
#include <string>

#include "containers.h"
#include "bank.h"

int main() {
    std::string command;

    bank::BankManager bm;

    while (std::cin >> command) {
        if (command == "addN") {
            containers::Rectangle boundry;
            std::string name;

            std::cout << "Enter neighborhood name: ";
            std::cin >> name;
            std::cout << "Enter neighborhood boundries:" << std::endl;
            std::cout << "Top left point: ";
            std::cin >> boundry.topLeft.x >> boundry.topLeft.y;
            std::cout << "Bottom right point: ";
            std::cin >> boundry.bottomRight.x >> boundry.bottomRight.y;
            std::cout << std::endl;

            bm.addNeighborhood({name, boundry});
        } else if (command == "addB") {
            containers::Point loc;
            std::string name;

            std::cout << "Enter location of bank (x, y): ";
            std::cin >> loc.x >> loc.y;
            std::cout << "Enter name of the bank: ";
            std::cin >> name;
            std::cout << std::endl;

            bank::Bank* newBank = new bank::Bank;
            newBank->branches = {};
            newBank->name = name;
            newBank->loc = loc;

            bm.addBank(newBank);
        } else if (command == "addBr") {
            containers::Point loc;
            std::string branchName;
            std::string bankName;

            std::cout << "Enter location of branch (x, y): ";
            std::cin >> loc.x >> loc.y;
            std::cout << "Enter name of the bank: ";
            std::cin >> bankName;
            std::cout << "Enter name of the branch: ";
            std::cin >> branchName;

            bank::Branch* newBranch = new bank::Branch;
            newBranch->loc = loc;
            newBranch->name = branchName;
            newBranch->bankName = bankName;

            bm.addBranch(newBranch);
        } else if (command == "listB") {
            std::string name;
            std::cout << "Enter neighborhood name: ";
            std::cin >> name;

            bm.printBanksInNeighborhood(name);
        } else if (command == "delBr") {
            containers::Point loc;
            std::cout << "Enter location of branch (x, y): ";
            std::cin >> loc.x >> loc.y;
            try {
                bm.removeBranch(loc);
            } catch (const std::string& msg) {
                std::cout << "Error: " << msg << std::endl;
            }
        } else if (command == "listBrs") {
            std::string bankName;
            std::cout << "Enter name of the bank: ";
            std::cin >> bankName;

            try {
                bm.listBranches(bankName);
            } catch (const std::string& msg) {
                std::cout << "Error: " << msg;
            }
        } else if (command == "nearB") {
            containers::Point loc;
            std::cout << "Enter location (x, y): ";
            std::cin >> loc.x >> loc.y;
            bank::Building* nearestBuilding = bm.nearestBank(loc);
            nearestBuilding->printInfo();
        } else if (command == "nearBr") {
            containers::Point loc;
            std::string bankName;
            std::cout << "Enter location (x, y): ";
            std::cin >> loc.x >> loc.y;
            std::cout << "Enter name of bank: ";
            std::cin >> bankName;
            
            bank::Branch* nearestBranch = bm.nearestBranchOfBank(loc, bankName);
            nearestBranch->printInfo();
        } else if (command == "availB") {
            containers::Circle area;
            std::cout << "Enter center of search area (x, y): ";
            std::cin >> area.center.x >> area.center.y;
            std::cout << "Enter radius of search: ";
            std::cin >> area.radius;

            auto availBanks = bm.availableBanks(area);
            for (int i = 0; i < availBanks.size(); i++) {
                availBanks[i]->printInfo();
            }
        }
     }

    return 0;
}