#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<time.h>
#include<iomanip>
using namespace std;
struct Page{
	int PageSize;		//页面大小 
	int Pagedeviation;	//页内偏移量
	int Pagecount;		//页表项个数
	int block[10];		//块号数组  
};
struct Segment{
	float length[10];		//段长
	int address[10];	//基址
	int Segmentcount;	//段表项个数
	 
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
	srand((unsigned)time(NULL));   //随机数种子
        
    for (int i = 0; i < 10; i++)
    {
      int   x = rand() % 10;           //产生0到9的随机数
        for (int j = 0; j < i; j++)
            while (x == page.block[j])      //如果x与前面的数相同，则再找一个数
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
	int pin=1;		//用来判断块号是否重复 
	cout<<"请输入每页大小：（0-1K；1-2K；2-4K；3-随机选择）"<<endl;
		cin>>flag1;
		srand((unsigned)time(NULL));   //随机数种子
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
//		cout<<"页面大小为："<<page.PageSize<<endl;

	cout<<"请输入页表项个数：（5到10之间整数，含端点）"<<endl;
	cin>>page.Pagecount;
	while(pin==1)
{

	cout<<"请输入页表中每页对应的块号：（0-手动输入；1-随机生成0至10之间的非重复整数作为块号）"<<endl;
	cin>>flag2;
	if(flag2==0)
	{
		for(int i=0;i<page.Pagecount;i++)
		{
			cin>>page.block[i];	
		}
		//需判断有无块号重复
		for(int i=0;i<page.Pagecount;i++)
		{
			int tmp=page.block[i];
			int pin1=0;
			for(int j=i+1;j<page.Pagecount;j++)
			{
				if(tmp==page.block[j])
				{
					cout<<"您输入的块号有误，与第"<<i<<"号页面输入的块号重复，请重新输入第"<<j<<"号页面对应的块号！"<<endl;
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
	//输出初始化数据
 	cout<<"您选择了分页方式，输入的数据如下："<<endl;
 	cout<<"每页大小"<<page.PageSize/1024<<"K,页表为"<<endl;
 	cout<<"页号    块号"<<endl;
 	for(int i=0;i<page.Pagecount;i++)
 	{
 		std::cout<<std::left<<std::setw(3)<<i<<"\t";
	 	std::cout<<std::left<<std::setw(3)<<page.block[i]<<"\t";
	 	cout<<endl;
	}
   //
	cout<<"请输入逻辑地址：";
	cin>>logicAddress;
	int p=logicAddress/page.PageSize;					//页号 
	page.Pagedeviation=logicAddress%page.PageSize;		//算页偏
	int b=page.block[p];								//算块号
	physicAddress=b*page.PageSize+page.Pagedeviation;
//	cout<<"总内存为："<<page.PageSize*page.Pagecount<<endl;
	if(logicAddress>page.PageSize*page.Pagecount){
		cout<<"您输入的地址已溢出，请重新输入！"<<endl;
		return false;
	}else{
	cout<<"您选择了分页方式，输入的逻辑地址为"<<logicAddress<<",其对应的页号为"<<p<<",页偏移为"<<page.Pagedeviation<<",该地址对应的块号为"<<b<<",块偏移为"<<page.Pagedeviation<<",物理地址为"<<physicAddress<<endl;
	}
	cout<<"是否要继续？(y/n)"<<endl;
	char c;
	cin>>c;
	if(c=='y')
	{
		return false;
	}else 
	return true;
}
void Rand2(int n)			//基址的随机生成 
{
	srand((unsigned)time(NULL));   //随机数种子
        
    for (int i = 0; i <	n; i++)
    {
      int   x = rand() % 100;           //产生0到100的随机数
        for (int j = 0; j < i; j++)
            while (x == segment.address[j])      //如果x与前面的数相同，则再找一个数
            {
                x = rand() % 10;
                j = 0;
            }
        segment.address[i]= x*k;
    }
}
void Rand3(int n)				//段长的随机生成 
{
	srand((unsigned)time(NULL));   //随机数种子
	int a[4]={1,2,4,8}; 
    for (int i = 0; i < n; i++)
    {
      int   random = rand() * 10%4;           //产生0到9的随机数
		int x = a[random];
        segment.length[i] = x*k;
    }

}
bool SegmentMethod(){
	int logicAddress;
	int physicAddress;
	int flag1,flag2;			
	cout<<"请输入段表项个数：（5到10之间整数，含端点）"<<endl;
	cin>>segment.Segmentcount;
	cout<<"请输入页表中每段对应的基址和段长：（0-手动输入；1-随机生成）"<<endl;
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
	//判断基址与段长是否冲突
	int tmp1=0;		//记录冲突的段号
	int tmp2=0; 
	int flag3=1;	//判断冲突的标志 
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
	 	cout<<"您输入的数据有误，与第"<<tmp1<<"号分段（基址"<<segment.address[tmp1]<<"段长"<<segment.length[tmp1]<<",请重新输入第"<<tmp2<<"号分段对应的基址和段长)"<<endl;
	 	return false;
	 }
	 //输出初始化数据
	 cout<<"您选择了分段方式，输入的数据如下:"<<endl;
	 cout<<"段号    基址    段长"<<endl;
	 for(int i=0;i<segment.Segmentcount;i++)
	 {
	 	std::cout<<std::left<<std::setw(3)<<i<<"\t";
	 	std::cout<<std::left<<std::setw(3)<<segment.address[i]<<"\t";
	 	std::cout<<std::left<<segment.length[i]/1024<<"K\t";
	 	cout<<endl;
	 }

	 //进行地址转换
	cout<<"请输入逻辑地址：";
	cin>>logicAddress;
	int cnt=0;
	int cnt1=0;
	int cnt2=0;
	int b;			//段号 
	int segdeviation;	//段偏 
	//判断逻辑地址是否存在内存中 
	for(int i=0;i<segment.Segmentcount;i++)
	{
		//逻辑地址高于任意地址 
		if(logicAddress>segment.address[i]+segment.length[i])
		{
			cnt++;
		}
		//逻辑地址小于任意地址 
		if(logicAddress<segment.address[i])
		{
			cnt1++;
		}
		//逻辑地址不在内存范围中 
		if(!in_range(logicAddress,segment.address[i],segment.address[i]+segment.length[i]))
		{
			cnt2++;
		}
	}
	if(cnt==segment.Segmentcount||cnt1==segment.Segmentcount||cnt2==segment.Segmentcount)
	{
		cout<<"逻辑地址不在内存中,重新输入！"<<endl;
		return false;
	}
	
	//逻辑地址换算 
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
	cout<<"您选择了分段方式，输入的逻辑地址为"<<logicAddress<<"，其对应的段号为"<<b<<"，段偏移为"<<segdeviation<<",该段对应的基址为"<<segment.address[b]<<",物理地址为"<<physicAddress<<endl;
	cout<<"是否要继续？(y/n)"<<endl;
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
	cout<<"请输入要选择的地址变化方式：（0-分页；1-分段）"<<endl;
	cin>>choice;
	if(choice==0)
	{
		while(!PageMethod()) ;
	}else
	{
		while(!SegmentMethod())	;
	}
}
