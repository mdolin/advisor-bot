### Description
Advisorbot is a command-line program that can carry out various tasks to help a cryptocurrency investor analyse the data available on an exchange. In this case, data is available in .csv file.

### Main bits of the project
* CSV Reader
* Order Book/ Order Book Entry
* AdvisorMain
* Main simulation starter

### Structure of the project
```
.
├── build
│   ├── 20200317.csv
│   └── 20200601.csv
├── Makefile
├── README.md
└── src
    ├── 20200317.csv
    ├── 20200601.csv
    ├── AdvisorMain.cpp
    ├── AdvisorMain.h
    ├── CSVReader.cpp
    ├── CSVReader.h
    ├── main.cpp
    ├── OrderBook.cpp
    ├── OrderBookEntry.cpp
    ├── OrderBookEntry.h
    └── OrderBook.h
```

### Requirements
To run and compile the project
* C++ Programming language
* C++ Compiler
* Make utility

### Compile
To run the simulation, we will need a terminal and make utility. Contents are in a file called Makefile, and in that directory, run the command make. The executable file will be placed in the build folder and will read .csv file, which is also there.

### Example interaction with advisorbot
Advisorbot responds to commands typed in by the user.
Here is an example interaction:
```
advisorbot> Please enter a command, or help for a list of commands

user> avg ETH/BTC ask 10
advisorbot> The average ETH/BTC ask price over the last 10 timesteps was 1.0

user> predict max ETH/BTC ask
advisorbot> The max ask for ETH/BTC might be 0.9
```