#include <iostream>
#include <string>

#include "shapes.h"
#include "bank.h"

void printError(const std::string& s) {
    std::cerr << "Error: " << s << std::endl;
}

int main() {
    std::string command;
    bank::BankManager bm;

    std::cout << " --      Bank Manager      --" << std::endl;
    std::cout << " -- DS Project - Fall 1400 --" << std::endl << std::endl;
    std::cout << "Enter commands below: " << std::endl;

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

            try {
                bm.addNeighborhood({name, boundry});
            } catch (const std::string& msg) {
                printError(msg);
            }
        } else if (command == "addB") {
            containers::Point loc;
            std::string name;

            std::cout << "Enter location of bank (x, y): ";
            std::cin >> loc.x >> loc.y;
            std::cout << "Enter name of the bank: ";
            std::cin >> name;

            bank::Bank* newBank = new bank::Bank;
            newBank->branches = {};
            newBank->name = name;
            newBank->loc = loc;

            try {
                bm.addBank(newBank);
            } catch (const std::string& msg) {
                printError(msg);
            }
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

            try {
                bm.addBranch(newBranch);
            } catch (const std::string& msg) {
                printError(msg);
            }
        } else if (command == "listB") {
            std::string name;
            std::cout << "Enter neighborhood name: ";
            std::cin >> name;

            try {
                bm.printBanksInNeighborhood(name);
            } catch (const std::string& msg) {
                printError(msg);
            }
        } else if (command == "delBr") {
            containers::Point loc;
            std::cout << "Enter location of branch (x, y): ";
            std::cin >> loc.x >> loc.y;
            try {
                bm.removeBranch(loc);
            } catch (const std::string& msg) {
                printError(msg);
            }
        } else if (command == "listBrs") {
            std::string bankName;
            std::cout << "Enter name of the bank: ";
            std::cin >> bankName;

            try {
                bm.listBranches(bankName);
            } catch (const std::string& msg) {
                printError(msg);
            }
        } else if (command == "nearB") {
            containers::Point loc;
            std::cout << "Enter location (x, y): ";
            std::cin >> loc.x >> loc.y;
            bank::Building* nearestBuilding = bm.nearestBank(loc);
            if (!nearestBuilding) printError("No bank exists");
            else nearestBuilding->printInfo();
        } else if (command == "nearBr") {
            containers::Point loc;
            std::string bankName;
            std::cout << "Enter location (x, y): ";
            std::cin >> loc.x >> loc.y;
            std::cout << "Enter name of bank: ";
            std::cin >> bankName;
            
            bank::Branch* nearestBranch;

            try {
                nearestBranch = bm.nearestBranchOfBank(loc, bankName);
            } catch (const std::string& msg) {
                printError(msg);
                std::cout << std::endl;
                continue;
            }

            if (!nearestBranch) printError("No bank exists");
            else nearestBranch->printInfo();
        } else if (command == "availB") {
            containers::Circle area;
            std::cout << "Enter center of search area (x, y): ";
            std::cin >> area.center.x >> area.center.y;
            std::cout << "Enter radius of search: ";
            std::cin >> area.radius;
            
            containers::Vector<bank::Building*> availBanks;

            try {
                availBanks = bm.availableBanks(area);
            } catch (const std::string& msg) {
                printError(msg);
                std::cout << std::endl;
                continue;
            }
            for (int i = 0; i < availBanks.size(); i++) {
                availBanks[i]->printInfo();
            }
        } else if (command == "exit") {
            break;
        } else {
            printError("Command not found");
        }

        std::cout << std::endl;
     }
}