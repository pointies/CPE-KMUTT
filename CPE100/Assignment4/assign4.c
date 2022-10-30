#include<stdio.h>
#include<math.h>
int main()
{
    double U, Ux, Uy, zeta, rad, Tgoal, Tall, Sgoal, Smax, Hgoal, g=-9.81;
    char ch;
    do {
        printf("    **************************************");
        printf("\n     Program Calculate Projectile Motions \n");
        printf("    **************************************\n\n");
        printf("    > Enter initial speed (m/sec) : ");
        while (scanf("%lf",&U)!=1)
        {   rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("    > Enter angle of inclination (degree) : ");
        while (scanf("%lf",&zeta)!=1)
        {   rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("    > Enter distance from goal (m) : ");
        while (scanf("%lf",&Sgoal)!=1)
        {   rewind(stdin);
            printf("Invalid input, Please enter again : ");
        }
        printf("\n");

        rad=zeta*M_PI/180;
        Ux=U*cos(rad);
        Uy=U*sin(rad);
        Tgoal=Sgoal/Ux; //v=s/t
        Hgoal=Uy*Tgoal+0.5*g*Tgoal*Tgoal; //s=ut+0.5gt^2

        if (Hgoal<0) {
            Tall=(2*Uy)/-g;
            Smax=Ux*Tall;
            printf("   _______________________________________________\n");
            printf("   |  Ball drop before goal %.2lf m. in %.2lf sec. |\n",Sgoal-Smax,Tall); //บอลตกก่อนถึงประตู
        }
        else {
            printf("   ______________________________________________\n");
            printf("   |  Ball height at goal %.2lf m. in %.2lf sec.  |\n",Hgoal, Tgoal); //บอกว่าบอลสูกจากประตูเท่าไหร่ และเวลา
        }

        if (Hgoal<0) {
            printf("   |  Fail Ball                                  |\n"); //บอลตกก่อน
            printf("   |_____________________________________________|\n");
        }
        else if (Hgoal>=2.44) {
            printf("   |  Overshoot                                 |\n"); //บอลโด่ง
            printf("   |____________________________________________|\n");
        }
        else if (Tgoal>0.5) {
            printf("   |  Save Ball                                 |\n"); //รับได้
            printf("   |____________________________________________|\n");
        }
        else {
            printf("   |  GOAL!!!                                   |\n"); //เข้าประตู
            printf("   |____________________________________________|\n");
        }

        printf("\n");
        do {
            printf(" Enter y to calculate again or n to exit. ");
            scanf(" %c",&ch);
        } while(ch!='y' && ch!='n');
            printf("\n");
            printf("--------------------------------------------------------------\n\n");
    } while (ch=='y');
    printf("End Program\n");
    return 0;
}
