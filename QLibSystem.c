#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#define path_choice "Choice.txt" // ѡ��������ļ�·��
#define path_filling_blank "Filling_blank.txt" // ���������ļ�·��
#define path_choice_bak "Choice_bak.txt" // ����ѡ��������ļ�·��
#define path_filling_blank_bak "Filling_blank_bak.txt" // �������������ļ�·��
#define MAXN 1000 // �����������߽� 
long long nextQid_choice = 1; // ��Ŀ��ŵ����ֵ + 1
long long nextQid_filling_blank = 1; 
//long long choiceNum = 0, fillingBlankNum = 0;  
struct Q_choice // ѡ����ṹ��
{ 
	long long qid; // ��Ŀ��� 
	char info[MAXN]; // ��Ŀ��Ϣ 
	char singleChoiceA[MAXN]; // ����A��B��C��Dѡ��
	char singleChoiceB[MAXN];  
	char singleChoiceC[MAXN];  
	char singleChoiceD[MAXN]; 
	char singleChoiceAns; // ���浥ѡ��� 
	struct Q_choice *next; // ָ����һ����Ŀ��ָ�� 
} *qLibc, *qLibcTail; // ѡ��������ͷָ���βָ��
struct Q_filling_blank // �����ṹ�� 
{
	long long qid; 
	char info[MAXN]; 
	char blanksAns[MAXN]; 
	struct Q_filling_blank *next; 
} *qLibf, *qLibfTail; 
void Add() // �����Ŀ 
{
	FILE* fp; // �����ļ�ָ��
	int type; 
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); 
	scanf("%d", &type); 
	getchar(); // ������뻺��
	if(type != 1 && type != 2) 
	{
		printf("�����Ŀʧ�ܣ�δ֪����Ŀ����\n"); 
		return; 
	}
	if(type == 1) 
	{
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // �����ڴ�ռ�
		fp=fopen(path_choice,"a+"); 
		q->qid = nextQid_choice++; 
		fprintf(fp,"%lld\n",q->qid); 
		printf("��������Ŀ��\n"); 
		gets(q->info); 
		fprintf(fp,"%s\n",q->info); 
		printf("������Aѡ�\n");
		gets(q->singleChoiceA);
		fprintf(fp,"%s\n",q->singleChoiceA); 
		printf("������Bѡ�\n"); 
		gets(q->singleChoiceB);
		fprintf(fp,"%s\n",q->singleChoiceB); 
		printf("������Cѡ�\n"); 
		gets(q->singleChoiceC); 
		fprintf(fp,"%s\n",q->singleChoiceC); 
		printf("������Dѡ�\n"); 
		gets(q->singleChoiceD); 
		fprintf(fp,"%s\n",q->singleChoiceD);
		printf("������𰸣�\n");
		char c = getchar(); // ��ȡ��ѡ���
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') 
		{
			printf("ֻ������A��B��C��D����һ���ַ���\n"); 
			getchar();// ������뻺��
			c = getchar(); // ���¶�ȡ��ѡ���
		}
		q->singleChoiceAns = c; // ���浥ѡ���
		fprintf(fp,"%c\n",q->singleChoiceAns); 
	    printf("�ɹ������Ŀ��ţ�%lld\n", q->qid); 
	    qLibcTail->next = q; // ������Ŀ�ӵ����β��
	    qLibcTail = qLibcTail->next; // �������βָ��
	}
	else if(type == 2) 
	{
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); 
		fp=fopen(path_filling_blank,"a+"); 
		q->qid = nextQid_filling_blank++; 
		fprintf(fp,"%lld\n",q->qid); 
		printf("��������Ŀ��\n"); 
		gets(q->info); 
		fprintf(fp,"%s\n",q->info); 
		printf("������𰸣�\n");
		char ans[MAXN]; 
		gets(q->blanksAns); 
		fprintf(fp,"%s\n",q->blanksAns);
	    printf("�ɹ������Ŀ��ţ�%lld\n", q->qid); 
	    qLibfTail->next = q; // ������Ŀ�ӵ����β��
	    qLibfTail = qLibfTail->next; // �������βָ��
	}
	fclose(fp); 
}
void Delete() // ɾ����Ŀ 
{
	int type; 
	FILE *fp; 
	long long thisQid; // ��Ŀ��� 
	printf("������Ҫɾ����Ŀ�����ͣ���1����ѡ�⡾2������⣩��\n"); 
	scanf("%d", &type); 
	if(type != 1 && type != 2) 
	{
		printf("ɾ����Ŀʧ�ܣ�δ֪����Ŀ����\n"); 
		return; // �˳�����
	}
	if(type == 1) 
	{
		printf("������Ҫɾ����Ŀ�ı�ţ�\n"); 
		scanf("%lld", &thisQid); 
		struct Q_choice *p = qLibc; // ָ�����ͷ�� 
		while(p->next != NULL) // �������
		{
			if(p->next->qid == thisQid) // �ҵ�Ҫɾ������Ŀ
			{
				struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // �½�����Ŀ
				q->next = p->next->next; // ����һ����ӵ���ǰ��ĺ���
				p->next = q->next; // ����ǰ��ӵ����ͷ��
				free(q); // �ͷ��ڴ�
				printf("ɾ���ɹ���\n"); 
			}
			p = p->next; // ָ����һ����Ŀ
		}
		fp = fopen(path_choice, "w"); // ���ļ�
		p = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
		{
			fprintf(fp, "%lld\n",p->qid); 
			fprintf(fp, "%s\n",p->info); 
			fprintf(fp, "%s\n",p->singleChoiceA); 
			fprintf(fp, "%s\n",p->singleChoiceB); 
			fprintf(fp, "%s\n",p->singleChoiceC); 
			fprintf(fp, "%s\n",p->singleChoiceD); 
			fprintf(fp, "%c\n",p->singleChoiceAns); 
			p = p->next; // ָ����һ����Ŀ
		}
		fclose(fp); // �ر��ļ�
	}
	else if(type == 2)
	{
		printf("������Ҫɾ����Ŀ�ı�ţ�\n"); 
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
				printf("ɾ���ɹ���\n");
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
void BackupAll() // �������
{
	FILE *fp1, *fp2; 
	fp1 = fopen(path_choice_bak, "w"); 
	fp2 = fopen(path_filling_blank_bak, "w"); 
	struct Q_choice *p1 = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
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
		p1 = p1->next; // ָ����һ����Ŀ
    }
    while(p2 != NULL) 
    {
    	fprintf(fp2, "%lld\n",p2->qid); 
		fprintf(fp2, "%s\n",p2->info); 
		fprintf(fp2, "%s\n",p2->blanksAns); 
		p2 = p2->next; // ָ����һ����Ŀ
	}
	fclose(fp1); // �ر��ļ�
	fclose(fp2); 
	printf("���ݳɹ�!\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}
void DeleteAll() // ɾ�����
{
    FILE *p1; 
    FILE *p2; 
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // ���³�ʼ�����
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); 
	fopen(path_choice,"w"); // ��д�ļ�
	fopen(path_filling_blank,"w"); 
	printf("�ɹ�ɾ��ȫ����Ŀ��\n"); 
}
void Modify() // �޸���Ŀ 
{
	FILE *fp; 
	long long thisQid; // ��Ŀ��� 
	int type; 
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); 
	scanf("%d", &type); 
	if(type != 1 && type != 2) 
	{
		printf("�޸���Ŀʧ�ܣ�δ֪����Ŀ����\n"); 
		return; 
	}
	printf("������Ҫ�޸����ݵı�ţ�\n"); 
	scanf("%lld", &thisQid); 
	if(type == 1) 
	{
		struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(p->qid == thisQid) // �ҵ�Ҫ�޸ĵ���Ŀ
			{
				printf("��ѡ����Ҫ�޸���Ŀ��Ϣ���Ǵ𰸣���1����Ŀ��2���𰸡�0�����أ���\n");
				{
					int option; // ѡ��
					scanf("%d", &option); // ָ��ѡ��
					if(option == 1) // �޸���Ŀ
					{
						printf("�����������޸����ݣ���A����B����C����D����������������ɡ�����\n"); 
						char c = getchar(); // ��ȡ�޸�����
						getchar(); // ������뻺��
						printf("�������޸ĺ����Ŀ���ݣ�\n"); // �����޸ĺ����Ŀ����
						getchar(); // ������뻺��
						switch(c) // �����޸�����ѡ���޸�λ��
						{
							case 'A': gets(p->singleChoiceA); break; 
							case 'B': gets(p->singleChoiceB); break; 
							case 'C': gets(p->singleChoiceC); break; 
							case 'D': gets(p->singleChoiceD); break; 
							default: gets(p->info); break; // �޸���Ŀ��Ϣ
						}	
					}
					else if(option == 2) // �޸Ĵ�
					{
						printf("�������޸ĺ�ĵ�ѡ��𰸣�\n"); 
						getchar(); 
						char c = getchar(); 
						getchar(); 
						while(c != 'A' && c != 'B' && c != 'C' && c != 'D') 
						{
							printf("ֻ������A��B��C��D����һ���ַ���\n");
							c = getchar(); 
							getchar(); 
						}
						p->singleChoiceAns = c; // �޸ĵ�ѡ���
					}
				}	
			}
			p = p->next; 
		}
		fp = fopen(path_choice, "w"); 
		p = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
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
				printf("��ѡ����Ҫ�޸���Ŀ��Ϣ���Ǵ𰸣���1����Ϣ��2���𰸡�0�����أ���\n"); 
				int option; 
				scanf("%d", &option); 
				if(option == 1) 
				{
					printf("�������޸ĺ����Ŀ���ݣ�\n"); 
					getchar(); 
					gets(p->info); 
				}
				else if(option == 2) 
				{
					printf("�������޸ĺ�������𰸣�\n"); 
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
void Search() // ��Ŀ��ѯ 
{
	int type, flag = 0; 
	printf("������Ҫ��ѯ����Ŀ����([1]ѡ����[2]�����)��\n"); 
	scanf("%d",&type); 
	if(type != 1 && type != 2) 
	{
		printf("��ѯʧ�ܣ�δ֪����Ŀ����\n");
		return; 
	}
	if(type == 1) 
	{
		long long thisQid; // ��Ŀ��� 
		printf("������Ҫ��ѯ��Ŀ�ı�ţ�\n"); 
		scanf("%lld", &thisQid); 
		struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
		while(p != NULL) // ������� 
		{
			if(p->qid == thisQid) // �ҵ�Ҫ��ѯ����Ŀ
			{
				// �����Ŀ��Ϣ
				printf("��Ŀ:%s\nA:%s\nB:%s\nC:%s\nD:%s\n��:%c\n", p->info, p->singleChoiceA, p->singleChoiceB, p->singleChoiceC, p->singleChoiceD, p->singleChoiceAns);
				flag = 1; // ����ҵ���Ŀ
				break; // �˳�ѭ��
			}
            p = p->next; // ָ����һ����Ŀ
		}
	}
	else if(type == 2) 
	{
		long long thisQid; 
		printf("������Ҫ��ѯ��Ŀ�ı�ţ�\n"); 
		scanf("%lld", &thisQid);
		struct Q_filling_blank *p = qLibf->next; 
		while(p != NULL) 
		{
			if(p->qid == thisQid) 
			{
				printf("\n��Ŀ:%s\n��:%s\n", p->info, p->blanksAns); 
				flag = 1; 
				break; 
			}
			p = p->next; 
		}
	}
	if(!flag) // ��δ�ҵ���Ŀ
		printf("δ��ѯ����Ч����Ŀ��Ϣ\n"); 
	return; 
}
void Statistic() // ��Ŀͳ�� 
{
	long long scNum = 0, fibNum = 0, totalNum = 0; // ��ѡ�⡢����⡢������
	struct Q_choice *q1 = qLibc->next; // ָ�����ͷ�� 
	struct Q_filling_blank *q2 = qLibf->next;
	while(q1 != NULL) // �������
	{
		scNum++; // ��ѡ����+1
		totalNum++; // ������+1
		q1 = q1->next; // ָ����һ����Ŀ
	}
	while(q2 != NULL) 
	{
		fibNum++; // �������+1
		totalNum++; 
		q2 = q2->next; 
	}    
	//choiceNum = scNum; 
	//fillingBlankNum = fibNum; 
	printf("����%lld����Ŀ(��ѡ�⣺%lld������⣺%lld)\n", totalNum, scNum, fibNum); // �����Ŀͳ����Ϣ
}
void FindSpecificContent() // ��ѯ�ض����� 
{
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n");
	int type; 
	scanf("%d", &type); 
	getchar(); // ������뻺��
	if(type != 1 && type != 2) 
	{
		printf("��ѯʧ�ܣ�δ֪����Ŀ����\n"); 
		return; 
	}
	int flag = 0; // ����Ƿ��ҵ���Ŀ
	char sp[1000]; // �ض�����
	printf("������������������ض����ݣ�\n"); // �����ض�����
	getchar(); // ������뻺��
	gets(sp); // �����ض�����
	if(type == 1)
	{
		struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(strstr(p->info,sp) != NULL) // ����Ŀ��Ϣ�а����ض�����
			{
				flag = 1; // ����ҵ���Ŀ
				printf("��ѯ��������������Ŀ��ţ�%lld\n", p->qid);
				printf("��Ŀ���ͣ���ѡ��\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%c\n", p->info, p->singleChoiceAns);
			}
			p = p->next; // ָ����һ����Ŀ
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
				printf("��ѯ��������������Ŀ��ţ�%lld\n", p->qid); 
				printf("��Ŀ���ͣ������\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%s\n", p->info, p->blanksAns); 
			}	
			p = p->next; 
		}
	}	
	if(!flag) // ��δ�ҵ���Ŀ
		printf("δ�ҵ�����Ŀ��\n"); 
}
void RandomQandA() // ����������� 
{
	FILE *fp1 = fopen("exam.txt", "w"); // ��������
    FILE *fp2 = fopen("answer.txt", "w"); // ������ 
	long long order = 1,scNum,fibNum; // ����˳�򡢵�ѡ�����������������Ŀ��ű������ 
	printf("���������ɵĵ�ѡ����Ŀ����\n"); 
	scanf("%lld", &scNum); 
	printf("���������ɵ��������Ŀ����\n"); 
	scanf("%lld", &fibNum); 
	//Statistic(); // ͳ����Ŀ 
	srand(time(NULL)); 
	// �����ѡ��ģ�� 
	fprintf(fp1, "һ����ѡ��\n"); // �����Ŀ���� 
	fprintf(fp2, "һ����ѡ��\n"); // �����Ŀ���� 
	while(scNum > 0) // ѭ�����ɵ�ѡ��
	{
		
		long long randomQid = 1 + rand() % (nextQid_choice - 1); // ����[1, qid max]�����ڵ������� 

		
			struct Q_choice *p = qLibc->next; // ָ�����ͷ��
			while(p != NULL) // �������
			{
				if(p->qid == randomQid) // �ҵ���ѡ��
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); 
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); 
					fprintf(fp1, "��Ŀ��%s\n", p->info); 
					fprintf(fp1, "A��%s\n", p->singleChoiceA); 
					fprintf(fp1, "B��%s\n", p->singleChoiceB); 
					fprintf(fp1, "C��%s\n", p->singleChoiceC); 
					fprintf(fp1, "D��%s\n", p->singleChoiceD); 
					fprintf(fp2, "��Ŀѡ�%c\n", p->singleChoiceAns); 
					order++; // ����˳��+1
					scNum--; // ��ѡ����-1
					break; // �˳�ѭ�� 
				}
				p = p->next; // ָ����һ����Ŀ
			}
		
	}
	fprintf(fp1, "==============================\n");
	fprintf(fp2, "==============================\n");
	// ��������ģ�� 
	fprintf(fp1, "���������\n"); 
	fprintf(fp2, "���������\n");
	order = 1; // ����˳���ʼ�� 
	while(fibNum > 0) // ѭ�����������
	{
		long long randomQid = 1 + rand() % (nextQid_filling_blank - 1); // ����[1, qid max]�����ڵ������� 

		
			struct Q_filling_blank *p = qLibf->next; // ָ�����ͷ�� 
			while(p != NULL) // �������
			{
				if(p->qid == randomQid) // �ҵ������
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); 
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); 
					fprintf(fp1, "��Ŀ��%s\n", p->info); 
					fprintf(fp2, "��Ŀ��%s\n", p->blanksAns);

					order++; // ����˳��+1
					fibNum--; // �������-1
					break; // �˳�ѭ�� 
				}
				p = p->next; // ָ����һ����Ŀ
			}
		
	}
	fclose(fp1); 
	fclose(fp2); 
	printf("�����Ծ�ɹ�!\n");
	return; 
}
int main() // ������ 
{
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice));     // Ϊ��⸳���ֵ 
	qLibcTail = qLibc; // ���βָ���ʼ�� 
	FILE *fp = fopen(path_choice,"r"); // �򿪵�ѡ���ļ� 
	long long thisQid; // ��Ŀ��� 
	while(fscanf(fp,"%lld\n",&thisQid) != EOF) // ��ȡ��ѡ���ļ� 
	{
		nextQid_choice = thisQid + 1; // ��¼��һ����Ŀ��� 
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // Ϊ��Ŀ�����ֵ 
		q->qid = thisQid; 
		fscanf(fp,"%s\n",&q->info); 
		fscanf(fp,"%s\n",&q->singleChoiceA); 
		fscanf(fp,"%s\n",&q->singleChoiceB);  
		fscanf(fp,"%s\n",&q->singleChoiceC); 
		fscanf(fp,"%s\n",&q->singleChoiceD); 
		fscanf(fp,"%c\n",&q->singleChoiceAns); 
		qLibcTail->next = q; // βָ��ָ���½�� 
	    qLibcTail = qLibcTail->next; // βָ��ָ����β��� 
	}
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // Ϊ��⸳���ֵ 
	qLibfTail = qLibf; // ���βָ���ʼ�� 
	fp = fopen(path_filling_blank,"r"); // ��������ļ� 
	while(fscanf(fp,"%lld\n",&thisQid) != EOF) // ��ȡ������ļ� 
	{
		nextQid_filling_blank = thisQid + 1; // ��¼��һ����Ŀ��� 
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // Ϊ��Ŀ�����ֵ 
		q->qid = thisQid;  
		fscanf(fp,"%s\n",&q->info); 
		fscanf(fp,"%s\n",&q->blanksAns); 
		qLibfTail->next = q; // βָ��ָ���½�� 
	    qLibfTail = qLibfTail->next; // βָ��ָ����β��� 
	}
	int option; // ������� 
	while(1) // �ṩ�˵���ѡ���ܣ��ڽ���ĳһ���ܺ������ṩ�˵� 
	{
		// ����˵� 
		printf("*** || -��ӭʹ���Ծ����ϵͳ- || ***\n==============================\n�˵���\n��1���������\n��2������ɾ��\n��3������ȫ����Ŀ\n��4��ɾ��ȫ����Ŀ\n��5�������޸�\n��6�������ѯ\n��7��ͳ����Ŀ\n��8����ѯ�ض�����\n��9�������������\n��0���˳�\n==============================\n"); // ����˵� 
		scanf("%d", &option); // ���빦����� 
		system("cls");
		switch(option) // ���ݹ������ѡ����
		{
			case 1: Add(); break; // ������� 
			case 2: Delete(); break; // ����ɾ�� 
     		case 3: BackupAll(); break; // ����ȫ����Ŀ 
		    case 4: DeleteAll(); break; // ɾ��ȫ����Ŀ 
			case 5: Modify(); break; // �����޸� 
			case 6: Search(); break; // �����ѯ 
			case 7: Statistic(); break; // ͳ����Ŀ 
			case 8: FindSpecificContent(); break; // ��ѯ�ض����� 
			case 9: RandomQandA(); break; // �����������      
			default: return 0; // �˳����� 
		}
		printf(">>> ����һ�������λس������½���˵�...\n"); // ��ʾ�û��������� 
		getchar(); // ������뻺��
		getchar(); 
		system("cls"); // ���� 
	}
}
