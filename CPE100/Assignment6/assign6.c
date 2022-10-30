#include<stdio.h>
#include<math.h>
int Newton_Raphson(double a, double b, double c, double err, double Xp, double *Xn)
{
    double delta=1;
    int count=1;
    do {
        if (2*a*Xp+b==0)
            Xp = Xp+0.00001;
        else
        {
            delta = (a*Xp*Xp+b*Xp+c)/(2*a*Xp+b);
            *Xn = Xp - delta;
            Xp = *Xn;
        } count++;
    } while (fabs(delta)>err && count<1000);
    if (count<1000)
        return count;
    else
        return 0;
}

int main()
{
    double a, b, c, x1, x2;
    int loop;
    char ch;
    do {
        printf("\n----- Program calculate root of Equation (Newton-Raphson) -----\n");
        printf("                  > Enter Parameter a : ");
        while (scanf("%lf", &a)!=1)
        {
            rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("                  > Enter Parameter b : ");
        while (scanf("%lf", &b)!=1)
        {
            rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("                  > Enter Parameter c : ");
        while (scanf("%lf", &c)!=1)
        {
            rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("\n");
        loop = Newton_Raphson(a, b, c, 0.0000001, 100.123, &x1);
        loop = Newton_Raphson(a, b, c, 0.0000001, -100.123, &x2);
        printf(" ::  %d Round  ::\n", loop);
        if (loop==0)
            printf(" ::: Can't find answer!! :::\n");
        else
        {
            printf(" ::: Answer x1 = %lf :::\n", x1);
            if (fabs(x1-x2)>0.00001)
                printf(" ::: Answer x2 = %lf :::\n", x2);
        }

        do {
            printf("\nEnter y to calculate again or n to exit. ");
            scanf(" %c", &ch);
        } while(ch!='y' && ch!='n');
            printf("\n");
    } while (ch=='y');
    printf("End Program\n");
}
