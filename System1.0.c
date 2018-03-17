#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shoudsave = 0;

struct student {
    char num[10];  //学号
    char name[20];
    int cgrade;
    int mgrade;
    int egrade;
    int totle;
    int ave;
};
//链表结构
typedef struct {
    struct student data;
    struct node *next;
} Node, *Link;    //Link是指向这个结构的指针 ,Node就代表这个结构

void menu() {
    printf("********************************************************************************");
    printf("/t1输入学生资料/t/t/t/t/t2删除学生资料/n");
    printf("/t3查询学生资料/t/t/t/t/t4修改学生资料/n");
    printf("/t5显示学生资料/t/t/t/t/t6统计学生成绩/n");
    printf("/t7排序学生成绩/t/t/t/t/t8保存学生资料/n");
    printf("/t9获取帮助信息/t/t/t/t/t0退出系统/n");
    printf("********************************************************************************/n");
}

void printstart() { printf("-----------------------------------------------------------------------/n"); }

void Wrong() { printf("/n=====>提示:输入错误!/n"); }

void Nofind() { printf("/n=====>提示:没有找到该学生!/n"); }

void printc() // 本函数用于输出中文
{ printf(" 学号/t 姓名 英语成绩 数学成绩 C语言成绩 总分 平均分/n"); }

void printe(Node *p)//本函数用于输出英文
{
    printf("%-12s%s/t%d/t%d/t%d/t %d/t %d/n", p->data.num, p->data.name, p->data.egrade, p->data.mgrade, p->data.cgrade,
           p->data.totle, p->data.ave);
}


//解释: 返回一个指向Node类型结构体
//名字或学号查找—--—查
Node *Locate(Link l, char findmess[], char nameornum[])  //该函数用于定位连表中符合要求的接点，并返回该指针

{
    Node *r;
    if (
            strcmp(nameornum, "num") == 0) //按学号查询，如果两个字符串一致
    {
        r = l->next;  //r指针等于第一个node的存放的指针
        //最后一个Node存放的指针是空指针
        while (r) {
            if (strcmp(r->data.num, findmess) == 0) return r;
            r = r->next;
        }
    } else if (
            strcmp(nameornum, "name") == 0)//按姓名查询
    {
        r = l->next;
        while (r) {
            if (
                    strcmp(r->data.name, findmess) == 0)
                return r;
            r = r->next;
        }
    }
    return 0;
}

void Add(Link l) //增加学生
{
    Node *p, *r, *s;
    char num[10];
    r = l;
    s = l->next; //s是下一个

    while (r->next != NULL)
        r = r->next; //将指针置于最末尾

    while (1) {
        printf("请你输入学号(以'0'返回上一级菜单:)");
        scanf("%s", num);
        if (
                strcmp(num,
                       "0") == 0)
            break;
        while (s) {
            if (
                    strcmp(s->data.num, num) == 0) {
                printf("=====>提示:学号为'%s'的学生已经存在,若要修改请你选择'4 修改'!/n", num);

                printstart();

                printc();

                printe(s);

                printstart();

                printf("/n");
                return;
            }
            s = s->next;
        }
        p = (Node *) malloc(sizeof(Node));
        strcpy(p->data.num, num);
        printf("请你输入姓名:");
        scanf("%s", p->data.name);
        getchar();
        printf("请你输入c语言成绩:");
        scanf("%d", &p->data.cgrade);
        getchar();
        printf("请你输入数学成绩:");
        scanf("%d", &p->data.mgrade);
        getchar();
        printf("请你输入英语成绩:");
        scanf("%d", &p->data.egrade);
        getchar();
        p->data.totle = p->data.egrade + p->data.cgrade + p->data.mgrade;
        p->data.ave = p->data.totle / 3;//信息输入已经完成
        p->next = NULL;
        r->next = p;
        r = p;
        shoudsave = 1;
    }
}


void Qur(Link l)//查询学生
{
    int sel;
    char findmess[20];
    Node *p;
    if (!l->next) {
        printf("/n=====>提示:没有资料可以查询!/n");
        return;
    }
    printf("/n=====>1按学号查找/n=====>2按姓名查找/n");
    scanf("%d", &sel);
    if (sel == 1)//学号
    {
        printf("请你输入要查找的学号:");
        scanf("%s", findmess);
        p = Locate(l, findmess, "num");
        if (p) {
            printf("/t/t/t/t查找结果/n");
            printstart();
            printc();
            printe(p);
            printstart();
        } else Nofind();
    } else if (sel == 2) //姓名
    {
        printf("请你输入要查找的姓名:");
        scanf("%s", findmess);
        p = Locate(l, findmess, "name");
        if (p) {
            printf("/t/t/t/t查找结果/n");
            printstart();
            printc();
            printe(p);
            printstart();
        } else Nofind();
    } else Wrong();
}

