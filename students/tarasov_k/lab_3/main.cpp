#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;


int dlinna(char* s1)
{
    int n=strlen(s1);
 
    return n;
}

int main()

{
    int i,j,n,m,d1,d2,temp,ti,tj;
	char s1[20],s2[20];
	n=5;
	m=5;
	setlocale(0,"rus");
	cout << "Введите строку № 1 ";
	cin.getline(s1,20);
	cout<<"Вы ввели: "<<s1<<endl;
	cout << "\nВведите строку № 2 ";
	cin.getline(s2,20);
	cout<<"Вы ввели: "<<s2<<endl;
	n=dlinna(s1)+1;
	m =dlinna(s2)+1;
	if (n<m){
		temp=n;
		n=m;
		m=temp;}

	int**a  = new int *[n];
    for (int i = 0; i < n; i++)
        a[i] = new int [m];
	
	 for(i=0;i<n;i++){
	 for(j=0;j<m;j++)
		 a[i][j]=0;}
	 
	 for(i=0;i<n;i++)
		 a[i][0]=i;
	 
	 for(j=0;j<m;j++)
		 a[0][j]=j;
	 

	 for(i=1;i<n;i++)
	 {
		 for(j=1;j<n;j++)
		 {
	        if(s1[i-1]==s2[j-1])
	          {
		        a[i][j]=a[i-1][j-1];

				
	          }

			if(s1[i-1]!=s2[j-1])
			{   
				temp=min( a[i-1][j], a[i][j-1]);
				a[i][j]=min( temp, a[i-1][j-1]) + 1;
				
			}
	     
		 }
	 }
	 
	for(i = 0; i < n; i++)
	{ 
		for ( j = 0; j < m ; j++)
		cout << " "<< a[i][j];
	    if (j == m)
			cout<< endl;
	}
	cout<< "Минимальное количество итераций : "<<a[n-1][m-1]<<endl;

	system("pause");
}
