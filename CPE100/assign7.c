#include<stdio.h>
int get_int(int min, int max) // กำหนดขอบเขต input
{
    int num;
    while(scanf("%d",&num)!=1 || num<min || num>max)
    {
        rewind(stdin);
        printf("Input error, Please enter again (%d-%d) : ", min, max);
    }
    return num;
}

int get_menu() // show menu
{
    int select;
    printf("*****************************************\n");
    printf("*            My Test function           *\n");
    printf("*****************************************\n");
    printf("*        > 1. Function 1                *\n");
    printf("*        > 2. Function 2                *\n");
    printf("*        > 3. Function 3                *\n");
    printf("*        > 4. Function 4                *\n");
    printf("*        > 5. Function 5                *\n");
    printf("*        > 0. Exit                      *\n");
    printf("*****************************************\n");
    printf("Enter menu number : ");
    select=get_int(0,5); // รับค่า menu
    return select;
}

/* Series1 */
double sigma(int n) // ผลบวกของเศษ ทำให้แต่ละพจน์เป็นเลขคู่ และบวกเลขก่อนหน้าเพิ่มไปเรื่อย ๆ จากนั้น return คำตอบ
{
    int i;
    double ans;
    for(i=1,ans=0;i<=n;i++)
        ans = ans+2*i;
    return ans;

}
double product(int n) // ผลคูณของส่วน ให้แต่ละพจน์เพพิ่มขึ้นทีละ 1 แล้วคูณกับเลขก่อนหน้าไปเรื่อย ๆ จากนั้น return คำตอบ
{
    int i;
    double ans;
    for(i=1,ans=1;i<=n;i++)
        ans = ans*i;
    return ans;

}
void Test_Series1(int n,double fi[],double data[],int *count) // ฟังก์ชันอนุกรมเศษส่วน
{
    int i;
    double sum,term;
    for (i=1,sum=0;i<=n;i++)
    {
        term = sigma(i)/product(i);
        sum = sum+term;
        fi[i] = term; // ให้ fi เก็บค่า term
        data[i] = sum; // ให้  data เก็บค่า sum
        *count = i;
    }
}
void Print_Series1(double fi[],double data[],int count) // ฟังก์ชันแสดงผลของ Test_Series1
{
    int i;
    printf("           - TEST #1 -\n");
    printf("*************************************\n");
    printf("*  i  *       fi      *     sum     *\n");
    printf("*************************************\n");
    for(i=1;i<=count;i++)
        printf("* %2d  * %11.6lf   * %10.6lf  *\n",i,fi[i],data[i]);
    printf("*************************************\n");
    printf("ans = %lf\n",data[count]);
    printf("_________________________________________\n\n\n");

}

/* Series2 */
int fibonacci(int n)
{
    int f0 = 0, f1 = 1, f2, i;
    if(n<=1)
        return n;
    else
    for(i=2;i<=n;i++)
    {
        f2=f1+f0;
        f0=f1;
        f1=f2;
    }
    return f2;
}
void Test_Series2(int n,int fi[],int fibo[],int *count) // ฟังก์ชันตรวจสอบ fibonacci ที่เป็นเลขคู่
{
    int i,fib;
    for(i=1,*count=0;*count<10;i++)
    {
        fib = fibonacci(i);
        if (fib%2==0) // ตรวจสอบคำตอบ fibonacci ว่าหาร 2 ลองตัวหรือไม่ เพื่อหาเลขคู่
        {
            *count = *count+1;
            fi[*count] = i; // ให้ fi เก็บค่า i
            fibo[*count] = fib; // ให้ data เก็บค่า fib
        }
    }
}
void Print_Series2(int fi[],int fibo[],int count) // ฟังก์ชันแสดงผลของ Test_Series2
{
    int i;
    printf("           - TEST #2 -\n");
    printf("************************************\n");
    printf("*  count  *     fi    *     sum    *\n");
    printf("************************************\n");
    for(i=1;i<=count;i++)
        printf("* %4d    * %5d     * %8d   *\n",i,fi[i],fibo[i]);
    printf("************************************\n");
    printf("count = %d, ans = %d\n",count,fibo[count]);
    printf("_________________________________________\n\n\n");
}

