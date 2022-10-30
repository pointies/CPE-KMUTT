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
    int check_db;
    char check_ch;
    while((index < count) && (sscanf(cmd[index], "%lf%s", &check_db, &check_ch) == 1))
        index++;
    *parameter = index-1;
    if(*parameter != (count-1))
        return 0;
    else
        return 1;
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

linkedList *create_node(double item)
{
    linkedList *ptr;
    ptr = (linkedList*)malloc(sizeof(linkedList));
    ptr->next = NULL;
    ptr->info = item;
    return ptr;
}

/* add f. */
void add_node(double item)
{
    linkedList *ptr = create_node(item);
    if(first == NULL)
        first = last = ptr;
    else {
        last->next = ptr;
        last = ptr;
    }
}

/* sort f. */
void scanSort()
{
    linkedList *ptr_i, *ptr_j;
    double x;
    for(ptr_i = first ; ptr_i->next != NULL ; ptr_i = ptr_i->next)
        for(ptr_j = ptr_i->next ; ptr_j != NULL ; ptr_j = ptr_j->next)
            if(ptr_j->info < ptr_i->info)
            {
                x = ptr_i->info;
                ptr_i->info = ptr_j->info;
                ptr_j->info = x;
            }
}

int sort()
{
    linkedList *ptr = first;
    while ((ptr != NULL) && (ptr->next != NULL) && (linkedlist_size() > 1))
    {
        if (ptr->info > ptr->next->info)
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

/* insert f. */
void insert_node(double item)
{
    if (sort() == 0)
        printf("answer> can't insert please sort before\n");
    else if(sort() == 1 || linkedlist_size() == 0)
    {
        add_node(item);
        scanSort();
    }
}

/* push f. */
void push_node(double item)
{
    linkedList *ptr = create_node(item);
    if(first == NULL)
        first = last = ptr;
    else
    {
        ptr->next = first;
        first = ptr;
    }
}

/* peek f. */
void peek_node(double item)
{
    linkedList *ptr;
    ptr = first;
    int count=0;
    if(item == -1)
        printf("answer> %g\n",last->info);
    else {
        while((ptr != NULL) && (ptr->info != item))
        {
            ptr = ptr->next;
            count++;
        }
        printf("answer > %g\n",ptr->info);
        if(item>=count)
            printf("answer > Maximum peek = %d\n",count-1);
    }
}

/* search f. */
int search_node(double item, int num)
{
    linkedList *ptr;
    int index=0;
    ptr = first;
    while((ptr != NULL) && (index < num))
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
        printf("answer> found %g at [%d]\n",item,index); //return index;
    else
        printf("answer> %g no data\n",item); // return -1;
}

linkedList *_delete(int pos) // เอาไปเรียกใช้ใน pop ด้วย
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
    char ch = '\0';
    int pos = search_node(item, 0);
    if(pos == -1)
        printf("answer> %.0lf not found\n", item);
    else
    {
        printf("answer> %.0lf found enter y to confirm ", item);
        scanf("%s", &ch);
        if(ch == 'y')
            _delete(pos);
        pos = search_node(item, pos+1);
    }
}

linkedList *pop_node(double *item)
{
    linkedList *ptr = first;
    *item = ptr->info;
    return _delete(0);

}

/* list f. */
void list_print()
{
    int count=0;
    ptr = first;
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

/* operation f. */
void operate_node(int count, int i)
{
    double item, ans;
    linkedList *x = pop_node(&item);
    if(count == 1)
    {
        if(i==5)
            ans = sqrt(x->info);
        else if(i==6)
            ans = 1 / (x->info);
        else if(i==7)
            ans = -1 * (x->info);
        printf("answer> %g\n",ans);
    }
    else if(count == 2)
    {
        linkedList *a = pop_node(&item), *b = pop_node(&item);
        if(a != NULL && b!= NULL)
        {
            if(i==8)
                ans = pow(b->info, a->info);
            else if(i==9)
                ans = (b->info) + (a->info);
            else if(i==10)
                ans = (b->info) - (a->info);
            else if(i==11)
                ans = (b->info) * (a->info);
            else if(i==12)
                ans = (b->info) / (a->info);
            push_node(ans);
            printf("answer> %g\n",ans);
        } else
            printf("answer> can't operation\n");
    }
}

void help()
{
    char cmd_list[20][40] = {"list:   show current stack",
                           "end:    end program",
                           "sort:   ascending sort",
                           "pop:    pop first element",
                           "help:   help menu",
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
        printf("\t%2d)\t%s\n", i, cmd_list[i]);
}

void group1(int i)
{
    double item;
    if(i==0)
        list_print();
    else if(i==2)
        scanSort();
    else if(i==3)
    {
        pop_node(&item);
        printf("answer> %g\n", item);
    }
    else if(i==4)
        help();
    else if(i>4 && i<8)
        operate_node(1, i);
    else if(i>=8 && i<13)
        operate_node(2, i);
}

void group2(int i, char cmd[][20])
{
    double num;
    sscanf(cmd[1], "%lf", &num);
    if(i==13)
        delete_node(num);
    else if(i==14)
        search_node(num, 0);
    else if(i==15)
        peek_node(num);
    else if(i==16)
        push_node(num);
}

void group3(int i, char cmd[][20], int parameter)
{
    double num[parameter];
    int j;
    while(j < parameter)
    {
        sscanf(cmd[j+1], "%lf", &num[j]);
        j++;
    }
    j=0;
    if(i==17)
        while(j < parameter)
            add_node(num[j++]);
    else if(i==18)
        while(j < parameter)
            insert_node(num[j++]);
}

int check_cmd(char cmd[][20], int group, int parameter, int i)
{
    if(group == 1 && parameter == 0)
        if((linkedlist_size() == 0) && (i != 1))
            printf("answer> No data\n");
        else
            group1(i);
    else if(group == 2 && parameter == 1)
        if((linkedlist_size() == 0) && (i != 16))
            printf("answer> No data\n");
        else
            group2(i, cmd);
    else if(group == 3 && parameter >= 1)
        group3(i, cmd, parameter);
    else if(group != 0 && parameter == 0)
        printf("answer> syntax error\n");
    else
        printf("answer> parameter error\n");
}

int main()
{
    char str[100], buff[100], cmd[10][20];
    int group,parameter,count,i;
    do {
        list_print();
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
            check_cmd(cmd, group, parameter, i);

    } while(strcmp(str,"end"));

    printf("\nEnd Program\n");
    printf("Program written by 63070501044 Parinda Kongwattanasin\n");

    return 0;
}
