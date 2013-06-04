#include <iostream>
#include "professor.h"

int main()
{
    int Nfloor, Ntransistor, Ncrash;
    std::cout<<"Введите количество этажей:";
    std::cin>>Nfloor;
    std::cout<<"Введите количество транзисторов, доступных для испытаний:";
    std::cin>>Ntransistor;
    std::cout<<"Введите этаж, с которого считать, что транзистор разбивается:";
    std::cin>>Ncrash;
    Professor pr(Ntransistor,Nfloor,Ncrash);
    pr.make_test(2,Nfloor);
    pr.print();
}
