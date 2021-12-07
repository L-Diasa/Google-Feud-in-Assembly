#include "displayFuncs.h"
#include "rounds.h"

int main()
{
    initGraph();

    printGoogleFeud();

    drawRectangles();

    printNumerics();

    rounds();

    closeGraph();

    return 0;
}
