//uploaded to https://github.com/p1gd0g/IS-homework 2016-10-21 09:03:35

#include <iostream>
#include <cmath>

using namespace std;

int prime(int n)
{
    int i;
    for(i=2;i<n-1;i++)
    {
        if(i*i%n==1)return 1;           //����н⣬�Ǻ��������1
    }
    return 0;                           //�޽⣬���0
}

int gcd(int e,int p)
{
    int i,j;
    for(;;)
    {
        j=p/e;
        i=p-j*e;
        if(i==1)return 1;
        else if(i==0)return 0;
        else
        {
            p=e;
            e=i;
        }
    }
}

int inv(int e,int p)
{
    int x1,x2,x3,y1,y2,y3;
    int z1,z2,z3;
    x1=1;x2=0;x3=p;
    y1=0;y2=1;y3=e;
    int q;
    for(;;)
    {
        q=x3/y3;
        z1=x1;z2=x2;z3=x3;
        x1=y1;x2=y2;x3=y3;
        y1=z1-y1*q;
        y2=z2-y2*q;
        y3=z3-y3*q;
        if(y3==1)return y2>0?y2:y2+p;
    }
}

int mul(int m,int e,int n)
{
    int i,j,c,bk;
    for(i=1,j=-1;;j++)
    {
        if(i<=e)
        {
            i*=2;
        }
        else break;
    }
    for(c=1;j;j--)
    {
        bk=e/pow(2.0,j);
        if(bk)e=e-pow(2.0,j);
        c=c*pow(m,bk);
        c=c*c%n;
    }
    if(e%2)c=c*m%n;
    return c;
}

int main()
{
    int p,q;
    cout<<"����p,q"<<endl;
    cin>>p>>q;
    if(prime(p)||prime(q))
    {
        cout<<"p,q������һ���Ǻ���"<<endl;
        return 0;
    }
    else cout<<"p,q������"<<endl;

    int n,phi;
    n=p*q;
    phi=(p-1)*(q-1);

    int e;
    cout<<"����e"<<endl;
    cin>>e;
    if(gcd(e,phi))cout<<"e����Ҫ��"<<endl;
    else
    {
        cout<<"e������Ҫ��"<<endl;
        return 0;
    }

    int d;
    d=inv(e,phi);
    cout<<"��ԪΪ"<<endl<<d<<endl;

    int m;
    cout<<"����m"<<endl;
    cin>>m;
    int c;
    c=mul(m,e,n);
    cout<<"����Ϊ"<<endl<<c<<endl;

    cout<<"����Ϊ"<<endl<<mul(c,d,n)<<endl;

    return 0;
}
