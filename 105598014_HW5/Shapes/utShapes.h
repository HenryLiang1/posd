#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include <string>
#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Media.h"
#include "Document.h"


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
    AreaVisitor av;

    ComboMedia cm1(ms);
    cm1.add(&sR1);
    cm1.accept(&av);
    DOUBLES_EQUAL(4*sqrt(3),av.getArea(),epsilon);

    cm1.add(&sT1);
    cm1.accept(&av);
    DOUBLES_EQUAL(5*sqrt(3),av.getArea(),epsilon);

    ComboMedia cm2(ms);
    cm2.add(&sT2);
    cm2.accept(&av);
    DOUBLES_EQUAL(sqrt(3),av.getArea(),epsilon);

    cm2.add(&cm1);
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
    PerimeterVisitor pv;

    ComboMedia cm1(ms);
    cm1.add(&sR1);
    cm1.accept(&pv);
    DOUBLES_EQUAL(4+4*sqrt(3),pv.getPerimeter(),epsilon);

    cm1.add(&sT1);
    cm1.accept(&pv);
    DOUBLES_EQUAL(8+6*sqrt(3),pv.getPerimeter(),epsilon);

    ComboMedia cm2(ms);
    cm2.add(&sT2);
    cm2.accept(&pv);
    DOUBLES_EQUAL(4+2*sqrt(3),pv.getPerimeter(),epsilon);

    cm2.add(&cm1);
    cm2.accept(&pv);
    DOUBLES_EQUAL(12+8*sqrt(3),pv.getPerimeter(),epsilon);

}

//Combo ---- Combo----------Rectangle
//		       |      |
//		       |      ----Triangle
//		       ---Triangle
TEST(ComboMedia, DescriptionVisitor){
    Rectangle r1(0,2*sqrt(3),2,2*sqrt(3));
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));
    ShapeMedia sR1(&r1);
    ShapeMedia sT1(&t1);
    ShapeMedia sT2(&t2);
    std::vector<Media *> ms;
    ComboMedia cm1(ms);
    cm1.add(&sR1);
    DescriptionVisitor dv1;
    cm1.accept(&dv1);
    CHECK(std::string("combo(r(0 3.4641 2 3.4641) )") == dv1.getDescription());

    cm1.add(&sT1);
    DescriptionVisitor dv1_2;
    cm1.accept(&dv1_2);
    CHECK(std::string("combo(r(0 3.4641 2 3.4641) t(0 0 -1 1.73205 0 3.4641) )") == dv1_2.getDescription());

    ComboMedia cm2(ms);
    cm2.add(&cm1);
    DescriptionVisitor dv2;
    cm2.accept(&dv2);
    CHECK(std::string("combo(combo(r(0 3.4641 2 3.4641) t(0 0 -1 1.73205 0 3.4641) ))") == dv2.getDescription());

    cm2.add(&sT2);
    DescriptionVisitor dv2_2;
    cm2.accept(&dv2_2);
    CHECK(std::string("combo(combo(r(0 3.4641 2 3.4641) t(0 0 -1 1.73205 0 3.4641) )t(2 0 3 1.73205 2 3.4641) )") == dv2_2.getDescription());
}

TEST(ComboMedia2, DescriptionVisitor){
    Rectangle r1(0,0,4,2);
    ShapeMedia sR1(&r1);
    DescriptionVisitor dv;
    sR1.accept(&dv);
    CHECK(std::string("r(0 0 4 2) ") == dv.getDescription());
}

TEST(ComboMedia3, DescriptionVisitor){
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
    CHECK(std::string("combo(r(0 0 4 2) t(0 0 3 0 6 0) c(5 5 10) )") == dv.getDescription())
}


TEST(AddMedia, ComboMedia){
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,4,3);
    ShapeMedia sR1(&r1);
    ShapeMedia sR2(&r2);
    std::vector<Media *> ms;
    ComboMedia cm(ms);
    AreaVisitor av;
    cm.add(&sR1);
    cm.accept(&av);
    DOUBLES_EQUAL(8,av.getArea(),epsilon);

    cm.add(&sR2);
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
    CHECK(std::string("c(0 0 5) ") == dv.getDescription());
}

