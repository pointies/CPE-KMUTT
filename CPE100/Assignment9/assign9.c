#include<stdio.h>
#include<string.h>
#include<ctype.h>
void add_space(char *buff) /* �ѧ��ѹ������ͧ��ҧ */
{
    int i,j;
    char str[255];
    for(i=0,j=0;i<strlen(buff);i++) //��Ǩ�ͺ�����ŷ��������١��� buff
    {
        if(strchr("+-*/^()",buff[i])!=NULL) // ��Ǩ�ͺ��Ң����ŷ��١��㹵���� buff �� operator �����������
        {
            str[j++] = ' '; // ������ͧ��ҧ��ҧ˹��
            str[j++] = buff[i]; // ������ǻ���
            str[j++] = ' '; // ������ͧ��ҧ��ҧ��ѧ
        }
        else
        {
            str[j++] = buff[i]; // �������� operator ��������ǻ���
        }
    }
    strcpy(buff,str);
}

int split(char *buff,char token[][20]) /* �ѧ��ѹ�觢��������� array �����ͧ��ҧ㹡���� */
{
    int count=0;
    char *tok;
    tok = strtok(buff," "); // �¡ string �͡�� array �¤�蹴��ª�ͧ��ҧ
    while(tok!=NULL)
    {
        strcpy(token[count++],tok); // copy tok ���� token[count] ��ѧ�ҡ���������� count ��鹷��� 1
        tok = strtok(NULL," "); // �觤��ա������������ҡ null ����������觨ҡ��ǡ�͹˹��
    }
    return count;
}

int check_operator(char *str) /* �ѧ��ѹ��Ǩ�ͺ operator */
{
    if((strlen(str)==1) && (strchr("+-*/^()",str[0])!=NULL)) // ��Ҥ�������� 1 ���� str[0] �� +-*/^( ) ��� return 1
        return 1;
    else
        return 0;
}

int check_number(char *str,double *n) /* �ѧ��ѹ��Ǩ�ͺ����Ţ */
{
    char ch;
    if(sscanf(str,"%lf%c",n,&ch)==1) // ��ҹ�����Ũҡ str
        return 1;
    else
        return 0;
}

int check_function(char *str) /* �ѧ��ѹ��Ǩ�ͺ function */
{
    char buff[20],fname[15][10] = {"sin","cos","tan","asin","acos","atan","sqrt","pow","log","exp","abs"};
    int fcount=11,i=0; // i start at 0 to 10
    strcpy(buff,str);
    strlwr(buff);
    while(i<fcount && strcmp(fname[i],buff)!=0)
        i++; // ��Ң������ buff �Ѻ fname[i] �����ҡѹ ���������� i �����ҵ�ǶѴ�
    if(i<fcount)
        return 1;
    else
        return 0;
}

int check_identifier(char *str) /* �ѧ��ѹ��Ǩ�ͺ����ѡ�� ����Ţ underscore*/
{
    int flag=1,i;
    int len=strlen(str);
    if((isalpha(str[0])) || str[0]=='_') // ��Ң����ŵ���á�繵���ѡ�� a-z ���� underscore
    {
        for(i=1;i<len;i++)
            if(!(isalpha(str[i])) || isdigit(str[i]) || str[i]=='_')
                flag=0; // �����������ѡ�� ����Ţ underscore ��� flag=0
        return flag; // �������� return flag
    }
    else
        return 0;
}

int main()
{
    int count,i;
    double n;
    char str[255],buff[255],token[40][20]; // token [] -> �����  [] -> �������
    do {
        printf("command > ");
        gets(str); // ��ҹ����������㹵���� str
        strcpy(buff,str); // copy str ���� buff
        strlwr(buff); // �ŧ����ѡ�÷������繵�Ǿ�������
        if(strcmp(str,"end")!=0 && strcmp(str,"exit")!=0)
        {
            add_space(buff); // �����ͧ��ҧ˹�������ѧ operator
            while(buff[strlen(buff)]==' ')
                buff[strlen(buff)]='\0'; // ��ҵ���ش������繪�ͧ��ҧ�������¹�� \0
            printf("\n\"%s\"\n\n",buff);
            count = split(buff,token); // �� buff ���� token ����� array 2 �Ե�
            for(i=0;i<count;i++)
            {
                printf("[%d] %s\n",i,token[i]);
                if(check_operator(token[i])==1)
                    printf("   > %s id operator\n",token[i]);
                else if(check_number(token[i],&n)==1)
                    printf("   > %s is number = %lf\n",token[i],n);
                else if(check_function(token[i])==1)
                    printf("   > %s is function\n",token[i]);
                else if(check_identifier(token[i])==1)
                    printf("   > %s is identifier\n",token[i]);
                else
                    printf("   > %s is error\n",token[i]);
            }
        }
    }while(strcmp(str,"end")!=0 && strcmp(str,"exit")!=0); // �����������ͻ�͹�������� end
    printf("\nEnd Program\n");
    return 0;
}

/*
 1+2.3(7^8)sin + sin_e-2x+x2*2!/_x1 sine
SIN(cos(Tan(aSin(Acos(Atan) SQRT) log)exP)pow)
+-/*^()2 3 .5 exit end 2$ 1A A1 sin2 2sin a@b 1.1. 1.1.1
*/
