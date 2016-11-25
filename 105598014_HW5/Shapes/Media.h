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
    virtual double area() const = 0 ;
    virtual double perimeter() const = 0;
    virtual void accept(MediaVisitor *mv) = 0;
    virtual void add(Media * m){
        throw std::string("Illegal: add on media");
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
public:
    TextMedia(Text* t): text(t) {}
    double area() const {
        return text->getShape()->area();
    }
    double perimeter() const {
        return text->getShape()->perimeter();
    }

    void accept(MediaVisitor *mv) {
         mv->visit(this);
    }
    Text * getText(){
        return text;
    }
};

class ShapeMedia : public Media {
private:
    Shape * shape ;
public :
    ShapeMedia(){};
    ShapeMedia( Shape* s ): shape(s) {}
    double area() const {
        return shape->area();
    }
    double perimeter() const {
        return shape->perimeter();
    }

    void accept(MediaVisitor *mv) {
         mv->visit(this);
    }
    Shape * getShape() const {
         return shape;
    }
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
    ComboMedia () {}
    ComboMedia( std::vector<Media*> m ) : media(m) {}
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
                ComboMedia *cm = dynamic_cast<ComboMedia*>(media[i]);
                cm->removeMedia(m);
            }
            if(media[i] == m){
                media.erase(media.begin()+i);
            }
        }
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


class MediaBuilder{
public:
    virtual void buildComboMedia() = 0;
    virtual void buildShapeMedia(Shape * s) = 0;
    virtual void buildAddComboMedia(Media * cm){}
    virtual Media * getMedia() = 0;
};

class ShapeMediaBuilder : public MediaBuilder{
public:
    ShapeMediaBuilder (): shapeMedia(0) {}
    void buildComboMedia() {
        throw std::string("Illegal: use buildShapeMedia");
    }
    void buildShapeMedia(Shape * s){
        shapeMedia = new ShapeMedia(s);
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
    void buildShapeMedia(Shape * s) {
        if(!comboMedia)
            throw std::string("null point ex") ;
        comboMedia->add(new ShapeMedia(s));

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
        //std::regex innerComboReg("combo\\((.*) (\\)com|\\))");
        std::regex rectReg("^(r\\((\\d+) (\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::regex circReg("^(c\\((\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::regex triaReg("^(t\\((\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)\\) )(.*)");
        std::smatch sm;
        std::smatch rectSm;
        std::smatch circSm;
        std::smatch triaSm;


        if(std::regex_match(content, sm, comboReg)){
            /*std::cout<<"match Combo!!"<<std::endl;
            std::cout<<"The matchs are:"<<std::endl;

            for(unsigned int i = 0 ; i < sm.size() ; i++ ){
                std::cout << i << ": [" << sm[i] << "]" << std::endl;
            }*/
                mb->push(new ComboMediaBuilder());
                mb->top()->buildComboMedia();
                //std::cout<<"current size : "<<mb->size()<<std::endl;

                content = sm[sm.size()-1];
        }

        /*if(std::regex_match(ss, sm, comboReg)){
            std::cout<<"match Combo!!"<<std::endl;
            std::cout<<"The matchs are:"<<std::endl;
            mb->push(new ComboMediaBuilder());
            mb->top()->buildComboMedia();
            std::cout<<"current size : "<<mb->size()<<std::endl;
            std::string ss = sm[sm.size()-1];
        }*/

        if(std::regex_match(content, sm, rectReg)){
            /*std::cout<<"match Rectangle!!"<<std::endl;
            std::cout<<"The match are:"<<std::endl;
            for(unsigned int i=0; i<sm.size(); i++){
                std::cout<<i<<": ["<< sm[i] << "]" <<std::endl;
            }*/

            std::string x = sm[2];
            std::string y = sm[3];
            std::string l = sm[4];
            std::string w = sm[5];

            Rectangle *r = new Rectangle(atoi(x.c_str()), atoi(y.c_str()), atoi(l.c_str()), atoi(w.c_str()));
            mb->top()->buildShapeMedia(r);

            content = sm[sm.size()-1];

        //std::cout<<sm[sm.size()-1]<<std::endl;
        }


        if(std::regex_match(content, sm, circReg)){
            /*std::cout<<"match Circle!!"<<std::endl;
            std::cout<<"The match are:"<<std::endl;
            for(unsigned int i=0; i<sm.size(); i++){
                std::cout<<i<<": ["<< sm[i] <<"]"<<std::endl;
            }*/

            std::string cx = sm[2];
            std::string cy = sm[3];
            std::string r = sm[4];

            Circle *c = new Circle(atoi(cx.c_str()), atoi(cy.c_str()), atoi(r.c_str()));
            mb->top()->buildShapeMedia(c);

            content = sm[sm.size()-1];
        }


        if(std::regex_match(content, sm, triaReg)){
            /*std::cout<<"match Triangle!!"<<std::endl;
            std::cout<<"The match are::"<<std::endl;
            for(unsigned int i=0;i<sm.size(); i++){
                std::cout<<i<<": ["<< sm[i] <<"]"<<std::endl;
            }*/

            std::string x1 = sm[2];
            std::string y1 = sm[3];
            std::string x2 = sm[4];
            std::string y2 = sm[5];
            std::string x3 = sm[6];
            std::string y3 = sm[7];

            Triangle *t = new Triangle(atoi(x1.c_str()), atoi(y1.c_str()), atoi(x2.c_str()), atoi(y2.c_str()), atoi(x3.c_str()), atoi(y3.c_str()));
            mb->top()->buildShapeMedia(t);

            content = sm[sm.size()-1];
        }

        if(std::regex_match(content, sm, popComboReg)){
            /*std::cout<<"match popCombo!!"<<std::endl;
            std::cout<<"The match are::"<<std::endl;
            for(unsigned int i=0;i<sm.size(); i++){
                std::cout<<i<<": ["<< sm[i] <<"]"<<std::endl;
            }
            std::cout<<"current size : "<<mb->size()<<std::endl;*/
            if(mb->size() > 1 ){
                Media * tcm = mb->top()->getMedia();
                mb->pop();
                mb->top()->buildAddComboMedia(tcm);
            }
            content = sm[sm.size()-1];
        }


        //std::cout<<"Content :"<<content<<std::endl;
        if(content != "")
            concrete(content);

        //std::cout<<"concrete content: "<<content<<std::endl;
    }
private:
    std::stack<MediaBuilder *> *mb;
};



#endif // MEDIA_H_INCLUDED
