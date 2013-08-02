#include "MockTag.h"

using namespace std;

/*
  MockTag constructor.
  The parameter isDeleted is used to know if the
  MockTag destructor has been called.
*/
MockTag::MockTag(string tagName, bool& isDeleted) : Tag(tagName), isDeleted_(isDeleted)
{

}

/*
  MockTag destructor.
  Set the value pointed by isDeleted pointer to true.
*/
MockTag::~MockTag()
{
    isDeleted_ = true;
}