TEST (ComboMediaBuider, MediaBuilder) {
    ComboMediaBuilder cmb;
    cmb.buildComboMedia();

    ComboMediaBuilder cmb2;
    cmb2.buildComboMedia();

    ComboMediaBuilder cmb3;
    cmb3.buildComboMedia();

    ShapeMediaBuilder smb3;
    Rectangle r1(10,0,15,5);
    smb3.buildShapeMedia(&r1);
    Media* smr1 = smb3.getMedia();
    cmb3.buildAddComboMedia(smr1); //add ShapeMedia

    DescriptionVisitor dv3;
    cmb3.getMedia()->accept(&dv3);
    CHECK(std::string("combo(r(10 0 15 5) )") == dv3.getDescription());


    Circle c1(12,5,2);
    smb3.buildShapeMedia(&c1);
    Media* smc1 = smb3.getMedia();
    cmb3.buildAddComboMedia(smc1); //add ShapeMedia

    DescriptionVisitor dv3_1;
    cmb3.getMedia()->accept(&dv3_1);
    CHECK(std::string("combo(r(10 0 15 5) c(12 5 2) )") == dv3_1.getDescription());

    Media *cm3 = cmb3.getMedia();
    cmb2.buildAddComboMedia(cm3); //add ComboMedia

    DescriptionVisitor dv2;
    cmb2.getMedia()->accept(&dv2);
    CHECK(std::string("combo(combo(r(10 0 15 5) c(12 5 2) ))") == dv2.getDescription());

    ShapeMediaBuilder smb2;
    Rectangle r2(0,0,25,20);
    smb2.buildShapeMedia(&r2);
    Media* smr2 = smb2.getMedia();
    cmb2.buildAddComboMedia(smr2); //add ShapeMedia

    DescriptionVisitor dv2_1;
    cmb2.getMedia()->accept(&dv2_1);
    CHECK(std::string("combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )") == dv2_1.getDescription());


    Media *cm2 = cmb2.getMedia();
    cmb.buildAddComboMedia(cm2); //add ComboMedia

    DescriptionVisitor dv;
    cmb.getMedia()->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) ))") == dv.getDescription());

    ShapeMediaBuilder smb;
    Triangle t1(0,20,16,32,25,20);
    smb.buildShapeMedia(&t1);
    Media* smt1 = smb.getMedia();
    cmb.buildAddComboMedia(smt1); //add ShapeMedia

    DescriptionVisitor dv_1;
    cmb.getMedia()->accept(&dv_1);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv_1.getDescription());
}

TEST(TextMedia, Media){
    Rectangle r1(0,0,4,2);
    Text te(&r1, std::string("text"));
    TextMedia tm(&te);
    DescriptionVisitor dv;
    tm.accept(&dv);
    CHECK(std::string("text r(0 0 4 2) ") == dv.getDescription());
    CHECK(std::string("text") == tm.getText()->getBText());
}

