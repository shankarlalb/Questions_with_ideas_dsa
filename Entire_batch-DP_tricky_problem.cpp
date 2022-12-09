/*
************************************    PROBLEM DESCRIPTION     *************************************

Description

You are given N elements, in an array A. You are also given 3 constants X, Y, and Z. You can take any 2 consecutive elements a and b and merge them. On merging you get a single element with value (aX+bY+Z)%50 and this process costs you a*b. After merging you will place this element in place of those 2 elements.
 

If the sequence is [A1, A2, A3, A4] and you merge A2 and A3, you incur a cost of A2*A3 and the array becomes [A1, (A2*X+A3*Y+Z)%50, A4].
 

Find the Minimum cost to merge all the elements into a single element.


Input Format

The first line contains 4 integers, N, X, Y, Z. 1 <= N <= 50, 0<= X,Y,Z < 50.

The Second line contains N space-separated integers, the Ai for the Array.  0 <= Ai < 50


Output Format

Output a single integer, the Minimum cost to Merge all the elements.


Sample Input 1

3 1 2 3
1 2 4
 


Sample Output 1

21

Sample Input 2

5 3 1 0
6 2 4 6 6



Sample Output 2

248

*/
// THIS CODE IS NOT WORKING FOR MULTIPLE TESTCASES 
// because here it is only focusing on cost(ans.second) but when it will return ans than its value (ans.first) would place an important role in further calculating values
// this commneted code is correct one
/*
********************   CORRECT CODE   *********************************
                        (not by me)
***Editorial :
                So we can design a DP with the states
                DP(l,r,x) = minimum cost to merge the segment into one element of value x. if x is not possible, then this store +INF cost.


                Now range (l,r) will form one element from 2 elements in the final step.
                So let's say the (l, mid) and (mid+1,r) range equivalents merge and produce the final element.


                So DP(l,r,(AX+BY+C)%50) = min(DP(l,mid,A) + DP(mid+1,r,B) + AB ) for all mid,A,B in range [l,r).

                Now if for every l,r,z we iterate on all mid and A, B … it turns out to be O(N^6) solution.

                This can be optimized to O(N^5) using the following logic.

                We can calculate the DP(l,r,z) for all values of z altogether. So keep a done for (l,r) pair.

                For a certain range (L,R) → We iterate on mid, and them lets say the left side has value A and the right side as B. So this particular portion updates at (AX+BY+C)%50 and value is (DP(l,mid,A) + DP(mid+1,r,B) + AB 

                So we are sort of keeping DP(L,R) only and this basically returns an array for all values of merging what is the optimal value.

                This makes the code given below O(N^5).

CODE : 


#include<bits/stdc++.h>
using namespace std;

int n,x,y,z;
int arr[51];
bool done[51][51];
int memo[51][51][51];

int dp(int l,int r,int xx){
    if(l==r){
        if(arr[l]==xx)return 0;
        else return 1e9;
    }
    if(done[l][r]){
        return memo[l][r][xx];
    }

    for(int i=0;i<50;i++)memo[l][r][i]=1e9;    

    for(int mid=l;mid<r;mid++){
        for(int fs=0;fs<50;fs++){
            for(int ls=0;ls<50;ls++){
                memo[l][r][(fs*x+ls*y+z)%50] = min(memo[l][r][(fs*x+ls*y+z)%50], dp(l,mid,fs)+ dp(mid+1,r,ls) + fs*ls);
            }
        }
    }
    done[l][r]=1;
    return memo[l][r][xx];
}

void solve(){
    memset(memo,-1,sizeof(memo));
    cin>>n>>x>>y>>z;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int ans = 1e9;
    for(int i=0;i<50;i++){
        ans=min(ans,dp(0,n-1,i));
    }
    cout<<ans<<endl;
}   

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //int _t;cin>>_t;while(_t--)
    solve();
}

*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod2 = 998244353;
int mod = 1e9+7;
#define endl "\n"
#define vint vector<int>
#define vchar vector<char>
#define vstring vector<string>
#define vpairintint vector<pair<int,int>>
#define all(x) x.begin(),x.end()
#define sortall(x) sort(all(x))
#define eprint(x) cerr<<#x<<" : ";for(auto h : x)cerr<<h<<", ";cerr<<endl;
#define print(x) for(auto h : x)cout<<h<<" ";cout<<endl;
#define input(x) for(auto &h:x)cin>>h;
#define eprnt(x) cerr<<#x<<" : "<<x<<endl;
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define cummulate(x,n) for(int i =1;i<n;i++)x[i]+=x[i-1];
int a,b,c,d,e,f,g,h,i,j,k,o,p,q,r,s,t,u,v,w,z,l,m,n,x,y;
int pow(int n,int p,int mod = INT_MAX){int ans = 1;while(p){if(p&1)ans = ans*n%mod;n = n*n%mod;p /= 2;}return ans%mod;}
int inv(int n,int m,int p = INT_MAX){return (pow(n,m-2,m));}
int max(vector<int>v){int ans = INT_MIN; for(auto &i : v)ans = max(ans,i);return ans;}
int min(vector<int>v){int ans = INT_MAX; for(auto &i : v)ans = min(ans,i);return ans;}
//*************************************************
int arr[505];
vector<vector<pair<int,int>>>dp;
pair<int,int> rec(int i,int j){
    if(i>j)return {0,0};
    if(i==j)return {arr[i],0};

    // val,cost
    if(dp[i][j].second!=-1)return dp[i][j];
    pair<int,int>ans={0,mod};
    for (int k = i; k < j; k++)
    {
        auto f = rec(i,k);
        auto s = rec(k+1,j);
        if(ans.second>(f.second+s.second+f.first*s.first))ans = {(f.first*x+y*s.first+z)%50,f.second+s.second+f.first*s.first};
    }
    return dp[i][j] = ans;
}

void solve(int tc){
    cin>>n>>x>>y>>z;
    for (int i = 0; i < n; i++)
    {
        cin>>arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        vpairintint temp;
        dp.push_back(temp);
        for (int j = 0; j < n; j++)
        {
            dp[i].push_back({-1,-1});
        }
        
    }
    
    cout<<rec(0,n-1).second<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
     //freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
     int t = 1;
    //  cin>>t;
     for(int i = 1;i<t+1;i++)solve(i);
     return 0;
}
