
#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
int Available[3]={3,3,2};
int Max[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
int Need[5][3]={{7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1}};
int Allocation[5][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int Work[3];
bool Finish[5];
vector<int> safeSeq;

void showSafe(int *work,int i)
{
	cout<<"P"<<i<<"\t";
	for(int j=0;j<3;j++)
	{
		std::cout<<std::left<<std::setw(3)<<work[j];
	}
	cout<<" \t";
	for(int j=0;j<3;j++)
	{
		std::cout<<std::left<<std::setw(3)<<Need[i][j];
	}
	cout<<" \t";
	for(int j=0;j<3;j++)
	{
		std::cout<<std::left<<std::setw(3)<<Allocation[i][j];
	}
	cout<<" \t";
	for(int j=0;j<3;j++)
	{
		std::cout<<std::left<<std::setw(3)<<work[j]+Allocation[i][j];
	}
	cout<<" \t"<<boolalpha<<Finish[i]<<endl;		//�������Ϊbool�� 
}
bool safeCheck()
{
	int m,j;
	cout<<"������Ҫ����ĸ�ʱ�̵İ�ȫ���У�";
	cin>>m;
	cout<<endl<<"T"<<m<<"ʱ�̰�ȫ�Լ����..."<<endl;
	cout<<"\tWORK  \t\tNEED\t\tALLO\t\tWORK+ALLO\tFINISH"<<endl;
	int count = 0;
	safeSeq.clear();
	for(int i=0;i<3;i++)
	{
		Work[i]=Available[i];
	}
	for(int i=0;i<5; i++)
	{
		Finish[i]=false;
	}for(int k=0;k<5;k++)
	{
		for(int i=0;i<5;i++)
		{
			if(Finish[i]==false)
			{
				count=0;
				for(int j=0;j<3;j++)
				{
					if(Need[i][j]<=Work[j])
						count++;
				}
				if(count==3)	//������Դ������need 
				{
					Finish[i]=true;
					showSafe(Work,i);
					safeSeq.push_back(i);
						for(int j=0;j<3;j++)
					{
						Work[j]=Work[j]+Allocation[i][j];
					}
				}
			}
		}
	}
	count = 0;
	for(int i = 0;i<5;i++)
	{
		if(Finish[i]==true)
			count++;
	}
	if(count==5)	//���н��̶���ȫ�ŷ��� 
		return true;
	else
		return false;

}
bool applyCheck()
{
	int a;
	int request[3];
	cout<<"��������Ҫ������Դ�Ľ��̺ţ�0-4��:";
	cin>>a;
	if(a!=0&&a!=1&&a!=2&&a!=3&&a!=4)
	{
		cout<<"������Դ���̺Ŵ��󣬳������";
		return false; 
	 } 
	cout<<"��������Ҫ�������Դ����";
	for(int i=0;i<3;i++)
		cin>>request[i];
	for(int i=0;i<3;i++)
	{
		if(request[i]<=Need[a][i])
		{
			if(request[i]<=Available[i])
			{
				Available[i]=Available[i]-request[i];
				Allocation[a][i]=Allocation[a][i]+request[i];
				Need[a][i]=Need[a][i]-request[i];
			}
			else{
				cout<<"����Ҫ����ʱ�޷����㣬����BLOCK������������~"<<endl;
				return true;
			}
		}
		else
		{
			cout<<"����Ҫ�󳬳�����Ҫ��Χ������ERROR�����������룡"<<endl;
			return true;
		}
	}
	bool sflag =safeCheck();
	if(sflag)
	{
		cout << "����һ����ȫ����Ϊ��" <<endl;
		for (int i=0;i<safeSeq.size();i++)
			cout<<"P"<<safeSeq[i]<<",";
		cout<<endl;
	}
	else{
		cout<<"δ�ҵ���ȫ���У��������佫����ϵͳ���벻��ȫ״̬�����������������������������Դ����"<<endl;
		for(int i=0;i<3;i++)
		{
			Available[i]=Available[i]+request[i];		//�黹��Դ 
			Allocation[a][i]=Allocation[a][i]-request[i];
			Need[a][i]=Need[a][i]+request[i];
		}
	}
	return true;
}
int main()
{

	bool flag=safeCheck();
	if(flag)
	{
		cout << "����һ����ȫ����Ϊ��" <<endl;
		for (int i=0;i<safeSeq.size();i++)
			cout<<"P"<<safeSeq[i]<<",";
		cout<<endl;
	}
	bool flag1=applyCheck();
	while(flag1)
	{
		flag1=applyCheck();
	}
	return 0;
}



