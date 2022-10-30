#include<stdio.h>
#include<string.h>
#include<math.h>
struct grade_info
{
    long long id;
    char name[40],grade[3];
    double mid,fin,attend,total,gpoint;
};
typedef struct grade_info student_type; // ��˹������������ struct grade_info �� student_type

int Read_File(char *name,student_type st[]) /* �ѧ��ѹ��ҹ��� */
{
    FILE *fp; // �ͧ����������������
    student_type x; // �ͧ�����������ҹ������ 1 ���
    int count;
    fp = fopen(name,"r"); // ��ҹ���
    if(fp!=NULL)// ��Ǩ�ͺ����Դ���
    {
        while(fscanf(fp,"%llu,%[^,],%lf,%lf,%lf",&x.id,x.name,&x.mid,&x.fin,&x.attend)==5) // ��� address �������ŷ���繵���Ţ / ��ҹ���á��騹���Ҩ��� comma / ��з����ҹ�� 5 ���
        { // �����ҹ�����
            x.total = x.mid + x.fin + x.attend; // �ӹǳ��ṹ���
            st[count++] = x; // ��ҹ������ x 1 �ش ����������㹵���� st ��ѧ�ҡ���������� count
        }
        fclose(fp); // �Դ���
        return count;
    }
    else  // �����ҹ��������
        return 0;
}

int get_int(int min, int max) // ��˹��ͺࢵ input
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
    printf("*******************************************************\n");
    printf("*            My Test function                         *\n");
    printf("*******************************************************\n");
    printf("*      > 1. Show info of all students                 *\n");
    printf("*      > 2. Grade and Statistics                      *\n");
    printf("*      > 3. Sorting scores highest to lowest          *\n");
    printf("*      > 4. Sorting scores in order of student id     *\n");
    printf("*      > 5. Search by range of scores                 *\n");
    printf("*      > 6. Search by grade                           *\n");
    printf("*      > 7. Search by name                            *\n");
    printf("*      > 0. Exit                                      *\n");
    printf("*******************************************************\n");
    printf("Enter menu number : ");
    select=get_int(0,7); // �Ѻ��� menu
    return select;
}

