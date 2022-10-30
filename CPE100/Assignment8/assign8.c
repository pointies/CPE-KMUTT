#include<stdio.h>
#include<math.h>

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
    printf("************************************\n");
    printf("*         My Test function         *\n");
    printf("************************************\n");
    printf("*        1. Add Data               *\n");
    printf("*        2. Delete Data            *\n");
    printf("*        3. Calculate              *\n");
    printf("*        0. Exit                   *\n");
    printf("************************************\n");
    printf("Enter menu number : ");
    select=get_int(0,3); // �Ѻ��� menu �� 0 - 3
    return select;
}

/* �ѧ��ѹ���������� */
void Add_Data(double data[],int *count)
{
    int i;
    double a;
    char ch;
    printf(" > Enter Stream of data : ");
    do
    {
        i=scanf("%lf%c",&a,&ch);
        if(i>0 && a>0) // ��Ǩ�ͺ��� input �դ���ҡ���� 0 �������
        {
            data[*count] = a;
            *count = *count+1;
        }
    }while(i!=0 && ch!='\n'); //���Ѻ��Ҩ����Ҩл�͹�����żԴ ���͡� enter
    rewind(stdin);
}

/* �ѧ��ѹ�ʴ��Ţ����� */
void Print_Data(double data[],int count)
{
    int i;
    for(i=0;i<count;i++)
        printf("data[%d] = %lf\n",i,data[i]);
}

/* �ѧ��ѹź������ */
void Delete_Data_index(double data[],int *count,int id)
{
    int i;
    for(i=id;i<*count-1;i++)
        data[i]=data[i+1];
    *count = *count-1;
}

/* �ѧ��ѹ��â����ŷ���ͧ��è�ź */
int search_index(double data[],int count,double del)
{
    int i;
    for(i=0;i<count;i++)
        if(data[i]==del)
            return i; // �������� return i
    return -1; // ����������� return -1
}

/* �ѧ��ѹ�ӹǳ��ҷҧʶԵ� */
void Calculate_Stat(double data[],int count,double *mean,double *sd,double *min,double *max) // �觡�Ѻ��� mean, sd, min, max �� pointer
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
            if(count>0) // ��ͧ�բ������������֧������ö�ӿѧ��ѹź��������
            {
                printf(" > Enter delete value : "); // ��͹�����ŷ���ͧ���ź
                scanf("%lf",&del);
                do {
                    id = search_index(data,count,del); // -1 -> not found
                    if(id>=0) // �������ŷ���ͧ��è�ź ���ͧ�ҡ�ѧ��ѹ search_index return ��� i ��Ѻ��
                    {
                        check = 1; // ���Ǩ�ͺ������������ǹ�ҵ�ǫ���� ������� 1 ���¶֧��ӡ��ź���������ҧ���� 1 ����
                        do {
                            printf("\nDo you want to delete %.2lf for sure? (y/n) : ",del); // ��駤Ӷ�������׹�ѹ���ź
                            scanf(" %c",&ch);
                        } while(ch!='y' && ch!='n');
                        if(ch=='y') // �׹�ѹ���ź������ �������зӡ��ź������
                        {
                            Delete_Data_index(data,&count,id);
                            Print_Data(data,count);
                        }
                        else if(ch=='n')
                        {
                            printf("Cancel delete\n");
                            id = -1; // ����ͻ���ʸ���ź���Ǩ���� id = -1 ���ͷ������͡�ҡ�ٻ do...while
                        }
                    }
                    else if(check==0) // �ó�ź�����ū�����µ�� �����ź������������� ��������ʴ��������辺�������ա �����������ǹ�ٻ������͹� if ���� check �ж١��������ҡѺ 1
                        printf("%lf not found\n",del);
                } while(id!=-1); // ������зӡ��ǹ�ٻ������ѧ��辺�����ŷ���ͧ���ź
                check = 0;
            }
            else // �������բ����������� ����ʴ����������բ�����
                printf("No Data, Please input data first.\n");
        }

        if(select==3)
        {
            if(count>1) // ��ͧ�բ��������ҧ���� 2 ��Ƕ֧�зӡ�äӹǳ��
            {
                Print_Data(data,count);
                Calculate_Stat(data,count,&mean,&sd,&min,&max);
                printf("\nMean = %.2lf , SD = %.2lf\n",mean,sd);
                printf("Min = %.2lf , Max = %.2lf\n",min,max);
            }
            else if(count==0) //����բ����ŷ�������
                printf("No Data, Please input data first.\n");
            else // �բ����Ź��¡��� 2 ��� �֧�������ö�ӹǳ��
                printf("Not enough data, Please input data at least 2 data.\n");
        }
    }while (select!=0);
    printf("Exit Program\n");
    return 0;
}

