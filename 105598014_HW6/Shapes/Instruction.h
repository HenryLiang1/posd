#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <regex>

void runInstruction(){
    std::regex defCircReg("def ([a-zA-Z]+) = Circle\\((\\d+),(\\d+),(\\d+)\\)");
    std::regex defRectReg("def ([a-zA-Z]+) = Rectangle\\((\\d+),(\\d+),(\\d+),(\\d+)\\)");
    std::regex defTriaReg("def ([a-zA-Z]+) = Triangle\\((\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)\\)");
    std::regex defComboReg("def ([a-zA-Z]+) = combo\\{([a-zA-Z]+)(,[a-zA-Z]+)*\\}");
    std::smatch sm;
    //,([a-zA-Z0-9]+)((?:,[a-zA-Z0-9]+)*)
    std::regex_match(std::string("def comboExclamation = combo{rTall,rTallcSmall,k}"), sm, defComboReg);
    for(int i = 0; i < sm.size(); i++) {
        std::cout << i << ":" << sm[i] << std::endl;
    }

    std::string instr("def cSmall = Circle(2,1,1)");
    //do{
        std::cin>>instr;
        if(std::regex_match(instr, sm, defCircReg)){
            std::string cx = sm[2];
            std::string cy = sm[3];
            std::string r = sm[4];
            ShapeMediaBuilder sMB;
            Circle *c = new Circle(atof(cx.c_str()), atof(cy.c_str()), atof(r.c_str()));
            sMB.buildShapeMedia(c);
            Media * m = sMB.getMedia();
            DescriptionVisitor dv;
            m->accept(&dv);
            std::cout<<dv.getDescription()<<std::endl;
        }
        else if(std::regex_match(instr, sm, defRectReg)){
            std::string x = sm[2];
            std::string y = sm[3];
            std::string l = sm[4];
            std::string w = sm[5];

            ShapeMediaBuilder sMB;
            Rectangle *r = new Rectangle(atof(x.c_str()), atof(y.c_str()), atof(l.c_str()), atof(w.c_str()));
            sMB.buildShapeMedia(r);
            Media * m = sMB.getMedia();
            DescriptionVisitor dv;
            m->accept(&dv);
            std::cout<<dv.getDescription()<<std::endl;
        }
        else if(std::regex_match(instr, sm, defTriaReg)){
            std::string x1 = sm[2];
            std::string y1 = sm[3];
            std::string x2 = sm[4];
            std::string y2 = sm[5];
            std::string x3 = sm[6];
            std::string y3 = sm[7];
            //ShapeMediaBuilder
            //Triangle *t = new Triangle(atof(x1.c_str()), atof(y1.c_str()), atof(x2.c_str()), atof(y2.c_str()), atof(x3.c_str()), atof(y3.c_str()));
        }

        //std::cout<<instr<<std::endl;
    //}while(instr != "e");
}


#endif // INSTRUCTION_H_INCLUDED
