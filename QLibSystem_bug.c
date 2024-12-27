#include <stdio.h> // ��׼�������ͷ�ļ� 
#include <stdlib.h> // ��׼��ͷ�ļ� 
#include <string.h> // �ַ���ͷ�ļ� 
#include <time.h> // ʱ��ͷ�ļ����ɵ������������
#define path_choice "Choice.txt" // ѡ��������ļ�·��
#define path_filling_blank "Filling_blank.txt" // ���������ļ�·��
#define path_choice_bak "Choice_bak.txt" // ����ѡ��������ļ�·��
#define path_filling_blank_bak "Filling_blank_bak.txt" // �������������ļ�·��
#define MAXN 1000 // �����������߽� 
long long nextQid_choice = 1; // ��Ŀ��ŵ����ֵ + 1
long long nextQid_filling_blank = 1; // ��Ŀ��ŵ����ֵ + 1
long long choiceNum = 0, fillingBlankNum = 0;  // ѡ���������������
struct Q_choice // ѡ����ṹ��
{ 
	long long qid; // ��Ŀ��� 
	char info[MAXN]; // ��Ŀ��Ϣ 
	char singleChoiceA[MAXN]; // ����Aѡ�����Ϣ 
	char singleChoiceB[MAXN]; // ����Bѡ�����Ϣ 
	char singleChoiceC[MAXN]; // ����Cѡ�����Ϣ 
	char singleChoiceD[MAXN]; // ����Dѡ�����Ϣ 
	char singleChoiceAns; // ���浥ѡ���Ϊ�ַ�A��B��C��D  
	struct Q_choice *next; // ָ����һ����Ŀ��ָ�� 
} *qLibc, *qLibcTail; // ѡ��������ͷָ���βָ��
struct Q_filling_blank // �����ṹ�� 
{
	long long qid; // ��Ŀ���
	char info[MAXN]; // ��Ŀ��Ϣ
	char blanksAns[MAXN]; // ����������Ϊ�ַ��� 
	struct Q_filling_blank *next; // ָ����һ����Ŀ��ָ��
} *qLibf, *qLibfTail; // ���������ͷָ���βָ��
void Add() // �����Ŀ 
{
	FILE* fp; // �����ļ�ָ��
	int type; // ��Ŀ����
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); // ������Ŀ����
	scanf("%d", &type); // ָ����Ŀ����
	getchar(); // ������뻺��
	if(type != 1 && type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("�����Ŀʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	if(type == 1) // ����Ŀ����Ϊ1
	{
		struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // �����ڴ�ռ�
		fp=fopen(path_choice,"a+"); // ���ļ�
		q->qid = nextQid_choice++; // Ϊ����Ŀ��ӱ�� 
		fprintf(fp,"%lld\n",q->qid); // �����Ŀ���
		printf("��������Ŀ��\n"); // ������Ŀ��Ϣ
		gets(q->info); // �����Ŀ��Ϣ
		fprintf(fp,"%s\n",q->info); // �����Ŀ��Ϣ
		printf("������Aѡ�\n"); // ����Aѡ����Ϣ
		gets(q->singleChoiceA); // ���ѡ����Ϣ
		fprintf(fp,"%s\n",q->singleChoiceA); // ���Aѡ����Ϣ
		printf("������Bѡ�\n"); // ����Bѡ����Ϣ
		gets(q->singleChoiceB); // ���ѡ����Ϣ
		fprintf(fp,"%s\n",q->singleChoiceB); // ���Bѡ����Ϣ
		printf("������Cѡ�\n"); // ����Cѡ����Ϣ
		gets(q->singleChoiceC); // ���ѡ����Ϣ
		fprintf(fp,"%s\n",q->singleChoiceC); // ���Cѡ����Ϣ
		printf("������Dѡ�\n"); // ����Dѡ����Ϣ
		gets(q->singleChoiceD); // ���ѡ����Ϣ
		fprintf(fp,"%s\n",q->singleChoiceD); // ���Dѡ����Ϣ
		printf("������𰸣�\n"); // ���뵥ѡ���
		char c = getchar(); // ��ȡ��ѡ���
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // ����ѡ��𰸲�ΪA��B��C��D
		{
			printf("ֻ������A��B��C��D����һ���ַ���\n"); // ���������Ϣ
			getchar();// ������뻺��
			c = getchar(); // ���¶�ȡ��ѡ���
		}
		q->singleChoiceAns = c; // ���浥ѡ���Ϊ�ַ�A��B��C��D
		fprintf(fp,"%c\n",q->singleChoiceAns); // �����ѡ���
	    printf("�ɹ������Ŀ��ţ�%lld\n", q->qid); // �������Ŀ�ı��
	    qLibcTail->next = q; // ������Ŀ�ӵ����β��
	    qLibcTail = qLibcTail->next; // �������βָ��
	}
	else if(type == 2) // ����Ŀ����Ϊ2
	{
		struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // �����ڴ�ռ�
		fp=fopen(path_filling_blank,"a+"); // ���ļ�
		q->qid = nextQid_filling_blank++; // Ϊ����Ŀ��ӱ�� 
		fprintf(fp,"%lld\n",q->qid); // �����Ŀ���
		printf("��������Ŀ��\n"); // ������Ŀ��Ϣ
		gets(q->info); // �����Ŀ��Ϣ
		fprintf(fp,"%s\n",q->info); // �����Ŀ��Ϣ
		printf("������𰸣�\n"); // ����������
		char ans[MAXN]; // ����������
		gets(q->blanksAns); // ���������
		fprintf(fp,"%s\n",q->blanksAns); // ���������
	    printf("�ɹ������Ŀ��ţ�%lld\n", q->qid); // �������Ŀ�ı��
	    qLibfTail->next = q; // ������Ŀ�ӵ����β��
	    qLibfTail = qLibfTail->next; // �������βָ��
	}
	fclose(fp); // �ر��ļ�
}
void Delete() // ɾ����Ŀ 
{
	int type; // ��Ŀ����
	FILE *fp; // �����ļ�ָ��
	long long thisQid; // ��Ŀ��� 
	printf("������Ҫɾ����Ŀ�����ͣ���1����ѡ�⡾2������⣩��\n"); // ������Ŀ����
	scanf("%d", &type); // ָ����Ŀ����
	if(type != 1 && type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("ɾ����Ŀʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	if(type == 1) // ����Ŀ����Ϊ1
	{
		printf("������Ҫɾ����Ŀ�ı�ţ�\n"); // ������Ŀ���
		scanf("%lld", &thisQid); // ָ����Ŀ���
		struct Q_choice *p = qLibc; // ָ�����ͷ�� 
		while(p->next != NULL) // �������
		{
			if(p->next->qid == thisQid) // �ҵ�Ҫɾ������Ŀ
			{
				struct Q_choice *q = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // �½�����Ŀ
				q->next = p->next->next; // ����һ����ӵ���ǰ��ĺ���
				p->next = q->next; // ����ǰ��ӵ����ͷ��
				free(q); // �ͷ��ڴ�
				printf("ɾ���ɹ���\n"); // ���ɾ���ɹ���Ϣ
			}
			p = p->next; // ָ����һ����Ŀ
		}
		fp = fopen(path_choice, "w"); // ���ļ�
		p = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
		{
			fprintf(fp, "%lld\n",p->qid); // �����Ŀ���
			fprintf(fp, "%s\n",p->info); // �����Ŀ��Ϣ
			fprintf(fp, "%s\n",p->singleChoiceA); // ���Aѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceB); // ���Bѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceC); // ���Cѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceD); // ���Dѡ����Ϣ
			fprintf(fp, "%c\n",p->singleChoiceAns); // �����Ŀ�� 
			p = p->next; // ָ����һ����Ŀ
		}
		fclose(fp); // �ر��ļ�
	}
	else if(type == 2) // ����Ŀ����Ϊ2
	{
		printf("������Ҫɾ����Ŀ�ı�ţ�\n"); // ������Ŀ���
		scanf("%lld",&thisQid); // ָ����Ŀ���
		struct Q_filling_blank *p = qLibf; // ָ�����ͷ�� 
		fp=fopen(path_filling_blank, "w"); // ���ļ�
		while(p->next != NULL) // �������
		{
			if(p->next->qid == thisQid) // �ҵ�Ҫɾ������Ŀ
			{
				struct Q_filling_blank *q = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // �½�����Ŀ
				q->next = p->next->next; // ����һ����ӵ���ǰ��ĺ���
				p->next = q->next; // ����ǰ��ӵ����ͷ��
				free(q); // �ͷ��ڴ�
				printf("ɾ���ɹ���\n"); // ���ɾ���ɹ���Ϣ
			}
			p = p->next; // ָ����һ����Ŀ
		}
		fp=fopen(path_filling_blank, "w"); // ���ļ�
		p = qLibf->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
		{
			fprintf(fp, "%lld\n",p->qid); // �����Ŀ���
			fprintf(fp, "%s\n",p->info); // �����Ŀ��Ϣ
			fprintf(fp, "%s\n",p->blanksAns); // ���������
			p = p->next; // ָ����һ����Ŀ
		}
		fclose(fp); // �ر��ļ�
	}
}
void BackupAll() // �������
{
	FILE *fp1, *fp2; // �����ļ�ָ��
	fp1 = fopen(path_choice_bak, "w"); // ���ļ�
	fp2 = fopen(path_filling_blank_bak, "w"); // ���ļ�
	struct Q_choice *p1 = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
	struct Q_filling_blank *p2 = qLibf->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
	while(p1 != NULL) // �������
	{
		fprintf(fp1, "%lld\n",p1->qid); // �����Ŀ���
		fprintf(fp1, "%s\n",p1->info); // �����Ŀ��Ϣ
		fprintf(fp1, "%s\n",p1->singleChoiceA); // ���Aѡ����Ϣ
		fprintf(fp1, "%s\n",p1->singleChoiceB); // ���Bѡ����Ϣ
		fprintf(fp1, "%s\n",p1->singleChoiceC); // ���Cѡ����Ϣ
		fprintf(fp1, "%s\n",p1->singleChoiceD); // ���Dѡ����Ϣ
		fprintf(fp1, "%c\n",p1->singleChoiceAns); // �����Ŀ�� 
		p1 = p1->next; // ָ����һ����Ŀ
    }
    while(p2 != NULL) // �������
    {
    	fprintf(fp2, "%lld\n",p2->qid); // �����Ŀ���
		fprintf(fp2, "%s\n",p2->info); // �����Ŀ��Ϣ
		fprintf(fp2, "%s\n",p2->blanksAns); // ���������
		p2 = p2->next; // ָ����һ����Ŀ
	}
	fclose(fp1); // �ر��ļ�
	fclose(fp2); // �ر��ļ� 
	printf("���ݳɹ�!\n"); // �����Ϣ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}
void DeleteAll() // ɾ�����
{
    FILE *p1; // �����ļ�ָ��
    FILE *p2; // �����ļ�ָ��
	qLibc = (struct Q_choice*)malloc(sizeof(struct Q_choice)); // ���³�ʼ�����
	qLibf = (struct Q_filling_blank*)malloc(sizeof(struct Q_filling_blank)); // ���³�ʼ�����
	fopen(path_choice,"w"); // ���ļ�
	fopen(path_filling_blank,"w"); // ���ļ�
	printf("�ɹ�ɾ��ȫ����Ŀ��\n"); // ���ɾ���ɹ���Ϣ
}
void Modify() // �޸���Ŀ 
{
	FILE *fp; // �����ļ�ָ��
	long long thisQid; // ��Ŀ��� 
	int type; // ��Ŀ����
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); // ������Ŀ����
	scanf("%d", &type); // ָ����Ŀ����
	if(type != 1 && type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("�޸���Ŀʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	printf("������Ҫ�޸����ݵı�ţ�\n"); // ������Ŀ���
	scanf("%lld", &thisQid); // ָ����Ŀ���
	if(type == 1) // ����Ŀ����Ϊ1
	{
		struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(p->qid == thisQid) // �ҵ�Ҫ�޸ĵ���Ŀ
			{
				printf("��ѡ����Ҫ�޸���Ŀ��Ϣ���Ǵ𰸣���1����Ϣ��2���𰸡�0�����أ���\n"); // ����ѡ��
				{
					int option; // ѡ��
					scanf("%d", &option); // ָ��ѡ��
					if(option == 1) // �޸���Ŀ��Ϣ
					{
						printf("�����������޸����ݣ���A����B����C����D����������������ɡ�����\n"); // �����޸�����
						char c = getchar(); // ��ȡ�޸�����
						getchar(); // ������뻺��
						printf("�������޸ĺ����Ŀ���ݣ�\n"); // �����޸ĺ����Ŀ����
						getchar(); // ������뻺��
						switch(c) // �����޸�����ѡ���޸�λ��
						{
							case 'A': gets(p->singleChoiceA); break; // �޸�Aѡ����Ϣ
							case 'B': gets(p->singleChoiceB); break; // �޸�Bѡ����Ϣ
							case 'C': gets(p->singleChoiceC); break; // �޸�Cѡ����Ϣ
							case 'D': gets(p->singleChoiceD); break; // �޸�Dѡ����Ϣ
							default: gets(p->info); break; // �޸���Ŀ��Ϣ
						}	
					}
					else if(option == 2) // �޸ĵ�ѡ���
					{
						printf("�������޸ĺ�ĵ�ѡ��𰸣�\n"); // �����޸ĺ�ĵ�ѡ���
						getchar(); // ������뻺��
						char c = getchar(); // ��ȡ�޸ĺ�ĵ�ѡ���
						getchar(); // ������뻺��
						while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // ����ѡ��𰸲�ΪA��B��C��D
						{
							printf("ֻ������A��B��C��D����һ���ַ���\n"); // ���������Ϣ
							c = getchar(); // ���¶�ȡ�޸ĺ�ĵ�ѡ���
							getchar(); // ������뻺��
						}
						p->singleChoiceAns = c; // �޸ĵ�ѡ���
					}
				}	
			}
			p = p->next; // ָ����һ����Ŀ
		}
		fp = fopen(path_choice, "w"); // ���ļ�
		p = qLibc->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
		{
			fprintf(fp, "%lld\n",p->qid); // �����Ŀ���
			fprintf(fp, "%s\n",p->info); // �����Ŀ��Ϣ
			fprintf(fp, "%s\n",p->singleChoiceA); // ���Aѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceB); // ���Bѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceC); // ���Cѡ����Ϣ
			fprintf(fp, "%s\n",p->singleChoiceD); // ���Dѡ����Ϣ
			fprintf(fp, "%c\n",p->singleChoiceAns); // �����Ŀ�� 
			p = p->next; // ָ����һ����Ŀ
    	}
    	fclose(fp); // �ر��ļ�
	}
	else if(type == 2) // ����Ŀ����Ϊ2
	{
		struct Q_filling_blank *p = qLibf->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(p->qid == thisQid) // �ҵ�Ҫ�޸ĵ���Ŀ
			{
				printf("��ѡ����Ҫ�޸���Ŀ��Ϣ���Ǵ𰸣���1����Ϣ��2���𰸡�0�����أ���\n"); // ����ѡ��
				int option; // ѡ��
				scanf("%d", &option); // ָ��ѡ��
				if(option == 1) // �޸���Ŀ��Ϣ
				{
					printf("�������޸ĺ����Ŀ���ݣ�\n"); // �����޸ĺ����Ŀ����
					getchar(); // ������뻺��
					gets(p->info); // �޸���Ŀ��Ϣ
				}
				else if(option == 2) // �޸�������
				{
					printf("�������޸ĺ�������𰸣�\n"); // �����޸ĺ��������
					getchar(); // ������뻺��
					gets(p->blanksAns); // �޸�������
				}
			}
			p = p->next; // ָ����һ����Ŀ
		}
		fp = fopen(path_filling_blank, "w"); // ���ļ�
		p = qLibf->next; // ָ�����ͷ������һ����� ��ͷ��㲻�������ݣ�ֻ��ָ�룩 
		while(p != NULL) // �������
		{
    		fprintf(fp, "%lld\n",p->qid); // �����Ŀ���
			fprintf(fp, "%s\n",p->info); // �����Ŀ��Ϣ
			fprintf(fp, "%s\n",p->blanksAns); // ���������
			p = p->next; // ָ����һ����Ŀ
    	}
    	fclose(fp); // �ر��ļ�
	}
}
void Search() // ��Ŀ��ѯ 
{
	int type, flag = 0; // ��Ŀ���͡�����Ƿ��ҵ���Ŀ
	printf("������Ҫ��ѯ����Ŀ����([1]ѡ����[2]�����)��\n"); // ������Ŀ����
	scanf("%d",&type); // ָ����Ŀ����
	if(type != 1 && type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("��ѯʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	if(type == 1) // ����Ŀ����Ϊ1
	{
		long long thisQid; // ��Ŀ��� 
		printf("������Ҫ��ѯ��Ŀ�ı�ţ�\n"); // ������Ŀ���
		scanf("%lld", &thisQid); // ָ����Ŀ���
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
	else if(type == 2) // ����Ŀ����Ϊ2
	{
		long long thisQid; // ��Ŀ��� 
		printf("������Ҫ��ѯ��Ŀ�ı�ţ�\n"); // ������Ŀ���
		scanf("%lld", &thisQid); // ָ����Ŀ���
		struct Q_filling_blank *p = qLibf->next; // ָ�����ͷ�� 
		while(p != NULL) //	�������
		{
			if(p->qid == thisQid) // �ҵ�Ҫ��ѯ����Ŀ
			{
				printf("\n��Ŀ:%s\n��:%s\n", p->info, p->blanksAns); // �����Ŀ��Ϣ
				flag = 1; // ����ҵ���Ŀ
				break; // �˳�ѭ��
			}
			p = p->next; // ָ����һ����Ŀ
		}
	}
	if(!flag) // ��δ�ҵ���Ŀ
		printf("δ��ѯ����Ч����Ŀ��Ϣ\n"); // ���δ�ҵ���Ŀ��Ϣ
	return; // �˳�����
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
	while(q2 != NULL) // �������
	{
		fibNum++; // �������+1
		totalNum++; // ������+1
		q2 = q2->next; // ָ����һ����Ŀ
	}    
	choiceNum = scNum; // ��ѡ������ֵ��ȫ�ֱ���
	fillingBlankNum = fibNum; // ���������ֵ��ȫ�ֱ���
	printf("����%lld����Ŀ(��ѡ�⣺%lld������⣺%lld)\n", totalNum, scNum, fibNum); // �����Ŀͳ����Ϣ
}
void FindSpecificContent() // ��ѯ�ض����� 
{
	printf("��������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); // ������Ŀ����
	int type; // ��Ŀ����
	scanf("%d", &type); // ָ����Ŀ����
	getchar(); // ������뻺��
	if(type != 1 && type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("�����Ŀʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	int flag = 0; // ����Ƿ��ҵ���Ŀ
	char sp[1000]; // �ض�����
	printf("������������������ض����ݣ�\n"); // �����ض�����
	getchar(); // ������뻺��
	gets(sp); // �����ض�����
	if(type == 1) // ����Ŀ����Ϊ1
	{
		struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(strstr(p->info,sp) != NULL) // ����Ŀ��Ϣ�а����ض�����
			{
				flag = 1; // ����ҵ���Ŀ
				printf("��ѯ��������������Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
				printf("��Ŀ���ͣ���ѡ��\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%c\n", p->info, p->singleChoiceAns); // �����Ŀ��Ϣ
			}
			p = p->next; // ָ����һ����Ŀ
		}
	}
	else if(type == 2) // ����Ŀ����Ϊ2
	{
		struct Q_filling_blank *p = qLibf->next; // ָ�����ͷ�� 
		while(p != NULL) // �������
		{
			if(strstr(p->info,sp) != NULL) // ����Ŀ��Ϣ�а����ض�����
			{
				flag = 1; // ����ҵ���Ŀ
				printf("��ѯ��������������Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
				printf("��Ŀ���ͣ������\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%s\n", p->info, p->blanksAns); // �����Ŀ��Ϣ
			}	
			p = p->next; // ָ����һ����Ŀ
		}
	}	
	if(!flag) // ��δ�ҵ���Ŀ
		printf("δ�ҵ�����Ŀ��\n"); // ���δ�ҵ���Ŀ��Ϣ
}
void RandomQandA() // ����������� 
{
	long long order = 1,scNum,fibNum,QidFlag[MAXN] = {0}; // ����˳�򡢵�ѡ�����������������Ŀ��ű������ 
	printf("���������ɵĵ�ѡ����Ŀ����\n"); // ���뵥ѡ����Ŀ��
	scanf("%lld", &scNum); // ָ����ѡ����Ŀ��
	printf("���������ɵ��������Ŀ����\n"); // �����������Ŀ��
	scanf("%lld", &fibNum); // ָ���������Ŀ��
	Statistic(); // ͳ����Ŀ 
	if(scNum > choiceNum) // ����ѡ����ⲻ�����
	{
		printf("��ѡ����ⲻ����䣡\n"); // ���������Ϣ
		return; // �˳�����
	}
	else if(fibNum > fillingBlankNum) // ���������ⲻ�����
	{
		printf("�������ⲻ����䣡\n"); // ���������Ϣ
		return; // �˳�����
	}
	FILE *fp1 = fopen("exam.txt", "w"); // ��������
    FILE *fp2 = fopen("answer.txt", "w"); // ������ 
	// �����ѡ��ģ�� 
	fprintf(fp1, "һ����ѡ��\n"); // �����Ŀ���� 
	fprintf(fp2, "һ����ѡ��\n"); // �����Ŀ���� 
	while(scNum > 0) // ѭ�����ɵ�ѡ��
	{
		long long randomQid = 1 + rand() % (nextQid_choice - 1); // ����[1, qid max]�����ڵ������� 
		if(!QidFlag[randomQid]) // ��qidδ��ǣ���δ���� 
		{
			struct Q_choice *p = qLibc->next; // ָ�����ͷ�� 
			while(p != NULL) // �������
			{
				if(p->qid == randomQid) // �ҵ���ѡ��
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp1, "��Ŀ��%s\n", p->info); // �����Ŀ��Ϣ
					fprintf(fp1, "A��%s\n", p->singleChoiceA); // ���Aѡ����Ϣ
					fprintf(fp1, "B��%s\n", p->singleChoiceB); // ���Bѡ����Ϣ
					fprintf(fp1, "C��%s\n", p->singleChoiceC); // ���Cѡ����Ϣ
					fprintf(fp1, "D��%s\n", p->singleChoiceD); // ���Dѡ����Ϣ
					fprintf(fp2, "��Ŀѡ�%c\n", p->singleChoiceAns); // �����Ŀѡ��
					QidFlag[randomQid] = 1; // ���qid
					order++; // ����˳��+1
					scNum--; // ��ѡ����-1
					break; // �˳�ѭ�� 
				}
				p = p->next; // ָ����һ����Ŀ
			}
		}
	}
	fprintf(fp1, "==============================\n"); // ����ָ���
	fprintf(fp2, "==============================\n"); // ����ָ���
	// ��������ģ�� 
	fprintf(fp1, "���������\n"); // �����Ŀ���� 
	fprintf(fp2, "���������\n"); // �����Ŀ���� 
	order = 1; // ����˳���ʼ�� 
	while(fibNum > 0) // ѭ�����������
	{
		long long randomQid = 1 + rand() % (nextQid_filling_blank - 1); // ����[1, qid max]�����ڵ������� 
		if(!QidFlag[randomQid]) // ��qidδ��ǣ���δ���� 
		{
			struct Q_filling_blank *p = qLibf->next; // ָ�����ͷ�� 
			while(p != NULL) // �������
			{
				if(p->qid == randomQid) // �ҵ������
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp1, "��Ŀ��%s\n", p->info); // �����Ŀ��Ϣ
					fprintf(fp2, "��Ŀ��%s\n", p->blanksAns); // �����Ŀ��
					QidFlag[randomQid] = 1; // ���qid
					order++; // ����˳��+1
					fibNum--; // �������-1
					break; // �˳�ѭ�� 
				}
				p = p->next; // ָ����һ����Ŀ
			}
		}
	}
	fclose(fp1); // �ر��ļ� 
	fclose(fp2); // �ر��ļ� 
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
		q->qid = thisQid; // ��Ŀ��Ÿ�ֵ 
		fscanf(fp,"%s\n",&q->info); // ��Ŀ��Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->singleChoiceA); // Aѡ����Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->singleChoiceB); // Bѡ����Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->singleChoiceC); // Cѡ����Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->singleChoiceD); // Dѡ����Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->singleChoiceD); // ѡ����Ϣ��ֵ 
		fscanf(fp,"%c\n",&q->singleChoiceAns); // �𰸸�ֵ 
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
		q->qid = thisQid; // ��Ŀ��Ÿ�ֵ 
		fscanf(fp,"%s\n",&q->info); // ��Ŀ��Ϣ��ֵ 
		fscanf(fp,"%s\n",&q->blanksAns); // �𰸸�ֵ 
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
		getchar(); // ������뻺��
		system("cls"); // ���� 
	}
}