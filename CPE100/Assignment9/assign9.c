#include<stdio.h>
#include<string.h>
#include<ctype.h>
void add_space(char *buff) /* ฟังก์ชันเพิ่มช่องว่าง */
{
    int i,j;
    char str[255];
    for(i=0,j=0;i<strlen(buff);i++) //ตรวจสอบข้อมูลทั้งหมดที่ถูกเก็บใน buff
    {
        if(strchr("+-*/^()",buff[i])!=NULL) // ตรวจสอบว่าข้อมูลที่ถูกเก็บในตัวแปร buff มี operator อยู่หรือไม่
        {
            str[j++] = ' '; // เพิ่มช่องว่างข้างหน้า
            str[j++] = buff[i]; // เพิ่มตัวปกติ
            str[j++] = ' '; // เพิ่มช่องว่างข้างหลัง
        }
        else
        {
            str[j++] = buff[i]; // ถ้าไม่เจอ operator ให้เติมตัวปกติ
        }
    }
    strcpy(buff,str);
}

int split(char *buff,char token[][20]) /* ฟังก์ชันแบ่งข้อมูลไปเก็บใน array โดยใช้ช่องว่างในการแบ่ง */
{
    int count=0;
    char *tok;
    tok = strtok(buff," "); // แยก string ออกเป็น array โดยคั่นด้วยช่องว่าง
    while(tok!=NULL)
    {
        strcpy(token[count++],tok); // copy tok ไปเก็บใน token[count] ฟลังจากนั้นให้เพิ่ม count ขึ้นทีละ 1
        tok = strtok(NULL," "); // แบ่งคำอีกครั้งโดยเริ่มจาก null เพื่อเริ่มแบ่งจากตัวก่อนหน้า
    }
    return count;
}

int check_operator(char *str) /* ฟังก์ชันตรวจสอบ operator */
{
    if((strlen(str)==1) && (strchr("+-*/^()",str[0])!=NULL)) // ถ้าความยาวเป็น 1 และใน str[0] เป็น +-*/^( ) ให้ return 1
        return 1;
    else
        return 0;
}

int check_number(char *str,double *n) /* ฟังก์ชันตรวจสอบตัวเลข */
{
    char ch;
    if(sscanf(str,"%lf%c",n,&ch)==1) // อ่านข้อมูลจาก str
        return 1;
    else
        return 0;
}

int check_function(char *str) /* ฟังก์ชันตรวจสอบ function */
{
    char buff[20],fname[15][10] = {"sin","cos","tan","asin","acos","atan","sqrt","pow","log","exp","abs"};
    int fcount=11,i=0; // i start at 0 to 10
    strcpy(buff,str);
    strlwr(buff);
    while(i<fcount && strcmp(fname[i],buff)!=0)
        i++; // ถ้าข้อมูลใน buff กับ fname[i] ไม่เท่ากัน ให้เพิ่มค่า i เพื่อหาตัวถัดไป
    if(i<fcount)
        return 1;
    else
        return 0;
}

int check_identifier(char *str) /* ฟังก์ชันตรวจสอบตัวอักษร ตัวเลข underscore*/
{
    int flag=1,i;
    int len=strlen(str);
    if((isalpha(str[0])) || str[0]=='_') // ถ้าข้อมูลตัวแรกเป็นตัวอักษร a-z หรือ underscore
    {
        for(i=1;i<len;i++)
            if(!(isalpha(str[i])) || isdigit(str[i]) || str[i]=='_')
                flag=0; // ถ้าไม่ใช่ตัวอักษร ตัวเลข underscore ให้ flag=0
        return flag; // ถ้าใช่ให้ return flag
    }
    else
        return 0;
}

int main()
{
    int count,i;
    double n;
    char str[255],buff[255],token[40][20]; // token [] -> กี่ตัว  [] -> ความยาว
    do {
        printf("command > ");
        gets(str); // อ่านข้อมูลเข้าไปในตัวแปร str
        strcpy(buff,str); // copy str ไปเก็บใน buff
        strlwr(buff); // แปลงตัวอักษรทั้งหมดเป็นตัวพิมพ์เล็ก
        if(strcmp(str,"end")!=0 && strcmp(str,"exit")!=0)
        {
            add_space(buff); // เพิมช่องว่างหน้าและหลัง operator
            while(buff[strlen(buff)]==' ')
                buff[strlen(buff)]='\0'; // ถ้าตัวสุดท้ายเป็็นช่องว่างให้เปลี่ยนเป็น \0
            printf("\n\"%s\"\n\n",buff);
            count = split(buff,token); // แบ่ง buff ไปเก็บใน token ซึ่งเป็น array 2 มิติ
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
    }while(strcmp(str,"end")!=0 && strcmp(str,"exit")!=0); // จบโปรแกรมเมื่อป้อนข้อมูลเป็น end
    printf("\nEnd Program\n");
    return 0;
}

/*
 1+2.3(7^8)sin + sin_e-2x+x2*2!/_x1 sine
SIN(cos(Tan(aSin(Acos(Atan) SQRT) log)exP)pow)
+-/*^()2 3 .5 exit end 2$ 1A A1 sin2 2sin a@b 1.1. 1.1.1
*/
