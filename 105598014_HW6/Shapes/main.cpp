#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "Instruction.h"



int main()
{
    runInstruction();
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}


