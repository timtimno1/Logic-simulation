#include "Device.h"

class iPin:public Device
{
    public:
        void setValue(__int8 value)
        {
            this->value=value;
        }
};