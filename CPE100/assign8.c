#include<stdio.h>
#include<math.h>

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
    printf("************************************\n");
    printf("*         My Test function         *\n");
    printf("************************************\n");
    printf("*        1. Add Data               *\n");
    printf("*        2. Delete Data            *\n");
    printf("*        3. Calculate              *\n");
    printf("*        0. Exit                   *\n");
    printf("************************************\n");
    printf("Enter menu number : ");
    select=get_int(0,3); // รับค่า menu แค่ 0 - 3
    return select;
}

/* ฟังก์ชันเพิ่มข้อมูล */
void Add_Data(double data[],int *count)
{
    int i;
    double a;
    char ch;
    printf(" > Enter Stream of data : ");
    do
    {
        i=scanf("%lf%c",&a,&ch);
        if(i>0 && a>0) // ตรวจสอบว่า input มีค่ามากกว่า 0 หรือไม่
        {
            data[*count] = a;
            *count = *count+1;
        }
    }while(i!=0 && ch!='\n'); //จะรับค่าจนกว่าจะป้อนข้อมูลผิด หรือกด enter
    rewind(stdin);
}

/* ฟังก์ชันแสดงผลข้อมูล */
void Print_Data(double data[],int count)
{
    int i;
    for(i=0;i<count;i++)
        printf("data[%d] = %lf\n",i,data[i]);
}

/* ฟังก์ชันลบข้อมูล */
void Delete_Data_index(double data[],int *count,int id)
{
    int i;
    for(i=id;i<*count-1;i++)
        data[i]=data[i+1];
    *count = *count-1;
}

/* ฟังก์ชันการข้อมูลที่ต้องการจะลบ */
int search_index(double data[],int count,double del)
{
    int i;
    for(i=0;i<count;i++)
        if(data[i]==del)
            return i; // ถ้าเจอให้ return i
    return -1; // ถ้าไม่เจอให้ return -1
}

/* ฟังก์ชันคำนวณค่าทางสถิติ */
void Calculate_Stat(double data[],int count,double *mean,double *sd,double *min,double *max) // ส่งกลับค่า mean, sd, min, max เป็น pointer
{
    int i;
    double sum,sum2;
    *min = data[i];
    for(i=0,sum=0,sum2=0;i<count;i++)
    {
        sum += data[i];
        sum2 += data[i]*data[i];
        if(data[i] < *min)
            *min = data[i];
        if(data[i] > *max)
            *max = data[i];
    }
    *mean = sum/count;
    *sd = sqrt(sum2/count - pow(*mean,2));
}

int main()
{
    double data[100],mean,sd,min,max,del;
    int select,count=0,id,i,check;
    char ch;
    do {
        printf("\n");
        select=get_menu();
        printf("\n");

        if(select==1)
        {
            Add_Data(data,&count);
            Print_Data(data,count);
        }

        if(select==2)
        {
            if(count>0) // ต้องมีข้อมูลในโปรแกรมถึงจะสามารถทำฟังก์ชันลบข้อมูลได้
            {
                printf(" > Enter delete value : "); // ป้อนข้อมูลที่ต้องการลบ
                scanf("%lf",&del);
                do {
                    id = search_index(data,count,del); // -1 -> not found
                    if(id>=0) // พบข้อมูลที่ต้องการจะลบ เนื่องจากฟังก์ชัน search_index return ค่า i กลับมา
                    {
                        check = 1; // ใช้ตรวจสอบเพื่อให้โปรแกรมวนหาตัวซ้ำได้ โดยให้เป็น 1 หมายถึงได้ทำการลบมาแล้วอย่างน้อย 1 ครั้ง
                        do {
                            printf("\nDo you want to delete %.2lf for sure? (y/n) : ",del); // ตั้งคำถามเพื่อยืนยันการลบ
                            scanf(" %c",&ch);
                        } while(ch!='y' && ch!='n');
                        if(ch=='y') // ยืนยันการลบข้อมูล โปรแกรมก็จะทำการลบข้อมูล
                        {
                            Delete_Data_index(data,&count,id);
                            Print_Data(data,count);
                        }
                        else if(ch=='n')
                        {
                            printf("Cancel delete\n");
                            id = -1; // เมื่อปฏิเสธการลบแล้วจะให้ id = -1 เพื่อที่จะได้ออกจากลูป do...while
                        }
                    }
                    else if(check==0) // กรณีลบข้อมูลซ้ำหลายตัว เมื่อลบข้อมูลหมดแล้ว จะได้ไม่แสดงผลว่าไม่พบข้อมูลอีก เพราะโปรแกรมได้วนลูปเข้าเงื่อนไข if แล้ว check จะถูกตั้งให้เท่ากับ 1
                        printf("%lf not found\n",del);
                } while(id!=-1); // โปรแกรมจะทำการวนลูปเมื่อยังไม่พบข้อมูลที่ต้องการลบ
                check = 0;
            }
            else // ถ้าไม่มีข้อมูลในโปรแกรม ให้แสดงผลว่าไม่มีข้อมูล
                printf("No Data, Please input data first.\n");
        }

        if(select==3)
        {
            if(count>1) // ต้องมีข้อมูลอย่างน้อย 2 ตัวถึงจะทำการคำนวณได้
            {
                Print_Data(data,count);
                Calculate_Stat(data,count,&mean,&sd,&min,&max);
                printf("\nMean = %.2lf , SD = %.2lf\n",mean,sd);
                printf("Min = %.2lf , Max = %.2lf\n",min,max);
            }
            else if(count==0) //ไม่มีข้อมูลที่เก็บไว้
                printf("No Data, Please input data first.\n");
            else // มีข้อมูลน้อยกว่า 2 ตัว จึงไม่สามารถคำนวณได้
                printf("Not enough data, Please input data at least 2 data.\n");
        }
    }while (select!=0);
    printf("Exit Program\n");
    return 0;
}

