#include "util.h"
#include <iostream>
using namespace std;

int clampInt(int val, int minVal, int maxVal)
{
if (val<minVal)
{
return minVal;
}
if (val>maxVal)
{
return maxVal;
}
return val;
}

void trimWhitespace(char* str)
{
if (str==0)
{
return;
}
int len=0;
while (str[len]!='\0')
{
len+=1;
}
while (len>0 && (str[len-1]==' ' || str[len-1]=='\t' || str[len-1]=='\r' || str[len-1]=='\n'))
{
    str[len-1]='\0';
    len-=1;
}
int start=0;
while (str[start]==' ' || str[start]=='\t' || str[start]=='\r' || str[start]=='\n')
{
start+=1;
}
if (start>0)
{
int i=0;
while (str[start+i]!='\0')
{
    str[i]=str[start+i];
    i+=1;
}
str[i]='\0';
}
}

bool stringEquals(const char* a, const char* b)
{
if (a==0 || b==0)
{
return false;
}
int i=0;
while (a[i]!='\0' && b[i]!='\0')
{
if (a[i]!=b[i])
{
return false;
}
i+=1;
}
if (a[i]=='\0' && b[i]=='\0')
{
return true;
}
else
{
return false;
}
}

void printHeader(const char* title)
{
cout<<"========================================"<<endl;
cout<<"  "<<title<<endl;
cout<<"========================================"<<endl;
}

void clearScreen()
{
cout<<endl;
cout<<"----------------------------------------"<<endl;
}
