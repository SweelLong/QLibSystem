#include <stdio.h> // 包含标准输入输出头文件 
#include <stdlib.h> // 包含标准库头文件 
#include <string.h> // 包含字符串头文件 
#include <time.h> // 包含时间头文件（可调用随机函数）
#define ll long long // 缩写长整型 
#define MAXN 1000 // 控制数组最大边界 
ll nextQid = 1; // 题目编号的最大值 + 1 
struct Q // 题目结构体，储存题目相关参数 
{
	ll qid; // 题目编号 
	int type; // 题目类型（【1】单选题【2】填空题） 
	char info[MAXN]; // 题目信息 
	char singleChoiceA[MAXN]; // 储存A选项的信息 
	char singleChoiceB[MAXN]; // 储存B选项的信息 
	char singleChoiceC[MAXN]; // 储存C选项的信息 
	char singleChoiceD[MAXN]; // 储存D选项的信息 
	char singleChoiceAns; // 储存单选题答案为字符A、B、C、D 
	char blanksAns[MAXN]; // 储存填空题答案为字符串 
	struct Q *next; // 指向下一个题目的指针 
} *qLib; // 全局题目链表（题库），在main入口处赋初值
void QlibAdd() // 添加题目 
{
	struct Q *q = (struct Q*)malloc(sizeof(struct Q)); // 新建空题目 
	printf("请键入题目类型（【1】单选题【2】填空题）：\n"); // 输入题目类型
	scanf("%d", &q->type); // 指定题目类型
	getchar(); // 清空输入缓存
	if(q->type != 1 && q->type != 2) // 若题目类型不为1或2
	{
		printf("添加题目失败：未知的题目类型\n"); // 输出错误信息
		return; // 退出函数
	}
	printf("请键入题目信息：\n"); // 输入题目信息
	gets(q->info); // 添加题目信息
	if(q->type == 1) // 若题目类型为1
	{
		printf("请键入A选项的信息：\n"); // 输入A选项信息
		gets(q->singleChoiceA); // 添加A选项信息
		printf("请键入B选项的信息：\n"); // 输入B选项信息
		gets(q->singleChoiceB); // 添加B选项信息
		printf("请键入C选项的信息：\n"); // 输入C选项信息
		gets(q->singleChoiceC); // 添加C选项信息
		printf("请键入D选项的信息：\n"); // 输入D选项信息
		gets(q->singleChoiceD); // 添加D选项信息
		printf("请键入单选题答案：\n"); // 输入单选题答案
		char c = getchar(); // 读取单选题答案
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // 若单选题答案不为A、B、C、D
		{
			// 若单选题答案不为A、B、C、D
			printf("只能输入A、B、C、D其中一个字符：\n"); // 输出错误信息
			getchar();// 清空输入缓存
			c = getchar(); // 重新读取单选题答案
		}
		q->singleChoiceAns = c; // 储存单选题答案为字符A、B、C、D
	}
	else if(q->type == 2) // 若题目类型为2
	{
		printf("请键入填空题答案：\n"); // 输入填空题答案
		gets(q->blanksAns); // 添加填空题答案
	}
	q->qid = nextQid++; // 为新题目添加编号 
	printf("成功添加题目编号：%lld\n", q->qid); // 输出新题目的编号
	q->next = qLib->next; // 将旧题接到新题的后面
	qLib->next = q; // 新题保持题目链表的最前面
}
void QlibDelete() // 删除题目 
{
	ll thisQid; // 题目编号 
	printf("请输入要删除题目的编号：\n"); // 输入题目编号
	scanf("%lld", &thisQid); // 指定题目编号
	struct Q *p = qLib; // 指向题库头部 
	while(p->next != NULL) // 遍历题库
	{
		if(p->next->qid == thisQid) // 找到要删除的题目
		{
			struct Q *q = (struct Q*)malloc(sizeof(struct Q)); // 新建空题目
			q->next = p->next->next; // 将下一个题接到当前题的后面
			p->next = q->next; // 将当前题接到题库头部
			free(q); // 释放内存
			printf("删除成功！\n"); // 输出删除成功信息
			return; // 退出函数
		}
		p = p->next; // 指向下一个题目
	}
	printf("删除失败！\n"); // 输出删除失败信息
}
void BackupAll() // 备份题库 
{
	FILE *fp1, *fp2; // 定义文件指针
	fp1 = fopen("单选题题库备份.txt", "w"); // 打开文件
	fp2 = fopen("填空题题库题备份.txt", "w"); // 打开文件
	struct Q *p = qLib; // 指向题库头部 
	while(p->next != NULL) // 遍历题库
	{
		if(p->type == 1) // 若题目类型为1
		{
			fprintf(fp1, "题目编号：%lld\n", p->qid); // 输出题目编号
			fprintf(fp1, "题目信息：%s\n", p->info); // 输出题目信息
			fprintf(fp1, "A选项信息：%s\n", p->singleChoiceA); // 输出A选项信息
			fprintf(fp1, "B选项信息：%s\n", p->singleChoiceB); // 输出B选项信息
			fprintf(fp1, "C选项信息：%s\n", p->singleChoiceC); // 输出C选项信息
			fprintf(fp1, "D选项信息：%s\n", p->singleChoiceD); // 输出D选项信息
			fprintf(fp1, "题目选项：%c\n", p->singleChoiceAns); // 输出题目选项
			fprintf(fp1, "=============================="); // 输出分隔符
		}
		else if(p->type == 2) // 若题目类型为2
		{
			fprintf(fp2, "题目编号：%lld\n", p->qid); // 输出题目编号
			fprintf(fp2, "题目信息：%s\n", p->info); // 输出题目信息
			fprintf(fp2, "题目答案：%s\n", p->blanksAns); // 输出题目答案
			fprintf(fp1, "=============================="); // 输出分隔符
		}
		p = p->next; // 指向下一个题目
	}
	fclose(fp1); // 关闭文件
	fclose(fp2); // 关闭文件                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}
void DeleteAll() // 删除题库
{
	qLib = (struct Q*)malloc(sizeof(struct Q)); // 重新初始化题库
	printf("成功删除全部题目！\n"); // 输出删除成功信息
}
void ModifyQ() // 修改题目 
{
	ll thisQid; // 题目编号 
	printf("请输入要修改内容的编号：\n"); // 输入题目编号
	scanf("%lld", &thisQid); // 指定题目编号
	struct Q *p = qLib->next; // 指向题库头部 
	while(p != NULL) // 遍历题库
	{
		if(p->qid == thisQid) // 找到要修改的题目
		{
			printf("请选择需要修改题目信息还是答案（【1】信息【2】答案【0】返回）：\n"); // 选择修改内容
			int option; // 选项
			scanf("%d", &option); // 指定选项
			if(option == 1) // 若修改题目信息
			{
				if(p->type == 1) // 若题目类型为1
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
					}			
				}
				else
				{
					printf("请输入修改后的题目内容：\n"); // 输入修改后的题目内容
					getchar(); // 清空输入缓存
					gets(p->info); // 修改题目信息
				}
			}
			else if(option == 2) // 若修改题目答案
			{
				if(p->type == 1) // 若题目类型为1
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
				else if(p->type == 2) // 若题目类型为2
				{
					printf("请输入修改后的填空题答案：\n"); // 输入修改后的填空题答案
					getchar(); // 清空输入缓存
					gets(p->blanksAns); // 修改填空题答案
				}
			}
			return; // 退出函数
		}
		p = p->next; // 指向下一个题目
	}
	printf("未找到该题目！\n"); // 输出未找到该题目信息
}
void Qquery() // 题目查询 
{
	ll thisQid; // 题目编号 
	printf("请输入要查询内容的编号：\n"); // 输入题目编号
	scanf("%lld", &thisQid); // 指定题目编号
	struct Q *p = qLib->next; // 指向题库头部 
	while(p != NULL) // 遍历题库
	{
		if(p->qid == thisQid) // 找到要查询的题目
		{
			if(p->type == 1) // 若题目类型为1
			{
				printf("题目类型：单选题\n题目信息：%s\nA选项信息：%s\nB选项信息：%s\nC选项信息：%s\nD选项信息：%s\n题目答案：%c\n", p->info, p->singleChoiceA, p->singleChoiceB, p->singleChoiceC, p->singleChoiceD, p->singleChoiceAns); // 输出题目信息
			}
			else if(p->type == 2) // 若题目类型为2
			{
				printf("题目类型：填空题\n题目信息：%s\n题目答案：%s\n", p->info, p->blanksAns); // 输出题目信息
			}
			else // 若题目类型不为1或2
			{
				printf("查询失败：未知的题目类型\n"); // 输出错误信息
			}
			return; // 退出函数
		}
		p = p->next; // 指向下一个题目
	}
	printf("未找到该题目！\n"); // 输出未找到该题目信息
}
void Statistic() // 题目统计 
{
	ll scNum = 0, fibNum = 0, totalNum = 0; // 单选题、填空题、总题数
	struct Q *p = qLib->next; // 指向题库头部 
	while(p != NULL) // 遍历题库
	{
		printf("查询到题目编号：%lld\n", p->qid); // 输出题目编号
		if(p->type == 1) // 若题目类型为1
			scNum++; // 单选题数+1
		else if(p->type == 2) // 若题目类型为2
			fibNum++; // 填空题数+1
		totalNum++; // 总题数+1
		p = p->next; // 指向下一个题目
	}
	printf("共有%lld道题目(单选题：%lld、填空题：%lld)\n", totalNum, scNum, fibNum); // 输出题目统计信息
}
void FindSpecificContent() // 查询特定内容 
{
	int flag = 0; // 标记是否找到题目
	char sp[1000]; // 特定内容
	printf("请输入题干所包含的特定内容：\n"); // 输入特定内容
	getchar(); // 清空输入缓存
	gets(sp); // 储存特定内容
	struct Q *p = qLib->next; // 指向题库头部 
	while(p != NULL) // 遍历题库
	{
		if(strstr(p->info,sp) != NULL) // 若题目信息中包含特定内容
		{
			printf("查询到符合条件的题目编号：%lld\n", p->qid); // 输出题目编号
			if(p->type == 1) // 若题目类型为1
			{
				printf("题目类型：单选题\n题目信息：%s\n题目答案：%c\n", p->info, p->singleChoiceAns); // 输出题目信息
			}
			else if(p->type == 2) // 若题目类型为2
			{
				printf("题目类型：填空题\n题目信息：%s\n题目答案：%s\n", p->info, p->blanksAns); // 输出题目信息
			}
			flag = 1; // 标记找到题目
		}
		p = p->next; // 指向下一个题目
	}
	if(!flag) // 若未找到题目
	{
		printf("未找到该题目！\n"); // 输出未找到题目信息
	}
}
void RandomQandA() // 随机生成试题 
{
	FILE *fp1 = fopen("exam.txt", "w"); // 创建试题
    FILE *fp2 = fopen("answer.txt", "w"); // 创建答案 
	ll order = 1, scNum, fibNum, QidFlag[MAXN] = {0}; // 试题顺序、单选题数、填空题数、题目编号标记数组 
	printf("请输入生成的单选题题目数：\n"); // 输入单选题题目数
	scanf("%lld", &scNum); // 指定单选题题目数
	printf("请输入生成的填空题题目数：\n"); // 输入填空题题目数
	scanf("%lld", &fibNum); // 指定填空题题目数
	// 随机单选题模块 
	fprintf(fp1, "一、单选题\n"); // 输出题目类型 
	fprintf(fp2, "一、单选题\n"); // 输出题目类型 
	while(scNum > 0) // 循环生成单选题
	{
		ll randomQid = 1 + rand() % (nextQid - 1); // 生成[1, qid max]区间内的随机编号 
		if(!QidFlag[randomQid]) // 该qid未标记，即未储存 
		{
			struct Q *p = qLib->next; // 指向题库头部 
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid && p->type == 1) // 找到单选题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp1, "题目信息：%s\n", p->info); // 输出题目信息
					fprintf(fp1, "A选项信息：%s\n", p->singleChoiceA); // 输出A选项信息
					fprintf(fp1, "B选项信息：%s\n", p->singleChoiceB); // 输出B选项信息
					fprintf(fp1, "C选项信息：%s\n", p->singleChoiceC); // 输出C选项信息
					fprintf(fp1, "D选项信息：%s\n", p->singleChoiceD); // 输出D选项信息
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
		ll randomQid = 1 + rand() % (nextQid - 1); // 生成[1, qid max]区间内的随机编号 
		if(!QidFlag[randomQid]) // 该qid未标记，即未储存 
		{
			struct Q *p = qLib->next; // 指向题库头部 
			while(p != NULL) // 遍历题库
			{
				if(p->qid == randomQid && p->type == 2) // 找到填空题
				{
					fprintf(fp1, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp2, "(%lld.)题目编号：%lld\n", order, p->qid); // 输出题目编号
					fprintf(fp1, "题目信息：%s\n", p->info); // 输出题目信息
					fprintf(fp2, "题目答案：%s\n", p->blanksAns); // 输出题目答案
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
	qLib = (struct Q*)malloc(sizeof(struct Q)); // 为题库赋予初值 
	int option; // 功能序号 
	printf("*** || -欢迎使用试卷管理系统- || ***\n"); // 输出欢迎信息 
	while(1) // 提供菜单，选择功能，在结束某一功能后，重新提供菜单 
	{
		printf("==============================\n菜单：\n【1】试题添加\n【2】试题删除\n【3】备份全部题目\n【4】删除全部题目\n【5】试题修改\n【6】试题查询\n【7】统计题目\n【8】查询特定内容\n【9】随机生成试题\n【0】退出\n==============================\n"); // 输出菜单 
		scanf("%d", &option); // 输入功能序号 
		switch(option) // 根据功能序号选择功能
		{
			case 1: QlibAdd(); break; // 试题添加 
			case 2: QlibDelete(); break; // 试题删除 
			case 3: BackupAll(); break; // 备份全部题目 
			case 4: DeleteAll(); break; // 删除全部题目 
			case 5: ModifyQ(); break; // 试题修改 
			case 6: Qquery(); break; // 试题查询 
			case 7: Statistic(); break; // 统计题目 
			case 8: FindSpecificContent(); break; // 查询特定内容 
			case 9: RandomQandA(); break; // 随机生成试题 
			default: return 0; // 退出程序 
		}
	}
}
