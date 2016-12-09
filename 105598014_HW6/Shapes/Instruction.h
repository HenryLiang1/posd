#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include <regex>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Media.h"


class Instruction{
private:
    std::vector<Media*> media;
    MediaBuilder * mb;
    Media * insertionMedia;
    Media * targetQueryMedia;
public:
    bool insertMedia(std::string instr){
        std::regex defCircReg("def ([a-zA-Z0-9]+) = (Circle\\((\\d+),(\\d+),(\\d+)\\))");
        std::regex defRectReg("def ([a-zA-Z0-9]+) = (Rectangle\\((\\d+),(\\d+),(\\d+),(\\d+)\\))");
        std::regex defTriaReg("def ([a-zA-Z0-9]+) = (Triangle\\((\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)\\))");
        std::regex defComboReg("def ([a-zA-Z0-9]+) = (combo\\{(.*)\\})");
        std::smatch sm;
        insertionMedia = NULL;
        if(std::regex_match(instr, sm, defCircReg)){
            std::string name = sm[1];
            std::string desc = sm[2];
            std::string cx = sm[3];
            std::string cy = sm[4];
            std::string r = sm[5];

            mb = new ShapeMediaBuilder();
            //ShapeMediaBuilder sMB;
            Circle *c = new Circle(atof(cx.c_str()), atof(cy.c_str()), atof(r.c_str()));
            mb->buildShapeMedia(name, c);
            insertionMedia = mb->getMedia();
            media.push_back(insertionMedia);
            std::cout<<">> "<<desc<<std::endl;
        }
        else if(std::regex_match(instr, sm, defRectReg)){
            std::string name = sm[1];
            std::string desc = sm[2];
            std::string x = sm[3];
            std::string y = sm[4];
            std::string l = sm[5];
            std::string w = sm[6];

            mb = new ShapeMediaBuilder();
            //ShapeMediaBuilder sMB;
            Rectangle *r = new Rectangle(atof(x.c_str()), atof(y.c_str()), atof(l.c_str()), atof(w.c_str()));
            mb->buildShapeMedia(name, r);
            insertionMedia = mb->getMedia();
            media.push_back(insertionMedia);
            std::cout<<">> "<<desc<<std::endl;
        }
        else if(std::regex_match(instr, sm, defTriaReg)){
            std::string name = sm[1];
            std::string desc = sm[2];
            std::string x1 = sm[3];
            std::string y1 = sm[4];
            std::string x2 = sm[5];
            std::string y2 = sm[6];
            std::string x3 = sm[7];
            std::string y3 = sm[8];

            mb = new ShapeMediaBuilder();
            //ShapeMediaBuilder sMB;
            Triangle *t = new Triangle(atof(x1.c_str()), atof(y1.c_str()), atof(x2.c_str()), atof(y2.c_str()), atof(x3.c_str()), atof(y3.c_str()));
            mb->buildShapeMedia(name, t);
            insertionMedia = mb->getMedia();
            media.push_back(insertionMedia);
            std::cout<<">> "<<desc<<std::endl;
        }
        else if(std::regex_match(instr, sm, defComboReg)){
            std::string name = sm[1];
            std::string desc = sm[2];
            std::string innerMedia = sm[3];
            std::vector<std::string> mediaName;

            std::stringstream ss(innerMedia);
            std::string subStr;
            while(getline(ss,subStr,' ')){
                mediaName.push_back(subStr);
            }

            mb = new ComboMediaBuilder();
            mb->buildComboMedia(name);
            for(unsigned int i = 0; i < mediaName.size(); i++){
                for(unsigned int j = 0; j < media.size(); j++){
                    if(mediaName[i] == media[j]->getName()){
                        mb->buildAddComboMedia(media[j]);
                    }
                }
            }

            insertionMedia = mb->getMedia();
            media.push_back(insertionMedia);
            DescriptionVisitor dv_cm;
            insertionMedia->accept(&dv_cm);
            NameVisitor nv_cm;
            insertionMedia->accept(&nv_cm);
            std::cout<<">> "<<nv_cm.getDescription()<<" = "<<dv_cm.getDescription()<<std::endl;
        }

        return insertionMedia;
    }

