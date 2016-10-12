#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Media.h"

const double epsilon = 0.000001;
// added this line

//HW1
TEST (first, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8,rect.area(),epsilon);
}

TEST (first_2, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(12,rect.perimeter(),epsilon);
}

TEST (sencond,Circle)
{
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300,circ.area(),epsilon);
}

TEST (sencond_2, Circle) {
    Circle circ(0,0,10);
    DOUBLES_EQUAL(60,circ.perimeter(),epsilon);
}

TEST (third, Triangle) {
    Triangle tri(0,0,3,4,6,0);
    CHECK_EQUAL(true,tri.checkSide());
}

TEST (third_2, Triangle) {
    Triangle tri(0,0,3,4,6,0);
    DOUBLES_EQUAL(12,tri.area(),epsilon);
}

TEST (third_3, Triangle) {
    Triangle tri(0,0,3,4,6,0);
    DOUBLES_EQUAL(16,tri.perimeter(),epsilon);
}

TEST (third_4, Triangle) {
    Triangle nonTri(0,0,3,0,6,0);
    CHECK_EQUAL(false,nonTri.checkSide());
}

TEST (third_5, Triangle) {
    Triangle nonTri(0,0,3,0,6,0);
    DOUBLES_EQUAL(-1,nonTri.perimeter(),epsilon);
}

TEST (third_6, Triangle) {
    Triangle nonTri(0,0,3,0,6,0);
    DOUBLES_EQUAL(-1,nonTri.area(),epsilon);
}

TEST (fourth, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(320,sumOfArea(ss),epsilon);
}

TEST (fifth, sumOfPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(88,sumOfPerimeter(ss),epsilon);
}


//HW2
TEST(sixth, maxArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(300,maxArea(ss),epsilon);
}

TEST(seventh, sortByDecreasingPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    ss.push_back(&t1);
    DOUBLES_EQUAL(12,ss[0]->perimeter(),epsilon);
    DOUBLES_EQUAL(60,ss[1]->perimeter(),epsilon);
    DOUBLES_EQUAL(16,ss[2]->perimeter(),epsilon);

    sortByDecreasingPerimeter(ss);
    DOUBLES_EQUAL(60,ss[0]->perimeter(),epsilon);
    DOUBLES_EQUAL(16,ss[1]->perimeter(),epsilon);
    DOUBLES_EQUAL(12,ss[2]->perimeter(),epsilon);
}

TEST(eighth, comboShapePerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    std::vector<Shape *> ss{&r1,&c1};
    ComboShape comboShape(ss);
    DOUBLES_EQUAL(72,comboShape.perimeter(),epsilon);
}

TEST(eighth_2, comboShapePerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss{&r1,&c1};
    ComboShape comboShape(ss);
    std::vector<Shape *> ss2{&t1};
    ComboShape comboShape2(ss2);
    comboShape2.add(&comboShape);
    DOUBLES_EQUAL(88,comboShape2.perimeter(),epsilon);
}

TEST(eighth_3, comboShapeArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    std::vector<Shape *> ss{&r1,&c1};
    ComboShape comboShape(ss);
    DOUBLES_EQUAL(308,comboShape.area(),epsilon);
}

TEST(eighth_4, comboShapeArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,3,4,6,0);
    std::vector<Shape *> ss{&r1,&c1};
    ComboShape comboShape(ss);
    std::vector<Shape *> ss2{&t1};
    ComboShape comboShape2(ss2);
    comboShape2.add(&comboShape);
    DOUBLES_EQUAL(320,comboShape2.area(),epsilon);
}


//HW3
TEST(ninth_2, ComboMediaArea){
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1(&r1);
    ShapeMedia sR2(&r2);
    std::vector<Media*> ms = {&sR1, &sR2};
    ComboMedia cs(ms);
    DOUBLES_EQUAL(20, cs.area(), epsilon);

}

#endif // UTSHAPES_H_INCLUDED
