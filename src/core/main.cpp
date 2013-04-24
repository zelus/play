#include <iostream>
#include "item.h"

using namespace std;

int main()
{
    Item item("test");
    cout << item.getItemName() << endl;
    return 0;
}