void Del(Link l) //删除
{
    int sel;
    Node *p, *r;
    char findmess[20];
    if (!l->next) {
        printf("/n=====>提示:没有资料可以删除!/n");
        return;
    }
    printf("/n=====>1按学号删除/n=====>2按姓名删除/n");
    scanf("%d", &sel);
    if (sel == 1) {
        printf("请你输入要删除的学号:");
        scanf("%s", findmess);
        p = Locate(l, findmess, "num");
        if (p) {
            r = l;
            while (r->next != p) r = r->next;
            r->next = p->next;
            free(p);
            printf("/n=====>提示:该学生已经成功删除!/n");
            shoudsave = 1;
        } else Nofind();
    } else if (sel == 2) {
        printf("请你输入要删除的姓名:");
        scanf("%s", findmess);
        p = Locate(l, findmess, "name");
        if (p) {
            r = l;
            while (r->next != p) r = r->next;
            r->next = p->next;
            free(p);
            printf("/n=====>提示:该学生已经成功删除!/n");
            shoudsave = 1;
        } else Nofind();
    } else Wrong();
}

void Modify(Link l) {
    Node *p;
    char findmess[20];
    if (!l->next) {
        printf("/n=====>提示:没有资料可以修改!/n");
        return;
    }
    printf("请你输入要修改的学生学号:");
    scanf("%s", findmess);
    p = Locate(l, findmess, "num");
    if (p) {
        printf("请你输入新的c语言成绩(原来是%d分):", p->data.cgrade);
        scanf("%d", &p->data.cgrade);
        getchar();
        printf("请你输入新的数学成绩(原来是%d分):", p->data.mgrade);
        scanf("%d", &p->data.mgrade);
        getchar();
        printf("请你输入新的英语成绩(原来是%d分):", p->data.egrade);
        scanf("%d", &p->data.egrade);
        printf("/n=====>提示:资料修改成功!/n");
        shoudsave = 1;
    } else Nofind();
}

void Disp(Link l) {
    int count = 0;
    Node *p;
    p = l->next;
    if (!p) {
        printf("/n=====>提示:没有资料可以显示!/n");
        return;
    }
    printf("/t/t/t/t显示结果/n");
    printstart();
    printc();
    printf("/n");
    while (p) {
        printe(p);
        p = p->next;
    }
    printstart();
    printf("/n");
}

void Save(Link l) {
    FILE *fp;
    Node *p;
    int flag = 1, count = 0;
    fp = fopen("c://student", "wb");
    if (fp == NULL) {
        printf("/n=====>提示:重新打开文件时发生错误!/n");
        exit(1);
    }
    p = l->next;
    while (p) {
        if (fwrite(p, sizeof(Node), 1, fp) == 1) {
            p = p->next;
            count++;
        } else {
            flag = 0;
            break;
        }
    }
    if (flag) {
        printf("/n=====>提示:文件保存成功.(有%d条记录已经保存.)/n", count);
        shoudsave = 0;
    }
    fclose(fp);
}

int main() {
    Link l;//连表
    FILE *fp; //文件指针
    int sel;
    char ch;
    int count = 0;
    Node *p, *r;
    printf("/t/t/t/t学生成绩管理系统/n/t/t/t-------------------------------/n");
    l = (Node *) malloc(sizeof(Node));
    l->next = NULL;
    r = l;
    fp = fopen("C://student", "ab+");
    if (fp == NULL) {
        printf("/n=====>提示:文件不能打开!/n");
        exit(0);
    }
    printf("/n=====>提示:文件已经打开,正在导入记录....../n");
    while (!feof(fp)) {
        p = (Node *) malloc(sizeof(Node));
        if (fread(p, sizeof(Node), 1, fp) == 1) //将文件的内容放入接点中 { p->next=NULL; r->next=p; r=p; //将该接点挂入连中
            count++;
    }


    fclose(fp); //关闭文件
    printf("/n=====>提示:记录导入完毕,共导入%d条记录./n", count);

    menu();

    while (1) {
        printf("请你选择操作:");
        scanf("%d", &sel);
        if (sel == 0) {
            if (shoudsave == 1) {
                getchar();

                printf("/n=====>提示:资料已经改动,是否将改动保存到文件中(y/n)?/n");
                scanf("%c", &ch);
                if (ch == 'y' || ch == 'Y')
                    Save(l);
            }
            printf("/n=====>提示:你已经退出系统,再见!/n");
            break;
        }
        switch (sel) {
            case 1:
                Add(l);
                break; //增加学生 case 2:Del(l);break;//删除学生 case 3:Qur(l);break;//查询学生 case 4:Modify(l);break;//修改学生 case 5:Disp(l);break;//显示学生 case 8:Save(l);break;//保存学生
            case 9:
                printf("/t/t/t==========帮助信息==========/n");

                menu();

                break;
            default:

                Wrong();

                getchar();

                break;
        }

        while (l) {
            //释放链表l(不是1)所占用的内存！
            p = l;
            l = l->next;
            free(p);
        }
       // getchar();

        return 0;
    }
}