void Print_bar() /* �ѧ��ѹ�ʴ���ǵ��ҧ */
{
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("No.     ID                  Name                              Mid    Final   Attend   Total   GPA   Grade\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

void Print_1_student(int i,student_type x) /* �ѧ��ѹ�ʴ��Ţ����ŷ��Ф� */
{
    printf("%2d) %llu  %-40s %7.1lf %7.1lf %8.1lf %8.1lf %5.1lf     %s\n",i,x.id,x.name,x.mid,x.fin,x.attend,x.total,x.gpoint,x.grade); // ��������ٻẺ�ç���ҧ ��� ���͵����.���Ϳ�Ŵ�
}

void Print_all_student(student_type st[],int stcount) /* �ѧ��ѹ�ʴ��Ţ����ŷ����� */
{
    int i;
    Print_bar();
    for(i=0;i<stcount;i++) // ���ٻ�����ʴ������ŷ�����
        Print_1_student(i+1,st[i]); // �ʴ������ź�÷Ѵ����
    printf("end of data\n\n");
}

void Set_grade(student_type st[],int stcount,double A,double Bp,double B,double Cp,double C,double Dp,double D) /* �ѧ��ѹ�Ѵ�ô */
{ // �Ѻ��� A, B+, B, C+, C, D+, D ��������͹��
    int i;
    for(i=0;i<stcount;i++)
    {
        if(st[i].total>=A)
        {
            st[i].gpoint = 4.0;
            strcpy(st[i].grade,"A");
        }
        else if(st[i].total>=Bp)
        {
            st[i].gpoint = 3.5;
            strcpy(st[i].grade,"B+");
        }
        else if(st[i].total>=B)
        {
            st[i].gpoint = 3.0;
            strcpy(st[i].grade,"B");
        }
        else if(st[i].total>=Cp)
        {
            st[i].gpoint = 2.5;
            strcpy(st[i].grade,"C+");
        }
        else if(st[i].total>=C)
        {
            st[i].gpoint = 2.0;
            strcpy(st[i].grade,"C");
        }
        else if(st[i].total>=Dp)
        {
            st[i].gpoint = 1.5;
            strcpy(st[i].grade,"D+");
        }
        else if(st[i].total>=D)
        {
            st[i].gpoint = 1.0;
            strcpy(st[i].grade,"D");
        }
        else
        {
            st[i].gpoint = 0.0;
            strcpy(st[i].grade,"F");
        }
    } // �ҡ��ṹ����ͧ�ѡ���¹�ç���ࡳ���������˹�����ʴ� gpoint ����ѧ��ѹ�ͧ if �ҡ��鹨� copy �ô (A, B +, B, C +, C, D +, D, F) ��ѧ����� grade �ͧ�ѡ���¹���Ф�
}

void Stat_mid(student_type st[],int stcount,double *min1,double *max1,double *mean1,double *sd1) /* �ѧ��ѹ�ӹǳ��ҷҧʶԵԢͧ mid */
{
    int i;
    double sum=0,sumsqr=0;
    *min1 = *max1 = st[0].mid;
    for(i=0;i<stcount;i++)
    {
        if(st[i].mid < *min1) // �ҡ����ṹ mid �����¡��Ҥ�ṹ�ͧ�ѡ���¹���á
            *min1 = st[i].mid; // ��� min = ��ṹ�ͧ�ѡ���¹�����
        if(st[i].mid > *max1) // �ҡ����ṹ mid ���ҡ���Ҥ�ṹ�ͧ�ѡ���¹���á
            *max1 = st[i].mid; // ��� max = ��ṹ�ͧ�ѡ���¹�����
        sum += st[i].mid; // �ӹǳ��ṹ����ͧ mid
        sumsqr += pow(st[i].mid,2);
    }
    *mean1 = sum/stcount; // �ӹǳ mean �ͧ mid
    *sd1 = sqrt(sumsqr/stcount-pow(*mean1,2)); // �ӹǳ sd �ͧ mid
}
void Stat_final(student_type st[],int stcount,double *min2,double *max2,double *mean2,double *sd2) /* �ѧ��ѹ�ӹǳ��ҷҧʶԵԢͧ final */
{
    int i;
    double sum=0,sumsqr=0;
    *min2 = *max2 = st[0].fin;
    for(i=0;i<stcount;i++)
    {
        if(st[i].fin < *min2)
            *min2 = st[i].fin;
        if(st[i].fin > *max2)
            *max2 = st[i].fin;
        sum += st[i].fin;
        sumsqr += pow(st[i].fin,2);
    }
    *mean2 = sum/stcount;
    *sd2 = sqrt(sumsqr/stcount-pow(*mean2,2));
}
void Stat_attend(student_type st[],int stcount,double *min3,double *max3,double *mean3,double *sd3) /* �ѧ��ѹ�ӹǳ��ҷҧʶԵԢͧ attend */
{
    int i;
    double sum=0,sumsqr=0;
    *min3 = *max3 = st[0].attend;
    for(i=0;i<stcount;i++)
    {
        if(st[i].attend < *min3)
            *min3 = st[i].attend;
        if(st[i].attend > *max3)
            *max3 = st[i].attend;
        sum += st[i].attend;
        sumsqr += pow(st[i].attend,2);
    }
    *mean3 = sum/stcount;
    *sd3 = sqrt(sumsqr/stcount-pow(*mean3,2));
}
void Stat_total(student_type st[],int stcount,double *min4,double *max4,double *mean4,double *sd4) /* �ѧ��ѹ�ӹǳ��ҷҧʶԵԢͧ total */
{
    int i;
    double sum=0,sumsqr=0;
    *min4 = *max4 = st[0].total;
    for(i=0;i<stcount;i++)
    {
        if(st[i].total < *min4)
            *min4 = st[i].total;
        if(st[i].total > *max4)
            *max4 = st[i].total;
        sum += st[i].total;
        sumsqr += pow(st[i].total,2);
    }
    *mean4 = sum/stcount;
    *sd4 = sqrt(sumsqr/stcount-pow(*mean4,2));
}
void Print_stat(student_type st[],int stcount,double min1,double max1,double mean1,double sd1, /* �ѧ��ѹ�ʴ��Ť�ҷҧʶԵԷ����� */
                double min2,double max2,double mean2,double sd2,
                double min3,double max3,double mean3,double sd3,
                double min4,double max4,double mean4,double sd4)
{
    printf("\n>> Statistics <<\n");
    printf("------------------------------------------------------------------\n");
    printf("  Score   |    Midterm        Final        Attend        Total     \n");
    printf("------------------------------------------------------------------\n");
    printf("   min    |     %5.2lf        %6.2lf       %6.2lf        %6.2lf    \n",min1,min2,min3,min4);
    printf("   max    |     %5.2lf        %6.2lf       %6.2lf        %6.2lf    \n",max1,max2,max3,max4);
    printf("   mean   |     %5.2lf        %6.2lf       %6.2lf        %6.2lf    \n",mean1,mean2,mean3,mean4);
    printf("   sd     |     %5.2lf        %6.2lf       %6.2lf        %6.2lf    \n",sd1,sd2,sd3,sd4);
    printf("------------------------------------------------------------------\n");
}

void Count_grade(student_type st[],int stcount,int *countA,int *countBp,int *countB,int *countCp, /* �ѧ��ѹ�Ҩӹǹ�ѡ���¹������ô��ҧ � */
                        int *countC,int *countDp,int *countD,int *countF)
{
    int i;
    *countA=0,*countBp=0,*countB=0,*countCp=0,*countC=0,*countDp=0,*countD=0,*countF=0; // ��˹�����ǹѺ�ء���������鹷�� 0
        for(i=0;i<stcount;i++)
        {
            if(strcmp(st[i].grade,"A")==0)
                *countA = *countA + 1;
            else if(strcmp(st[i].grade,"B+")==0)
                *countBp = *countBp + 1;
            else if(strcmp(st[i].grade,"B")==0)
                *countB = *countB + 1;
            else if(strcmp(st[i].grade,"C+")==0)
                *countCp = *countCp + 1;
            else if(strcmp(st[i].grade,"C")==0)
                *countC = *countC + 1;
            else if(strcmp(st[i].grade,"D+")==0)
                *countDp = *countDp + 1;
            else if(strcmp(st[i].grade,"D")==0)
                *countD = *countD + 1;
            else if(strcmp(st[i].grade,"F")==0)
                *countF = *countF + 1;
        } // ��ѧ��ѹ strcmp ���͵�Ǩ�ͺ������ô�����ҵ�ͧ��ä���������� �ҡ�� strcmp == 0 ��йѺ�ӹǹ�ô����������˹��
}

void Print_count_grade(student_type st[],int stcount,int countA,int countBp,int countB,int countCp, /* �ѧ��ѹ�ʴ��Ũӹǹ�ѡ���¹������ô��ҧ � */
                        int countC,int countDp,int countD,int countF)
{
    printf("\n>> Numbers of students of each grade <<\n");
    printf("--------------------------------------------------\n");
    printf("       |   A    B+   B    C+   C    D+   D    F   \n");
    printf("--------------------------------------------------\n");
    printf(" count |  %2d   %2d   %2d   %2d   %2d   %2d   %2d   %2d\n",countA,countBp,countB,countCp,countC,countDp,countD,countF);
    printf("--------------------------------------------------\n");
}

void Average_grade(student_type student[],int stcount,double *ans) /* �ѧ��ѹ�ӹǳ�ô����� */
{
    int i;
    double sum=0;
    for(i=0;i<stcount;i++)
        sum += student[i].gpoint; //�Ҥ�ṹ����ͧ��ṹ�ѡ���¹������
    *ans = sum/stcount; // �ӹǳ�ô�����
}

void Sort_by_total(student_type st[],int stcount) /* �ѧ��ѹ���§�����Ũҡ�ҡ仹��������ṹ��� */
{
    int i,j;
    student_type x;
    for(i=0;i<stcount-1;i++)
        for(j=i;j<stcount;j++)
            if(st[j].total > st[i].total)
            {
                x = st[i];
                st[i] = st[j]; // ��Ѻ������
                st[j] = x;
            }
}

void Sort_by_id(student_type st[],int stcount) /* �ѧ��ѹ���§�����Ũҡ������ҡ�������ʻ�Шӵ�� */
{
    int i,j;
    student_type x;
    for(i=0;i<stcount-1;i++)
        for(j=i;j<stcount;j++)
            if(st[j].id < st[i].id)
            {
                x = st[i];
                st[i] = st[j];
                st[j] = x;
            }
}

void Search_score(student_type st[],int stcount) /* �ѧ��ѹ���ҹѡ���¹������ṹ��������ǧ����˹� */
{
    int i,count=0;
    double min,max;
    printf("\nEnter Range of min score and max score : ");
    scanf("%lf %lf",&min,&max);
    Print_bar();
    for(i=0;i<stcount;i++)
        if(st[i].total >= min && st[i].total <= max) // ��Ǩ�ͺ��Ҥ�ṹ�������㹪�ǧ����˹��������
        {
            count = count+1; // ��Ѻ����չѡ���¹��褹����դ�ṹ����㹪�ǧ����˹�
            Print_1_student(i,st[i]);

        }
    printf("\nTotal students : %d\n\n",count);
}

void Search_by_grade(student_type st[],int stcount) /* �ѧ��ѹ���ҹѡ���¹������ô�����ǧ����˹� */
{
    char key[3];
    int i,count;
    do {
        printf("\nEnter grade to search (A, B+, B, C+, C, D+, D, F or 0 to Exit) : ");
        scanf("%2s",key);
        count=0;
        if(strcmp(key,"0")!=0)
        {
            Print_bar();
            for(i=0;i<stcount;i++)
                if(strcmp(st[i].grade,key)==0) // ��Ҿ��ô����ͧ�����
                {
                    count = count+1; // ��Ѻ����չѡ���¹��褹������ô����˹�
                    Print_1_student(i,st[i]);
                }
            printf("\nTotal students : %d\n\n",count);
        }
    }while(strcmp(key,"0")!=0);
}

void Search_name(student_type st[],int stcount) /* �ѧ��ѹ���ҹѡ���¹�ҡ�ҧ��ǹ�ͧ���� */
{
    char key[16];
    int i,count;
    do {
        printf("\nEnter key name to search (0 = Exit) : ");
        scanf("%15s",key);
        count=0;
        if(strcmp(key,"0")!=0)
        {
            Print_bar();
            for(i=0;i<stcount;i++)
                if(strstr(st[i].name,key)!=NULL) // ��Ҿ��ӷ���ͧ���������㹪���
                {
                    count = count+1; // ��Ѻ����չѡ���¹��褹����դӷ���ͧ���������㹪���
                    Print_1_student(i,st[i]);
                }
            printf("\nTotal students : %d\n\n",count);
        }
    }while(strcmp(key,"0")!=0);
}

int main()
{
    student_type x,st[100]; // x �յ�������� 8 ���
    int stcount,i,select;
    int countA,countBp,countB,countCp,countC,countDp,countD,countF;
    double A,Bp,B,Cp,C,Dp,D,ans;
    double min1,max1,mean1,sd1,min2,max2,mean2,sd2,min3,max3,mean3,sd3,min4,max4,mean4,sd4;
    stcount = Read_File("score.csv",st); // ��ҹ������ score.csv ����觡�Ѻ count �繵���� stcount

    printf("What score you want to set the grade for A, B+, B, C+, C, D+, D : ");
    scanf("%lf %lf %lf %lf %lf %lf %lf",&A,&Bp,&B,&Cp,&C,&Dp,&D);
    Set_grade(st,stcount,A,Bp,B,Cp,C,Dp,D);

    do {
        select = get_menu();

        if(stcount>0 && select!=0) // �����ҹ����� ��� select!=0 ���Ӥ��������͹� if
        {
            if(select==1)
            {
                printf("\ntotal read %d records\n",stcount); // �ʴ�����������ҹ������������������
                Print_all_student(st,stcount);
            }
            else if(select==2)
            {

                Stat_mid(st,stcount,&min1,&max1,&mean1,&sd1);
                Stat_final(st,stcount,&min2,&max2,&mean2,&sd2);
                Stat_attend(st,stcount,&min3,&max3,&mean3,&sd3);
                Stat_total(st,stcount,&min4,&max4,&mean4,&sd4);
                Print_stat(st,stcount,min1,max1,mean1,sd1,min2,max2,mean2,sd2,min3,max3,mean3,sd3,min4,max4,mean4,sd4);

                Count_grade(st,stcount,&countA,&countBp,&countB,&countCp,&countC,&countDp,&countD,&countF);
                Print_count_grade(st,stcount,countA,countBp,countB,countCp,countC,countDp,countD,countF);

                Average_grade(st,stcount,&ans);
                printf("\n> GPA = %.2lf\n\n",ans);
            }
            else if(select==3)
            {
                Sort_by_total(st,stcount);
                printf("\ntotal read %d records\n",stcount);
                Print_all_student(st,stcount);
            }
            else if(select==4)
            {
                Sort_by_id(st,stcount);
                printf("\ntotal read %d records\n",stcount);
                Print_all_student(st,stcount);
            }
            else if(select==5)
            {
                Search_score(st,stcount);
            }
            else if(select==6)
            {
                Search_by_grade(st,stcount);
            }
            else if(select==7)
            {
                Search_name(st,stcount);
            }
        }
        printf("\n");
    } while(select!=0);
    printf("\nEnd Program\n");
    return 0;
}