    bool queryMedia(std::string instr){
        std::regex queryReg("([a-zA-Z0-9]+)\\.([a-z]+)\\?");
        std::smatch sm;

        targetQueryMedia = NULL;
        if(std::regex_match(instr, sm, queryReg)){
            std::string name = sm[1];
            std::string oper = sm[2];
            for(Media * m : media){
                if(m->getName() == name){
                    targetQueryMedia = m;
                    if("area" == oper){
                        std::cout<<">> "<<targetQueryMedia->area()<<std::endl;
                    }
                    else if("perimeter" == oper){
                        std::cout<<">> "<<targetQueryMedia->perimeter()<<std::endl;
                    }
                }
            }
        }
        return targetQueryMedia;
    }

    bool addMedia(std::string instr){
        std::regex addReg("add ([a-zA-Z0-9]+) to ([a-zA-Z0-9]+)");
        std::smatch sm;
        bool isMatchLeftMedia = false;
        bool isMatchRightMedia = false;
        Media * leftMedia = NULL;
        Media * rightMedia = NULL;

        if(std::regex_match(instr, sm, addReg)){
            std::string leftMediaName = sm[1];
            std::string rightMediaName = sm[2];
            for(Media * m : media){
                if(m->getName() == leftMediaName){
                    isMatchLeftMedia = true;
                    leftMedia = m;
                }
                if(m->getName() == rightMediaName){
                    isMatchRightMedia = true;
                    rightMedia = m;
                }
            }
            if(isMatchLeftMedia && isMatchRightMedia){
                rightMedia->add(leftMedia);
                DescriptionVisitor dv_add;
                rightMedia->accept(&dv_add);
                NameVisitor nv_add;
                rightMedia->accept(&nv_add);
                std::cout<<">> "<<rightMedia->getName()<<" = "<<nv_add.getDescription()<<" = "<<dv_add.getDescription()<<std::endl;
                return true;
            }
        }
        return false;
    }

    bool deleteMedia(std::string instr){
        std::regex delReg("delete ([a-zA-Z0-9]+) from ([a-zA-Z0-9]+)");
        std::regex delAllReg("delete ([a-zA-Z0-9]+)");
        std::smatch sm;
        bool isMatchLeftMedia = false;
        bool isMatchRightMedia = false;
        Media * leftMedia = NULL;
        Media * rightMedia = NULL;

        if(std::regex_match(instr, sm, delReg)){
            std::string leftMediaName = sm[1];
            std::string rightMediaName = sm[2];

            for(Media * m : media){
                if(m->getName() == leftMediaName){
                    isMatchLeftMedia = true;
                    leftMedia = m;
                }
                if(m->getName() == rightMediaName){
                    isMatchRightMedia = true;
                    rightMedia = m;
                }
            }
            if(isMatchLeftMedia && isMatchRightMedia){
                rightMedia->removeMedia(leftMedia);
                DescriptionVisitor dv_add;
                rightMedia->accept(&dv_add);
                NameVisitor nv_add;
                rightMedia->accept(&nv_add);
                std::cout<<">> "<<rightMedia->getName()<<" = "<<nv_add.getDescription()<<" = "<<dv_add.getDescription()<<std::endl;
                return true;
            }
        }
        else if(std::regex_match(instr, sm, delAllReg)){
            std::string delMediaName = sm[1];
            for(unsigned int i = 0; i < media.size(); i++){
                if(media[i]->getName() == delMediaName){
                    media.erase(media.begin() + i);
                }
                if(dynamic_cast<ComboMedia*>(media[i])){
                    media[i]->removeMediaByName(delMediaName);
                }

            }

        }
        return false;

    }