/* Series3 */
int isprime(int n) // ฟังก์ชันหาค่าจำนวนเฉพาะ โดยถ้าเป็นจำนวนเฉพาะจะให้ return 1 แต่ถ้าไม่ใช่ให้ return 0
{
    int i;
    if(n<=1)
        return 0;
    else
        for(i=2;i<n;i++)
            if(n%i==0)
                return 0;
    return 1;
}
void Test_Series3(int min,int max,int fi[],int prime[],int *count) // ฟังก์ชันจำนวนเฉพาะตั้งแต่ 1 - 30 และผลบวกของค่าในเทอมนั้นบวกกับค่าก่อนหน้า
{
    int i,sum;
    for(i=2,*count=0,sum=0;i<max;i++)
    {
        if(isprime(i)!=0)
            if(i>min)
            {
                sum = sum+i;
                *count = *count+1;
                fi[*count] = i; // ให้ fi เก็บค่า i
                prime[*count] = sum; // ให้ prime เก็บค่า sum
            }
    }
}
void Print_Series3(int fi[],int data[],int count) // ฟังก์ชันแสดงผลของ Test_Series3
{
    int i;
    printf("           - TEST #3 -\n");
    printf("*********************************\n");
    printf("*  no  *     i     *     sum    *\n");
    printf("*********************************\n");
    for(i=1;i<=count;i++)
        printf("* %3d  * %5d     * %6d     *\n",i,fi[i],data[i]);
    printf("*********************************\n");
    printf("count = %d, sum = %d\n",count,data[count]);
    printf("_________________________________________\n\n\n");
}

/* Series4 */
int advproduct(int n) // ฟังก์ชันการหาผลคูณ
{
    int i,j,ans,max;
    for(i=1,ans=0,max=40,j=1;j<=n;j++)
    {
        ans = i*max;
        i=i+2;
        max=max-2;
    }
    return ans;
}
void Test_Series4(int max,int fi[],int data[],int *count) // ฟังก์ชันหาผลรวมของอนุกรม
{
    int i,sum;
    for(i=1,sum=0;sum<max;i++)
    {
        sum = sum + advproduct(i);
        fi[i] = advproduct(i); // ให้ fi เก็บค่า ผลคูณของแต่ละพจน์
        data[i] = sum; // ให้ data เก็บค่า sum
        *count = i-1;
    }
}
void Print_Series4(int fi[],int data[],int count) // ฟังก์ชันแสดงผลของ Test_Series4
{
    int i;
    printf("           - TEST #4 -\n");
    printf("**********************************\n");
    printf("*   i  *     fi     *     sum    *\n");
    printf("**********************************\n");
    for(i=1;i<=count;i++)
        printf("* %3d  * %6d     * %7d    *\n",i,fi[i],data[i]);
    printf("**********************************\n");
    printf("count = %d, ans = %d\n",count,data[count]);
    printf("_________________________________________\n\n\n");
}

/* Series5 */
void Test_Series5(int n,int data[],int *count) // ฟังก์ชันหาพจน์ที่ซ้ำกัน
{
    int i,term;
    for(i=1,*count=0,term=1;i<=n;i++)
    {
        term = 1+((i-1)*15);
        *count = *count+1;
        data[*count] = term; // ให้ data เก็บค่า term
    }
}
void Print_Series5(int data[],int count) // ฟังก์ชันแสดงผลของ Test_Series5
{
    int i;
    printf("    - TEST #5 -\n");
    printf("********************\n");
    printf("*  no  *   term    *\n");
    printf("********************\n");
    for(i=1;i<=count;i++)
        printf("* %3d  * %6d    *\n",i,data[i]);
    printf("********************\n");
    printf("count = %d\n",count);
    printf("_________________________________________\n\n\n");
}

int main()
{
    double fi[20],data[20];
    int i,count,select,intdata[20],term[20];
    do {
        select = get_menu();
        printf("\n");
        if (select==1) {
            Test_Series1(10,fi,data,&count);
            Print_Series1(fi,data,count);
        }
        else if (select==2) {
            Test_Series2(10,term,intdata,&count);
            Print_Series2(term,intdata,count);
        }
        else if (select==3) {
            Test_Series3(1,30,term,intdata,&count);
            Print_Series3(term,intdata,count);
        }
        else if (select==4) {
            Test_Series4(5000,term,intdata,&count);
            Print_Series4(term,intdata,count);
        }
        else if (select==5) {
            Test_Series5(15,intdata,&count);
            Print_Series5(intdata,count);
        }
    } while (select!=0);
    printf("End Program\n");
}
