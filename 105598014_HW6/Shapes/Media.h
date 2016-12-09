#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED
#include <stack>
#include <regex>

class ShapeMedia;
class ComboMedia;
class TextMedia;

class MediaVisitor{
public:
    virtual void visit(ShapeMedia *sm) = 0;
    virtual void visit(ComboMedia *cm, bool start) = 0;
    virtual void visit(TextMedia *tm) = 0;
};

class Media {
public :
    virtual void setName(std::string  name) = 0;
    virtual std::string getName() = 0;
    virtual double area() const = 0 ;
    virtual double perimeter() const = 0;
    virtual void accept(MediaVisitor *mv) = 0;
    virtual void add(Media * m){
        throw std::string("Illegal: add on media");
    }
    virtual void removeMedia(Media * m) = 0;
    virtual void removeMediaByName(std::string name) = 0;
};

class ShapeMedia : public Media {
private:
    Shape * shape ;
    std::string  shapeName;
public :
    ShapeMedia(){};
    ShapeMedia( Shape* s ): shape(s) {}
    void setName(std::string  name){
        shapeName = name;
    }
    std::string getName(){
        return shapeName;
    }
    double area() const {
        return shape->area();
    }
    double perimeter() const {
        return shape->perimeter();
    }

    void accept(MediaVisitor *mv) {
         mv->visit(this);
    }
    void removeMedia(Media * m){}
    Shape * getShape() const {
         return shape;
    }
    void removeMediaByName(std::string name){}
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
    std::string  comboName;
public:
    ComboMedia () {}
    ComboMedia( std::vector<Media*> m ) : media(m) {}
    void setName(std::string  name){
        comboName = name;
    }
    std::string getName(){
        return comboName;
    }
    double area() const{
        double total =0;
            for (Media *m: media)
                total += m->area();
        return total;
    }
    double perimeter() const{
        double total = 0;
        for(Media* m : media)
            total += m->perimeter();
        return total;
    }

    void add(Media* m){
        media.push_back(m);
    }

    void accept(MediaVisitor *mv){
        mv->visit(this,true);
        for(Media *m: media){
            m->accept(mv);
        }
        mv->visit(this,false);
    }
    void removeMedia(Media *m){
        for(unsigned int i=0; i<media.size();i++){
            if(dynamic_cast<ComboMedia*>(media[i])){
                //ComboMedia *cm = dynamic_cast<ComboMedia*>(media[i]);
                media[i]->removeMedia(m);
            }
            if(media[i] == m){
                media.erase(media.begin()+i);
            }
        }
    }
    void removeMediaByName(std::string name){
        for(unsigned int i=0; i<media.size();i++){
            if(dynamic_cast<ComboMedia*>(media[i])){
                //ComboMedia *cm = dynamic_cast<ComboMedia*>(media[i]);
                media[i]->removeMediaByName(name);
            }
            if(media[i]->getName() == name){
                media.erase(media.begin()+i);
            }
        }
    }
};

class Text{
private:
    Shape * shape;
    std::string btext;

public:
    Text(Rectangle * boundingbox, std::string text): shape(boundingbox), btext(text) {};
    Shape * getShape(){
        return shape;
    }
    std::string getBText(){
        return btext;
    }
};

class TextMedia : public Media{
private:
    Text * text;
    std::string  myName;
public:
    TextMedia(Text* t): text(t) {}
    void setName(std::string  name){
        myName = name;
    }
    std::string getName(){
        return myName;
    }
    double area() const {
        return text->getShape()->area();
    }
    double perimeter() const {
        return text->getShape()->perimeter();
    }

    void accept(MediaVisitor *mv) {
         mv->visit(this);
    }
    void removeMedia(Media * m){}
    void removeMediaByName(std::string name){}
    Text * getText(){
        return text;
    }
};

class AreaVisitor : public MediaVisitor{
public:
    void visit(ShapeMedia *sm){
        area = sm->getShape()->area();
    }

    void visit(ComboMedia *cm, bool start){
        area = cm->area();
    }

    void visit(TextMedia *tm){
        area = tm->area();
    }

    double getArea(){
        return area;
    }

private:
    double area;
};

