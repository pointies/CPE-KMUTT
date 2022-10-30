#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

typedef struct node {
    double info;
    struct node *next;
} linkedList;
linkedList *first, *last, *ptr;

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

int check_group(char cmd[][20], int *i)
{
    *i=0;
    char cmd_list[20][19] = {"list", "end", "sort", "pop", "help",
                            "sqrt", "rec", "neg", "pow", "+", "-", "*", "/",
                            "delete", "search", "peek", "push",
                            "add", "insert"};
    while((*i < 19) && (strcmp(cmd_list[*i], cmd[0]) != 0))
        (*i)++;
    if(*i < 13)
        return 1;
    else if(*i > 12 && *i < 17)
        return 2;
    else if(*i > 16 && *i < 19)
        return 3;
    return 0;
}

int check_parameter(char cmd[][20], int count, int *parameter)
{
    int index = 1;
    double check_db;
    char check_ch;
    while((index < count) && (sscanf(cmd[index], "%lf%s", &check_db, &check_ch) == 1)) 
        index++;
    *parameter = index-1;
    if(*parameter != (count-1))
        return 0;
    else
        return 1;
}

/* list f. */
void print_list()
{
    int count=0;
    ptr = first;
    printf("\n");
    if(ptr == NULL)
        printf("list> NULL\n");
    else {
        printf("list> ");
        while(ptr != NULL)
        {
            count++;
            printf("%g ",ptr->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void create_node(double item)
{
    ptr = (linkedList*)malloc(sizeof(linkedList));
    ptr->next = NULL;
    ptr->info = item;
}

/* add f. */
void add_node(double *item, int count)
{
    for(int i=0;i<count;i++)
    {
        create_node(item[i]);
        if(first == NULL)
            first = last = ptr;
        else {
            last->next = ptr;
            last = ptr;
        }
    }
}

/* sort f. */
void sort()
{
    linkedList *ptr_i, *ptr_j;
    double x;
    if(first==NULL)
        printf("answer> no data\n");
    else
    {
        for(ptr_i = first; ptr_i->next != NULL; ptr_i = ptr_i->next)
            for(ptr_j = ptr_i->next; ptr_j != NULL; ptr_j = ptr_j->next)
                if(ptr_j->info < ptr_i->info)
                {
                    x = ptr_i->info;
                    ptr_i->info = ptr_j->info;
                    ptr_j->info = x;
                }
    }
}

int check_sort()
{
    ptr = first;
    while((ptr != NULL) && (ptr->next != NULL))
    {
        if(ptr->info > ptr->next->info)
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

/* insert f. */
void insert_node(double item[], int count)
{
    if(check_sort() == 0)
        printf("answer> can't insert please sorted before\n");
    else if(check_sort() == 1)
    {
        add_node(item, count);
        sort();
    }
}

/* push f. */
void push_node(double item)
{
    create_node(item);
    if(first == NULL)
        first = last = ptr;
    else
    {
        ptr->next = first;
        first = ptr;
    }
}

int linkedlist_size()
{
    linkedList *ptr;
    int count=0;
    ptr = first;
    while(ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

/* peek f. */
void peek_node(double item)
{
    int count=0;
    ptr = first;
    if(first == NULL)
        printf("answer> no data\n");
    else if(item < -1)
        printf("answer> parameter error\n");
    else if(item == -1)
        printf("answer> %g\n",last->info);
    else if (item >= linkedlist_size())
        printf("answer > Maximum peek = %d\n",linkedlist_size()-1);
    else {
        double res = ptr->info;
        while(ptr != NULL && count < item)
        { 
            ptr = ptr->next;
            res = ptr->info;
            count++;
        }
        printf("answer > %g\n",res);
    }
}

/* search f. */
int search_node(double item)
{
    int ch = 0;
    int index = 0;
    ptr = first;
    while((ptr != NULL) && (ptr->info != item))
    {
        ptr = ptr->next;
        index++;
    }
    if(first == NULL)
        printf("answer> no data\n");
    else if(ptr!=NULL)
    {
        printf("answer> found %g at [%d]\n",item,index);
        ch = 1;
    }
    else
    {
        printf("answer> %g not found\n",item);
        ch = 0;
    }
    return ch;
}

int search(double item, int start)
{
    linkedList *ptr;
    int index=0;
    ptr = first;
    while((index < start) && (ptr != NULL))
    {
        ptr = ptr->next;
        index++;
    }
    while((ptr != NULL) && (ptr->info != item))
    {
        ptr = ptr->next;
        index++;
    }
    if(ptr != NULL)
        return index;
    else
        return -1;
}

linkedList *delete_pos(int pos)
{
    linkedList *ptr;
    linkedList *prev = first;
    int i=0;
    if((pos == 0) && (linkedlist_size() == 1))
    {
        ptr = first;
        first = last = NULL;
    }
    else if(pos == 0)
    {
        ptr = first;
        first = first->next;
    }
    else {
        while(i != pos-1)
        {
            prev = prev->next;
            i++;
        }
        if(pos == linkedlist_size())
        {
            ptr = last;
            last = prev;
            last->next = NULL;
        }
        else {
            ptr = prev->next;
            prev->next = ptr->next;
        }
    }
    return ptr;
}

/* delete f. */
void delete_node(double item)
{
    char ch;
    int pos = search(item, 0);
    if(first == NULL)
        printf("answer> no data\n");
    else if(pos == -1)
        printf("answer> %g not found\n", item);
    else
        for(int i=0; (i < linkedlist_size()) && (pos != -1); i++)
        {
            printf("answer> %g found enter y to confirm ", item);
            scanf("%s", &ch);
            if(ch == 'y')
                delete_pos(pos);
            pos = search(item, pos+1);
        }
}

/* pop f. */
linkedList *pop(double *item)
{
    if(first != NULL)
    {
        linkedList *ptr = first;
        *item = ptr->info;
    }
    return delete_pos(0);

}

void pop_node()
{
    double item;
    if(linkedlist_size()!=0)
    {
        pop(&item);
        printf("answer> %g\n", item);
    }
    else
        printf("answer> no data\n");
}

void operator1(int n)
{
    ptr = first;
    double item;
    if(first == NULL)
        printf("answer> no data\n");
    else
    {
        ptr = pop(&item);
        if(n==1)
            ptr->info = sqrt(ptr->info);
        else if(n==2)
            ptr->info = 1 / ptr->info;
        else if(n==3)
            ptr->info = -1 * ptr->info;
        push_node(ptr->info);
        printf("answer> %g\n", ptr->info);
    }
}

void operator2(int n)
{
    linkedList *ptr_1, *ptr_2;
    ptr_1 = first;
    double item;
    if(first == NULL)
        printf("answer> no data\n");
    else
    {
        if (ptr_1->next == NULL)
            printf("answer> can't operation\n");
        else
        {
            ptr_1 = pop(&item);
            ptr_2 = pop(&item);
            if(n==1)
                ptr_2->info = pow(ptr_2->info, ptr_1->info);
            else if(n==2)
                ptr_2->info = ptr_2->info + ptr_1->info;
            else if(n==3)
                ptr_2->info = ptr_2->info - ptr_1->info;
            else if(n==4)
                ptr_2->info = ptr_2->info * ptr_1->info;
            else if(n==5)
                ptr_2->info = ptr_2->info / ptr_1->info;
            push_node(ptr_2->info);
            printf("answer> %g\n", ptr_2->info);
        }
    }
}

void help()
{
    char cmd_list[20][40] = {"list:  show current stack",
                           "end:  end program",
                           "sort:  ascending sort",
                           "pop:  pop first element",
                           "help:  help menu",
                           "sqrt",
                           "rec",
                           "neg",
                           "pow",
                           "+",
                           "-",
                           "*",
                           "/",
                           "delete <n>",
                           "search <n>",
                           "peek <n>",
                           "push <n>",
                           "add <list>",
                           "insert <list>"};

    printf("answer> list of command\n");
    for (int i = 0; i < 19; i++)
        printf("\t%2d) %s\n", i, cmd_list[i]);
}

int check_cmd(char cmd[][20], int group, int parameter)
{
    int ch=0;
    if(group == 1 && parameter == 0)
        ch = 1;
    else if(group == 2 && parameter == 1)
        ch = 1;
    else if(group == 3 && parameter >= 1)
        ch = 1;
    else if(group != 0 && parameter == 0)
        printf("answer> syntax error\n");
    else
        printf("answer> parameter error\n");
    return ch;
}

void do_command(char cmd[][20], int n, int count)
{
    double num[50];
    for(int i=0; i<count; i++)
        sscanf(cmd[i+1],"%lf",&num[i]);
    if(n==0)          print_list();
    else if(n==2)     sort();
    else if(n==3)     pop_node();
    else if(n==4)     help();
    else if(n==5)     operator1(1);
    else if(n==6)     operator1(2);
    else if(n==7)     operator1(3);
    else if(n==8)     operator2(1);
    else if(n==9)     operator2(2);
    else if(n==10)    operator2(3);
    else if(n==11)    operator2(4);
    else if(n==12)    operator2(5);
    else if(n==13)    delete_node(num[0]);
    else if(n==14)    search_node(num[0]);
    else if(n==15)    peek_node(num[0]);
    else if(n==16)    push_node(num[0]);
    else if(n==17)    add_node(num, count);
    else if(n==18)    insert_node(num, count);
}

int main()
{
    char str[100], buff[100], cmd[10][20];
    int group=0,parameter=0,count=0,i=0,ch=0;
    do {
        rewind(stdin);

        print_list();
        printf("command> ");
        gets(str);
        strcpy(buff, str);
        strlwr(buff);

        count = split(buff,cmd);
        group = check_group(cmd, &i);
        if(group == 0)
            printf("answer> syntax error\n");
        else if(check_parameter(cmd, count, &parameter) == 0)
            printf("answer> parameter error\n");
        else
        {
            ch = check_cmd(cmd, group, parameter);
            if(ch == 1)
                do_command(cmd, i, count-1);
        }

    } while(strcmp(str,"end"));

    printf("\nEnd Program\n");
    printf("Program written by 63070501044 Parinda Kongwattanasin\n");

    return 0;
}