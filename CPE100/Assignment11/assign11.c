#include<stdio.h>
#include<string.h>
#include<math.h>
struct grade_info
{
    long long id;
    char name[40],grade[3];
    double mid,fin,attend,total,gpoint;
};
typedef struct grade_info student_type; // กำหนดชื่อใหม่ให้ struct grade_info เป็น student_type

int Read_File(char *name,student_type st[]) /* ฟังก์ชันอ่านไฟล์ */
{
    FILE *fp; // จองตัวแปรเพื่อใช้เป็นไฟล์
    student_type x; // จองตัวแปรเพื่ออ่านข้อมูล 1 ตะว
    int count;
    fp = fopen(name,"r"); // อ่านไฟล์
    if(fp!=NULL)// ตรวจสอบการเปิดไฟล์
    {
        while(fscanf(fp,"%llu,%[^,],%lf,%lf,%lf",&x.id,x.name,&x.mid,&x.fin,&x.attend)==5) // ใส่ address ให้ข้อมูลที่เป็นตัวเลข / อ่านอะไรก็ได้จนกว่าจะเจอ comma / ขณะที่อ่านได้ 5 ตัว
        { // ถ้าอ่านไฟล์ได้
            x.total = x.mid + x.fin + x.attend; // คำนวณคะแนนรวม
            st[count++] = x; // อ่านข้อมูล x 1 ชุด แล้วเอาไปเก็บในตัวแปร st หลังจากนั้นให้เพิ่ม count
        }
        fclose(fp); // ปิดไฟล์
        return count;
    }
    else  // ถ้าอ่านไฟล์ไม่ได้
        return 0;
}

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
    select=get_int(0,7); // รับค่า menu
    return select;
}

void Print_bar() /* ฟังก์ชันแสดงหัวตาราง */
{
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("No.     ID                  Name                              Mid    Final   Attend   Total   GPA   Grade\n");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

void Print_1_student(int i,student_type x) /* ฟังก์ชันแสดงผลข้อมูลทีละคน */
{
    printf("%2d) %llu  %-40s %7.1lf %7.1lf %8.1lf %8.1lf %5.1lf     %s\n",i,x.id,x.name,x.mid,x.fin,x.attend,x.total,x.gpoint,x.grade); // ใช้ตัวแปรในรูปแบบโครงสร้าง ตือ ชื่อตัวแปร.ชื่อฟิลด์
}

void Print_all_student(student_type st[],int stcount) /* ฟังก์ชันแสดงผลข้อมูลทั้งหมด */
{
    int i;
    Print_bar();
    for(i=0;i<stcount;i++) // ใช้ลูปเพื่อแสดงข้อมูลทั้งหมด
        Print_1_student(i+1,st[i]); // แสดงข้อมูลบรรทัดเดียว
    printf("end of data\n\n");
}

void Set_grade(student_type st[],int stcount,double A,double Bp,double B,double Cp,double C,double Dp,double D) /* ฟังก์ชันตัดเกรด */
{ // รับค่า A, B+, B, C+, C, D+, D ที่ผู้ใช้ป้อนมา
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
    } // หากคะแนนรวมของนักเรียนตรงตามเกณฑ์ที่ผู้ใช้กำหนดก็จะแสดง gpoint ตามฟังก์ชันของ if จากนั้นจะ copy เกรด (A, B +, B, C +, C, D +, D, F) ไปยังตัวแปร grade ของนักเรียนแต่ละคน
}

void Stat_mid(student_type st[],int stcount,double *min1,double *max1,double *mean1,double *sd1) /* ฟังก์ชันคำนวณค่าทางสถิติของ mid */
{
    int i;
    double sum=0,sumsqr=0;
    *min1 = *max1 = st[0].mid;
    for(i=0;i<stcount;i++)
    {
        if(st[i].mid < *min1) // หากพบคะแนน mid ที่น้อยกว่าคะแนนของนักเรียนคนแรก
            *min1 = st[i].mid; // ให้ min = คะแนนของนักเรียนคนนั้น
        if(st[i].mid > *max1) // หากพบคะแนน mid ทีมากกว่าคะแนนของนักเรียนคนแรก
            *max1 = st[i].mid; // ให้ max = คะแนนของนักเรียนคนนั้น
        sum += st[i].mid; // คำนวณคะแนนรวมของ mid
        sumsqr += pow(st[i].mid,2);
    }
    *mean1 = sum/stcount; // คำนวณ mean ของ mid
    *sd1 = sqrt(sumsqr/stcount-pow(*mean1,2)); // คำนวณ sd ของ mid
}
void Stat_final(student_type st[],int stcount,double *min2,double *max2,double *mean2,double *sd2) /* ฟังก์ชันคำนวณค่าทางสถิติของ final */
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
void Stat_attend(student_type st[],int stcount,double *min3,double *max3,double *mean3,double *sd3) /* ฟังก์ชันคำนวณค่าทางสถิติของ attend */
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
void Stat_total(student_type st[],int stcount,double *min4,double *max4,double *mean4,double *sd4) /* ฟังก์ชันคำนวณค่าทางสถิติของ total */
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
void Print_stat(student_type st[],int stcount,double min1,double max1,double mean1,double sd1, /* ฟังก์ชันแสดงผลค่าทางสถิติทั้งหมด */
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

void Count_grade(student_type st[],int stcount,int *countA,int *countBp,int *countB,int *countCp, /* ฟังก์ชันหาจำนวนนักเรียนที่ได้เกรดต่าง ๆ */
                        int *countC,int *countDp,int *countD,int *countF)
{
    int i;
    *countA=0,*countBp=0,*countB=0,*countCp=0,*countC=0,*countDp=0,*countD=0,*countF=0; // กำหนดให้ตัวนับทุกตัวเริ่มต้นที่ 0
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
        } // ใช้ฟังก์ชัน strcmp เพื่อตรวจสอบว่ามีเกรดที่เราต้องการค้นหาหรือไม่ หากพบ strcmp == 0 ก็จะนับจำนวนเกรดนั้นเพิ่มขึ้นหนึ่ง
}

