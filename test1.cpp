 #include <bits/stdc++.h>
#include "buddyAlgorithmHeader.h"
// #include <malloc.h>

using namespace std;
string logFileName="Buddylogs.log";

void clearLog(){
    ofstream out;
    out.open("Buddylogs.log");
    out.clear();
    out.close();
}

void debugLog(void *text){
    ofstream log_file(logFileName, ios_base::out | ios_base::app );
    log_file << text << endl;
}

void infoLog(const string &text ){
    ofstream log_file(logFileName, ios_base::out | ios_base::app );
    log_file << text;
}

int main()
{
  clearLog();
  size_t size1 = 12;
  int *mem = (int*)malloc(size1);
  printf("Successfully malloc'd %zu bytes at addr %p\n", size1, mem);
  infoLog("\nSuccessfully malloc "+to_string(size1)+" bytes at addr "+to_string((long long unsigned int)mem));
  infoLog("\nmalloc test cases for integer datatype");
  int n1 = size1/sizeof(int);
  for(int i = 0;i < n1;i++)
  {
    mem[i] = i;
  }
  for(int i = 0;i<n1;i++)
  {
    //cout<<mem[i]<<" ";
    infoLog("\nAddress of "+to_string(i)+"th element: ");
    debugLog((mem+i));
    cout<<*(mem+i)<<endl;
  }

  // size_t i = 5;

  float *ptr  = (float *)calloc(5,sizeof(float));
  printf("Successfully calloc'd %zu bytes at addr %p\n", 5*sizeof(float), ptr);
  infoLog("\nSuccessfully calloc "+to_string(5*sizeof(float))+" bytes at addr "+to_string((long long unsigned int)ptr));
  infoLog("\ncalloc test cases for float datatype");
  for(int i = 0;i < 5;i++)
  {
    ptr[i] = i;
  }
  for(int i = 0;i<5;i++)
  {
    //cout<<mem[i]<<" ";
    infoLog("\nAddress of "+to_string(i)+"th element: ");
    debugLog((ptr+i));
    cout<<*(ptr+i)<<endl;
  }

  float *new_ptr = (float*) realloc(mem, 10*sizeof(float));
  printf("Successfully realloc'd %zu bytes at addr %p\n", 10*sizeof(float), new_ptr);
  infoLog("\nSuccessfully realloc "+to_string(10*sizeof(float))+" bytes at addr "+to_string((long long unsigned int)new_ptr));
  infoLog("\nrealloc test cases for float datatype");
  for(int i =0;i<10;i++)
  {
    new_ptr[i] = i;
  }
   for(int i = 0;i<10;i++)
  {
    //cout<<mem[i]<<" ";
    infoLog("\nAddress of "+to_string(i)+"th element: ");
    debugLog((new_ptr+i));
    cout<<*(new_ptr+i)<<endl;
  }



  // void * pointer;
   double* ptr2 =  (double *)reallocarray(ptr, 25, sizeof(double));
  printf("Successfully reallocarray'd %zu bytes at addr %p\n", 25*sizeof(double), ptr2);
  infoLog("\nSuccessfully reallocarray "+to_string(25*sizeof(double))+" bytes at addr "+to_string((long long unsigned int)ptr2));
  infoLog("\nreallocarray test cases for double datatype");
   for (int i =0 ; i<25; i++)
   {
    ptr2[i] = i;
   }
    for(int i = 0;i<25;i++)
  {
    //cout<<mem[i]<<" ";
    infoLog("\nAddress of "+to_string(i)+"th element: ");
    debugLog((ptr2+i));
    cout<<*(ptr2+i)<<endl;
  }

  // int *tmp = (int *)memalign(16, 48);
  // for (int i = 0; i < 3; i++)
  // {
  //   tmp[i] = i + 1;
  // }

  // for (int i = 0; i < 3; i++)
  // {
  //   cout << tmp[i] << endl;
  // }


  
  
  free(ptr2);
  // free(ptr);
  infoLog("\nSuccessfully free'd "+ to_string(25*sizeof(double))+" bytes from addr");
  debugLog((ptr2));
  printf("Successfully free'd %zu bytes from addr %p\n", 25*sizeof(double), ptr2);
  free(new_ptr);
  infoLog("\nSuccessfully free'd "+ to_string(10*sizeof(float))+" bytes from addr");
  debugLog((new_ptr));
  printf("Successfully free'd %zu bytes from addr %p\n", 10*sizeof(float), new_ptr);

  return 0;
}
