#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<time.h>
#include<iomanip>
using namespace std;
struct Page{
	int PageSize;		//ҳ���С 
	int Pagedeviation;	//ҳ��ƫ����
	int Pagecount;		//ҳ�������
	int block[10];		//�������  
};
struct Segment{
	float length[10];		//�γ�
	int address[10];	//��ַ
	int Segmentcount;	//�α������
	 
};
Segment segment;
Page page;
static int k=1024;
bool in_range(int x, int a, int b)
{
    return (x - a) * (x - b) < 0;
}
void Rand1()
{
	srand((unsigned)time(NULL));   //���������
        
    for (int i = 0; i < 10; i++)
    {
      int   x = rand() % 10;           //����0��9�������
        for (int j = 0; j < i; j++)
            while (x == page.block[j])      //���x��ǰ�������ͬ��������һ����
            {
                x = rand() % 10;
                j = 0;
            }
        page.block[i] = x;
    }

}
bool PageMethod()
{
	int logicAddress;
	int physicAddress;
	int flag1=0,flag2=0;
	int pin=1;		//�����жϿ���Ƿ��ظ� 
	cout<<"������ÿҳ��С����0-1K��1-2K��2-4K��3-���ѡ��"<<endl;
		cin>>flag1;
		srand((unsigned)time(NULL));   //���������
		if(flag1==3)
		{
			flag1=rand()%3;
		}
		if(flag1==0){
			page.PageSize=1024;
		}else if(flag1==1)
		{
			page.PageSize=2048;
		}
		else if(flag1==2)
		{
			page.PageSize=4096;
		}
//		cout<<"ҳ���СΪ��"<<page.PageSize<<endl;

	cout<<"������ҳ�����������5��10֮�����������˵㣩"<<endl;
	cin>>page.Pagecount;
	while(pin==1)
{

	cout<<"������ҳ����ÿҳ��Ӧ�Ŀ�ţ���0-�ֶ����룻1-�������0��10֮��ķ��ظ�������Ϊ��ţ�"<<endl;
	cin>>flag2;
	if(flag2==0)
	{
		for(int i=0;i<page.Pagecount;i++)
		{
			cin>>page.block[i];	
		}
		//���ж����޿���ظ�
		for(int i=0;i<page.Pagecount;i++)
		{
			int tmp=page.block[i];
			int pin1=0;
			for(int j=i+1;j<page.Pagecount;j++)
			{
				if(tmp==page.block[j])
				{
					cout<<"������Ŀ���������"<<i<<"��ҳ������Ŀ���ظ��������������"<<j<<"��ҳ���Ӧ�Ŀ�ţ�"<<endl;
					pin1=1;
					break;
				}
			}
			if(pin1==1)
			{
				pin=1;
				break;
			}else
			{
				pin=0;
			}
		}
	}
	else{
		Rand1();
		pin=0;
	}
}
	//�����ʼ������
 	cout<<"��ѡ���˷�ҳ��ʽ��������������£�"<<endl;
 	cout<<"ÿҳ��С"<<page.PageSize/1024<<"K,ҳ��Ϊ"<<endl;
 	cout<<"ҳ��    ���"<<endl;
 	for(int i=0;i<page.Pagecount;i++)
 	{
 		std::cout<<std::left<<std::setw(3)<<i<<"\t";
	 	std::cout<<std::left<<std::setw(3)<<page.block[i]<<"\t";
	 	cout<<endl;
	}
   //
	cout<<"�������߼���ַ��";
	cin>>logicAddress;
	int p=logicAddress/page.PageSize;					//ҳ�� 
	page.Pagedeviation=logicAddress%page.PageSize;		//��ҳƫ
	int b=page.block[p];								//����
	physicAddress=b*page.PageSize+page.Pagedeviation;
//	cout<<"���ڴ�Ϊ��"<<page.PageSize*page.Pagecount<<endl;
	if(logicAddress>page.PageSize*page.Pagecount){
		cout<<"������ĵ�ַ����������������룡"<<endl;
		return false;
	}else{
	cout<<"��ѡ���˷�ҳ��ʽ��������߼���ַΪ"<<logicAddress<<",���Ӧ��ҳ��Ϊ"<<p<<",ҳƫ��Ϊ"<<page.Pagedeviation<<",�õ�ַ��Ӧ�Ŀ��Ϊ"<<b<<",��ƫ��Ϊ"<<page.Pagedeviation<<",�����ַΪ"<<physicAddress<<endl;
	}
	cout<<"�Ƿ�Ҫ������(y/n)"<<endl;
	char c;
	cin>>c;
	if(c=='y')
	{
		return false;
	}else 
	return true;
}
void Rand2(int n)			//��ַ��������� 
{
	srand((unsigned)time(NULL));   //���������
        
    for (int i = 0; i <	n; i++)
    {
      int   x = rand() % 100;           //����0��100�������
        for (int j = 0; j < i; j++)
            while (x == segment.address[j])      //���x��ǰ�������ͬ��������һ����
            {
                x = rand() % 10;
                j = 0;
            }
        segment.address[i]= x*k;
    }
}
void Rand3(int n)				//�γ���������� 
{
	srand((unsigned)time(NULL));   //���������
	int a[4]={1,2,4,8}; 
    for (int i = 0; i < n; i++)
    {
      int   random = rand() * 10%4;           //����0��9�������
		int x = a[random];
        segment.length[i] = x*k;
    }

}
bool SegmentMethod(){
	int logicAddress;
	int physicAddress;
	int flag1,flag2;			
	cout<<"������α����������5��10֮�����������˵㣩"<<endl;
	cin>>segment.Segmentcount;
	cout<<"������ҳ����ÿ�ζ�Ӧ�Ļ�ַ�Ͷγ�����0-�ֶ����룻1-������ɣ�"<<endl;
	cin>>flag1;
	if(flag1==0)
	{
		for(int i=0;i<segment.Segmentcount;i++)
		{
			cin>>segment.address[i]>>segment.length[i];
			cout<<endl;
			segment.address[i]*=k;
			segment.length[i]*=k;
		}
	}
	else{
		Rand2(segment.Segmentcount);
		Rand3(segment.Segmentcount);
	}
	//�жϻ�ַ��γ��Ƿ��ͻ
	int tmp1=0;		//��¼��ͻ�Ķκ�
	int tmp2=0; 
	int flag3=1;	//�жϳ�ͻ�ı�־ 
	for(int i=0;i<segment.Segmentcount;i++)
	{
		for(int j=i+1;j<segment.Segmentcount;j++)
		{
			if(segment.address[j]<segment.address[j-1])
			{
				if(segment.address[j]+segment.length[j]>segment.address[j-1])
				{
					flag3=0;
					tmp1=i;
					tmp2=j;
					break;
					
				}
			}else if(segment.address[j]>segment.address[j-1])
			{
				if(segment.address[j-1]+segment.length[j-1]>segment.address[j])
				{
					flag3=0;
					tmp1=i;
					tmp2=j;
					break;
				}
			}else if(segment.address[j]==segment.address[j-1])
			{
				flag3=0;
				tmp1=i;
				tmp2=j;
				break;
			}
		}
	 } 
	 if(flag3==0)
	 {
	 	cout<<"������������������"<<tmp1<<"�ŷֶΣ���ַ"<<segment.address[tmp1]<<"�γ�"<<segment.length[tmp1]<<",�����������"<<tmp2<<"�ŷֶζ�Ӧ�Ļ�ַ�Ͷγ�)"<<endl;
	 	return false;
	 }
	 //�����ʼ������
	 cout<<"��ѡ���˷ֶη�ʽ���������������:"<<endl;
	 cout<<"�κ�    ��ַ    �γ�"<<endl;
	 for(int i=0;i<segment.Segmentcount;i++)
	 {
	 	std::cout<<std::left<<std::setw(3)<<i<<"\t";
	 	std::cout<<std::left<<std::setw(3)<<segment.address[i]<<"\t";
	 	std::cout<<std::left<<segment.length[i]/1024<<"K\t";
	 	cout<<endl;
	 }

	 //���е�ַת��
	cout<<"�������߼���ַ��";
	cin>>logicAddress;
	int cnt=0;
	int cnt1=0;
	int cnt2=0;
	int b;			//�κ� 
	int segdeviation;	//��ƫ 
	//�ж��߼���ַ�Ƿ�����ڴ��� 
	for(int i=0;i<segment.Segmentcount;i++)
	{
		//�߼���ַ���������ַ 
		if(logicAddress>segment.address[i]+segment.length[i])
		{
			cnt++;
		}
		//�߼���ַС�������ַ 
		if(logicAddress<segment.address[i])
		{
			cnt1++;
		}
		//�߼���ַ�����ڴ淶Χ�� 
		if(!in_range(logicAddress,segment.address[i],segment.address[i]+segment.length[i]))
		{
			cnt2++;
		}
	}
	if(cnt==segment.Segmentcount||cnt1==segment.Segmentcount||cnt2==segment.Segmentcount)
	{
		cout<<"�߼���ַ�����ڴ���,�������룡"<<endl;
		return false;
	}
	
	//�߼���ַ���� 
	for(int i=0;i<segment.Segmentcount;i++)
	{
		if(logicAddress>segment.address[i])
		{
			if(logicAddress<=segment.address[i]+segment.length[i])
			{
				b=i;
				break;		
			}
		}
	}
	segdeviation=logicAddress-segment.address[b];
	physicAddress=segment.address[b]+segdeviation;
	cout<<"��ѡ���˷ֶη�ʽ��������߼���ַΪ"<<logicAddress<<"�����Ӧ�Ķκ�Ϊ"<<b<<"����ƫ��Ϊ"<<segdeviation<<",�öζ�Ӧ�Ļ�ַΪ"<<segment.address[b]<<",�����ַΪ"<<physicAddress<<endl;
	cout<<"�Ƿ�Ҫ������(y/n)"<<endl;
	char c;
	cin>>c;
	if(c=='y')
	{
		return false;
	}else 
	return true;
}
int main()
{
	int choice;
	cout<<"������Ҫѡ��ĵ�ַ�仯��ʽ����0-��ҳ��1-�ֶΣ�"<<endl;
	cin>>choice;
	if(choice==0)
	{
		while(!PageMethod()) ;
	}else
	{
		while(!SegmentMethod())	;
	}
}
