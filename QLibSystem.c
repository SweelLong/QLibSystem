#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#define path_choice "Choice.txt" // 选择题题库文件路径
#define path_filling_blank "Filling_blank.txt" // 填空题题库文件路径
#define path_choice_bak "Choice_bak.txt" // 备份选择题题库文件路径
#define path_filling_blank_bak "Filling_blank_bak.txt" // 备份填空题题库文件路径
#define MAXN 1000 // 控制数组最大边界 
long long nextQid_choice = 1; // 题目编号的最大值 + 1
long long nextQid_filling_blank = 1; 
//long long choiceNum = 0, fillingBlankNum = 0;  
struct Q_choice // 选择题结构体
{ 
	long long qid; // 题目编号 
	char info[MAXN]; // 题目信息 
	char singleChoiceA[MAXN]; // 储存A、B、C、D选项
	char singleChoiceB[MAXN];  
	char singleChoiceC[MAXN];  
	char singleChoiceD[MAXN]; 
	char singleChoiceAns; // 储存单选题答案 
	struct Q_choice *next; // 指向下一个题目的指针 
} *qLibc, *qLibcTail; // 选择题题库的头指针和尾指针
struct Q_filling_blank // 填空题结构体 
{
	long long qid; 
	char info[MAXN]; 
	char blanksAns[MAXN]; 
	struct Q_filling_blank *next; 
} *qLibf, *qLibfTail; 
void Add() // 添加题目 
{
	FILE* fp; // 定义文件指针
	int type; 
	printf("请输入题目类型（【1】单选题【2】填空题）：\n"); 
	scanf("%d", &type); 
	getchar(); // 清空输入缓存
	if(type != 1 && type != 2) 
	{
		printf("添加题目失败：未知的题目类型\n"); 
		return; 
	}
	if(type == 1) 
	{
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 申请内存空间
		fp=fopen(path_choice,"a+"); 
		q->qid = nextQid_choice++; 
		fprintf(fp,"%lld\n",q->qid); 
		printf("请输入题目：\n"); 
		gets(q->info); 
		fprintf(fp,"%s\n",q->info); 
		printf("请输入A选项：\n");
		gets(q->singleChoiceA);
		fprintf(fp,"%s\n",q->singleChoiceA); 
		printf("请输入B选项：\n"); 
		gets(q->singleChoiceB);
		fprintf(fp,"%s\n",q->singleChoiceB); 
		printf("请输入C选项：\n"); 
		gets(q->singleChoiceC); 
		fprintf(fp,"%s\n",q->singleChoiceC); 
		printf("请输入D选项：\n"); 
		gets(q->singleChoiceD); 
		fprintf(fp,"%s\n",q->singleChoiceD);
		printf("请输入答案：\n");
		char c = getchar(); // 读取单选题答案
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') 
		{
			printf("只能输入A、B、C、D其中一个字符：\n"); 
			getchar();// 清空输入缓存
			c = getchar(); // 重新读取单选题答案
		}
		q->singleChoiceAns = c; // 储存单选题答案
		fprintf(fp,"%c\n",q->singleChoiceAns); 
	    printf("成功添加题目编号：%lld\n", q->qid); 
	    qLibcTail->next = q; // 将新题目接到题库尾部
	    qLibcTail = qLibcTail->next; // 更新题库尾指针
	}
	else if(type == 2) 
	{
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); 
		fp=fopen(path_filling_blank,"a+"); 
		q->qid = nextQid_filling_blank++; 
		fprintf(fp,"%lld\n",q->qid); 
		printf("请输入题目：\n"); 
		gets(q->info); 
		fprintf(fp,"%s\n",q->info); 
		printf("请输入答案：\n");
		char ans[MAXN]; 
		gets(q->blanksAns); 
		fprintf(fp,"%s\n",q->blanksAns);
	    printf("成功添加题目编号：%lld\n", q->qid); 
	    qLibfTail->next = q; // 将新题目接到题库尾部
	    qLibfTail = qLibfTail->next; // 更新题库尾指针
	}
	fclose(fp); 
}
void Delete() // 删除题目 
{
	int type; 
	FILE *fp; 
	long long thisQid; // 题目编号 
	printf("请输入要删除题目的类型（【1】单选题【2】填空题）：\n"); 
	scanf("%d", &type); 
	if(type != 1 && type != 2) 
	{
		printf("删除题目失败：未知的题目类型\n"); 
		return; // 退出函数
	}
	if(type == 1) 
	{
		printf("请输入要删除题目的编号：\n"); 
		scanf("%lld", &thisQid); 
		struct Q_choice *p = qLibc; // 指向题库头部 
		while(p->next != NULL) // 遍历题库
		{
			if(p->next->qid == thisQid) // 找到要删除的题目
			{
				struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 新建空题目
				q->next = p->next->next; // 将下一个题接到当前题的后面
				p->next = q->next; // 将当前题接到题库头部
				free(q); // 释放内存
				printf("删除成功！\n"); 
			}
			p = p->next; // 指向下一个题目
		}
		fp = fopen(path_choice, "w"); // 打开文件
		p = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
			fprintf(fp, "%lld\n",p->qid); 
			fprintf(fp, "%s\n",p->info); 
			fprintf(fp, "%s\n",p->singleChoiceA); 
			fprintf(fp, "%s\n",p->singleChoiceB); 
			fprintf(fp, "%s\n",p->singleChoiceC); 
			fprintf(fp, "%s\n",p->singleChoiceD); 
			fprintf(fp, "%c\n",p->singleChoiceAns); 
			p = p->next; // 指向下一个题目
		}
		fclose(fp); // 关闭文件
	}
	else if(type == 2)
	{
		printf("请输入要删除题目的编号：\n"); 
		scanf("%lld",&thisQid); 
		struct Q_filling_blank *p = qLibf; 
		fp=fopen(path_filling_blank, "w"); 
		while(p->next != NULL) 
		{
			if(p->next->qid == thisQid)
			{
				struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); 
				q->next = p->next->next; 
				p->next = q->next; 
				free(q);
				printf("删除成功！\n");
			}
			p = p->next; 
		}
		fp=fopen(path_filling_blank, "w"); 
		p = qLibf->next; 
		while(p != NULL)
		{
			fprintf(fp, "%lld\n",p->qid); 
			fprintf(fp, "%s\n",p->info); 
			fprintf(fp, "%s\n",p->blanksAns); 
			p = p->next; 
		}
		fclose(fp); 
	}
}
void BackupAll() // 备份题库
{
	FILE *fp1, *fp2; 
	fp1 = fopen(path_choice_bak, "w"); 
	fp2 = fopen(path_filling_blank_bak, "w"); 
	struct Q_choice *p1 = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
	struct Q_filling_blank *p2 = qLibf->next; 
	while(p1 != NULL) 
	{
		fprintf(fp1, "%lld\n",p1->qid); 
		fprintf(fp1, "%s\n",p1->info); 
		fprintf(fp1, "%s\n",p1->singleChoiceA); 
		fprintf(fp1, "%s\n",p1->singleChoiceB); 
		fprintf(fp1, "%s\n",p1->singleChoiceC); 
		fprintf(fp1, "%s\n",p1->singleChoiceD); 
		fprintf(fp1, "%c\n",p1->singleChoiceAns); 
		p1 = p1->next; // 指向下一个题目
    }
    while(p2 != NULL) 
    {
    	fprintf(fp2, "%lld\n",p2->qid); 
		fprintf(fp2, "%s\n",p2->info); 
		fprintf(fp2, "%s\n",p2->blanksAns); 
		p2 = p2->next; // 指向下一个题目
	}
	fclose(fp1); // 关闭文件
	fclose(fp2); 
	printf("备份成功!\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}
void DeleteAll() // 删除题库
{
    FILE *p1; 
    FILE *p2; 
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // 重新初始化题库
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); 
	fopen(path_choice,"w"); // 重写文件
	fopen(path_filling_blank,"w"); 
	printf("成功删除全部题目！\n"); 
}
void Modify() // 修改题目 
{
	FILE *fp; 
	long long thisQid; // 题目编号 
	int type; 
	printf("请输入题目类型（【1】单选题【2】填空题）：\n"); 
	scanf("%d", &type); 
	if(type != 1 && type != 2) 
	{
		printf("修改题目失败：未知的题目类型\n"); 
		return; 
	}
	printf("请输入要修改内容的编号：\n"); 
	scanf("%lld", &thisQid); 
	if(type == 1) 
	{
		struct Q_choice *p = qLibc->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(p->qid == thisQid) // 找到要修改的题目
			{
				printf("请选择需要修改题目信息还是答案（【1】题目【2】答案【0】返回）：\n");
				{
					int option; // 选项
					scanf("%d", &option); // 指定选项
					if(option == 1) // 修改题目
					{
						printf("请输入具体的修改内容（【A】【B】【C】【D】【其他按键：题干】）：\n"); 
						char c = getchar(); // 读取修改内容
						getchar(); // 清空输入缓存
						printf("请输入修改后的题目内容：\n"); // 输入修改后的题目内容
						getchar(); // 清空输入缓存
						switch(c) // 根据修改内容选择修改位置
						{
							case 'A': gets(p->singleChoiceA); break; 
							case 'B': gets(p->singleChoiceB); break; 
							case 'C': gets(p->singleChoiceC); break; 
							case 'D': gets(p->singleChoiceD); break; 
							default: gets(p->info); break; // 修改题目信息
						}	
					}
					else if(option == 2) // 修改答案
					{
						printf("请输入修改后的单选题答案：\n"); 
						getchar(); 
						char c = getchar(); 
						getchar(); 
						while(c != 'A' && c != 'B' && c != 'C' && c != 'D') 
						{
							printf("只能输入A、B、C、D其中一个字符：\n");
							c = getchar(); 
							getchar(); 
						}
						p->singleChoiceAns = c; // 修改单选题答案
					}
				}	
			}
			p = p->next; 
		}
		fp = fopen(path_choice, "w"); 
		p = qLibc->next; // 指向题库头结点的下一个结点 （头结点不储存数据，只有指针） 
		while(p != NULL) // 遍历题库
		{
			fprintf(fp, "%lld\n",p->qid); 
			fprintf(fp, "%s\n",p->info); 
			fprintf(fp, "%s\n",p->singleChoiceA); 
			fprintf(fp, "%s\n",p->singleChoiceB); 
			fprintf(fp, "%s\n",p->singleChoiceC); 
			fprintf(fp, "%s\n",p->singleChoiceD); 
			fprintf(fp, "%c\n",p->singleChoiceAns); 
			p = p->next; 
    	}
    	fclose(fp); 
	}
	else if(type == 2) 
	{
		struct Q_filling_blank *p = qLibf->next;
		while(p != NULL) 
		{
			if(p->qid == thisQid) 
			{
				printf("请选择需要修改题目信息还是答案（【1】信息【2】答案【0】返回）：\n"); 
				int option; 
				scanf("%d", &option); 
				if(option == 1) 
				{
					printf("请输入修改后的题目内容：\n"); 
					getchar(); 
					gets(p->info); 
				}
				else if(option == 2) 
				{
					printf("请输入修改后的填空题答案：\n"); 
					getchar(); 
					gets(p->blanksAns); 
				}
			}
			p = p->next; 
		}
		fp = fopen(path_filling_blank, "w"); 
		p = qLibf->next; 
		while(p != NULL) 
		{
    		fprintf(fp, "%lld\n",p->qid);
			fprintf(fp, "%s\n",p->info); 
			fprintf(fp, "%s\n",p->blanksAns); 
			p = p->next; 
    	}
    	fclose(fp);
	}
}
void Search() // 题目查询 
{
	int type, flag = 0; 
	printf("请输入要查询的题目类型([1]选择题[2]填空题)：\n"); 
	scanf("%d",&type); 
	if(type != 1 && type != 2) 
	{
		printf("查询失败：未知的题目类型\n");
		return; 
	}
	if(type == 1) 
	{
		long long thisQid; // 题目编号 
		printf("请输入要查询题目的编号：\n"); 
		scanf("%lld", &thisQid); 
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
	else if(type == 2) 
	{
		long long thisQid; 
		printf("请输入要查询题目的编号：\n"); 
		scanf("%lld", &thisQid);
		struct Q_filling_blank *p = qLibf->next; 
		while(p != NULL) 
		{
			if(p->qid == thisQid) 
			{
				printf("\n题目:%s\n答案:%s\n", p->info, p->blanksAns); 
				flag = 1; 
				break; 
			}
			p = p->next; 
		}
	}
	if(!flag) // 若未找到题目
		printf("未查询到有效的题目信息\n"); 
	return; 
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
	while(q2 != NULL) 
	{
		fibNum++; // 填空题数+1
		totalNum++; 
		q2 = q2->next; 
	}    
	//choiceNum = scNum; 
	//fillingBlankNum = fibNum; 
	printf("共有%lld道题目(单选题：%lld、填空题：%lld)\n", totalNum, scNum, fibNum); // 输出题目统计信息
}
void FindSpecificContent() // 查询特定内容 
{
	printf("请输入题目类型（【1】单选题【2】填空题）：\n");
	int type; 
	scanf("%d", &type); 
	getchar(); // 清空输入缓存
	if(type != 1 && type != 2) 
	{
		printf("查询失败：未知的题目类型\n"); 
		return; 
	}
	int flag = 0; // 标记是否找到题目
	char sp[1000]; // 特定内容
	printf("请输入题干所包含的特定内容：\n"); // 输入特定内容
	getchar(); // 清空输入缓存
	gets(sp); // 储存特定内容
	if(type == 1)
	{
		struct Q_choice *p = qLibc->next; // 指向题库头部 
		while(p != NULL) // 遍历题库
		{
			if(strstr(p->info,sp) != NULL) // 若题目信息中包含特定内容
			{
				flag = 1; // 标记找到题目
				printf("查询到符合条件的题目编号：%lld\n", p->qid);
				printf("题目类型：单选题\n题目信息：%s\n题目答案：%c\n", p->info, p->singleChoiceAns);
			}
			p = p->next; // 指向下一个题目
		}
	}
	else if(type == 2) 
	{
		struct Q_filling_blank *p = qLibf->next; 
		while(p != NULL) 
		{
			if(strstr(p->info,sp) != NULL) 
			{
				flag = 1; 
				printf("查询到符合条件的题目编号：%lld\n", p->qid); 
				printf("题目类型：填空题\n题目信息：%s\n题目答案：%s\n", p->info, p->blanksAns); 
			}	
			p = p->next; 
		}
	}	
	if(!flag) // 若未找到题目
		printf("未找到该题目！\n"); 
}
void RandomQandA() // 随机生成试题 
{
	FILE *fp1 = fopen("exam.txt", "w"); // 创建试题
    FILE *fp2 = fopen("answer.txt", "w"); // 创建答案 
	long long order = 1,scNum,fibNum; // 试题顺序、单选题数、填空题数、题目编号标记数组 
	printf("请输入生成的单选题题目数：\n"); 
	scanf("%lld", &scNum); 
	printf("请输入生成的填空题题目数：\n"); 
	scanf("%lld", &fibNum); 
	//Statistic(); // 统计题目 
	srand(time(NULL)); 
	// 随机单选题模块 
	fprintf(fp1, "一、单选题\n"); // 输出题目类型 
	fprintf(fp2, "一、单选题\n"); // 输出题目类型 
	while(scNum > 0) // 循环生成单选题
	{
		
		long long randomQid = 1 + rand() % (nextQid_choice - 1); // 生成[1, qid max]区间内的随机编号 

		
			struct Q_choice *p = qLibc->next; // 指向题库头部
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid) // 找到单选题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); 
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); 
					fprintf(fp1, "题目：%s\n", p->info); 
					fprintf(fp1, "A：%s\n", p->singleChoiceA); 
					fprintf(fp1, "B：%s\n", p->singleChoiceB); 
					fprintf(fp1, "C：%s\n", p->singleChoiceC); 
					fprintf(fp1, "D：%s\n", p->singleChoiceD); 
					fprintf(fp2, "题目选项：%c\n", p->singleChoiceAns); 
					order++; // 试题顺序+1
					scNum--; // 单选题数-1
					break; // 退出循环 
				}
				p = p->next; // 指向下一个题目
			}
		
	}
	fprintf(fp1, "==============================\n");
	fprintf(fp2, "==============================\n");
	// 随机填空题模块 
	fprintf(fp1, "二、填空题\n"); 
	fprintf(fp2, "二、填空题\n");
	order = 1; // 试题顺序初始化 
	while(fibNum > 0) // 循环生成填空题
	{
		long long randomQid = 1 + rand() % (nextQid_filling_blank - 1); // 生成[1, qid max]区间内的随机编号 

		
			struct Q_filling_blank *p = qLibf->next; // 指向题库头部 
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid) // 找到填空题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); 
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); 
					fprintf(fp1, "题目：%s\n", p->info); 
					fprintf(fp2, "题目：%s\n", p->blanksAns);

					order++; // 试题顺序+1
					fibNum--; // 填空题数-1
					break; // 退出循环 
				}
				p = p->next; // 指向下一个题目
			}
		
	}
	fclose(fp1); 
	fclose(fp2); 
	printf("生成试卷成功!\n");
	return; 
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
		q->qid = thisQid; 
		fscanf(fp,"%s\n",&q->info); 
		fscanf(fp,"%s\n",&q->singleChoiceA); 
		fscanf(fp,"%s\n",&q->singleChoiceB);  
		fscanf(fp,"%s\n",&q->singleChoiceC); 
		fscanf(fp,"%s\n",&q->singleChoiceD); 
		fscanf(fp,"%c\n",&q->singleChoiceAns); 
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
		q->qid = thisQid;  
		fscanf(fp,"%s\n",&q->info); 
		fscanf(fp,"%s\n",&q->blanksAns); 
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
		printf(">>> 输入一次至两次回车以重新进入菜单...\n"); // 提示用户重新输入 
		getchar(); // 清空输入缓存
		getchar(); 
		system("cls"); // 清屏 
	}
}
