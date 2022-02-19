#pragma once
#include <vector>
#include <string> 
#include "Device.h"


class LogicSimulator
{
    public:
        std::string getSimulationResult(std::vector<__int8> inputValue);
        std::string getTruthTable();
        int getiPinsSize();
        bool load(std::string fileName);
        bool isLoad();
    private:
        bool Load=false;
        int nextInt(std::string& str);
        std::vector<Device *> *circuit;
        std::vector<Device *> *iPins;
        std::vector<Device *> *oPins;

};