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
        /** print MOTD*/
        void printMOTD();
        /** print help menu and help for each command*/
        void printHelp(std::string helpOption);
        /** list available products*/
        void printProd();
        /** find min/max bid or ask for product in currnt time step*/
        void printMinOrMax(std::string userOption);
        /** compute average ask or bid for the sent product over the sent number of time steps*/
        void printAvg(std::string userOption);
        /** predict max or min ask or bid for the sent product for the next time step*/
        void printPredict();
        /** state current time in dataset*/
        void printTime();
        /** move to next time step*/
        void nextTimeframe();
        /** get user input from command line*/
        std::string getUserOption();
        /** process used input*/
        void processUserOption(std::string userOption);

        std::string botPrompt = "advisorbot> ";
        std::string userPrompt = "user> ";

        std::string currentTime;
        OrderBook orderBook{"20200601.csv"};
};