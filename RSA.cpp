//uploaded to https://github.com/p1gd0g/IS-homework

#include <iostream>
#include <cmath>

using namespace std;

unsigned long long prime(unsigned long long n)
{
    unsigned long long i;
    for(i=2;i<n-1;i++)
    {
        if(i*i%n==1)return 1;           //如果有解，是合数，输出1
    }
    return 0;                           //无解，输出0
}

unsigned long long gcd(unsigned long long e,unsigned long long p)
{
    unsigned long long i,j;
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

unsigned long long inv(unsigned long long e,unsigned long long p)
{
    long long x1,x2,x3,y1,y2,y3;
    long long z1,z2,z3;
    x1=1;x2=0;x3=p;
    y1=0;y2=1;y3=e;
    unsigned long long q;
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

int bit(unsigned long long n)
{
    int i,j;
    for(i=1,j=-1;;j++)
    {
        if(i<=n)
        {
            i*=2;
        }
        else break;
    }
    return j;
}

unsigned long long mul(unsigned long long m,unsigned long long e,unsigned long long n)
{
    unsigned long long c;
    int j,bk;
    j=bit(e);
    for(c=1;j;j--)
    {
        bk=e/(1<<j);
        if(bk)e=e-(1<<j);
        if(bk)c=c*m;
        c=c%n;
        c=(c*c)%n;
    }
    if(e%2)c=c*m%n;
    return c;
}

/*unsigned long long mul_test(unsigned long long c,unsigned long long d,unsigned long long n)
{
    unsigned long long i;
    for(i=1;d;d--)
    {
        i=i*c;
        if(i>n)
        {
            i=i%n;
            cout<<i<<" ";
        }
    }
    return i;
}*/

int main()
{
    unsigned long long p,q;
    //cout<<"输入p,q"<<endl;
    //cin>>p>>q;
    p=36749;
    q=41597;
    cout<<"p="<<p<<" q="<<q<<endl;

    if(prime(p)||prime(q))
    {
        cout<<"p,q至少有一个是合数"<<endl;
        return 0;
    }
    else cout<<"p,q是素数"<<endl<<endl;

    unsigned long long n,phi;
    n=p*q;
    cout<<"n="<<n<<endl;
    phi=(p-1)*(q-1);
    cout<<"phi="<<phi<<endl<<endl;

    unsigned long long e;
    //cout<<"输入e"<<endl;
    //cin>>e;
    e=5;
    cout<<"e="<<e<<endl;
    if(gcd(e,phi))cout<<"e符合要求"<<endl<<endl;
    else
    {
        cout<<"e不符合要求"<<endl;
        return 0;
    }

    unsigned long long d;
    d=inv(e,phi);
    cout<<"逆元为"<<endl<<d<<endl;

    unsigned long long m;
    //cout<<"输入m"<<endl;
    //cin>>m;
    m='a'*1000000+'b'*1000+'c';
    cout<<"明文为"<<endl<<m<<endl;

    unsigned long long c;
    c=mul(m,e,n);
    cout<<"密文为"<<endl<<c<<endl;

    cout<<"解密为"<<endl<<mul(c,d,n)<<endl;

    return 0;
}
