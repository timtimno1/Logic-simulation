#ifndef Device_h
#define Device_h

#include <vector>
#include <iostream>

const int AND=1;
const int OR=2;
const int NOT=3;

class Device
{
    public:
        void addInputPin(Device *);
        void setId(int);
        void clearValue();
        bool processValue();
        bool checkIsConnected();
        bool getIsConnected();
        virtual int getType();
        __int8 getValue();
    protected:
        std::vector<Device *> iPins;
        __int8 value=-1;
    private:
        int id;
        bool isConnected=false;
};
#endif