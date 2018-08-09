#define  _CRT_SECURT_NO_WARNINGS 1

#ifndef __COMMENT_CONVERT_H__
#define __COMMENT_CONVERT_H__

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>

enum STATE   //枚举类型
{
    NUL_STATE,
	  C_STATE,
  	CPP_STATE,
	  END_STATE,
};

void DoConvertWork(FILE* pfIn, FILE* pfOut);
void DoNulState(FILE* pfIn, FILE* pfOut);
void DoCState(FILE* pfIn, FILE* pfOut);
void DoCppState(FILE* pfIn, FILE* pfOut);

#endif 
