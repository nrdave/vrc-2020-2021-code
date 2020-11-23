#include "main.h"

double roundDouble(double input, int places)
{
    int tempVal = input * pow(10, places);
    return (double)input / pow(10, places);
}
