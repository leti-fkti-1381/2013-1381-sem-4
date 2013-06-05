#include "graph.h"

Graph::Graph()
{
    if (!init())
        return;
    for (unsigned int i=0; i<N; i++)
    {
        Numbers.push_back(0);
        Color.push_back(0);
    }
    std::cout<<"Исходный граф:"<<std::endl;
    print();
    if (!topological_sort())
        return;

    std::cout<<"При анализе стека можно создать правило замены вершин:"<<std::endl;
    for (unsigned int i=0; i<N; i++)
        std::cout<<i+1<<"="<<Numbers[i]<<std::endl;
    std::cout<<std::endl;
    for (unsigned int i=0; i<N; i++)
        for (unsigned int j=0; j<Edges[i]->size(); j++)
            (*Edges[i])[j]=Numbers[(*Edges[i])[j]-1];
    std::vector <unsigned int>* temp;
    for (unsigned int i=0; i<N; i++)
        if ((Numbers[i]-1)!=i)
        {
            temp=Edges[i];
            Edges[i]=Edges[Numbers[i]-1];
            Edges[Numbers[i]-1]=temp;
            Numbers[Numbers[i]-1]=Numbers[i];
            Numbers[i]=i+1;
        }
    std::cout<<"Произведем замену вершин по созданному правилу\nи сбросим окраску вершин (она нам больше не нужна):"<<std::endl;
    for (unsigned int i=0; i<N; i++)
        Color[i]=0;
    print();

    std::cout<<"=================================="<<std::endl;
    std::cout<<"Результат топологической сортировки:"<<std::endl;
    print();
}

bool Graph::init()
{
    std::ifstream ifile ("graph.dat");
    if (!ifile.is_open())
    {
        std::cerr<<"EEROR! File not open!"<<std::endl;
        return false;
    }
    int node;
    bool new_node=true;
    std::vector <unsigned int>* temp;
    while (ifile>>node)
    {
        //std::cout<<node;
        if (new_node)
        {
            new_node=false;
            N++;
            temp=new std::vector <unsigned int>;
            Edges.push_back(temp);
        }
        if (node)
        {
            //Edges[N].push_back(node);
            Edges[N-1]->push_back(node);
        }
        else
            new_node=true;
    }
    //N++;
    ifile.close();
    return true;
}

bool Graph::topological_sort()
{
    for(unsigned int i=0; i<N; i++)
        if (dfs(i+1))
            return false;
    for(unsigned int i=0; i<N; i++)
    {
        Numbers[i]=Stack.top();
        Stack.pop();
    }
    return true;
}

bool Graph::dfs(unsigned int v)
{
    v--;
    std::cout<<"----------------------------------"<<std::endl;
    std::cout<<"Текущая вершина:"<<v+1<<std::endl;
    if (Color[v]==1)
    {
        print();
        std::cerr<<"ERROR! Обнаружен цикл в графе!"<<std::endl;
        return true;
    }
    if (Color[v]==2)
    {
        print();
        std::cout<<"Эта вершина уже использована. Возврат к предыдушей вершине."<<std::endl;
        std::cout<<std::endl;
        return false;
    }
    Color[v]=1;
    std::cout<<"Окрасим ее в серый цвет."<<std::endl;
    print();
    for (unsigned int i=0; i<Edges[v]->size(); i++)
        if (dfs((*Edges[v])[i]))
            return true;
    std::cout<<"Из вершины "<<v+1<<" необследованных путей нет."<<std::endl;
    std::cout<<"Помещаем в стек вершину с номером:"<<v+1<<std::endl;
    std::cout<<"Возврат к предыдушей вершине."<<std::endl;
    std::cout<<std::endl;
    Stack.push(v+1);
    Color[v]=2;
    return false;
}

void Graph::print()
{
    for (unsigned int i=0; i<N; i++)
    {
        std::cout<<i+1<<"("<<Color[i]<<")"<<"\t|";
        for (unsigned int j=0; j<Edges[i]->size(); j++)
            std::cout<<"->"<<(*Edges[i])[j];
        std::cout<<"->X"<<std::endl;
    }
}
