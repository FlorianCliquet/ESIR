#include <iostream>
#include "vecteur.hh"
using std::cin;
using std::cout;
using std::cerr;
#define endl "\n"
int main(){
    Vecteur<std::string> *v1 = new Vecteur<std::string>(5);
    Vecteur<int> *v2 = new Vecteur<int>(10);
    Vecteur<int> *v3 = new Vecteur<int>(10);
    Vecteur<int> v4(10);
    
    try {
        cin >> *v1;
        cout << "Vecteur saisi : " << *v1 << endl;
        cin >> *v2;
        cout << "Vecteur saisi : " << *v2 << endl;
        cin >> v4;
        cout << "Vecteur saisi : " << v4 << endl;
        *v3 = *v2;
        std::sort(v2->begin(),v2->end());
        cout << "Vecteur saisi : " << *v2 << endl;
        cout << "Vecteur saisi : " << *v3 << endl;
        cout << "Index 1 du vecteur v3 : " << (*v3)[1] << endl;
        (*v3)[1] = 3;
        cout << "Vecteur saisi : " << *v3 << endl;
        Vecteur<int> v4 = *v2 + *v3;
        cout << "Vecteur saisi : " << v4 << endl;
    } catch (const std::exception &e) {
        cerr << "Erreur : " << e.what() << endl;
    }
    
    delete v1;
    delete v2;
    delete v3;
    return 0;
}
