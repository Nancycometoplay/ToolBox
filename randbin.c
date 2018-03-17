
//二进制文件的读写操作
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ARSIZE 1000

int main() {

    double numbers[ARSIZE];
    double value;
    const char *file = "number.dat";

    int i;
    long pos;
    FILE *iofile;

    //创建一组double类型的值
    for (i = 0; i < ARSIZE; i++) { numbers[i] = 100 * i + 1.0 / (i + 1); }

    //尝试打开文件
    if ((iofile = fopen(file, "wb")) == NULL) {
        fprintf(stderr, "Could not open %s for output.\n", file);
        exit(EXIT_FAILURE);
    }

    //以二进制格式把数组写入文件
    fwrite(numbers,sizeof(double),ARSIZE,iofile);  //最后放文件
    fclose(iofile);
    if((iofile=fopen(file,"rb"))==NULL)
    {
        fprintf(stderr,"Could not open %s for random access.\n",file);
        exit(EXIT_FAILURE);
    }

    //从文件中读取选定的内容
    printf("Enter an index in the range 0-%d\n",ARSIZE-1);
    while(scanf("%d",&i)==1 && i>=0 && i<ARSIZE)
    {
        pos=(long) i*sizeof(double);
        fseek(iofile,pos,SEEK_SET);
        fread(&value, sizeof(double),1,iofile);
        printf("The value there is %f.\n",value);
        printf("Next index (out of range to quit) :\n");
    }

    //完成
    fclose(iofile);
    puts("BYE!");

    return 0;
}