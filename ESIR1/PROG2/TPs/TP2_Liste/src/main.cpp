#include <iostream>
#include "liste.hpp"
#include "copier.h"
int main() {
    Liste<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(5);
    list.push_back(-50);
    list.push_front(400);
    std::cout << "List size after insertions: " << list.size() << std::endl;
    std::cout << list;
    Liste<int> list2 = copierTri(list);
    Liste<int> copie(copierTri(list));
    std::cout << copie << std::endl;
    const Liste<int> list4(list);
    for(Liste<int>::const_iterator it = list4.begin(); it!=list4.end();++it){
        std::cout << *it << std::endl;
    }
    std::cout << list2 << std::endl;
    return 0;
}
