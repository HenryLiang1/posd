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
TEST(ninth_2, ComboMediaArea){
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1(&r1);
    ShapeMedia sR2(&r2);
    std::vector<Media*> ms = {&sR1, &sR2};
    ComboMedia cs(ms);
    DOUBLES_EQUAL(20, cs.area(), epsilon);
}

TEST(shapeMedia, AreaVisitor){
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1(&r1);
    AreaVisitor av;
    sR1.accept(&av);
    DOUBLES_EQUAL(8,av.getArea(),epsilon);;
}

TEST(comboMedia, AreaVisitor){
    Rectangle r1(0,2,4,2);
    Circle c1(0,0,10);
    ShapeMedia sR1(&r1);
    ShapeMedia sC1(&c1);
    std::vector<Media *> ms = {&sR1, &sC1};
    ComboMedia cs(ms);
    AreaVisitor av;
    cs.accept(&av);
    DOUBLES_EQUAL(308, av.getArea(),epsilon);
}

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
    ComboMedia cHexgon(ms);
    cHexgon.add(&sR1);
    cHexgon.add(&sT1);
    cHexgon.add(&sT2);
    AreaVisitor av;
    cHexgon.accept(&av);
    DOUBLES_EQUAL(6*sqrt(3),av.getArea(),epsilon);

    ComboMedia cms(ms);
    cms.add(&cHexgon);
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
    std::vector<Media *> ms = {&sR1,&sT1,&sT2};
    ComboMedia cHexgon(ms);
    PerimeterVisitor pv;
    cHexgon.accept(&pv);
    DOUBLES_EQUAL(12+8*sqrt(3),pv.getPerimeter(),epsilon);

    ComboMedia cms(ms);
    cms.add(&cHexgon);
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

TEST(IllegalAdd, ShapeMedia){
    Rectangle r1(0,0,4,2);
    Circle c1 (0,0,10);
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


#endif // UTSHAPES_H_INCLUDED
