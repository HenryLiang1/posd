#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <vector>

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};
class Rectangle : public Shape {
public:
    Rectangle(double ulcx, double ulcy, double length, double width):
        x(ulcx),y(ulcy),l(length),w(width){}
    double area() const {return l*w;}
    double perimeter() const {return 2*(l+w);}
private:
    double x,y,l,w;
};

class Circle : public Shape{
public:
    Circle(double centerX,double centerY,double radius):
        cx(centerX),cy(centerY),r(radius){}
    double area()const {return 3*r*r;}
    double perimeter() const {return 3*2*r;}
private:
    double cx,cy,r;
};

class Triangle : public Shape{
public:
    Triangle(double pointX1, double pointY1, double pointX2, double pointY2, double pointX3, double pointY3):
        x1(pointX1),y1(pointY1),x2(pointX2),y2(pointY2),x3(pointX3),y3(pointY3){}
    double area() const {
        double edge1 = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        double edge2 = sqrt(pow(x2-x3,2)+pow(y2-y3,2));
        double edge3 = sqrt(pow(x1-x3,2)+pow(y1-y3,2));
        double s = 0.5*(edge1+edge2+edge3);
        return sqrt(s*(s-edge1)*(s-edge2)*(s-edge3));
    }
    double perimeter() const {
        double edge1 = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
        double edge2 = sqrt(pow(x2-x3,2)+pow(y2-y3,2));
        double edge3 = sqrt(pow(x1-x3,2)+pow(y1-y3,2));
        return  edge1+edge2+edge3;
    }
private:
    double x1,y1,x2,y2,x3,y3;
};

double sumOfArea(std::vector<Rectangle> rects) {
    double total =0;
    for (Rectangle r: rects)
        total += r.area();
    return total;
}

double sumOfArea(std::vector<Shape *> shapes) {
    double total =0;
    for (Shape *s: shapes)
        total += s->area();
    return total;
}

double sumOfPerimeter(std::vector<Shape *> shapes){
    double total=0;
    for(Shape *s: shapes)
        total += s->perimeter();
    return total;
}

#endif // SHAPES_H_INCLUDED
