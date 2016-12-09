#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"
#include "Instruction.h"



int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    Instruction Instr;
    std::string ins;
    do{
        std::cout<<":- ";
        std::getline(std::cin,ins);
        Instr.runInstruction(ins);
    }while(ins != "e");
    return 0;
}