TEST(RemoveMedia, MediaBuilder){
    ComboMediaBuilder cmb;
    cmb.buildComboMedia();

    ComboMediaBuilder cmb2;
    cmb2.buildComboMedia();

    ComboMediaBuilder cmb3;
    cmb3.buildComboMedia();

    ShapeMediaBuilder smb3;
    Rectangle r1(10,0,15,5);
    smb3.buildShapeMedia(&r1);
    Media* smr1 = smb3.getMedia();
    cmb3.buildAddComboMedia(smr1); //add ShapeMedia

    DescriptionVisitor dv3;
    cmb3.getMedia()->accept(&dv3);
    CHECK(std::string("combo(r(10 0 15 5) )") == dv3.getDescription());


    Circle c1(12,5,2);
    smb3.buildShapeMedia(&c1);
    Media* smc1 = smb3.getMedia();
    cmb3.buildAddComboMedia(smc1); //add ShapeMedia

    DescriptionVisitor dv3_1;
    cmb3.getMedia()->accept(&dv3_1);
    CHECK(std::string("combo(r(10 0 15 5) c(12 5 2) )") == dv3_1.getDescription());

    Media *cm3 = cmb3.getMedia();
    cmb2.buildAddComboMedia(cm3); //add ComboMedia

    DescriptionVisitor dv2;
    cmb2.getMedia()->accept(&dv2);
    CHECK(std::string("combo(combo(r(10 0 15 5) c(12 5 2) ))") == dv2.getDescription());

    ShapeMediaBuilder smb2;
    Rectangle r2(0,0,25,20);
    smb2.buildShapeMedia(&r2);
    Media* smr2 = smb2.getMedia();
    cmb2.buildAddComboMedia(smr2); //add ShapeMedia

    DescriptionVisitor dv2_1;
    cmb2.getMedia()->accept(&dv2_1);
    CHECK(std::string("combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )") == dv2_1.getDescription());


    Media *cm2 = cmb2.getMedia();
    cmb.buildAddComboMedia(cm2); //add ComboMedia

    DescriptionVisitor dv;
    cmb.getMedia()->accept(&dv);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) ))") == dv.getDescription());

    ShapeMediaBuilder smb;
    Triangle t1(0,20,16,32,25,20);
    smb.buildShapeMedia(&t1);
    Media* smt1 = smb.getMedia();
    cmb.buildAddComboMedia(smt1); //add ShapeMedia

    DescriptionVisitor dv_1;
    cmb.getMedia()->accept(&dv_1);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv_1.getDescription());

    cmb.buildRemoveShapeMedia(smr2);

    DescriptionVisitor dv_r;
    cmb.getMedia()->accept(&dv_r);
    CHECK(std::string("combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == dv_r.getDescription());
}

TEST(IllegalAdd, ShapeMediaBuilder){
    ShapeMediaBuilder sMB;
    Circle c1(0,0,5);
    try{
        sMB.buildComboMedia();
        FAIL("should not be here");
    }
    catch(std::string s){
        CHECK(std::string("Illegal: use buildShapeMedia") == s);
    }
}

//HW5
TEST(OpenNotExistDocument, Document){
    MyDocument doc;
    try{
        doc.openDocument("myShapeTest.txt");
        FAIL("should not be here");
    }
    catch(std::string s){
        CHECK(s == std::string("file is not existed. "));
    }
}

TEST(OpenDocument, Document){
    MyDocument doc;
    std::string content;

    content = doc.openDocument("myShape.txt");

    //std::cout<<content<<std::endl;
    CHECK(std::string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == content);
}

TEST(MediaBuilderStack, MediaBuilder){
    std::stack<MediaBuilder *> mbs;
    mbs.push(new ComboMediaBuilder());
    mbs.top()->buildComboMedia();

    Rectangle r1(0,0,3,2);
    mbs.top()->buildShapeMedia(&r1);
    Circle c1(0,0,5);
    mbs.top()->buildShapeMedia(&c1);

    mbs.push(new ComboMediaBuilder());
    mbs.top()->buildComboMedia();

    Rectangle r2(0,0,5,4);
    mbs.top()->buildShapeMedia(&r2);
    Circle c2(0,0,10);
    mbs.top()->buildShapeMedia(&c2);

    Media *tcm = mbs.top()->getMedia();
    mbs.pop();
    mbs.top()->buildAddComboMedia(tcm);

    mbs.push(new ComboMediaBuilder());
    mbs.top()->buildComboMedia();

    Rectangle r3(0,1,8,7);
    mbs.top()->buildShapeMedia(&r3);
    Circle c3(0,1,10);
    mbs.top()->buildShapeMedia(&c3);

    Media *tcm2 = mbs.top()->getMedia();
    mbs.pop();
    mbs.top()->buildAddComboMedia(tcm2);

    Media * cm = mbs.top()->getMedia();
    DescriptionVisitor dv;
    cm->accept(&dv);
    //std::cout<<dv.getDescription()<<std::endl;
    CHECK(std::string("combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == dv.getDescription());

}

TEST(MediaDirector, MediaDirector){
    MyDocument doc;
    std::string content;
    content = doc.openDocument("myShape.txt");

    MediaDirector md;
    std::stack<MediaBuilder *> mbs;
    //mbs.push(new ComboMediaBuilder());
   // mbs.top()->buildComboMedia();
    md.setMediaBuilder(&mbs);
    md.concrete(content);

    DescriptionVisitor dv;
    Media *cm = mbs.top()->getMedia();
    cm->accept(&dv);
    //std::cout<<"regex mediabuilder: "<<dv.getDescription()<<std::endl;
    CHECK(content == dv.getDescription());
}


#endif // UTSHAPES_H_INCLUDED
