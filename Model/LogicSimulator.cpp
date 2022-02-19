#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "LogicSimulator.h"
#include "gateAND.h"
#include "gateNOT.h"
#include "gateOR.h"
#include "iPin.h"
#include "oPin.h"

//#define DEBUG

bool LogicSimulator::load(std::string fileName)
{
    using namespace std;

    ifstream ifs(fileName, std::ios::in);                                   // read file

    if (!ifs.is_open())                                                     // check file open
        return false;

    stringstream ss;
    ss << ifs.rdbuf();

    string word;

    getline(ss, word, '\n');                                                //read input pins
    iPins = new vector<Device *>;
    iPins->reserve(stoi(word));
    cout << "Circuit: " << word << " input pins, 1 output pins and ";

    getline(ss, word, '\n');                                                //reas gates
    circuit = new vector<Device *>;
    circuit->reserve(stoi(word));
    cout << word << " gates\n";

    vector<vector<int>> *conPin;                                            //This is to save temp gate pins
    conPin=new vector<vector<int>>;
    conPin->reserve(stoi(word));
    for(int i=0;i<conPin->capacity();i++)
    {
        vector<int> a;
        conPin->push_back(a);
    }

    for (int i = 0; i < iPins->capacity(); i++)                             //create iPins
    {
        Device *temp = new iPin();
        int ip = iPins->capacity();
        temp->setId(i+1);
        iPins->push_back(temp);
    }

    for (int i = 0; i < circuit->capacity(); i++)                           //create circuit
    {
        getline(ss, word, '\n');

        int gateType;
        try
        {
            gateType = nextInt(word);
        }
        catch (const exception &e)
        {
            return false;
        }
        if (gateType == AND)
        {
            Device *temp = new gateAND();
            temp->setId(i+1);
            int pin = -1;
            while (pin != 0)
            {
                pin = nextInt(word);
                if (pin != 0)
                    conPin->at(i).push_back(pin);
            }
            circuit->push_back(temp);
        }
        else if (gateType == OR)
        {
            Device *temp = new gateOR();
            temp->setId(i+1);
            int pin = -1;
            while (pin != 0)
            {
                pin = nextInt(word);
                if (pin != 0)
                    conPin->at(i).push_back(pin);
                    
            }
            circuit->push_back(temp);
        }
        else if (gateType == NOT)
        {
            Device *temp = new gateNOT();
            temp->setId(i+1);
            int pin = -1;
            while (pin != 0)
            {
                pin = nextInt(word);
                if (pin != 0)
                    conPin->at(i).push_back(pin);
            }
            circuit->push_back(temp);
        }
    }

    for (int i = 0; i < circuit->size(); i++)                               //set device input pin
    {
        for (int j = 0; j < conPin->at(i).size(); j++)
        {
            int debug=conPin->at(i).at(j);
            int cirsize=circuit->size();
            int pinsize=conPin[i].size();
            if (conPin->at(i).at(j) < 0)
                circuit->at(i)->addInputPin(iPins->at(conPin->at(i).at(j)*-1-1));
            else
                circuit->at(i)->addInputPin(circuit->at((conPin->at(i).at(j))-1));
        }
    }

    for(int i=0;i<circuit->size();i++)
    {
        circuit->at(i)->checkIsConnected();
    }
    ifs.close();                                                            // close file

    Load=true;
    return true;
}

std::string LogicSimulator::getSimulationResult(std::vector<__int8> inputValue)
{
    using namespace std;

    oPins=new vector<Device *>;                                             //set  output pin
    for(int i=0;i<circuit->size();i++)
    {
        if(!circuit->at(i)->getIsConnected())
        {
            Device *temp=new oPin();
            temp->addInputPin(circuit->at(i));
            oPins->push_back(temp);
        }
    }

    if(oPins->at(0)->processValue())                                        //clear the past state
    {
        for(int i=0;i<circuit->size();i++)
        {
            circuit->at(i)->clearValue();
        }
        oPins->at(0)->clearValue();
    }
    
    for(int i=0;i<iPins->size();i++)                                        //set input value
    {
        iPin* temp=(iPin*)(iPins->at(i));
        temp->setValue(inputValue[i]);
    }

    int count=0;                                                            //process gates value
    bool finalProcess[circuit->size()]={false}; 
    while(oPins->at(0)->getValue()==-1)
    {
        if(!finalProcess[count])
            finalProcess[count]=circuit->at(count)->processValue();
        count++;
        if(count >= circuit->size())
            count=0;
        oPins->at(0)->processValue();
    }

    string outPut="";                                                       //create string
    for(int i=0;i<inputValue.size();i++)
    {
        outPut+=to_string(inputValue[i]) + " ";
    }

    outPut+="| " + to_string(oPins->at(0)->getValue());

    return outPut + "\n";
}

int LogicSimulator::getiPinsSize()
{
    return iPins->size();
}

bool LogicSimulator::isLoad()
{
    return Load;
}

int LogicSimulator::nextInt(std::string &str)
{
    size_t pos = str.find(" ");
    int temp;

    try
    {
        temp = stoi(str.substr(0, pos));
    }
    catch (const std::invalid_argument &e)
    {
        temp = stoi(str.substr(0, pos - 2));
    }

    str.erase(0, pos + 1);
    return temp;
}