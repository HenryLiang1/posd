#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

class Media {
public :
    virtual double area() const = 0 ;
    virtual double perimeter() const = 0;
};

class ShapeMedia :public Media {
private:
    Shape* shape ;
public :
    ShapeMedia( Shape* s ): shape(s) {}
    double area() const { return shape->area(); }
    double perimeter() const { return shape->perimeter(); }
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
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
};

#endif // MEDIA_H_INCLUDED
