#include<stdio.h>
#include<string.h>

int split(char *buff, char cmd[][20])
{
    int count=0;
    char *token;
    token = strtok(buff," ");
    while(token != NULL)
    {
        strcpy(cmd[count++],token);
        token = strtok(NULL," ");
    }
    return count;
}

int check_group(char cmd[][20])
{
    int i=0;
    char cmd_list[20][19] = {"list","end","sort","pop","help","sqrt","rec","neg","pow","+","-","*","/",
                            "delete","search","peek","push",
                            "add","insert"};
    while ((i < 19) && (strcmp(cmd_list[i], cmd[0]) != 0))
        i++;
    if (i < 13)
        return 1;
    else if (i > 12 && i < 17)
        return 2;
    else if (i > 16 && i < 19)
        return 3;
    return 0;
}

int check_parameter(char cmd[][20], int count, int *parameter)
{
    int index = 1;
    int check_int;
    char check_ch;
    while((index < count) && (sscanf(cmd[index], "%d%s", &check_int, &check_ch) == 1))
        index++;
    *parameter = index-1;
    if(*parameter != (count-1))
        return 0;
    else
        return 1;
}

int check_cmd(char cmd[][20], int group, int parameter)
{

    if(group == 1 && parameter == 0)
        printf("answer> OK\n");
    else if(group == 2 && parameter == 1)
        printf("answer> OK\n");
    else if(group == 3 && parameter >= 1)
        printf("answer> OK\n");
    else
        printf("answer> parameter error\n");
}

int main()
{
    char str[100], buff[100], cmd[10][20];
    int group,parameter,count;
    do {
        printf("command> ");
        gets(str);
        strcpy(buff, str);
        strlwr(buff);

        count = split(buff,cmd);
        group = check_group(cmd);
        if(group == 0)
            printf("answer> syntax error\n");
        else if(check_parameter(cmd, count, &parameter) == 0)
            printf("answer> parameter error\n");
        else
            check_cmd(cmd, group, parameter);

    } while(strcmp(str,"end"));

    printf("\nEnd Program\n");
    printf("Program written by 63070501044 Parinda Kongwattanasin\n");

    return 0;
}
