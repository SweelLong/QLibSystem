#include <stdio.h> // ������׼�������ͷ�ļ� 
#include <stdlib.h> // ������׼��ͷ�ļ� 
#include <string.h> // �����ַ���ͷ�ļ� 
#include <time.h> // ����ʱ��ͷ�ļ����ɵ������������
#define ll long long // ��д������ 
#define MAXN 1000 // �����������߽� 
ll nextQid = 1; // ��Ŀ��ŵ����ֵ + 1 
struct Q // ��Ŀ�ṹ�壬������Ŀ��ز��� 
{
	ll qid; // ��Ŀ��� 
	int type; // ��Ŀ���ͣ���1����ѡ�⡾2������⣩ 
	char info[MAXN]; // ��Ŀ��Ϣ 
	char singleChoiceA[MAXN]; // ����Aѡ�����Ϣ 
	char singleChoiceB[MAXN]; // ����Bѡ�����Ϣ 
	char singleChoiceC[MAXN]; // ����Cѡ�����Ϣ 
	char singleChoiceD[MAXN]; // ����Dѡ�����Ϣ 
	char singleChoiceAns; // ���浥ѡ���Ϊ�ַ�A��B��C��D 
	char blanksAns[MAXN]; // ����������Ϊ�ַ��� 
	struct Q *next; // ָ����һ����Ŀ��ָ�� 
} *qLib; // ȫ����Ŀ������⣩����main��ڴ�����ֵ
void QlibAdd() // �����Ŀ 
{
	struct Q *q = (struct Q*)malloc(sizeof(struct Q)); // �½�����Ŀ 
	printf("�������Ŀ���ͣ���1����ѡ�⡾2������⣩��\n"); // ������Ŀ����
	scanf("%d", &q->type); // ָ����Ŀ����
	getchar(); // ������뻺��
	if(q->type != 1 && q->type != 2) // ����Ŀ���Ͳ�Ϊ1��2
	{
		printf("�����Ŀʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
		return; // �˳�����
	}
	printf("�������Ŀ��Ϣ��\n"); // ������Ŀ��Ϣ
	gets(q->info); // �����Ŀ��Ϣ
	if(q->type == 1) // ����Ŀ����Ϊ1
	{
		printf("�����Aѡ�����Ϣ��\n"); // ����Aѡ����Ϣ
		gets(q->singleChoiceA); // ���Aѡ����Ϣ
		printf("�����Bѡ�����Ϣ��\n"); // ����Bѡ����Ϣ
		gets(q->singleChoiceB); // ���Bѡ����Ϣ
		printf("�����Cѡ�����Ϣ��\n"); // ����Cѡ����Ϣ
		gets(q->singleChoiceC); // ���Cѡ����Ϣ
		printf("�����Dѡ�����Ϣ��\n"); // ����Dѡ����Ϣ
		gets(q->singleChoiceD); // ���Dѡ����Ϣ
		printf("����뵥ѡ��𰸣�\n"); // ���뵥ѡ���
		char c = getchar(); // ��ȡ��ѡ���
		while(c != 'A' && c != 'B' && c != 'C' && c != 'D') // ����ѡ��𰸲�ΪA��B��C��D
		{
			// ����ѡ��𰸲�ΪA��B��C��D
			printf("ֻ������A��B��C��D����һ���ַ���\n"); // ���������Ϣ
			getchar();// ������뻺��
			c = getchar(); // ���¶�ȡ��ѡ���
		}
		q->singleChoiceAns = c; // ���浥ѡ���Ϊ�ַ�A��B��C��D
	}
	else if(q->type == 2) // ����Ŀ����Ϊ2
	{
		printf("����������𰸣�\n"); // ����������
		gets(q->blanksAns); // ���������
	}
	q->qid = nextQid++; // Ϊ����Ŀ��ӱ�� 
	printf("�ɹ������Ŀ��ţ�%lld\n", q->qid); // �������Ŀ�ı��
	q->next = qLib->next; // ������ӵ�����ĺ���
	qLib->next = q; // ���Ᵽ����Ŀ�������ǰ��
}
void QlibDelete() // ɾ����Ŀ 
{
	ll thisQid; // ��Ŀ��� 
	printf("������Ҫɾ����Ŀ�ı�ţ�\n"); // ������Ŀ���
	scanf("%lld", &thisQid); // ָ����Ŀ���
	struct Q *p = qLib; // ָ�����ͷ�� 
	while(p->next != NULL) // �������
	{
		if(p->next->qid == thisQid) // �ҵ�Ҫɾ������Ŀ
		{
			struct Q *q = (struct Q*)malloc(sizeof(struct Q)); // �½�����Ŀ
			q->next = p->next->next; // ����һ����ӵ���ǰ��ĺ���
			p->next = q->next; // ����ǰ��ӵ����ͷ��
			free(q); // �ͷ��ڴ�
			printf("ɾ���ɹ���\n"); // ���ɾ���ɹ���Ϣ
			return; // �˳�����
		}
		p = p->next; // ָ����һ����Ŀ
	}
	printf("ɾ��ʧ�ܣ�\n"); // ���ɾ��ʧ����Ϣ
}
void BackupAll() // ������� 
{
	FILE *fp1, *fp2; // �����ļ�ָ��
	fp1 = fopen("��ѡ����ⱸ��.txt", "w"); // ���ļ�
	fp2 = fopen("���������ⱸ��.txt", "w"); // ���ļ�
	struct Q *p = qLib; // ָ�����ͷ�� 
	while(p->next != NULL) // �������
	{
		if(p->type == 1) // ����Ŀ����Ϊ1
		{
			fprintf(fp1, "��Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
			fprintf(fp1, "��Ŀ��Ϣ��%s\n", p->info); // �����Ŀ��Ϣ
			fprintf(fp1, "Aѡ����Ϣ��%s\n", p->singleChoiceA); // ���Aѡ����Ϣ
			fprintf(fp1, "Bѡ����Ϣ��%s\n", p->singleChoiceB); // ���Bѡ����Ϣ
			fprintf(fp1, "Cѡ����Ϣ��%s\n", p->singleChoiceC); // ���Cѡ����Ϣ
			fprintf(fp1, "Dѡ����Ϣ��%s\n", p->singleChoiceD); // ���Dѡ����Ϣ
			fprintf(fp1, "��Ŀѡ�%c\n", p->singleChoiceAns); // �����Ŀѡ��
			fprintf(fp1, "=============================="); // ����ָ���
		}
		else if(p->type == 2) // ����Ŀ����Ϊ2
		{
			fprintf(fp2, "��Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
			fprintf(fp2, "��Ŀ��Ϣ��%s\n", p->info); // �����Ŀ��Ϣ
			fprintf(fp2, "��Ŀ�𰸣�%s\n", p->blanksAns); // �����Ŀ��
			fprintf(fp1, "=============================="); // ����ָ���
		}
		p = p->next; // ָ����һ����Ŀ
	}
	fclose(fp1); // �ر��ļ�
	fclose(fp2); // �ر��ļ�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}
void DeleteAll() // ɾ�����
{
	qLib = (struct Q*)malloc(sizeof(struct Q)); // ���³�ʼ�����
	printf("�ɹ�ɾ��ȫ����Ŀ��\n"); // ���ɾ���ɹ���Ϣ
}
void ModifyQ() // �޸���Ŀ 
{
	ll thisQid; // ��Ŀ��� 
	printf("������Ҫ�޸����ݵı�ţ�\n"); // ������Ŀ���
	scanf("%lld", &thisQid); // ָ����Ŀ���
	struct Q *p = qLib->next; // ָ�����ͷ�� 
	while(p != NULL) // �������
	{
		if(p->qid == thisQid) // �ҵ�Ҫ�޸ĵ���Ŀ
		{
			printf("��ѡ����Ҫ�޸���Ŀ��Ϣ���Ǵ𰸣���1����Ϣ��2���𰸡�0�����أ���\n"); // ѡ���޸�����
			int option; // ѡ��
			scanf("%d", &option); // ָ��ѡ��
			if(option == 1) // ���޸���Ŀ��Ϣ
			{
				if(p->type == 1) // ����Ŀ����Ϊ1
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
					}			
				}
				else
				{
					printf("�������޸ĺ����Ŀ���ݣ�\n"); // �����޸ĺ����Ŀ����
					getchar(); // ������뻺��
					gets(p->info); // �޸���Ŀ��Ϣ
				}
			}
			else if(option == 2) // ���޸���Ŀ��
			{
				if(p->type == 1) // ����Ŀ����Ϊ1
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
				else if(p->type == 2) // ����Ŀ����Ϊ2
				{
					printf("�������޸ĺ�������𰸣�\n"); // �����޸ĺ��������
					getchar(); // ������뻺��
					gets(p->blanksAns); // �޸�������
				}
			}
			return; // �˳�����
		}
		p = p->next; // ָ����һ����Ŀ
	}
	printf("δ�ҵ�����Ŀ��\n"); // ���δ�ҵ�����Ŀ��Ϣ
}
void Qquery() // ��Ŀ��ѯ 
{
	ll thisQid; // ��Ŀ��� 
	printf("������Ҫ��ѯ���ݵı�ţ�\n"); // ������Ŀ���
	scanf("%lld", &thisQid); // ָ����Ŀ���
	struct Q *p = qLib->next; // ָ�����ͷ�� 
	while(p != NULL) // �������
	{
		if(p->qid == thisQid) // �ҵ�Ҫ��ѯ����Ŀ
		{
			if(p->type == 1) // ����Ŀ����Ϊ1
			{
				printf("��Ŀ���ͣ���ѡ��\n��Ŀ��Ϣ��%s\nAѡ����Ϣ��%s\nBѡ����Ϣ��%s\nCѡ����Ϣ��%s\nDѡ����Ϣ��%s\n��Ŀ�𰸣�%c\n", p->info, p->singleChoiceA, p->singleChoiceB, p->singleChoiceC, p->singleChoiceD, p->singleChoiceAns); // �����Ŀ��Ϣ
			}
			else if(p->type == 2) // ����Ŀ����Ϊ2
			{
				printf("��Ŀ���ͣ������\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%s\n", p->info, p->blanksAns); // �����Ŀ��Ϣ
			}
			else // ����Ŀ���Ͳ�Ϊ1��2
			{
				printf("��ѯʧ�ܣ�δ֪����Ŀ����\n"); // ���������Ϣ
			}
			return; // �˳�����
		}
		p = p->next; // ָ����һ����Ŀ
	}
	printf("δ�ҵ�����Ŀ��\n"); // ���δ�ҵ�����Ŀ��Ϣ
}
void Statistic() // ��Ŀͳ�� 
{
	ll scNum = 0, fibNum = 0, totalNum = 0; // ��ѡ�⡢����⡢������
	struct Q *p = qLib->next; // ָ�����ͷ�� 
	while(p != NULL) // �������
	{
		printf("��ѯ����Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
		if(p->type == 1) // ����Ŀ����Ϊ1
			scNum++; // ��ѡ����+1
		else if(p->type == 2) // ����Ŀ����Ϊ2
			fibNum++; // �������+1
		totalNum++; // ������+1
		p = p->next; // ָ����һ����Ŀ
	}
	printf("����%lld����Ŀ(��ѡ�⣺%lld������⣺%lld)\n", totalNum, scNum, fibNum); // �����Ŀͳ����Ϣ
}
void FindSpecificContent() // ��ѯ�ض����� 
{
	int flag = 0; // ����Ƿ��ҵ���Ŀ
	char sp[1000]; // �ض�����
	printf("������������������ض����ݣ�\n"); // �����ض�����
	getchar(); // ������뻺��
	gets(sp); // �����ض�����
	struct Q *p = qLib->next; // ָ�����ͷ�� 
	while(p != NULL) // �������
	{
		if(strstr(p->info,sp) != NULL) // ����Ŀ��Ϣ�а����ض�����
		{
			printf("��ѯ��������������Ŀ��ţ�%lld\n", p->qid); // �����Ŀ���
			if(p->type == 1) // ����Ŀ����Ϊ1
			{
				printf("��Ŀ���ͣ���ѡ��\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%c\n", p->info, p->singleChoiceAns); // �����Ŀ��Ϣ
			}
			else if(p->type == 2) // ����Ŀ����Ϊ2
			{
				printf("��Ŀ���ͣ������\n��Ŀ��Ϣ��%s\n��Ŀ�𰸣�%s\n", p->info, p->blanksAns); // �����Ŀ��Ϣ
			}
			flag = 1; // ����ҵ���Ŀ
		}
		p = p->next; // ָ����һ����Ŀ
	}
	if(!flag) // ��δ�ҵ���Ŀ
	{
		printf("δ�ҵ�����Ŀ��\n"); // ���δ�ҵ���Ŀ��Ϣ
	}
}
void RandomQandA() // ����������� 
{
	FILE *fp1 = fopen("exam.txt", "w"); // ��������
    FILE *fp2 = fopen("answer.txt", "w"); // ������ 
	ll order = 1, scNum, fibNum, QidFlag[MAXN] = {0}; // ����˳�򡢵�ѡ�����������������Ŀ��ű������ 
	printf("���������ɵĵ�ѡ����Ŀ����\n"); // ���뵥ѡ����Ŀ��
	scanf("%lld", &scNum); // ָ����ѡ����Ŀ��
	printf("���������ɵ��������Ŀ����\n"); // �����������Ŀ��
	scanf("%lld", &fibNum); // ָ���������Ŀ��
	// �����ѡ��ģ�� 
	fprintf(fp1, "һ����ѡ��\n"); // �����Ŀ���� 
	fprintf(fp2, "һ����ѡ��\n"); // �����Ŀ���� 
	while(scNum > 0) // ѭ�����ɵ�ѡ��
	{
		ll randomQid = 1 + rand() % (nextQid - 1); // ����[1, qid max]�����ڵ������� 
		if(!QidFlag[randomQid]) // ��qidδ��ǣ���δ���� 
		{
			struct Q *p = qLib->next; // ָ�����ͷ�� 
			while(p != NULL) // �������
			{
				if(p->qid == randomQid && p->type == 1) // �ҵ���ѡ��
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp1, "��Ŀ��Ϣ��%s\n", p->info); // �����Ŀ��Ϣ
					fprintf(fp1, "Aѡ����Ϣ��%s\n", p->singleChoiceA); // ���Aѡ����Ϣ
					fprintf(fp1, "Bѡ����Ϣ��%s\n", p->singleChoiceB); // ���Bѡ����Ϣ
					fprintf(fp1, "Cѡ����Ϣ��%s\n", p->singleChoiceC); // ���Cѡ����Ϣ
					fprintf(fp1, "Dѡ����Ϣ��%s\n", p->singleChoiceD); // ���Dѡ����Ϣ
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
		ll randomQid = 1 + rand() % (nextQid - 1); // ����[1, qid max]�����ڵ������� 
		if(!QidFlag[randomQid]) // ��qidδ��ǣ���δ���� 
		{
			struct Q *p = qLib->next; // ָ�����ͷ�� 
			while(p != NULL) // �������
			{
				if(p->qid == randomQid && p->type == 2) // �ҵ������
				{
					fprintf(fp1, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp2, "(%lld.)��Ŀ��ţ�%lld\n", order, p->qid); // �����Ŀ���
					fprintf(fp1, "��Ŀ��Ϣ��%s\n", p->info); // �����Ŀ��Ϣ
					fprintf(fp2, "��Ŀ�𰸣�%s\n", p->blanksAns); // �����Ŀ��
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
	qLib = (struct Q*)malloc(sizeof(struct Q)); // Ϊ��⸳���ֵ 
	int option; // ������� 
	printf("*** || -��ӭʹ���Ծ����ϵͳ- || ***\n"); // �����ӭ��Ϣ 
	while(1) // �ṩ�˵���ѡ���ܣ��ڽ���ĳһ���ܺ������ṩ�˵� 
	{
		printf("==============================\n�˵���\n��1���������\n��2������ɾ��\n��3������ȫ����Ŀ\n��4��ɾ��ȫ����Ŀ\n��5�������޸�\n��6�������ѯ\n��7��ͳ����Ŀ\n��8����ѯ�ض�����\n��9�������������\n��0���˳�\n==============================\n"); // ����˵� 
		scanf("%d", &option); // ���빦����� 
		switch(option) // ���ݹ������ѡ����
		{
			case 1: QlibAdd(); break; // ������� 
			case 2: QlibDelete(); break; // ����ɾ�� 
			case 3: BackupAll(); break; // ����ȫ����Ŀ 
			case 4: DeleteAll(); break; // ɾ��ȫ����Ŀ 
			case 5: ModifyQ(); break; // �����޸� 
			case 6: Qquery(); break; // �����ѯ 
			case 7: Statistic(); break; // ͳ����Ŀ 
			case 8: FindSpecificContent(); break; // ��ѯ�ض����� 
			case 9: RandomQandA(); break; // ����������� 
			default: return 0; // �˳����� 
		}
	}
}
