#include "Device.h"

#include <iostream>

void Device::setId(int id)
{
    this->id = id;
}

void Device::addInputPin(Device *pin)
{
    iPins.push_back(pin);
}

__int8 Device::getValue()
{
    return this->value;
}

bool Device::processValue()
{
    int type = this->getType();
    __int8 tempValue = (type == OR ? 0 : 1);

    for (int i = 0; i < iPins.size(); i++) {
        if (iPins.at(i)->getValue() == -1)
            return false;
        else if (type == AND)
            tempValue = tempValue & iPins.at(i)->getValue();
        else if (type == OR)
            tempValue = tempValue | iPins.at(i)->getValue();
        else if (type == NOT)
            tempValue = (!(iPins.at(i)->getValue()));
        else
            tempValue = iPins.at(0)->getValue();
    }
    this->value = tempValue;
    return true;
}

bool Device::checkIsConnected()
{
    for (int i = 0; i < iPins.size(); i++) {
        iPins.at(i)->isConnected = true;
    }
    return true;
}

bool Device::getIsConnected()
{
    return this->isConnected;
}

int Device::getType()
{
    return 0;
}

void Device::clearValue()
{
    this->value = -1;
}