#include "Set.h"
using namespace std;

void Set::add(const string& val) {
    if (list.findVal(val) == -1) list.pushBack(val);
}
void Set::del(const string& val) {
    list.deleteValue(val);
}
bool Set::incl(const string& val) {
    return list.findVal(val) != -1;
}
void Set::print() {
    list.print();
}
string Set::ToString() const {
    return list.ToString();
}