class PerimeterVisitor : public MediaVisitor{
public:
    void visit(ShapeMedia *sm){
        perimeter = sm->getShape()->perimeter();
    }
    void visit(ComboMedia *cm, bool start){
        perimeter = cm->perimeter();
    }
    void visit(TextMedia *tm){
        perimeter = tm->perimeter();
    }

    double getPerimeter(){
        return perimeter;
    }

private:
    double perimeter;
};

class DescriptionVisitor : public MediaVisitor{
public:
    void visit(ShapeMedia *sm){
        desc += sm->getShape()->description();
    }
    void visit(ComboMedia *cm, bool start){
        if(start)
            desc = desc + std::string("combo(");
        else
            desc = desc + std::string(")");
    }
    void visit(TextMedia *tm){
        desc +=  tm->getText()->getBText() + " " + tm->getText()->getShape()->description();
    }

    std::string getDescription(){
        return desc;
    }
private:
    std::string desc;
};

class NameVisitor : public MediaVisitor{
public:
    void visit(ShapeMedia *sm){
        desc += sm->getName() + std::string(" ");
    }
    void visit(ComboMedia *cm, bool start){
        if(start)
            desc = desc + cm->getName() + std::string("{");
        else
            desc = desc + std::string("}");
    }
    void visit(TextMedia *tm){
        desc +=  tm->getName();
    }

    std::string getDescription(){
        return desc;
    }
private:
    std::string desc;
};


class MediaBuilder{
public:
    virtual void buildComboMedia() = 0;
    virtual void buildComboMedia(std::string comboName) = 0;
    virtual void buildShapeMedia(Shape * s) = 0;
    virtual void buildShapeMedia(std::string  shapeName, Shape * s) = 0;
    virtual void buildAddComboMedia(Media * cm){}
    virtual Media * getMedia() = 0;
};

class ShapeMediaBuilder : public MediaBuilder{
public:
    ShapeMediaBuilder (): shapeMedia(0) {}
    void buildComboMedia() {
        throw std::string("Illegal: use buildShapeMedia");
    }
    void buildComboMedia(std::string comboName){
        throw std::string("Illegal: use buildShapeMedia");
    }
    void buildShapeMedia(Shape * s){
        shapeMedia = new ShapeMedia(s);
    }
    void buildShapeMedia(std::string  shapeName, Shape * s){
        shapeMedia = new ShapeMedia(s);
        shapeMedia->setName(shapeName);

    }
    Media * getMedia(){
        return shapeMedia;
    }
private:
    ShapeMedia * shapeMedia ;
};

class ComboMediaBuilder : public MediaBuilder {
public:
    ComboMediaBuilder (): comboMedia(0) {}
    void buildComboMedia() {comboMedia = new ComboMedia;}
    void buildComboMedia(std::string comboName){
        comboMedia = new ComboMedia;
        comboMedia->setName(comboName);
    }
    void buildShapeMedia(Shape * s) {
        if(!comboMedia)
            throw std::string("null point ex") ;
        comboMedia->add(new ShapeMedia(s));

    }
    void buildShapeMedia(std::string shapeName, Shape * s){
        if(!comboMedia)
            throw std::string("null point ex") ;
        ShapeMedia * shapeMedia = new ShapeMedia(s);
        shapeMedia->setName(shapeName); // 把我們傳進來的name給新建的shapeMedia取名子
        comboMedia->add(shapeMedia); // 一開始你沒有加這行, 這行就是把新建出來的ShapeMedia給add到comboMedia裡面 你一開始不是呼叫這個function阿XD
    }
    void buildAddComboMedia(Media * cm){
        comboMedia->add(cm);
    }
    void buildRemoveShapeMedia(Media * cm){
        comboMedia->removeMedia(cm);
    }

    Media * getMedia(){
        return comboMedia;
    }
private:
    ComboMedia * comboMedia;
};

