#include <stdio.h> // 标准输入输出头文件 
#include <stdlib.h> // 标准库头文件 
#include <string.h> // 字符串头文件 
#include <time.h> // 时间头文件（可调用随机函数）
#define path_choice "Choice.txt" // 选择题题库文件路径
#define path_filling_blank "Filling_blank.txt" // 填空题题库文件路径
#define path_choice_bak "Choice_bak.txt" // 备份选择题题库文件路径
#define path_filling_blank_bak "Filling_blank_bak.txt" // 备份填空题题库文件路径
#define MAXN 1000 // 控制数组最大边界 
long long nextQid_choice = 1; // 题目编号的最大值 + 1
long long nextQid_filling_blank = 1; // 题目编号的最大值 + 1
long long choiceNum = 0, fillingBlankNum = 0;  // 选择题和填空题的数量
struct Q_choice // 选择题结构体
{ 
	long long qid; // 题目编号 
	char info[MAXN]; // 题目信息 
	char singleChoiceA[MAXN]; // 储存A选项的信息 
	char singleChoiceB[MAXN]; // 储存B选项的信息 
	char singleChoiceC[MAXN]; // 储存C选项的信息 
	char singleChoiceD[MAXN]; // 储存D选项的信息 
	char singleChoiceAns; // 储存单选题答案为字符A、B、C、D  
	struct Q_choice *next; // 指向下一个题目的指针 
} *qLibc, *qLibcTail; // 选择题题库的头指针和尾指针
struct Q_filling_blank // 填空题结构体 
{
	long long qid; // 题目编号
	char info[MAXN]; // 题目信息
	char blanksAns[MAXN]; // 储存填空题答案为字符串 
	struct Q_filling_blank *next; // 指向下一个题目的指针
} *qLibf, *qLibfTail; // 填空题题库的头指针和尾指针
void Add() // 添加题目 
{
	FILE* fp; // 定义文件指针
	int type; // 题目类型
	printf("请输入题目类型（【1】单选题【2】填空题）：\n"); // 输入题目类型
	scanf("%d", &type); // 指定题目类型
	getchar(); // 清空输入缓存
	if(type != 1 && type != 2) // 若题目类型不为1或2
	{
		printf("添加题目失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	if(type == 1) // 若题目类型为1
	{
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 申请内存空间
		fp=fopen(path_choice,"a+"); // 打开文件
		q->qid = nextQid_choice++; // 为新题目添加编号 
		fprintf(fp,"%lld\n",q->qid); // 输出题目编号
		printf("请输入题目：\n"); // 输入题目信息
		gets(q->info); // 添加题目信息
		fprintf(fp,"%s\n",q->info); // 输出题目信息
		printf("请输入A选项：\n"); // 输入A选项信息
		gets(q->singleChoiceA); // 添加选项信息
		fprintf(fp,"%s\n",q->singleChoiceA); // 输出A选项信息
		printf("请输入B选项：\n"); // 输入B选项信息
		gets(q->singleChoiceB); // 添加选项信息
		fprintf(fp,"%s\n",q->singleChoiceB); // 输出B选项信息
		printf("请输入C选项：\n"); // 输入C选项信息
		gets(q->singleChoiceC); // 添加选项信息
		fprintf(fp,"%s\n",q->singleChoiceC); // 输出C选项信息
		printf("请输入D选项：\n"); // 输入D选项信息
		gets(q->singleChoiceD); // 添加选项信息
		fprintf(fp,"%s\n",q->singleChoiceD); // 输出D选项信息
		printf("请输入答案：\n"); // 输入单选题答案
		char c = getchar(); // 读取单选题答案
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // 若单选题答案不为A、B、C、D
		{
			printf("只能输入A、B、C、D其中一个字符：\n"); // 输出错误信息
			getchar();// 清空输入缓存
			c = getchar(); // 重新读取单选题答案
		}
		q->singleChoiceAns = c; // 储存单选题答案为字符A、B、C、D
		fprintf(fp,"%c\n",q->singleChoiceAns); // 输出单选题答案
	    printf("成功添加题目编号：%lld\n", q->qid); // 输出新题目的编号
	    qLibcTail->next = q; // 将新题目接到题库尾部
	    qLibcTail = qLibcTail->next; // 更新题库尾指针
	}
	else if(type == 2) // 若题目类型为2
	{
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // 申请内存空间
		fp=fopen(path_filling_blank,"a+"); // 打开文件
		q->qid = nextQid_filling_blank++; // 为新题目添加编号 
		fprintf(fp,"%lld\n",q->qid); // 输出题目编号
		printf("请输入题目：\n"); // 输入题目信息
		gets(q->info); // 添加题目信息
		fprintf(fp,"%s\n",q->info); // 输出题目信息
		printf("请输入答案：\n"); // 输入填空题答案
		char ans[MAXN]; // 储存填空题答案
		gets(q->blanksAns); // 添加填空题答案
		fprintf(fp,"%s\n",q->blanksAns); // 输出填空题答案
	    printf("成功添加题目编号：%lld\n", q->qid); // 输出新题目的编号
	    qLibfTail->next = q; // 将新题目接到题库尾部
	    qLibfTail = qLibfTail->next; // 更新题库尾指针
	}
	fclose(fp); // 关闭文件
}
void Delete() // 删除题目 
{
	int type; // 题目类型
	FILE *fp; // 定义文件指针
	long long thisQid; // 题目编号 
	printf("请输入要删除题目的类型（【1】单选题【2】填空题）：\n"); // 输入题目类型
	scanf("%d", &type); // 指定题目类型
	if(type != 1 && type != 2) // 若题目类型不为1或2
	{
		printf("删除题目失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	if(type == 1) // 若题目类型为1
	{
		printf("请输入要删除题目的编号：\n"); // 输入题目编号
		scanf("%lld", &thisQid); // 指定题目编号
		struct Q_choice *p = qLibc; // 指向题库头部 
		while(p->next != NULL) // 遍历题库
		{
			if(p->next->qid == thisQid) // 找到要删除的题目
			{
				struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 新建空题目
				q->next = p->next->next; // 将下一个题接到当前题的后面
				p->next = q->next; // 将当前题接到题库头部
				free(q); // 释放内存
				printf("删除成功！\n"); // 输出删除成功信息
			}
			p = p->next; // 指向下一个题目
		}
		fp = fopen(path_choice, "w"); // 打开文件
		p = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
			fprintf(fp, "%lld\n",p->qid); // 输出题目编号
			fprintf(fp, "%s\n",p->info); // 输出题目信息
			fprintf(fp, "%s\n",p->singleChoiceA); // 输出A选项信息
			fprintf(fp, "%s\n",p->singleChoiceB); // 输出B选项信息
			fprintf(fp, "%s\n",p->singleChoiceC); // 输出C选项信息
			fprintf(fp, "%s\n",p->singleChoiceD); // 输出D选项信息
			fprintf(fp, "%c\n",p->singleChoiceAns); // 输出题目答案 
			p = p->next; // 指向下一个题目
		}
		fclose(fp); // 关闭文件
	}
	else if(type == 2) // 若题目类型为2
	{
		printf("请输入要删除题目的编号：\n"); // 输入题目编号
		scanf("%lld",&thisQid); // 指定题目编号
		struct Q_filling_blank *p = qLibf; // 指向题库头部 
		fp=fopen(path_filling_blank, "w"); // 打开文件
		while(p->next != NULL) // 遍历题库
		{
			if(p->next->qid == thisQid) // 找到要删除的题目
			{
				struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // 新建空题目
				q->next = p->next->next; // 将下一个题接到当前题的后面
				p->next = q->next; // 将当前题接到题库头部
				free(q); // 释放内存
				printf("删除成功！\n"); // 输出删除成功信息
			}
			p = p->next; // 指向下一个题目
		}
		fp=fopen(path_filling_blank, "w"); // 打开文件
		p = qLibf->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
			fprintf(fp, "%lld\n",p->qid); // 输出题目编号
			fprintf(fp, "%s\n",p->info); // 输出题目信息
			fprintf(fp, "%s\n",p->blanksAns); // 输出填空题答案
			p = p->next; // 指向下一个题目
		}
		fclose(fp); // 关闭文件
	}
}
void BackupAll() // 备份题库
{
	FILE *fp1, *fp2; // 定义文件指针
	fp1 = fopen(path_choice_bak, "w"); // 打开文件
	fp2 = fopen(path_filling_blank_bak, "w"); // 打开文件
	struct Q_choice *p1 = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
	struct Q_filling_blank *p2 = qLibf->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
	while(p1 != NULL) // 遍历题库
	{
		fprintf(fp1, "%lld\n",p1->qid); // 输出题目编号
		fprintf(fp1, "%s\n",p1->info); // 输出题目信息
		fprintf(fp1, "%s\n",p1->singleChoiceA); // 输出A选项信息
		fprintf(fp1, "%s\n",p1->singleChoiceB); // 输出B选项信息
		fprintf(fp1, "%s\n",p1->singleChoiceC); // 输出C选项信息
		fprintf(fp1, "%s\n",p1->singleChoiceD); // 输出D选项信息
		fprintf(fp1, "%c\n",p1->singleChoiceAns); // 输出题目答案 
		p1 = p1->next; // 指向下一个题目
    }
    while(p2 != NULL) // 遍历题库
    {
    	fprintf(fp2, "%lld\n",p2->qid); // 输出题目编号
		fprintf(fp2, "%s\n",p2->info); // 输出题目信息
		fprintf(fp2, "%s\n",p2->blanksAns); // 输出填空题答案
		p2 = p2->next; // 指向下一个题目
	}
	fclose(fp1); // 关闭文件
	fclose(fp2); // 关闭文件 
	printf("备份成功!\n"); // 输出信息                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}
void DeleteAll() // 删除题库
{
    FILE *p1; // 定义文件指针
    FILE *p2; // 定义文件指针
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 重新初始化题库
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // 重新初始化题库
	fopen(path_choice,"w"); // 打开文件
	fopen(path_filling_blank,"w"); // 打开文件
	printf("成功删除全部题目！\n"); // 输出删除成功信息
}
void Modify() // 修改题目 
{
	FILE *fp; // 定义文件指针
	long long thisQid; // 题目编号 
	int type; // 题目类型
	printf("请输入题目类型（【1】单选题【2】填空题）：\n"); // 输入题目类型
	scanf("%d", &type); // 指定题目类型
	if(type != 1 && type != 2) // 若题目类型不为1或2
	{
		printf("修改题目失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	printf("请输入要修改内容的编号：\n"); // 输入题目编号
	scanf("%lld", &thisQid); // 指定题目编号
	if(type == 1) // 若题目类型为1
	{
		struct Q_choice *p = qLibc->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(p->qid == thisQid) // 找到要修改的题目
			{
				printf("请选择需要修改题目信息还是答案（【1】信息【2】答案【0】返回）：\n"); // 输入选项
				{
					int option; // 选项
					scanf("%d", &option); // 指定选项
					if(option == 1) // 修改题目信息
					{
						printf("请输入具体的修改内容（【A】【B】【C】【D】【其他按键：题干】）：\n"); // 输入修改内容
						char c = getchar(); // 读取修改内容
						getchar(); // 清空输入缓存
						printf("请输入修改后的题目内容：\n"); // 输入修改后的题目内容
						getchar(); // 清空输入缓存
						switch(c) // 根据修改内容选择修改位置
						{
							case 'A': gets(p->singleChoiceA); break; // 修改A选项信息
							case 'B': gets(p->singleChoiceB); break; // 修改B选项信息
							case 'C': gets(p->singleChoiceC); break; // 修改C选项信息
							case 'D': gets(p->singleChoiceD); break; // 修改D选项信息
							default: gets(p->info); break; // 修改题目信息
						}	
					}
					else if(option == 2) // 修改单选题答案
					{
						printf("请输入修改后的单选题答案：\n"); // 输入修改后的单选题答案
						getchar(); // 清空输入缓存
						char c = getchar(); // 读取修改后的单选题答案
						getchar(); // 清空输入缓存
						while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // 若单选题答案不为A、B、C、D
						{
							printf("只能输入A、B、C、D其中一个字符：\n"); // 输出错误信息
							c = getchar(); // 重新读取修改后的单选题答案
							getchar(); // 清空输入缓存
						}
						p->singleChoiceAns = c; // 修改单选题答案
					}
				}	
			}
			p = p->next; // 指向下一个题目
		}
		fp = fopen(path_choice, "w"); // 打开文件
		p = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
			fprintf(fp, "%lld\n",p->qid); // 输出题目编号
			fprintf(fp, "%s\n",p->info); // 输出题目信息
			fprintf(fp, "%s\n",p->singleChoiceA); // 输出A选项信息
			fprintf(fp, "%s\n",p->singleChoiceB); // 输出B选项信息
			fprintf(fp, "%s\n",p->singleChoiceC); // 输出C选项信息
			fprintf(fp, "%s\n",p->singleChoiceD); // 输出D选项信息
			fprintf(fp, "%c\n",p->singleChoiceAns); // 输出题目答案 
			p = p->next; // 指向下一个题目
    	}
    	fclose(fp); // 关闭文件
	}
	else if(type == 2) // 若题目类型为2
	{
		struct Q_filling_blank *p = qLibf->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(p->qid == thisQid) // 找到要修改的题目
			{
				printf("请选择需要修改题目信息还是答案（【1】信息【2】答案【0】返回）：\n"); // 输入选项
				int option; // 选项
				scanf("%d", &option); // 指定选项
				if(option == 1) // 修改题目信息
				{
					printf("请输入修改后的题目内容：\n"); // 输入修改后的题目内容
					getchar(); // 清空输入缓存
					gets(p->info); // 修改题目信息
				}
				else if(option == 2) // 修改填空题答案
				{
					printf("请输入修改后的填空题答案：\n"); // 输入修改后的填空题答案
					getchar(); // 清空输入缓存
					gets(p->blanksAns); // 修改填空题答案
				}
			}
			p = p->next; // 指向下一个题目
		}
		fp = fopen(path_filling_blank, "w"); // 打开文件
		p = qLibf->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
    		fprintf(fp, "%lld\n",p->qid); // 输出题目编号
			fprintf(fp, "%s\n",p->info); // 输出题目信息
			fprintf(fp, "%s\n",p->blanksAns); // 输出填空题答案
			p = p->next; // 指向下一个题目
    	}
    	fclose(fp); // 关闭文件
	}
}
void Search() // 题目查询 
{
	int type, flag = 0; // 题目类型、标记是否找到题目
	printf("请输入要查询的题目类型([1]选择题[2]填空题)：\n"); // 输入题目类型
	scanf("%d",&type); // 指定题目类型
	if(type != 1 && type != 2) // 若题目类型不为1或2
	{
		printf("查询失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	if(type == 1) // 若题目类型为1
	{
		long long thisQid; // 题目编号 
		printf("请输入要查询题目的编号：\n"); // 输入题目编号
		scanf("%lld", &thisQid); // 指定题目编号
		struct Q_choice *p = qLibc->next; // 指向题库头部 
		while(p != NULL) // 遍历题库 
		{
			if(p->qid == thisQid) // 找到要查询的题目
			{
				// 输出题目信息
				printf("题目:%s\nA:%s\nB:%s\nC:%s\nD:%s\n答案:%c\n", p->info, p->singleChoiceA, p->singleChoiceB, p->singleChoiceC, p->singleChoiceD, p->singleChoiceAns);
				flag = 1; // 标记找到题目
				break; // 退出循环
			}
            p = p->next; // 指向下一个题目
		}
	}
	else if(type == 2) // 若题目类型为2
	{
		long long thisQid; // 题目编号 
		printf("请输入要查询题目的编号：\n"); // 输入题目编号
		scanf("%lld", &thisQid); // 指定题目编号
		struct Q_filling_blank *p = qLibf->next; // 指向题库头部 
		while(p != NULL) //	遍历题库
		{
			if(p->qid == thisQid) // 找到要查询的题目
			{
				printf("\n题目:%s\n答案:%s\n", p->info, p->blanksAns); // 输出题目信息
				flag = 1; // 标记找到题目
				break; // 退出循环
			}
			p = p->next; // 指向下一个题目
		}
	}
	if(!flag) // 若未找到题目
		printf("未查询到有效的题目信息\n"); // 输出未找到题目信息
	return; // 退出函数
}
void Statistic() // 题目统计 
{
	long long scNum = 0, fibNum = 0, totalNum = 0; // 单选题、填空题、总题数
	struct Q_choice *q1 = qLibc->next; // 指向题库头部 
	struct Q_filling_blank *q2 = qLibf->next;
	while(q1 != NULL) // 遍历题库
	{
		scNum++; // 单选题数+1
		totalNum++; // 总题数+1
		q1 = q1->next; // 指向下一个题目
	}
	while(q2 != NULL) // 遍历题库
	{
		fibNum++; // 填空题数+1
		totalNum++; // 总题数+1
		q2 = q2->next; // 指向下一个题目
	}    
	choiceNum = scNum; // 单选题数赋值给全局变量
	fillingBlankNum = fibNum; // 填空题数赋值给全局变量
	printf("共有%lld道题目(单选题：%lld、填空题：%lld)\n", totalNum, scNum, fibNum); // 输出题目统计信息
}
void FindSpecificContent() // 查询特定内容 
{
	printf("请输入题目类型（【1】单选题【2】填空题）：\n"); // 输入题目类型
	int type; // 题目类型
	scanf("%d", &type); // 指定题目类型
	getchar(); // 清空输入缓存
	if(type != 1 && type != 2) // 若题目类型不为1或2
	{
		printf("添加题目失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	int flag = 0; // 标记是否找到题目
	char sp[1000]; // 特定内容
	printf("请输入题干所包含的特定内容：\n"); // 输入特定内容
	getchar(); // 清空输入缓存
	gets(sp); // 储存特定内容
	if(type == 1) // 若题目类型为1
	{
		struct Q_choice *p = qLibc->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(strstr(p->info,sp) != NULL) // 若题目信息中包含特定内容
			{
				flag = 1; // 标记找到题目
				printf("查询到符合条件的题目编号：%lld\n", p->qid); // 输出题目编号
				printf("题目类型：单选题\n题目信息：%s\n题目答案：%c\n", p->info, p->singleChoiceAns); // 输出题目信息
			}
			p = p->next; // 指向下一个题目
		}
	}
	else if(type == 2) // 若题目类型为2
	{
		struct Q_filling_blank *p = qLibf->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(strstr(p->info,sp) != NULL) // 若题目信息中包含特定内容
			{
				flag = 1; // 标记找到题目
				printf("查询到符合条件的题目编号：%lld\n", p->qid); // 输出题目编号
				printf("题目类型：填空题\n题目信息：%s\n题目答案：%s\n", p->info, p->blanksAns); // 输出题目信息
			}	
			p = p->next; // 指向下一个题目
		}
	}	
	if(!flag) // 若未找到题目
		printf("未找到该题目！\n"); // 输出未找到题目信息
}
void RandomQandA() // 随机生成试题 
{
	long long order = 1,scNum,fibNum,QidFlag[MAXN] = {0}; // 试题顺序、单选题数、填空题数、题目编号标记数组 
	printf("请输入生成的单选题题目数：\n"); // 输入单选题题目数
	scanf("%lld", &scNum); // 指定单选题题目数
	printf("请输入生成的填空题题目数：\n"); // 输入填空题题目数
	scanf("%lld", &fibNum); // 指定填空题题目数
	Statistic(); // 统计题目 
	if(scNum > choiceNum) // 若单选题题库不足分配
	{
		printf("单选题题库不足分配！\n"); // 输出错误信息
		return; // 退出函数
	}
	else if(fibNum > fillingBlankNum) // 若填空题题库不足分配
	{
		printf("填空题题库不足分配！\n"); // 输出错误信息
		return; // 退出函数
	}
	FILE *fp1 = fopen("exam.txt", "w"); // 创建试题
    FILE *fp2 = fopen("answer.txt", "w"); // 创建答案 
	// 随机单选题模块 
	fprintf(fp1, "一、单选题\n"); // 输出题目类型 
	fprintf(fp2, "一、单选题\n"); // 输出题目类型 
	while(scNum > 0) // 循环生成单选题
	{
		long long randomQid = 1 + rand() % (nextQid_choice - 1); // 生成[1, qid max]区间内的随机编号 
		if(!QidFlag[randomQid]) // 该qid未标记，即未储存 
		{
			struct Q_choice *p = qLibc->next; // 指向题库头部 
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid) // 找到单选题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp1, "题目：%s\n", p->info); // 输出题目信息
					fprintf(fp1, "A：%s\n", p->singleChoiceA); // 输出A选项信息
					fprintf(fp1, "B：%s\n", p->singleChoiceB); // 输出B选项信息
					fprintf(fp1, "C：%s\n", p->singleChoiceC); // 输出C选项信息
					fprintf(fp1, "D：%s\n", p->singleChoiceD); // 输出D选项信息
					fprintf(fp2, "题目选项：%c\n", p->singleChoiceAns); // 输出题目选项
					QidFlag[randomQid] = 1; // 标记qid
					order++; // 试题顺序+1
					scNum--; // 单选题数-1
					break; // 退出循环 
				}
				p = p->next; // 指向下一个题目
			}
		}
	}
	fprintf(fp1, "==============================\n"); // 输出分隔符
	fprintf(fp2, "==============================\n"); // 输出分隔符
	// 随机填空题模块 
	fprintf(fp1, "二、填空题\n"); // 输出题目类型 
	fprintf(fp2, "二、填空题\n"); // 输出题目类型 
	order = 1; // 试题顺序初始化 
	while(fibNum > 0) // 循环生成填空题
	{
		long long randomQid = 1 + rand() % (nextQid_filling_blank - 1); // 生成[1, qid max]区间内的随机编号 
		if(!QidFlag[randomQid]) // 该qid未标记，即未储存 
		{
			struct Q_filling_blank *p = qLibf->next; // 指向题库头部 
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid) // 找到填空题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp1, "题目：%s\n", p->info); // 输出题目信息
					fprintf(fp2, "题目：%s\n", p->blanksAns); // 输出题目答案
					QidFlag[randomQid] = 1; // 标记qid
					order++; // 试题顺序+1
					fibNum--; // 填空题数-1
					break; // 退出循环 
				}
				p = p->next; // 指向下一个题目
			}
		}
	}
	fclose(fp1); // 关闭文件 
	fclose(fp2); // 关闭文件 
}
int main() // 主函数 
{
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice));     // 为题库赋予初值 
	qLibcTail = qLibc; // 题库尾指针初始化 
	FILE *fp = fopen(path_choice,"r"); // 打开单选题文件 
	long long thisQid; // 题目编号 
	while(fscanf(fp,"%lld\n",&thisQid) != EOF) // 读取单选题文件 
	{
		nextQid_choice = thisQid + 1; // 记录下一个题目编号 
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 为题目赋予初值 
		q->qid = thisQid; // 题目编号赋值 
		fscanf(fp,"%s\n",&q->info); // 题目信息赋值 
		fscanf(fp,"%s\n",&q->singleChoiceA); // A选项信息赋值 
		fscanf(fp,"%s\n",&q->singleChoiceB); // B选项信息赋值 
		fscanf(fp,"%s\n",&q->singleChoiceC); // C选项信息赋值 
		fscanf(fp,"%s\n",&q->singleChoiceD); // D选项信息赋值 
		fscanf(fp,"%s\n",&q->singleChoiceD); // 选项信息赋值 
		fscanf(fp,"%c\n",&q->singleChoiceAns); // 答案赋值 
		qLibcTail->next = q; // 尾指针指向新结点 
	    qLibcTail = qLibcTail->next; // 尾指针指向新尾结点 
	}
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // 为题库赋予初值 
	qLibfTail = qLibf; // 题库尾指针初始化 
	fp = fopen(path_filling_blank,"r"); // 打开填空题文件 
	while(fscanf(fp,"%lld\n",&thisQid) != EOF) // 读取填空题文件 
	{
		nextQid_filling_blank = thisQid + 1; // 记录下一个题目编号 
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // 为题目赋予初值 
		q->qid = thisQid; // 题目编号赋值 
		fscanf(fp,"%s\n",&q->info); // 题目信息赋值 
		fscanf(fp,"%s\n",&q->blanksAns); // 答案赋值 
		qLibfTail->next = q; // 尾指针指向新结点 
	    qLibfTail = qLibfTail->next; // 尾指针指向新尾结点 
	}
	int option; // 功能序号 
	while(1) // 提供菜单，选择功能，在结束某一功能后，重新提供菜单 
	{
		// 输出菜单 
		printf("*** || -欢迎使用试卷管理系统- || ***\n==============================\n菜单：\n【1】试题添加\n【2】试题删除\n【3】备份全部题目\n【4】删除全部题目\n【5】试题修改\n【6】试题查询\n【7】统计题目\n【8】查询特定内容\n【9】随机生成试题\n【0】退出\n==============================\n"); // 输出菜单 
		scanf("%d", &option); // 输入功能序号 
		system("cls");
		switch(option) // 根据功能序号选择功能
		{
			case 1: Add(); break; // 试题添加 
			case 2: Delete(); break; // 试题删除 
     		case 3: BackupAll(); break; // 备份全部题目 
		    case 4: DeleteAll(); break; // 删除全部题目 
			case 5: Modify(); break; // 试题修改 
			case 6: Search(); break; // 试题查询 
			case 7: Statistic(); break; // 统计题目 
			case 8: FindSpecificContent(); break; // 查询特定内容 
			case 9: RandomQandA(); break; // 随机生成试题      
			default: return 0; // 退出程序 
		}
		printf(">>> 键入一次至两次回车以重新进入菜单...\n"); // 提示用户重新输入 
		getchar(); // 清空输入缓存
		getchar(); // 清空输入缓存
		system("cls"); // 清屏 
	}
}