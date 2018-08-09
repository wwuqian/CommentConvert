#define  _CRT_SECURT_NO_WARNINGS 1

#include "CommentConvert.h"

enum STATE state = NUL_STATE;
void DoConvertWork(FILE* pfIn, FILE* pfOut)
{
     while(state != END_STATE)
	 {
	      switch(state)
		  {
		      case NUL_STATE:
                   DoNulState(pfIn, pfOut);//处理无状态的情况
			       break;
		      case C_STATE:
                   DoCState(pfIn, pfOut);//处理C状态的情况
			       break;
		      case CPP_STATE:
                   DoCppState(pfIn, pfOut);//处理CPP状态的情况
			       break;
			  default:
				   break;
		    
		  }
	 }
}

//处理无状态转换的情况
void DoNulState(FILE* pfIn, FILE* pfOut)
{
     int first = 0;
	 int second = 0;
	 first = fgetc(pfIn);
     switch(first)
	 {
	     case '/':
		  {
			  second = fgetc(pfIn);
			  switch(second)
			  {    case '*':  //进入c注释状态
			        {
			           fputc('/', pfOut);//在pfOut中将C注释改为CPP注释输出到文件
				       fputc('/', pfOut);
			           state = C_STATE;
			        }
					   break;
			       case '/'://表示进入CPP注释状态
			        {
			            fputc(first, pfOut);//将'//'放入到输出中
				        fputc(second, pfOut);
						state = CPP_STATE;
			        }
					    break;
				   default://是其他字符的情况，就直接输出
					{
					   fputc(first, pfOut);
					   fputc(second, pfOut);
					}
					   break;
		       }
		  }
		       break;
		 case EOF:
			  state = END_STATE;
			  break;
		 default:
             fputc(first, pfOut);//当遇到其他字符时，直接输出到文件
			 break;
	 }
}

//处理C状态转换的情况
void DoCState(FILE *pfIn, FILE* pfOut)
{
     int first = 0;
	 int second = 0;
	 int third = 0;

	 first = fgetc(pfIn);
     switch(first)//C注释状态，不会直接转换为END_STATE
	 {
	      case '*':
		   {
			  second = fgetc(pfIn);
			  switch(second)//判断第二个字符
			  {
			      case '/'://C注释结束,判断后面是否有'\n',若有则输出，若无则我们要加上换行
				   {
					   third = fgetc(pfIn);//处理换行问题
					   state = NUL_STATE;
					   if(third == '\n')
					   {
					       fputc(third, pfOut);
					   
					   }
					   else
					   {
					       fputc('\n', pfOut);
						   ungetc(third, pfIn);//把字符撤销，防止下次判断时少一个字符
					   }
					   
				    } 
					  break;
				  default:
					  {
					     fputc(first, pfOut);
						 ungetc(second, pfIn);
					  }
					  break;
			  }
			  
		   }
		       break;
		  case '\n'://处理多行注释问题，换行之后要加上//，CPP注释只能注释一行
			{
			    fputc(first, pfOut);
				fputc('/', pfOut);
				fputc('/', pfOut); 
		    }
			  break;
		  default:
			  fputc(first, pfOut);//直接输出
			  break;
	 }
}

//处理CPP状态转换的情况
void DoCppState(FILE* pfIn, FILE* pfOut)
{
     int first = 0;
	 
     first = fgetc(pfIn);
	 switch(first)
	 {
	      case '\n'://CPP注释结束
			{
			  fputc(first, pfOut);
			  state = NUL_STATE;
			}
			  break;
		  case EOF:
			  state = END_STATE;
			  break;
		  default:
			  fputc(first, pfOut);
			  break;
	 }
}
