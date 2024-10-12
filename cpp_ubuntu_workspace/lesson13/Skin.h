#ifndef __SKIN_HEAD_H__
#define __SKIN_HEAD_H__

#include <iostream>

using namespace std;

class Skin {
    public:
        Skin(const string &color):color(color) {
            cout << "Skin(const string &color):color(color)" << endl;
        }
        ~Skin() {
            cout << "~Skin()" << endl;
        }
        string getSkin() const {
            return color;
        }

    private:
        string color;
};

#endif