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
    //如果以i开始,长度为k的字符串的长度,已经超出了字符串尾,那么就赋值为-1
    //这是因为,在前面所有数据相同的情况下,字符串短的字典序小.
    int ri = i + tlen <= len ? Rank[i + tlen] : -inf;
    int rj = j + tlen <= len ? Rank[j + tlen] : -inf;
    return ri < rj;
}
void construct_sa() {
    //初始的RANK为字符的ASCII码
    for (int i = 0; i <= len; i++) {
        sa[i] = i;
        Rank[i] = i < len ? s[i] : -inf;
    }
    for (tlen = 1; tlen <= len; tlen *= 2) {
        sort(sa, sa + len + 1, compare_sa);
        tmp[sa[0]] = 0;
        //全新版本的RANK,tmp用来计算新的rank
        //将字典序最小的后缀rank计为0
        //sa之中表示的后缀都是有序的,所以将下一个后缀与前一个后缀比较,如果大于前一个后缀,rank就比前一个加一.
        //否则就和前一个相等.
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
    for (int i = 0; i < len; i++) {//i为后缀数组起始位置
        int j = sa[Rank[i] - 1];//获取当前后缀的前一个后缀(排序后)
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
    for(int i=1;i<=len;i++){//i是长度
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
