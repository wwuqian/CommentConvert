#define  _CRT_SECURT_NO_WARNINGS 1

#include "CommentConvert.h" //引定义的头文件

//注释转换的主逻辑
void test()
{
	 FILE *pfIn = NULL;  //定义两个文件指针
	 FILE *pfOut = NULL;
     pfIn = fopen("input.c", "r"); //以只读方式打开读取文件
	 if(NULL == pfIn)
	 {
	     perror("open file for read"); //读取失败
		 exit(EXIT_FAILURE);
	 }
     pfOut = fopen("output.c", "w"); 

	 if(NULL == pfOut)
	 {
	     perror("open file for write");//读取失败
		 fclose(pfIn); //关闭读取文件
		 exit(EXIT_FAILURE);

	 }

	 DoConvertWork(pfIn, pfOut);
	 printf("转换成功！");
	 fclose(pfIn);
	 fclose(pfOut);
}


int main()
{
	test();
	system("pause");
    return 0;
}
