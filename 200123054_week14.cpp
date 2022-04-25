#include <bits/stdc++.h>

using namespace std;

void external_merge(vector<vector<int>>&temp,vector<int>&temp1)
{
  vector<int>pointer;
  int count=0;
  for(int i=0;i<temp.size();i++)
  {
    pointer.push_back(0);
    count+=temp[i].size();
  }
  for(int i=0;i<count;i++)
  {
    int min=INT_MAX;
    int k;
    for(int j=0;j<pointer.size();j++)
    {
      if(pointer[j]<temp[j].size() && temp[j][pointer[j]]<min)
      {
        min=temp[j][pointer[j]];
        k=j;
      }
    }
    temp1.push_back(min);
    pointer[k]++;
  }
}

void external_sort(vector<vector<int>>&v,int buffer_pages)
{
  for(int i=0;i<v.size();i++)
  {
    sort(v[i].begin(),v[i].end());
  }
  while(v.size()>1)
  {
    vector<vector<int>>sorted_ones;
    vector<vector<int>>temp;
    vector<int>temp1;
    int i=0;
    while(i<v.size())
    {
      for(int j=0;j<buffer_pages-1 && i<v.size();j++)
      {
        temp.push_back(v[i]);
        i++;
      }
      external_merge(temp,temp1);
      sorted_ones.push_back(temp1);
      temp.clear();
      temp1.clear();
    }
    v=sorted_ones;
  }
}

int main()
{
  int buffer_pages,rec_per_page,total_recs;
  cin>>buffer_pages>>rec_per_page>>total_recs;
  vector<vector<int>>v;
  int i=0;
  vector<int>temp;
  while(i<total_recs)
  {
    for(int j=0;j<rec_per_page && i<total_recs ;j++)
    {
      int k;
      cin>>k;
      temp.push_back(k);
      i++;
    }
    v.push_back(temp);
    temp.clear();
  }
  external_sort(v,buffer_pages);
  for(int i=0;i<v[0].size();i++)
  {
    cout<<v[0][i]<<'\n';
  }
}