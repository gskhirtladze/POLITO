#include <iostream>
#include <stdio.h>
 
using namespace std;
 
long long tr[524288];
long long sh[524288];
 
void tree_add(int t,int l,int r,int L,int R,int X) {
    if (r < L || R < l) return;
    if (L <= l && r <= R) {
        tr[t]+=X;
        sh[t]+=X;
        return;
    }
 
    if (sh[t]) {
        sh[2*t]+=sh[t];
        sh[2*t+1]+=sh[t];
        tr[2*t]+=sh[t];
        tr[2*t+1]+=sh[t];
        sh[t]=0;
    }
 
    tree_add(2*t,l,(l+r)/2,L,R,X);
    tree_add(2*t+1,(l+r)/2+1,r,L,R,X);
    tr[t]=max(tr[2*t],tr[2*t+1]);
}
 
long long tree_max(int t,int l,int r,int L,int R) {
    if (r < L || R < l) return 0;
    if (L <= l && r <= R) return tr[t];
 
    if (sh[t]) {
        sh[2*t]+=sh[t];
        sh[2*t+1]+=sh[t];
        tr[2*t]+=sh[t];
        tr[2*t+1]+=sh[t];
        sh[t]=0;
    }
 
    return max(tree_max(2*t,l,(l+r)/2,L,R),tree_max(2*t+1,(l+r)/2+1,r,L,R));
}
 
int n,k,q,t,x,y;
 
int main() {
 
    cin>>n>>k>>q;
    while (q--) {
        scanf("%d%d%d",&t,&x,&y);
        if (t == 0)
            tree_add(1,0,n-1,max(0,x-k+1),x,y); else
            cout<<tree_max(1,0,n-1,x,y)<<endl;
    }
 
}