class MediaDirector{
public:
    void setMediaBuilder(std::stack<MediaBuilder *> *mbs){
        mb = mbs;
    }
    void concrete(std::string content){
        std::regex comboReg("combo\\((.*\\))");
        std::regex popComboReg("^\\)(.*)");
        std::regex rectReg("^(r\\((\\d+) (\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::regex circReg("^(c\\((\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::regex triaReg("^(t\\((\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::smatch sm;

        if(std::regex_match(content, sm, comboReg)){
            mb->push(new ComboMediaBuilder());
            mb->top()->buildComboMedia();
            if(mediaName.size() > 0){
                Media * m = mb->top()->getMedia();
                m->setName(mediaName[0]);
                std::cout<<"GET1"<<m->getName()<<std::endl;
                mediaName.erase(mediaName.begin() + 0);
            }
            /*for(unsigned int i = 0; i < mediaName.size(); i++){
            std::cout<<"WWW"<<mediaName[i]<<std::endl;
            }*/

            content = sm[sm.size()-1];
        }

        else if(std::regex_match(content, sm, rectReg)){
            std::string x = sm[2];
            std::string y = sm[3];
            std::string l = sm[4];
            std::string w = sm[5];
            Rectangle *r = new Rectangle(atof(x.c_str()), atof(y.c_str()), atof(l.c_str()), atof(w.c_str()));
            if(mediaName.size() > 0){
                //Media * m = mb->top()->getMedia(); // 這一行不明所以 這個取出來的m是combo的Media 第二個問題是你對錯誤的media去呼叫setName,
                //m->setName(mediaName[0]);             // 我們這邊要setname的media並不是combo的media, 我們要set的對象是shapeMedia才對, 所以你這邊對錯誤的人呼叫了
                mb->top()->buildShapeMedia(mediaName[0], r); // 這一行代表我建一個ShapeMedia同時跟他講我的Shape和name 好 我了解了 我一職對comboMedia 做 yes
                //std::cout<<"GET2"<<m->getName()<<std::endl;
                mediaName.erase(mediaName.begin() + 0);
            }
            content = sm[sm.size()-1];
        }

        else if(std::regex_match(content, sm, circReg)){
            std::string cx = sm[2];
            std::string cy = sm[3];
            std::string r = sm[4];
            Circle *c = new Circle(atof(cx.c_str()), atof(cy.c_str()), atof(r.c_str()));
            //mb->top()->buildShapeMedia(c); // 這才是你一開始呼叫的 呼叫錯function是第一個問題
            if(mediaName.size() > 0){
                //Media * m = mb->top()->getMedia();
                //m->setName(mediaName[0]);
                mb->top()->buildShapeMedia(mediaName[0], c);
                //std::cout<<"GET3"<<m->getName()<<std::endl;
                mediaName.erase(mediaName.begin() + 0);
            }
            content = sm[sm.size()-1];
        }

        else if(std::regex_match(content, sm, triaReg)){
            std::string x1 = sm[2];
            std::string y1 = sm[3];
            std::string x2 = sm[4];
            std::string y2 = sm[5];
            std::string x3 = sm[6];
            std::string y3 = sm[7];
            Triangle *t = new Triangle(atof(x1.c_str()), atof(y1.c_str()), atof(x2.c_str()), atof(y2.c_str()), atof(x3.c_str()), atof(y3.c_str()));
           // mb->top()->buildShapeMedia(t);
            if(mediaName.size() > 0){
                //Media * m = mb->top()->getMedia();
                //m->setName(mediaName[0]);
                mb->top()->buildShapeMedia(mediaName[0], t);
                //std::cout<<"GET4"<<m->getName()<<std::endl;
                mediaName.erase(mediaName.begin() + 0);
            }
            content = sm[sm.size()-1];
        }

        else if(std::regex_match(content, sm, popComboReg)){
            if(mb->size() > 1){
                //std::cout<<"POP"<<std::endl;
                Media * tcm = mb->top()->getMedia();
                mb->pop();
                mb->top()->buildAddComboMedia(tcm);
            }
            content = sm[sm.size()-1];
        }
        else{
            throw std::string("data format is incorrect");
        }



        if(content != ""){
            concrete(content);
        }

    }
    void setMediaName(std::vector<std::string> mn){
        mediaName = mn;

            for(unsigned int i = 0; i < mediaName.size(); i++){
                std::cout<<mediaName[i]<<std::endl;
            }
    }
private:
    std::stack<MediaBuilder *> *mb;
    std::vector<std::string> mediaName;
};



#endif // MEDIA_H_INCLUDED
