#include <iostream>
#include <stdio.h>
using namespace std;
int main()
{
    int i,j,n,t;
    int k;
    int s[256];
    int o[256];
    //unsigned char m[256]={"Shenzhen University"};
    char mm[256]={"Shenzhen University"};
    int m[256]={0};
    for(i=0;mm[i]!='\0';i++)
    {
        m[i]=mm[i];
    }
    for(i=0;i<256;i++)
    {
        s[i]=i;
        if(i%5==0)o[i]='a';
        else if(i%5==1)o[i]='b';
        else if(i%5==2)o[i]='c';
        else if(i%5==3)o[i]='d';
        else if(i%5==4)o[i]='e';
    }
    for(i=0,j=0;i<256;i++)
    {
        j=(j+s[i]+o[i])%256;
        k=s[i];
        s[i]=s[j];
        s[j]=k;
    }

    for(i=0;i<256;i++)cout<<s[i];
    cout<<endl;

    for(i=j=n=0;m[n]!='\0';n++)
    {
        i=(i+1)%256;
        j=(j+s[i])%256;
        k=s[i];
        s[i]=s[j];
        s[j]=k;
        t=(s[i]+s[j])%256;
        m[n] ^= s[t];
    }
    for(i=0;m[i]!=0;i++)
    {
        printf("%x",m[i]);
    }
    return 0;
}
