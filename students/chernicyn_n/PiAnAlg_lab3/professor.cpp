#include "professor.h"

Professor::Professor(int transistor, int floor, int crash_floor)
{
    way_length=0;
    new_transistors=transistor;
    discarded_transistors=0;
    crash=crash_floor;
    low=1;
    high=floor;
}

int Professor::make_test(int floor, int divider)
{
    //поднять транзисторы
    int ret=0;
    //print();
    new_transistors--;
    way_length+=divider;
    std::cout<<"------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Этаж:"<<floor<<std::endl;
    if (!(floor<crash))   //транзистор бъется
    {
        std::cout<<"Транзистор разбит!!!"<<std::endl;
        high=floor;
        if (low+1==floor)
        {
            low=floor;
            return 1;
        }
        way_length+=divider;
        return 0;
    }
    low=floor;
    discarded_transistors++;

    for (int i=2; !ret; i*=2)
    {
        if (!(new_transistors))
        {
            std::cout<<"Спускаемся взниз и забираем все неразбитые транзисторы. Текуший этаж:"<<floor<<std::endl;
            new_transistors=discarded_transistors;
            discarded_transistors=0;
            way_length+=(floor*2);
        }
        if (!(new_transistors+discarded_transistors<2) && (int)(divider/i)) //транзисторов больше двух
            ret=make_test(floor+divider/i,divider/i);
        else                    //транзисторов меньше двух
            ret=make_test(floor+1,2);
    }
    return 1;
}

void Professor::print()
{
    std::cout<<"========================================================================"<<std::endl;
    std::cout<<"Пройденный путь:"<<way_length<<std::endl;
    std::cout<<"Минимальная высота разбития транзистора:"<<low<<std::endl;
    std::cout<<"Осталось неразбитых транзисторов:"<<new_transistors+discarded_transistors<<std::endl;
}