void Print_count_grade(student_type st[],int stcount,int countA,int countBp,int countB,int countCp, /* ฟังก์ชันแสดงผลจำนวนนักเรียนที่ได้เกรดต่าง ๆ */
                        int countC,int countDp,int countD,int countF)
{
    printf("\n>> Numbers of students of each grade <<\n");
    printf("--------------------------------------------------\n");
    printf("       |   A    B+   B    C+   C    D+   D    F   \n");
    printf("--------------------------------------------------\n");
    printf(" count |  %2d   %2d   %2d   %2d   %2d   %2d   %2d   %2d\n",countA,countBp,countB,countCp,countC,countDp,countD,countF);
    printf("--------------------------------------------------\n");
}

void Average_grade(student_type student[],int stcount,double *ans) /* ฟังก์ชันคำนวณเกรดเฉลี่ย */
{
    int i;
    double sum=0;
    for(i=0;i<stcount;i++)
        sum += student[i].gpoint; //หาคะแนนรวมของคะแนนนักเรียนทั้งหมด
    *ans = sum/stcount; // คำนวณเกรดเฉลี่ย
}

void Sort_by_total(student_type st[],int stcount) /* ฟังก์ชันเรียงข้อมูลจากมากไปน้อยโดยใช้คะแนนรวม */
{
    int i,j;
    student_type x;
    for(i=0;i<stcount-1;i++)
        for(j=i;j<stcount;j++)
            if(st[j].total > st[i].total)
            {
                x = st[i];
                st[i] = st[j]; // สลับข้อมูล
                st[j] = x;
            }
}

void Sort_by_id(student_type st[],int stcount) /* ฟังก์ชันเรียงข้อมูลจากน้อยไปมากโดยใช้รหัสประจำตัว */
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

void Search_score(student_type st[],int stcount) /* ฟังก์ชันค้นหานักเรียนที่ได้คะแนนรวมตามช่วงที่กำหนด */
{
    int i,count=0;
    double min,max;
    printf("\nEnter Range of min score and max score : ");
    scanf("%lf %lf",&min,&max);
    Print_bar();
    for(i=0;i<stcount;i++)
        if(st[i].total >= min && st[i].total <= max) // ตรวจสอบว่าคะแนนรวมอยู่ในช่วงที่กำหนดหรือไม่
        {
            count = count+1; // ใช้นับว่ามีนักเรียนกี่คนที่มีคะแนนอยู่ในช่วงที่กำหนด
            Print_1_student(i,st[i]);

        }
    printf("\nTotal students : %d\n\n",count);
}

void Search_by_grade(student_type st[],int stcount) /* ฟังก์ชันค้นหานักเรียนที่ได้เกรดตามช่วงที่กำหนด */
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
                if(strcmp(st[i].grade,key)==0) // ถ้าพบเกรดที่ต้องการหา
                {
                    count = count+1; // ใช้นับว่ามีนักเรียนกี่คนที่มีเกรดที่กำหนด
                    Print_1_student(i,st[i]);
                }
            printf("\nTotal students : %d\n\n",count);
        }
    }while(strcmp(key,"0")!=0);
}

void Search_name(student_type st[],int stcount) /* ฟังก์ชันค้นหานักเรียนจากบางส่วนของชื่อ */
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
                if(strstr(st[i].name,key)!=NULL) // ถ้าพบคำที่ต้องการหาอยู่ในชื่อ
                {
                    count = count+1; // ใช้นับว่ามีนักเรียนกี่คนที่มีคำที่ต้องการหาอยู่ในชื่อ
                    Print_1_student(i,st[i]);
                }
            printf("\nTotal students : %d\n\n",count);
        }
    }while(strcmp(key,"0")!=0);
}

int main()
{
    student_type x,st[100]; // x มีตัวแปรอยู่ 8 ตัว
    int stcount,i,select;
    int countA,countBp,countB,countCp,countC,countDp,countD,countF;
    double A,Bp,B,Cp,C,Dp,D,ans;
    double min1,max1,mean1,sd1,min2,max2,mean2,sd2,min3,max3,mean3,sd3,min4,max4,mean4,sd4;
    stcount = Read_File("score.csv",st); // อ่านไฟล์ชื่อ score.csv และส่งกลับ count เป็นตัวแปร stcount

    printf("What score you want to set the grade for A, B+, B, C+, C, D+, D : ");
    scanf("%lf %lf %lf %lf %lf %lf %lf",&A,&Bp,&B,&Cp,&C,&Dp,&D);
    Set_grade(st,stcount,A,Bp,B,Cp,C,Dp,D);

    do {
        select = get_menu();

        if(stcount>0 && select!=0) // ถ้าอ่านไฟล์ได้ และ select!=0 ให้ทำคำสั่งในเงื่อนไข if
        {
            if(select==1)
            {
                printf("\ntotal read %d records\n",stcount); // แสดงว่าโปรแกรมอ่านข้อมูลในโปรแกรมได้กี่ตัว
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
