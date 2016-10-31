#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

class ShapeMedia;
class ComboMedia;

class MediaVisitor{
public:
    virtual void visit(ShapeMedia *sm) = 0;
    virtual void visit(ComboMedia *cm) = 0;
};

class Media {
public :
    virtual double area() const = 0 ;
    virtual double perimeter() const = 0;
    virtual void accept(MediaVisitor *mv);
    virtual void add(Media * m){
        throw std::string("Illegal: add on media");
    }
};

class ShapeMedia : public Media {
private:
    Shape* shape ;
public :
    ShapeMedia () {};
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
    void * setShape(Shape * s) {
        shape = s;
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
        for(Media *m: media){
            m->accept(mv);
        }
        mv->visit(this);
    }
};

class AreaVisitor : public MediaVisitor{
public:
    void visit(ShapeMedia *sm){
        area = sm->getShape()->area();
    }

    void visit(ComboMedia *cm){
        area = cm->area();
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
    void visit(ComboMedia *cm){

        perimeter = cm->perimeter();
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
    void visit(ComboMedia *cm){
        desc = std::string("combo(")+desc+std::string(")");
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
    virtual Media * getMedia() = 0;
};

class ShapeMediaBuilder : public MediaBuilder{
public:
    ShapeMediaBuilder (): shapeMedia(0) {}
    void buildComboMedia() {}
    void buildShapeMedia(Shape * s){
        shapeMedia = new ShapeMedia(s);
        //shapeMedia->setShape(s);
    }
    Media * getMedia(){
        return shapeMedia;
    }
private:
    ShapeMedia * shapeMedia ;
};

class ComboMediaBuilder : public MediaBuilder{
public:
    ComboMediaBuilder (): comboMedia(0) {}
    void buildComboMedia(){
        comboMedia = new ComboMedia();
    }
    void buildShapeMedia(Shape * s) {
        if(!comboMedia)
            throw std::string("Null pointer exception!!!");
        comboMedia->add(new ShapeMedia(s));
    }
private:
    ComboMedia * comboMedia;
};


#endif // MEDIA_H_INCLUDED
