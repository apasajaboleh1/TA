#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <algorithm>
#define mp make_pair
#define ins insert
#define MAX (int)(1e6)+1
#define MAXK (int)(1e5)+1
using namespace std;
char plaintext[MAX], ciphertext[MAX];
int key[MAXK], both[MAX], known[MAX], knownall;
unordered_map<int,int> tf;
inline bool VALIDITY(int n)noexcept
{
	memset(key, -1, sizeof(int)*n);
	for(int x=0; x<knownall; x++){
		int temp=known[x];
		if(key[temp%n]==-1) {
			key[temp%n]=both[temp];
			}
		else if(key[temp%n]!=both[temp])
			return false;
		}
	return true;
}
inline void SOLVE(int m)noexcept
{
	int ntofind = 0;
	for(int i=0; plaintext[i]!=0; i++)
		if(plaintext[i]!='*'&&ciphertext[i]!='*'){
				known[knownall++]=i;
				both[i]=((ciphertext[i]-plaintext[i]
				+26)%26);
		}
		else if(plaintext[i]=='*'&&ciphertext[i]!='*'){
				tf.ins(mp(ntofind,i));
				ntofind++;
		}
		unordered_map<int,int>::iterator it;
		m = min(m, (int)strlen(plaintext));
		for(int n=m/2+1;n<=m;n++)
		{	
			if(VALIDITY(n))
			{ 
				it=tf.begin();
				while(it!=tf.end())
					if(key[(it->second)%n]==-1){
						plaintext[it->second]='*';
						it=tf.erase(it);
					}
			 		else if(plaintext[it->second]=='*'){
						plaintext[it->second]=
						(ciphertext[it->second]-'A'
						-key[(it->second)%n]+26)%26 + 'A';
						it++;
					}
					else if(plaintext[it->second] != 
					(ciphertext[it->second]-'A'
					-key[(it->second)%n]+26)%26 + 'A'){
						plaintext[it->second]='*';
						it=tf.erase(it);
					}
					else it++;
			}
		}
		printf("%s\n", plaintext);
}

int main()noexcept{
	int tc; 
	scanf("%d", &tc);
	while(tc--){
		int m;
		scanf("%d", &m);
		scanf("%s %s", plaintext, ciphertext);
		tf.clear();
		knownall=0;
		SOLVE(m);
	}
}
