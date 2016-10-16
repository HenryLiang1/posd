#ifndef MEDIAVISITOR_H_INCLUDED
#define MEDIAVISITOR_H_INCLUDED

#include "Media.h"

class ShapeMedia;
class ComboMedia;

class MediaVisitor{
    virtual void visit(ShapeMedia *sm) = 0;
    virtual void visit(ComboMedia *cm) = 0;
};

class AreaVisitor : MediaVisitor{
    void visit(ShapeMedia *sm){
        sm->getShape()->area();
    }

    void visit(ComboMedia *cm){
        cm->getMedia().area();
    }
};

#endif // MEDIAVISITOR_H_INCLUDED
