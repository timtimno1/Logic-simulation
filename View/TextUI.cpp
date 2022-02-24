#include "TextUI.h"

#include <math.h>
#include <string.h>

#include <bitset>
#include <iostream>
#include <string>

#include "..\Model\LogicSimulator.h"

using namespace std;
void createString(string &outPut, int iPinsSize, int oPinsSie);

void TextUI::displayMenu()
{
    cout << "1. Load logic circuit file" << endl
         << "2. Simulation" << endl
         << "3. Display truth table" << endl
         << "4. Exit" << endl;
}

void TextUI::processCommand()
{
    int com = 0;
    LogicSimulator LS;
    while (com != 4)
    {
        cout << "Command:" << ends;
        cin >> com;

        if (com == 1)
        {
            string fileName;
            cout << "Please key in a file path: " << ends;
            cin >> fileName;

            try
            {
                if (!LS.load(fileName))
                    cout << "File not found or file format error!!" << endl;
            }
            catch (const exception &e)
            {
                cout << "File not found or file format error!!" << endl;
            }
        }

        if (com == 2)
        {
            string outPut = "";
            if (!LS.isLoad())
            {
                cout << "Please load an lcf file, before using this operation." << endl;
            }
            else
            {
                int iPinsSize = LS.getiPinsSize();
                vector<__int8> inputValue(iPinsSize);
                for (int i = 0; i < iPinsSize; i++)
                {
                    int value;
                    cout << "Please key in the value of input pin " << i + 1 << ": ";
                    cin >> value;
                    if (value != 1 && value != 0)
                    {
                        cout << "The value of input pin must be 0/1" << endl;
                        i--;
                    }
                    else
                    {
                        inputValue[i] = value;
                    }
                }

                string outputTemp = LS.getSimulationResult(inputValue);
                createString(outPut, iPinsSize, LS.getoPinsSize());
                outPut += "\n" + outputTemp;
                cout << outPut;
            }
        }

        if (com == 3)
        {
            if (!LS.isLoad())
            {
                cout << "Please load an lcf file, before using this operation." << endl;
            }
            else
            {
                int iPinsSize = LS.getiPinsSize();
                vector<__int8> inputBinary(iPinsSize);
                string outputTemp = "";
                string outPut = "Truth table:\n";

                int binarySize = pow(2, iPinsSize);
                for (int i = 0; i < binarySize; i++)
                {
                    outputTemp += LS.getSimulationResult(inputBinary);
                    // add function
                    int count = iPinsSize - 1;
                    inputBinary[iPinsSize - 1] += 1;
                    while (true)
                    {
                        if (inputBinary[count] >= 2)
                        {
                            inputBinary[count] -= 2;
                            count--;
                            inputBinary[count] += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                createString(outPut, iPinsSize, LS.getoPinsSize());
                outPut += "\n" + outputTemp;

                cout << outPut;
            }
        }

        if (com == 4)
        {
            cout << "Goodbye, thanks for using LS.";
        }

        cout << endl;

        if (com != 4)
            this->displayMenu();
    }
}

void createString(string &outPut, int iPinsSize, int oPinsSie)
{
    for (int i = 0; i < iPinsSize; i++)
    {
        outPut += "i ";
    }
    outPut += "| ";
    for (int i = 0; i < oPinsSie; i++)
    {
        outPut += "o ";
    }
    outPut += "\n";
    for (int i = 0; i < iPinsSize; i++)
    {
        outPut += to_string(i + 1) + " ";
    }
    outPut += "| ";
    for (int i = 0; i < oPinsSie; i++)
    {
        outPut += to_string(i + 1) + " ";
    }
    outPut += "\n";
    for (int i = 0; i < iPinsSize * 2; i++)
    {
        outPut += "-";
    }
    outPut += "+";
    for (int i = 0; i < oPinsSie * 2; i++)
    {
        outPut += "-";
    }
}