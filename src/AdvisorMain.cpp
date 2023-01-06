#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "OrderBook.h"
#include "AdvisorMain.h"
#include "CSVReader.h"

AdvisorMain::AdvisorMain() {

}

void AdvisorMain::init() {
    std::string input;
    currentTime.first = orderBook.getEarliestTime();
    printMOTD();

    while(true)
    {
        input = getUserOption();
        processUserOption(input);
    }
}

void AdvisorMain::printMOTD() {
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
    // flag for comma
    bool first = true;

    // loop through known products and pretty print them
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
    // tokenise input data on spaces to get min or max, product (ETH/BTC) and type (bid or ask)
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');
    std::string minMax;
    std::string product;
    std::string type;
    bool unknownProd = false;

    // to not use scientific notation
    std::cout.precision(10);
    std::cout << std::fixed;

    // check that there are three tokens (min/max, product, type)
    if (tokens.size() != 3) {
        std::cout << "Wrong input, type 'help <cmd>'" << std::endl;
        return;
    } else if ((tokens[0] != "min" && tokens[0] != "max") || (tokens[2] != "ask" && tokens[2] != "bid")) {
        std::cout << "Wrong input, type 'help <cmd>'" << std::endl;
        return;
    } else {
        minMax = tokens[0];
        product = tokens[1];
        type = tokens[2];
    }

    // check if product exists
    if (!knownProduct(product)) {
        std::cout << "Unknown product" << std::endl;
        return;
    }

    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, currentTime.first);

    if (minMax == "min") {
        std::cout << botPrompt << "The min " << type << " for " << product << " is " << OrderBook::getLowPrice(entries) << std::endl;
    } else if (minMax == "max")
        std::cout << botPrompt << "The max " << type << " for " << product << " is " << OrderBook::getHighPrice(entries) << std::endl;
}

void AdvisorMain::printAvg(std::string userOption) {
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');
    std::string product;
    std::string type;
    double average;
    int timeSteps;
    int stepsBack;
    int stepsSkip;
    bool unknownProd = false;

    // to not use scientific notation
    std::cout.precision(10);
    std::cout << std::fixed;

    // check that there are three tokens (min/max, product, type)
    if (tokens.size() != 4) {
        std::cout << "Wrong input, type 'help <cmd>'" << std::endl;
        return;
    } else if ((tokens[0] != "avg") || (tokens[2] != "ask" && tokens[2] != "bid")) {
        std::cout << "Wrong input, type 'help <cmd>'" << std::endl;
        return;
    } else {
        product = tokens[1];
        type = tokens[2];
        timeSteps = std::stoi(tokens[3]);
    }

    // check if product exists
    if (!knownProduct(product)) {
        std::cout << "Unknown product" << std::endl;
        return;
    }

    std::vector<OrderBookEntry> orders = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(type), product, currentTime.first);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);

    if (timeSteps > currentTime.second) {
        std::cout << botPrompt << "Wrong input. Went too far back in time. Current timesteps: " << currentTime.second << std::endl;
        return;
    }

    std::vector<OrderBookEntry> ordersBack;
    ordersBack = std::vector<OrderBookEntry>(orders.begin() + std::max(currentTime.second - timeSteps, 0), orders.begin() + timeSteps);

    average = OrderBook::getMeanValue(ordersBack);
    std::cout << botPrompt << "The average " << product << " " << type << " price over the last " << timeSteps << " timesteps was " << average << std::endl;
}

void AdvisorMain::printPredict() {

}

void AdvisorMain::printTime() {
    // tokenise time to rid of the decimal point of seconds
    std::vector<std::string> timeOutput = CSVReader::tokenise(currentTime.first, '.');
    std::cout << timeOutput[0] << ", Timesteps: " << currentTime.second << std::endl;

}

void AdvisorMain::nextTimeframe() {
    // jump to next time frame and print time
    currentTime.first = orderBook.getNextTime(currentTime.first);
    currentTime.second++;
    std::cout << botPrompt << "now at ";
    printTime();
}

std::string AdvisorMain::getUserOption() {
    // get user input
    std::string userOption;
    std::cout << userPrompt;
    std::getline(std::cin, userOption);

    return userOption;
}


bool AdvisorMain::knownProduct(std::string product) {
    bool knownProd = false;
    for (std::string const& p : orderBook.getKnownProducts()) {
        if (product == p) {
            knownProd = true;
        }
    }

    return knownProd;
}

void AdvisorMain::processUserOption(std::string userOption) {
    // process user input
    if (userOption.rfind("help", 0) == 0) {
        printHelp(userOption);
    } else if (userOption == "prod") {
        printProd();
    } else if ((userOption.rfind("min", 0) == 0) || (userOption.rfind("max", 0) == 0)) {
        printMinOrMax(userOption);
    } else if (userOption.rfind("avg", 0) == 0) {
        printAvg(userOption);
    } else if (userOption.rfind("predict", 0) == 0) {
        printPredict();
    } else if (userOption == "time") {
        printTime();
    } else if (userOption.rfind("step", 0) == 0) {
        nextTimeframe();
    } else if (userOption == "exit") {
        std::cout << botPrompt << "Goodbye!" << std::endl;
        exit(3);
    } else {
        std::cout << "Type 'help' for help" << std::endl;
    }
}
