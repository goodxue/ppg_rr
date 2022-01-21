#include "ppg_rr_cpp.h"

int main() 
{
    std::vector<double> ppg = {1,2,3,4,5};
    std::vector<double> v1 = {5,6,7,8,9};
    ppg_rr(ppg,v1);
    return 0;
}