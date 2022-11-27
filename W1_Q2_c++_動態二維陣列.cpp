
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory
{
public:
  static T** allocArray (int m, int n)
  {
        T **p;
        p = new T*[m];
        int x, y;

        T *tmp = (T*)malloc (sizeof(T) * m * n);
        for (y=0; y < m; y++)
            p[y] = tmp + n * y;

        /*
        p[0] = (T*)malloc(sizeof(T) * m * n);
        for (x=1; x < m; x++)
            p[x] = p[x-1] + n;
        */
        return p;
  }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
}
