#ifndef MOCKITEMVISITOR_H
#define MOCKITEMVISITOR_H

#include "ItemVisitor.h"

using namespace play_core;

/*
  A mock of the ItemVisitor class to test the
  if the right methods are called from Item.
 */
class MockItemVisitor : public ItemVisitor
{
public:
    MockItemVisitor(int& calledMethod);
    void visitFolder(Folder *folder);
    void visitMovie(Movie *movie);
private:
    int& calledMethod_;
};

#endif // MOCKITEMVISITOR_H
