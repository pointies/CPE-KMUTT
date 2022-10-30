#include<stdio.h>
#include<math.h>

int get_int(int min, int max) //กำหนดขอบเขต input
{
    int num;
    while(scanf("%d",&num)!=1 || num<min || num>max)
    {
        rewind(stdin);
        printf("Input error, Please enter again (%d-%d) : ", min, max);
    }
    return num;
}

//Fibonacci func.
int fibonacci(int n)
{
    // f2 = f1 + f0
    int f0 = 0, f1 = 1, f2, i;
    if(n<=1)
        return n;
    else
    for(i=2;i<=n;i++) {
        f2=f1+f0;
        f0=f1;
        f1=f2;
    }
    return f2;
}

//Combination func.
    // factorial
int factorial(int n)
{
    int ans, i;
    for(ans=1, i=n ; i>=1 ; i=i-1) {
        ans=ans*i;
    }
    return ans;
}
    //nCr
int nCr(int n, int r)
{
    int ans;
    ans=factorial(n)/(factorial(r)*factorial(n-r));
    return ans;
}

//GCD
int GCD(int n, int r)
{
    int ans;
    for(ans=n;n%ans!=0 || r%ans!=0;ans=ans-1) {

    }
    return ans;
}

int get_menu()
{
    int select;
    printf("*****************************************\n");
    printf("*            My Test function           *\n");
    printf("*****************************************\n");
    printf("*        > 1. Fibonacci function        *\n");
    printf("*        > 2. Combination number        *\n");
    printf("*        > 3. Find GCD (x,y)            *\n");
    printf("*        > 4. Factorial                 *\n");
    printf("*        > 0. Exit                      *\n");
    printf("*****************************************\n");
    printf("Enter menu number : ");
    select=get_int(0,4);
    return select;
}

int main()
{
    int select, n, r, ans;
    do {
        select=get_menu();
        if(select==1) {
            printf("\n--- Calculate fibonacci number ---\n");
            printf("Enter fibonacci term f(n) = (0-45) : ");
            n=get_int(0,45);
            ans=fibonacci(n);
            printf("Answer of fibonacci (%d) = %d\n\n\n", n, ans);
        }
        else if(select==2) {
            printf("\n--- Calculate combination number ---\n");
            printf("Enter n : ");
            n=get_int(1,10);
            printf("Enter r : ");
            r=get_int(1,n);
            ans=nCr(n,r);
            printf("Answer of %dC%d = %d\n\n\n",n ,r, ans);
        }
        else if(select==3) {
            printf("\n--- Calculate GDC(x,y) ---\n");
            printf("Enter x : ");
            n=get_int(1,1000);
            printf("Enter y : ");
            r=get_int(1,1000);
            ans=GCD(n,r);
            printf("Answer of GCD(%d,%d) = %d\n\n\n", n, r, ans);
        }
        else if(select==4) {
            printf("\n--- Calculate Factorial ---\n");
            printf("Enter n : ");
            n=get_int(0,12);
            ans=factorial(n);
            printf("Answer of Factorial %d = %d\n\n\n", n, ans);
        }
    }while(select!=0);
    printf("\n------ END PROGRAM ------\n");
    return 0;
}
