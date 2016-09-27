#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include <vector>

const double epsilon = 0.000001;
// added this line
TEST (first, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
}

TEST(sencond,Circle)
{
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
}

TEST (third, Triangle) {
    Triangle tri(0,0,3,4,6,0);
    DOUBLES_EQUAL(12,tri.area(),epsilon);
}

TEST (fourth, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,3,3);
    std::vector<Rectangle> rects;
    rects.push_back(r1);
    rects.push_back(r2);
    DOUBLES_EQUAL(17, sumOfArea(rects),epsilon);
}

TEST (fifth, sumOfArea) {
    std::vector<Rectangle> rects;
    DOUBLES_EQUAL(0, sumOfArea(rects),epsilon);
}

TEST (sixth, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(320,sumOfArea(ss),epsilon);
}

TEST (seventh, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(12,rect.perimeter(),epsilon);
}

TEST (eighth, Circle) {
    Circle circ(0,0,10);
    DOUBLES_EQUAL(60,circ.perimeter(),epsilon);
}

TEST (ninth, Triangle) {
    Triangle tri(0,0,3,4,6,0);
    DOUBLES_EQUAL(16,tri.perimeter(),epsilon);
}

TEST (eleventh, sumOfPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(88,sumOfPerimeter(ss),epsilon);
}


#endif // UTSHAPES_H_INCLUDED
