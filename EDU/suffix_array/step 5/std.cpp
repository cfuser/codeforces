#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>

using namespace std;
const int maxn = 400086;
const int inf = 0x3f3f3f3f;

string s;
int len, Rank[maxn], sa[maxn], tlen, tmp[maxn];
bool compare_sa(int i, int j) {
    if (Rank[i] != Rank[j]) { return Rank[i] < Rank[j]; }
    //�����i��ʼ,����Ϊk���ַ����ĳ���,�Ѿ��������ַ���β,��ô�͸�ֵΪ-1
    //������Ϊ,��ǰ������������ͬ�������,�ַ����̵��ֵ���С.
    int ri = i + tlen <= len ? Rank[i + tlen] : -inf;
    int rj = j + tlen <= len ? Rank[j + tlen] : -inf;
    return ri < rj;
}
void construct_sa() {
    //��ʼ��RANKΪ�ַ���ASCII��
    for (int i = 0; i <= len; i++) {
        sa[i] = i;
        Rank[i] = i < len ? s[i] : -inf;
    }
    for (tlen = 1; tlen <= len; tlen *= 2) {
        sort(sa, sa + len + 1, compare_sa);
        tmp[sa[0]] = 0;
        //ȫ�°汾��RANK,tmp���������µ�rank
        //���ֵ�����С�ĺ�׺rank��Ϊ0
        //sa֮�б�ʾ�ĺ�׺���������,���Խ���һ����׺��ǰһ����׺�Ƚ�,�������ǰһ����׺,rank�ͱ�ǰһ����һ.
        //����ͺ�ǰһ�����.
        for (int i = 1; i <= len; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= len; i++) {
            Rank[i] = tmp[i];

        }
    }
}
int height[maxn];
void construct_lcp() {
//    for(int i=0;i<=n;i++){Rank[sa[i]]=i;}
    int h = 0;
    height[0] = 0;
    for (int i = 0; i < len; i++) {//iΪ��׺������ʼλ��
        int j = sa[Rank[i] - 1];//��ȡ��ǰ��׺��ǰһ����׺(�����)
        if (h > 0)h--;
        for (; j + h < len && i + h < len; h++) {
            if (s[j + h] != s[i + h])break;
        }
        height[Rank[i]] = h;
    }
}

int st[maxn][25];
void rmq_init(){
    for(int i=1;i<=len;i++){
        st[i][0]=height[i];
    }
    int l=2;
    for(int i=1;l<=len;i++){
        for(int j=1;j+l/2<=len;j++){
            st[j][i]=min(st[j][i-1],st[j+l/2][i-1]);
        }
        l<<=1;
    }
}
int ask_min(int i,int j){
    int k=int(log(j-i+1.0)/log(2.0));
    return min(st[i][k],st[j-(1<<k)+1][k]);
}
int lcp(int a,int b)
{
    a=Rank[a],b=Rank[b];
    if(a>b)
        swap(a,b);
    return ask_min(a+1,b);
}


int main() {
//    ios::sync_with_stdio(false);
//    freopen("in.txt", "r", stdin);

    cin >> s;
    len = s.size();
    construct_sa();
    construct_lcp();
    rmq_init();

    int ans=0,ans1=1;
    for(int i=1;i<=len;i++){//i�ǳ���
        for(int j=0;j+i<len;j+=i){
            ans=lcp(j,j+i);
            int k=j-(i-ans%i);
            ans=ans/i+1;
            int p=ans-1;
            if(k>=0&&lcp(k,k+i)>=i){ans++;}
            ans1=max(ans,ans1);
            j+=p*i;
        }
    }
    for (int i = 0; i <= len; i++) cout<<Rank[i]<< " "; cout << endl;
    for (int i = 0; i <= len; i++) cout<<height[i]<< " "; cout << endl;
    printf("%d\n",ans1);

    return 0;
}
