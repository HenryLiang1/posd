#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <algorithm>    // std::sort

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
        x1(pointX1),y1(pointY1),x2(pointX2),y2(pointY2),x3(pointX3),y3(pointY3){
            lengthOfSide1 = sqrt(pow(x1-x2,2)+pow(y1-y2,2));
            lengthOfSide2 = sqrt(pow(x2-x3,2)+pow(y2-y3,2));
            lengthOfSide3 = sqrt(pow(x1-x3,2)+pow(y1-y3,2));
        }
    double area() const {
        if(checkSide() == false){
            return -1;
        }
        double s = 0.5*(lengthOfSide1+lengthOfSide2+lengthOfSide3);
        return sqrt(s*(s-lengthOfSide1)*(s-lengthOfSide2)*(s-lengthOfSide3));
    }
    double perimeter() const {
        if(checkSide() == false){
            return -1;
        }
        return lengthOfSide1+lengthOfSide2+lengthOfSide3;
    }
    bool checkSide() const {
        bool check1 = lengthOfSide1 + lengthOfSide2 > lengthOfSide3;
        bool check2 = lengthOfSide2 + lengthOfSide3 > lengthOfSide1;
        bool check3 = lengthOfSide1 + lengthOfSide3 > lengthOfSide2;

        if(lengthOfSide1 < 0 || lengthOfSide2 < 0 || lengthOfSide3 < 0){
            return false;
        }

        if(check1 == false || check2 == false || check3 == false){
            return false;
        }

        return true;
    }
private:
    double x1,y1,x2,y2,x3,y3;
    double lengthOfSide1,lengthOfSide2,lengthOfSide3;
};

double sumOfArea(std::vector<Rectangle> rects){
    double total =0;
    for (Rectangle r: rects)
        total += r.area();
    return total;
}

double sumOfArea(const std::vector<Shape *> &shapes){
    double total =0;
    for (Shape *s: shapes)
        total += s->area();
    return total;
}

double sumOfPerimeter(const std::vector<Shape *> &shapes){
    double total=0;
    for(Shape *s: shapes)
        total += s->perimeter();
    return total;
}

bool sortByIncreasingAreaOperator(Shape *si, Shape *sj){
    return si->area() < sj->area();
}

bool sortByDecreasingPerimeterOperator(Shape *si, Shape *sj){
    return si->perimeter() > sj->perimeter();
}

double maxArea(std::vector<Shape *> &shapes){
    std::vector<Shape *>::iterator result = std::max_element(shapes.begin(), shapes.end(), sortByIncreasingAreaOperator);
    return (*result)->area();
}

void sortByDecreasingPerimeter(std::vector<Shape *> &shapes){
    std::sort(shapes.begin(), shapes.end(), sortByDecreasingPerimeterOperator);
}

class ComboShape : public Shape{
public:
    ComboShape(const std::vector<Shape *> & shapes):
        ss(shapes) {};

    void add(Shape * shape){
        ss.push_back(shape);
    }

    double area() const {
        return sumOfArea(ss);
    }

    double perimeter() const{
        return sumOfPerimeter(ss);
    }

private:
    std::vector<Shape *> ss;

};


#endif // SHAPES_H_INCLUDED
