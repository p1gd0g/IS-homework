//test data are taken from http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
//uploaded to
//2016年10月11日17:31:39

#include <iostream>
#include <cmath>

using namespace std;

int IP[]={

                58, 50, 42, 34, 26, 18, 10, 2,
                60, 52, 44, 36, 28, 20, 12, 4,
                62, 54, 46, 38, 30, 22, 14, 6,
                64, 56, 48, 40, 32, 24, 16, 8,
                57, 49, 41, 33, 25, 17, 9,  1,
                59, 51, 43, 35, 27, 19, 11, 3,
                61, 53, 45, 37, 29, 21, 13, 5,
                63, 55, 47, 39, 31, 23, 15, 7
        };

int PC_1[]={

                // 前半部分
	            57, 49, 41, 33, 25, 17, 9,
                1,  58, 50, 42, 34, 26, 18,
                10, 2,  59, 51, 43, 35, 27,
                19, 11, 3,  60, 52, 44, 36,
                // 后半部分
                63, 55, 47, 39, 31, 23, 15,
                7,  62, 54, 46, 38, 30, 22,
                14, 6,  61, 53, 45, 37, 29,
                21, 13, 5,  28, 20, 12, 4
        };

int E[]={

	            32, 1,  2,  3,  4,  5,  4,  5,
                6,  7,  8,  9,  8,  9,  10, 11,
                12, 13, 12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21, 20, 21,
                22, 23, 24, 25, 24, 25, 26, 27,
                28, 29, 28, 29, 30, 31, 32, 1
	    };

int M[]={

                1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
	    };

int PC_2[]={

	            14, 17, 11, 24, 1,  5,  3,  28,
                15, 6,  21, 10, 23, 19, 12, 4,
                26, 8,  16, 7,  27, 20, 13, 2,
                41, 52, 31, 37, 47, 55, 30, 40,
                51, 45, 33, 48, 44, 49, 39, 56,
                34, 53, 46, 42, 50, 36, 29, 32
	    };

