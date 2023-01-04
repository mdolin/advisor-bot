#include <iostream>
#include <vector>
#include <string>
#include "OrderBook.h"
#include "AdvisorMain.h"
#include "CSVReader.h"

AdvisorMain::AdvisorMain() {

}

void AdvisorMain::init() {
    std::string input;
    currentTime = orderBook.getEarliestTime();
    printMenu();

    while(true)
    {
        input = getUserOption();
        processUserOption(input);
    }
}

void AdvisorMain::printMenu() {
    std::cout << "Advisorbot is a command line program that can carry out" << std::endl;
    std::cout << "various tasks to help a cryptocurrency investor analyse"  << std::endl;
    std::cout << "the data available on an exchange." << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "" << std::endl;
    std::cout << botPrompt << "Please enter a command, or help for a list of commands" << std::endl;
}

void AdvisorMain::printHelp(std::string helpOption) {
    if (helpOption == "help") {
        std::cout << "Command: help" << std::endl;
        std::cout << "Purpose: list all available commands" << std::endl;
        std::cout << "Example: help, help <cmd>, prod, min, max, avg, predict, time, step, exit" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help cmd") {
        std::cout << "Command: help cmd" << std::endl;
        std::cout << "Purpose: output help for the specified command" << std::endl;
        std::cout << "Example: help avg" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help prod") {
        std::cout << "Command: prod" << std::endl;
        std::cout << "Purpose: list available products" << std::endl;
        std::cout << "Example: user> prod" << std::endl;
        std::cout << "         advisorbot> ETH/BTC, DOGE/BTC" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help min") {
        std::cout << "Command: min product bid/ask" << std::endl;
        std::cout << "Purpose: find minimum bid or ask for product in current time step" << std::endl;
        std::cout << "Example: user> min ETH/BTC ask" << std::endl;
        std::cout << "         advisorbot> The min ask for ETH/BTC is 1.0" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help max") {
        std::cout << "Command: max product bid/ask" << std::endl;
        std::cout << "Purpose: find maximum bid or ask for product in current time step" << std::endl;
        std::cout << "Example: user> max ETH/BTC ask" << std::endl;
        std::cout << "         advisorbot> The max ask for ETH/BTC is 1.0" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help avg") {
        std::cout << "Command: avg product ask/bid timesteps" << std::endl;
        std::cout << "Purpose: compute average ask or bid for the sent product over the sent number of time steps" << std::endl;
        std::cout << "Example: user> avg ETH/BTC ask 10" << std::endl;
        std::cout << "         advisorbot> The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help predict") {
        std::cout << "Command: predict max/min product ask/bid" << std::endl;
        std::cout << "Purpose: predict max or min ask or bid for the sent product for the next time step" << std::endl;
        std::cout << "Example: user> predict max ETH/BTC bid" << std::endl;
        std::cout << "         advisorbot> The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help time") {
        std::cout << "Command: time" << std::endl;
        std::cout << "Purpose: state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
        std::cout << "Example: user> time" << std::endl;
        std::cout << "         advisorbot> 2020/03/17 17:01:24" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help step") {
        std::cout << "Command: step" << std::endl;
        std::cout << "Purpose: move to next time step" << std::endl;
        std::cout << "Example: user> step" << std::endl;
        std::cout << "         advisorbot> now at 2020/03/17 17:01:30" << std::endl;
        std::cout << "" << std::endl;
    } else if (helpOption == "help exit") {
        std::cout << "Command: exit" << std::endl;
        std::cout << "Purpose: exit from AdvisorBot" << std::endl;
        std::cout << "Example: user> exit" << std::endl;
        std::cout << "         advisorbot> Goodbye!" << std::endl;
        std::cout << "" << std::endl;
    }
}

void AdvisorMain::printProd() {
    bool first = true;
    for (std::string const& p : orderBook.getKnownProducts()) {
        // std::cout << botPrompt << p << std::endl;
        if (first) {
            std::cout << botPrompt << p << "";
            first = false;
        } else {
            std::cout << ", " << p << "";
        }
    }
    std::cout << "" << std::endl;
}

void AdvisorMain::printMinOrMax(std::string userOption) {
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');
    std::string product;
    std::string type;

    // to not use scientific notation
    std::cout.precision(10);
    std::cout << std::fixed;

    if (tokens.size() != 3) {
        std::cout << "Wrong input, type 'help min'" << std::endl;
    } else {
        product = tokens[1];
        type = tokens[2];
    }

    for (std::string const& p : orderBook.getKnownProducts()) {
        if (product == p) {
            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), p, currentTime);
            if (tokens[0] == "min") {
                std::cout << botPrompt << "The min " << type << " for " << product << " is " << OrderBook::getLowPrice(entries) << std::endl;
            } else if (tokens[0] == "max")
            std::cout << botPrompt << "The max " << type << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
        }
    }
}

void AdvisorMain::printAvg() {

}

void AdvisorMain::printPredict() {

}

void AdvisorMain::printTime() {
    std::vector<std::string> timeOutput = CSVReader::tokenise(currentTime, '.');
    std::cout << timeOutput[0] << std::endl;

}

void AdvisorMain::nextTimeStep() {

}

std::string AdvisorMain::getUserOption() {
    std::string userOption;
    std::cout << userPrompt;
    std::getline(std::cin, userOption);

    return userOption;
}

void AdvisorMain::processUserOption(std::string userOption) {
    if (userOption.rfind("help", 0) == 0) {
        printHelp(userOption);
    } else if (userOption == "prod") {
        printProd();
    } else if ((userOption.rfind("min", 0) == 0) || (userOption.rfind("max", 0) == 0)) {
        printMinOrMax(userOption);
    }
    else if (userOption == "time") {
        printTime();
    }
    
    else if (userOption == "exit") {
        std::cout << botPrompt << "Goodbye!" << std::endl;
        exit(3);
    }
}
