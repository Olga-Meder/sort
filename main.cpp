#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

constexpr int QUANTITY = 100;
using namespace std;
/****************************************************************************
* QUICK SORT*/
void quick_sort(int *tab, int left, int right)
{
    if(right <= left) return;

    int i = left - 1, j = right + 1,
            pivot = tab[(left+right)/2]; //wybieramy punkt odniesienia

    while(1)
    {
        //szukam elementu wiekszego lub rownego piwot stojacego
        //po prawej stronie wartosci pivot
        while(pivot>tab[++i]);

        //szukam elementu mniejszego lub rownego pivot stojacego
        //po lewej stronie wartosci pivot
        while(pivot<tab[--j]);

        //jesli liczniki sie nie minely to zamieñ elementy ze soba
        //stojace po niewlasciwej stronie elementu pivot
        if( i <= j)
            //zamienia wartosciami tab[i] z tab[j]
            swap(tab[i],tab[j]);
        else
            break;
    }

    if(j > left)
        quick_sort(tab, left, j);
    if(i < right)
        quick_sort(tab, i, right);
}
/****************************************************************************
* MERGE SORT*/
void merge(int* tab, int l, int m, int r)
{
    int lSize = m - l + 1;
    int rSize = r - m;

//Tablice pomocnicze
    int* tabL = new int[lSize];
    int* tabR = new int[rSize];

// Kopiowanie danych do tablic pomocniczych
    for (int x = 0; x < lSize; x++)
        tabL[x] = tab[l + x];
    for (int y = 0; y < rSize; y++)
        tabR[y] = tab[m + 1 + y];

    int indexL = 0;
    int indexR = 0;
    int currIndex;

//Łączenie tablic R i L
    for (currIndex = l; indexL < lSize && indexR < rSize; currIndex++)
    {
        if (tabL[indexL] <= tabR[indexR])
            tab[currIndex] = tabL[indexL++];
        else
            tab[currIndex] = tabR[indexR++];
    }

//Jeśli w tablicy tabL pozostały jeszcze jakieś elementy
//kopiujemy je
    while (indexL < lSize)
        tab[currIndex++] = tabL[indexL++];

//Jeśli w tablicy tabR pozostały jeszcze jakieś elementy
//kopiujemy je
    while (indexR < rSize)
        tab[currIndex++] = tabR[indexR++];

    delete[] tabL;
    delete[] tabR;
}


void mergeSort(int* tab, int l, int r)
{
    if (r > l)
    {
        int m = (l + r) / 2;
        mergeSort(tab, l, m);
        mergeSort(tab, m + 1, r);
        merge(tab, l, m, r);
    }
}


/****************************************************************************
* HEAP SORT*/

void heapify(int *tab, int heap_size, int i)
{
    int largest, temp;
    int l=2*i, r=(2*i)+1;
    if (l<=heap_size && tab[l]>tab[i])
        largest=l;
    else largest=i;
    if (r<=heap_size && tab[r]>tab[largest])
        largest=r;
    if (largest!=i)
    {
        temp=tab[largest];
        tab[largest]=tab[i];
        tab[i]=temp;
        heapify(tab,heap_size,largest);
    }
}
void buildHeap(int *tab, int size)
{
    for (int i=size/2;i>0;i--)
        heapify(tab,size, i);
}

void heapsort(int *tab, int size)
{
    int temp;
    buildHeap(tab, size);
    for (int i=size;i>1;i--)
    {
        temp=tab[i];
        tab[i]=tab[1];
        tab[1]=temp;
        size--;
        heapify(tab,size,1);
    }
}
/***************************************************************************/

int main()
{

    int n1 = 50000;
    // 10000; 50000; 100000; 500000; 1000000;
    float procent = 99.7;
    // 25; 50; 75; 95; 99; 99.7;

// czas systemowy delkaracja
    double t;
    clock_t start;
    clock_t stop;
    double tc;
// tablica pomocnicza
    int tab[n1];

///////////////////////////////////////////////////////////////////////////////////////////////////////

    int quick[n1];

    cout<<"QUICK SORT"<<endl;
    for(int i = 0; i<QUANTITY; i++) //100 TABLIC
    {

        for(int j = 0; j<n1; j++) //ZAPELNIANIE TABLICY RAND()
        {
            tab[j] = (rand()%1000);
        }
        quick_sort(tab,0, n1-1-(n1*(100-procent)/100)); //SORTOWANIE CZESCI TABLICY
        //    quick_sort(tab,0,n1-1);

        for(int j = 0; j<n1; j++) //ZAPISANIE POSOSRTOWANEJ CZESCIOWO TABLICY
        {
            quick[j] = tab[j];
            //    quick[j] = tab[n1-j-1];
        }

        start = clock();
        quick_sort(quick,0, n1-1); //SORTOWANIE
        stop = clock();
        t = double(stop -start)/CLOCKS_PER_SEC;
        tc =t + tc;
        t=0;
    }
    cout << tc <<endl;
    tc=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////

    int heap[n1];

    cout<<"HEAP SORT"<<endl;
    for(int i = 0; i<QUANTITY; i++) //100 TABLIC
    {

        for(int j = 0; j<n1; j++) //ZAPELNIANIE TABLICY RAND()
        {
            tab[j] = (rand()%1000);
        }
        quick_sort(tab,0, n1-1-(n1*(100-procent)/100)); //SORTOWANIE CZESCI TABLICY
        //    quick_sort(tab,0,n1-1);

        for(int j = 0; j<n1; j++) //ZAPELNIANIE TABLICY RAND()
        {
            heap[j] = tab[j];
            //    heap[j] = tab[n1-j-1];
        }

        start = clock();
        heapsort(heap,n1-1);//SORTOWANIE
        stop = clock();
        t = double(stop -start)/CLOCKS_PER_SEC;
        tc =t + tc;
        t=0;
    }
    cout << tc <<endl;
    tc=0;
/////////////////////////////////////////////////////////////////////////////////////////////////////

    int merge[n1];

    cout<<"MERGE SORT"<<endl;
    for(int i = 0; i<QUANTITY; i++) //100 TABLIC
    {

        for(int j = 0; j<n1; j++) //ZAPELNIANIE TABLICY RAND()
        {
            tab[j] = (rand()%1000);
        }
        quick_sort(tab,0, n1-1-(n1*(100-procent)/100)); //SORTOWANIE CZESCI TABLICY
        //    quick_sort(tab,0,n1-1);

        for(int j = 0; j<n1; j++) //ZAPELNIANIE TABLICY RAND()
        {
            merge[j] = tab[j];
            //    merge[j] = tab[n1-j-1];
        }

        start = clock();
        mergeSort(merge,0,n1-1);//SORTOWANIE
        stop = clock();
        t = double(stop -start)/CLOCKS_PER_SEC;
        tc =t + tc;
        t=0;

    }
    cout << tc <<endl;
    tc=0;

    return 0;
}

