#include "Luban.h"
#include "Houyi.h"

void playGame(Hero &hero)
{
    hero.skill();
}

int main(int argc, char const *argv[])
{
    Luban Luban("luban", 10, 2);
    Luban.show();
    cout << "------------------" << endl;
    playGame(Luban);// 这里传进取的Luban 在方法参数中变成了Hero, 父类引用指向子类对象

    cout << "------------------" << endl;
    cout << "------------------" << endl;

    Houyi houyi("houyi", 10, 9);
    houyi.show();
    cout << "------------------" << endl;
    playGame(houyi);// 这里传进取的Luban 在方法参数中变成了Hero, 父类引用指向子类对象
    
    return 0;
}
