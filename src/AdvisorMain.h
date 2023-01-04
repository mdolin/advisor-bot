#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class AdvisorMain {
    public:
        AdvisorMain();
        /** Call this to start the sim */
        void init();

    private:
        void printMenu();
        void printHelp(std::string helpOption);
        void printProd();
        void printMinOrMax(std::string userOption);
        void printAvg(std::string userOption);
        void printPredict();
        void printTime();
        void nextTimeframe();
        std::string getUserOption();
        void processUserOption(std::string userOption);

        std::string botPrompt = "advisorbot> ";
        std::string userPrompt = "user> ";

        std::string currentTime;
        OrderBook orderBook{"20200601.csv"};
};