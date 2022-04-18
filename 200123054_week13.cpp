#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
	int no_of_records=0;
	int start=0;
	Node* prev=NULL;
	Node* next=NULL;
	vector<pair<int,int>>v;
};

int main()
{
	int page_size;
	cin>>page_size;
	page_size-=16;
	Node*head=new Node();
	while(1)
	{
		int t;
		cin>>t;
		if(t==4)
		{
			break;
		}
		if(t==1)
		{
			int size,val;
			cin>>size>>val;
			Node*temp=head;
			int flag=0;
			while(temp!=NULL)
			{
				int k=page_size-temp->start;
				if(k>=size)
				{
					(temp->v).push_back(make_pair(size,val));
					temp->start+=size+4;
					temp->no_of_records++;
					flag=1;
					break;
				}
				temp=temp->next;
			}
			if(!flag)
			{
				Node* hey=new Node();
				hey->no_of_records++;
				hey->start+=size+4;
				temp=head;
				while(temp->next!=NULL)
				{
					temp=temp->next;
				}
				temp->next=hey;
				hey->prev=temp;
			}
		}
		if(t==2)
		{
			if((head->v).size()==0)
			{
				cout<<"0\n";
				continue;
			}
			Node* temp=head;
			int count=0;
			while(temp!=NULL)
			{
				count++;
				temp=temp->next;
			}
			cout<<count<<" ";
			temp=head;
			while(temp!=NULL)
			{
				cout<<temp->no_of_records<<" ";
				temp=temp->next;
			}
			cout<<'\n';
		}
		if(t==3)
		{
			int val;
			cin>>val;
			Node* temp=head;
			bool found=0;
			int count=0;
			while(temp!=NULL)
			{
				for(int i=0;i<(temp->v).size();i++)
				{
					if((temp->v)[i].second==val)
					{
						found=1;
						cout<<count<<" "<<i<<'\n';
						break;
					}
				}
				if(found)
				{
					break;
				}
				count++;
				temp=temp->next;
			}
			if(!found)
			{
				cout<<"-1 -1\n";
			}
		}
	}
}