    bool saveMedia(std::string instr){
        std::regex saveReg("save ([a-zA-Z0-9]+) to \"([a-zA-Z0-9]+.txt)\"");
        std::smatch sm;
        bool isMatchSaveMedia = false;
        Media * saveMedia = NULL;

        MyInstructionDocument instrDoc;
        std::vector<std::string> dataset;

        if(std::regex_match(instr, sm, saveReg)){
            std::string saveMediaName = sm[1];
            std::string saveFileName = sm[2];
            for(Media * m : media){
                if(m->getName() == saveMediaName){
                    isMatchSaveMedia = true;
                    saveMedia = m;
                    DescriptionVisitor dv_save;
                    saveMedia->accept(&dv_save);
                    NameVisitor nv_save;
                    saveMedia->accept(&nv_save);
                    dataset.push_back(dv_save.getDescription());
                    dataset.push_back(nv_save.getDescription());
                    instrDoc.writeDocument(saveFileName, dataset);
                }
            }
            if(isMatchSaveMedia){
                std::cout<<">> "<<saveMediaName<<" saved to "<<saveFileName<<std::endl;
                return true;
            }
        }
        return false;
    }

    bool loadMedia(std::string instr){
        std::regex loadReg("load \"([a-zA-Z0-9]+.txt)\"");
        std::smatch sm;
        MyInstructionDocument instrDoc;
        std::vector<std::string> dataset;
        if(std::regex_match(instr, sm, loadReg)){

            std::string loadFileName = sm[1];
            std::cout<<">> "<<"loading "<<loadFileName<<"..."<<std::endl;
            try{
                dataset = instrDoc.openDocument(loadFileName);
            }
            catch(std::string s){
                std::cout<<s<<std::endl;
            }

            std::string mediaStrustureData = dataset[0];
            std::string mediaNameData = dataset[1];

            for(unsigned int i=0; i<mediaNameData.size(); i++){
                if(mediaNameData[i] == '{' || mediaNameData[i] == '}'){
                    mediaNameData[i] = ' ';
                }
            }

            std::vector<std::string> mediaName;
            std::stringstream ss(mediaNameData);
            std::string subStr;
            while(getline(ss,subStr,' ')){
                mediaName.push_back(subStr);
            }
            //std::reverse(mediaName.begin(), mediaName.end());


            MediaDirector md;
            std::stack<MediaBuilder *> mbs;
            md.setMediaName(mediaName);
            md.setMediaBuilder(&mbs);
            md.concrete(mediaStrustureData);

            DescriptionVisitor dv_load;
            Media *m = mbs.top()->getMedia();
            m->accept(&dv_load);
            NameVisitor nv_load;
            m->accept(&nv_load);
            media.push_back(m);
            std::cout<<">> "<<m->getName()<<" = "<<nv_load.getDescription()<<" = "<<dv_load.getDescription()<<std::endl;

            /*for(unsigned int i = 0; i < mediaName.size(); i++){
                std::cout<<mediaName[i]<<std::endl;
            }*/

            /*for(unsigned int i = 0; i < dataset.size(); i++){
                std::cout<<dataset[i]<<std::endl;
            }*/
        }
        return false;
    }

    void showMedia(){
        for(Media * m : media){
            std::cout<<">> "<<m->getName()<<std::endl;
        }
    }

    void runInstruction(std::string instr){
        std::regex defReg("def(.*)");
        std::regex addReg("add(.*)");
        std::regex delReg("delete(.*)");
        std::regex saveReg("save(.*)");
        std::regex loadReg("load(.*)");
        std::regex showReg("show");

        std::regex queryReg("([a-zA-Z0-9]+).([a-z]+)\\?");
        std::smatch sm;
        if(std::regex_match(instr, sm, defReg)){
            insertMedia(instr);
        }
        else if(std::regex_match(instr, sm, queryReg)){
            queryMedia(instr);
        }
        else if(std::regex_match(instr, sm, showReg)){
            showMedia();
        }
        else if(std::regex_match(instr, sm, addReg)){
            addMedia(instr);
        }
        else if(std::regex_match(instr, sm, delReg)){
            deleteMedia(instr);
        }
        else if(std::regex_match(instr, sm, saveReg)){
            saveMedia(instr);
        }
       else if(std::regex_match(instr, sm, loadReg)){
            loadMedia(instr);
       }
    }

    Media * getInsertionMedia(){
        return insertionMedia;
    }

    Media * getTargetQueryMedia(){
        return targetQueryMedia;
    }

};



#endif // INSTRUCTION_H_INCLUDED