int s[][4][16]={

            // S_Box[1]
	        {
            { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
            { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
            { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
            { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
	        },
            // S_Box[2]
	        {
            { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
            { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
            { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
            { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
	        },
            // S_Box[3]
	        {
	        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
	        { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
	        { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
	        { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
	        },
            // S_Box[4]
	        {
	        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
	        { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
	        { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
	        { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
	        },
            // S_Box[5]
	        {
	        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
	        { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
	        { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
	        { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
	        },
            // S_Box[6]
	        {
	        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
	        { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
	        { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
	        { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
	        },
            // S_Box[7]
	        {
	        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
	        { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
	        { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
	        { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
	        },
            // S_Box[8]
	        {
	        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
	        { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
	        { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
	        { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	        }
	    };

int P[]={

	        16, 7,  20, 21, 29, 12, 28, 17,
            1,  15, 23, 26, 5,  18, 31, 10,
            2,  8,  24, 14, 32, 27, 3,  9,
            19, 13, 30, 6,  22, 11, 4,  25
	    };

int IP_1[]={

            40, 8,  48, 16, 56, 24, 64, 32,
            39, 7,  47, 15, 55, 23, 63, 31,
            38, 6,  46, 14, 54, 22, 62, 30,
            37, 5,  45, 13, 53, 21, 61, 29,
            36, 4,  44, 12, 52, 20, 60, 28,
            35, 3,  43, 11, 51, 19, 59, 27,
            34, 2,  42, 10, 50, 18, 58, 26,
            33, 1,  41, 9,  49, 17, 57, 25
        };

int shift_temp=16;

void bit(unsigned char m[],int m_bit[])
{
    int i;
    for(i=0;i<64;i++)
    {
        m_bit[i]=(m[i/8]&(int)pow(2.0,7-i%8))/(int)pow(2.0,7-i%8);
        //if(i%8==0)cout<<endl;cout<<m_bit[i];
    }
}

void IP_change(int IP_temp[],int m_bit[])
{
    int i;
    for(i=0;i<64;i++)
    {
        IP_temp[i]=m_bit[IP[i]-1];
        //if(i%8==0)cout<<endl;cout<<m_bit[IP[i]-1]<<" ";
    }
}

void PC_1_change(int k_bit[],int PC_1_temp[])
{
    int i;
    for(i=0;i<56;i++)
    {
        PC_1_temp[i]=k_bit[PC_1[i]-1];
        //if(i%7==0)cout<<endl;cout<<PC_1_temp[i];
    }
}

void E_change(int E_temp[],int R[])
{
    int i;
    for(i=0;i<48;i++)
    {
        E_temp[i]=R[E[i]-1];
        //if(i%6==0)cout<<endl;cout<<E_temp[i];
    }
}

void shift(int C[],int D[],int n)
{
    int i;
    if(M[n]==1)
    {
        int temp;

        temp=C[0];                          //C的移位
        for(i=0;i<27;i++)
        {
            C[i]=C[i+1];
            //if(i%7==0)cout<<endl;cout<<C[i];
        }
        C[i]=temp;

        temp=D[0];                          //D的移位
        for(i=0;i<27;i++)
        {
            D[i]=D[i+1];
            //if(i%7==0)cout<<endl;cout<<C[i];
        }
        D[i]=temp;
    }
    else
    {
        int temp1,temp2;

        temp1=C[0];                         //C的移位
        temp2=C[1];
        for(i=0;i<26;i++)
        {
            C[i]=C[i+2];
        }
        C[i++]=temp1;
        C[i]=temp2;

        temp1=D[0];                         //D的移位
        temp2=D[1];
        for(i=0;i<26;i++)
        {
            D[i]=D[i+2];
        }
        D[i++]=temp1;
        D[i]=temp2;
    }
}

void shift_1(int C[],int D[],int n)
{
    int i;
    M[0]=0;
    if(M[n]==1)
    {
        int temp;

        temp=C[27];                          //C的移位
        for(i=27;i>0;i--)
        {
            C[i]=C[i-1];
            //if(i%7==0)cout<<endl;cout<<C[i];
        }
        C[i]=temp;

        temp=D[27];                          //D的移位
        for(i=27;i>0;i--)
        {
            D[i]=D[i-1];
            //if(i%7==0)cout<<endl;cout<<C[i];
        }
        D[i]=temp;
    }
    else if(M[n]==2)
    {
        int temp1,temp2;

        temp1=C[27];                         //C的移位
        temp2=C[26];
        for(i=27;i>1;i--)
        {
            C[i]=C[i-2];
        }
        C[i--]=temp1;
        C[i]=temp2;

        temp1=D[27];                         //D的移位
        temp2=D[26];
        for(i=27;i>1;i--)
        {
            D[i]=D[i-2];
        }
        D[i--]=temp1;
        D[i]=temp2;
    }
}

void PC_2_change(int C[],int D[],int PC_2_temp[])
{
    int i;
    for(i=0;i<48;i++)
    {
        if(PC_2[i]<29)
        {
            PC_2_temp[i]=C[PC_2[i]-1];
        }
        else
        {
            PC_2_temp[i]=D[PC_2[i]-1-28];
        }
        //if(i%6==0)cout<<endl;cout<<PC_2_temp[i];
    }
}

void xor_change(int E_temp[],int PC_2_temp[],int xor_temp[])
{
    int i;
    for(i=0;i<48;i++)
    {
        xor_temp[i]=E_temp[i]^PC_2_temp[i];
        //if(i%6==0)cout<<endl;cout<<xor_temp[i];
    }
}

void S_change(int S_temp[],int xor_temp[])
{
    int i,p,q;
    for(i=0;i<8;i++)
    {
        p=xor_temp[i*6]*2+xor_temp[i*6+5];
        q=xor_temp[i*6+1]*8+xor_temp[i*6+2]*4+xor_temp[i*6+3]*2+xor_temp[i*6+4];
        S_temp[i*4]=s[i][p][q]/8;
        S_temp[i*4+1]=s[i][p][q]/4%2;
        S_temp[i*4+2]=s[i][p][q]/2%2;
        S_temp[i*4+3]=s[i][p][q]%2;
        //cout<<S_temp[i*4]*8+S_temp[i*4+1]*4+S_temp[i*4+2]*2+S_temp[i*4+3]<<endl;
    }
}

void P_change(int P_temp[],int S_temp[])
{
    int i;
    for(i=0;i<32;i++)
    {
        P_temp[i]=S_temp[P[i]-1];
        //if(i%8==0)cout<<endl;cout<<P_temp[i];
    }
}

void lun(int L[],int R[],int C[],int D[],int n)
{
    int E_temp[48];                         //R扩展E
    E_change(E_temp,R);

    if(shift_temp-->0)shift(C,D,n);           //C,D的循环移位
    else shift_1(C,D,n);                    //C,D的右循环移位

    int PC_2_temp[48];                      //置换选择2
    PC_2_change(C,D,PC_2_temp);

    int xor_temp[48];                       //异或运算
    xor_change(E_temp,PC_2_temp,xor_temp);

    int S_temp[32];                         //S盒运算
    S_change(S_temp,xor_temp);

    int P_temp[32];                         //P置换
    P_change(P_temp,S_temp);

    int i;                                  //完成R和L
    for(i=0;i<32;i++)
    {
        P_temp[i]=L[i]^P_temp[i];
        L[i]=R[i];
        R[i]=P_temp[i];
        //if(i%8==0)cout<<endl;cout<<L[i];
    }
}

int main()
{
    int i;

    unsigned char m[]={"renhaore"};         //明文
    cout<<"明文:"<<endl<<m<<endl<<endl;
    //unsigned char m[]={1,35,69,103,137,171,205,239};
    int m_bit[64];
    bit(m,m_bit);                           //明文转bit

    unsigned char k[]={"21601304"};         //密钥
    cout<<"密钥:"<<endl<<k<<endl<<endl;
    //unsigned char k[]={19,52,87,121,155,188,223,241};
    int k_bit[64];
    bit(k,k_bit);                           //密钥转bit

    int IP_temp[64];                        //明文初始变换
    IP_change(IP_temp,m_bit);

    int L[32],R[32];                        //明文分块
    for(i=0;i<32;i++)
    {
        L[i]=IP_temp[i];
        R[i]=IP_temp[i+32];
        //if(i%8==0)cout<<endl;cout<<R[i];
    }

    int PC_1_temp[56];                      //密钥置换选择1
    PC_1_change(k_bit,PC_1_temp);

    int C[28],D[28];                        //密钥分块
    for(i=0;i<28;i++)
    {
        C[i]=PC_1_temp[i];
        D[i]=PC_1_temp[i+28];
        //if(i%7==0)cout<<endl;cout<<C[i];
    }

    for(i=0;i<16;i++)                       //轮结构
    {
        lun(L,R,C,D,i);
    }

    for(i=0;i<32;i++)                       //左右交换,合并
    {
        IP_temp[i]=R[i];
        IP_temp[i+32]=L[i];
        //if(i%8==0)cout<<endl;cout<<IP_temp[i+32];
    }

    for(i=0;i<64;i++)                       //逆置换
    {
        m_bit[i]=IP_temp[IP_1[i]-1];
        //if(i%8==0)cout<<endl;cout<<m_bit[i];
    }

    cout<<"密文:"<<endl;
    for(i=0;i<16;i++)                       //输出密文
    {
        cout<<hex<<m_bit[i*4]*8+m_bit[i*4+1]*4+m_bit[i*4+2]*2+m_bit[i*4+3];
    }
    cout<<endl<<endl;

    IP_change(IP_temp,m_bit);               //解密,密文初始置换

    for(i=0;i<32;i++)                       //密文分块
    {
        L[i]=IP_temp[i];
        R[i]=IP_temp[i+32];
        //if(i%8==0)cout<<endl;cout<<R[i];
    }

    for(i=0;i<16;i++)                       //轮结构
    {
        lun(L,R,C,D,i);
    }

    for(i=0;i<32;i++)                       //左右交换,合并
    {
        IP_temp[i]=R[i];
        IP_temp[i+32]=L[i];
        //if(i%8==0)cout<<endl;cout<<IP_temp[i+32];
    }

    for(i=0;i<64;i++)                       //逆置换
    {
        m_bit[i]=IP_temp[IP_1[i]-1];
        //if(i%8==0)cout<<endl;cout<<m_bit[i];
    }

    cout<<"解密:"<<endl;
    for(i=0;i<8;i++)
    {
        m_bit[i*8]=m_bit[i*8]*128+m_bit[i*8+1]*64+m_bit[i*8+2]*32+m_bit[i*8+3]*16
                    +m_bit[i*8+4]*8+m_bit[i*8+5]*4+m_bit[i*8+6]*2+m_bit[i*8+7];
        cout<<(char)m_bit[i*8]<<" ";
    }

    return 0;
}
