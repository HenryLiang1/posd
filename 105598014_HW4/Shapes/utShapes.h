#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Media.h"
#include <string>

const double epsilon = 0.000001;
// added this line

//test shape
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

//test triangle sides
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

//HW3
//Combo ---- Combo----------Rectangle
//		       |      |
//		       |      ----Triangle
//		       ---Triangle
TEST(ComboMedia, AreaVisitor){
    Rectangle r1(0,2*sqrt(3),2,2*sqrt(3));
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));
    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    std::vector<Media *> ms;
    ComboMedia cm1(ms);
    cm1.add(&sR1);
    cm1.add(&sT1);

    ComboMedia cm2(ms);
    cm1.add(&sT2);
    cm2.add(&cm1);

    AreaVisitor av;
    cm2.accept(&av);
    DOUBLES_EQUAL(6*sqrt(3),av.getArea(),epsilon);
}

//Combo ---- Combo----------Rectangle
//		       |      |
//		       |      ----Triangle
//		       ---Triangle
TEST(ComboMedia, PerimeterVisitor){
    Rectangle r1(0,2*sqrt(3),2,2*sqrt(3));
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));
    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    std::vector<Media *> ms;
    ComboMedia cm1(ms);
    cm1.add(&sR1);
    cm1.add(&sT1);

    ComboMedia cm2(ms);
    cm1.add(&sT2);
    cm2.add(&cm1);

    PerimeterVisitor pv;
    cm2.accept(&pv);
    DOUBLES_EQUAL(12+8*sqrt(3),pv.getPerimeter(),epsilon);

}

TEST(ShapeMedia, DescriptionVisitor){
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1(&r1);
    DescriptionVisitor dv;
    sR1.accept(&dv);
    CHECK(std::string("r(0,0,4,2) ") == dv.getDescription());
}

TEST(ComboMedia, DescriptionVisitor){
    Rectangle r1(0,0,4,2);
    Triangle t1(0,0,3,0,6,0);
    Circle c1(5,5,10);
    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sC1(&c1);
    std::vector<Media *> ms = {&sR1,&sT1,&sC1};
    ComboMedia cHexgon(ms);
    DescriptionVisitor dv;
    cHexgon.accept(&dv);
    CHECK(std::string("combo(r(0,0,4,2) t(0,0,3,0,6,0) c(5,5,10) )") == dv.getDescription())
}


TEST(AddMedia, ComboMedia){
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1(&r1);
    ShapeMedia sR2(&r2);
    std::vector<Media *> ms;
    ComboMedia cm(ms);
    cm.add(&sR1);
    cm.add(&sR2);
    AreaVisitor av;
    cm.accept(&av);
    DOUBLES_EQUAL(20,av.getArea(),epsilon);
}

TEST(IllegalAdd, ShapeMedia){
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    ShapeMedia sR1(&r1);
    ShapeMedia sC1(&c1);
    try{
        sR1.add(&sC1);
        FAIL("should not be here");
    }
    catch(std::string s){
        CHECK(std::string("Illegal: add on media") == s);
    }
}


//HW4
TEST(ShapeMediaBuilder, MediaBuilder){
    ShapeMediaBuilder sMB;
    Circle c1(0,0,5);
    sMB.buildShapeMedia(&c1);
    Media * m = sMB.getMedia();
    DescriptionVisitor dv;
    m->accept(&dv);
    CHECK(std::string("c(0,0,5) ") == dv.getDescription());
}

//buildShapeMedia issue
TEST(ComboMediaBuilder, MediaBuilder){
    ShapeMediaBuilder sMB;
    Rectangle r1(10,0,15,5);
    Circle c1(12,5,2);
    Rectangle r2(0,0,25,20);
    sMB.buildShapeMedia(&r1);
    sMB.buildShapeMedia(&c1);
    sMB.buildShapeMedia(&r2);
    Media * m = sMB.getMedia();
    DescriptionVisitor dv;
    m->accept(&dv);
    CHECK(std::string("r(0,0,25,20) ") == dv.getDescription());

    /*ComboMediaBuilder cMB;
    cMB.buildComboMedia()*/

}

#endif // UTSHAPES_H_INCLUDED
