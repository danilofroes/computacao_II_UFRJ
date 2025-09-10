#include "aula0201.h"

ull CalcularMaximoDivisorComum(ull x, ull y) {
    if (x % y != 0)
        return CalcularMaximoDivisorComum(y, x % y);
    
    else if (x % y == 0 || x == 0)
        return y;
    
    else if (y == 0)
        return x;

    return 0;
}