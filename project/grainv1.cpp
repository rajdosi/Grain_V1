# include <bits/stdc++.h>
using namespace std;

bool LFSR[80],NFSR[80];
int ivsize=64,keysize=80;
int key;

//function for LFSR
bool fSt()
	{
	bool s=LFSR[0]^LFSR[13]^LFSR[23]^LFSR[38]^LFSR[51]^LFSR[62];
	return s;
	}

//function for NFSR
bool fBt()
	{
	bool b=LFSR[0]^NFSR[62]^NFSR[60]^NFSR[52]^NFSR[45]^NFSR[37]^NFSR[33]^NFSR[28]^NFSR[2]^NFSR[14]^NFSR[9]^NFSR[0]^(NFSR[63] & NFSR[60])^(NFSR[37] & NFSR[33])^(NFSR[15] & NFSR[9])^(NFSR[60] & NFSR[52] & NFSR[45])^(NFSR[33] & NFSR[28] & NFSR[21])^(NFSR[63] & NFSR[45] & NFSR[28] & NFSR[9])^(NFSR[60] & NFSR[52] & NFSR[37] & NFSR[33])^(NFSR[63] & NFSR[60] & NFSR[21] & NFSR[15])^(NFSR[63] & NFSR[60] & NFSR[52] & NFSR[45] & NFSR[37])^(NFSR[33] & NFSR[28] & NFSR[21] & NFSR[15] & NFSR[9])^(NFSR[52] & NFSR[45] & NFSR[37] & NFSR[33] & NFSR[28] & NFSR[21]);
	return b;
	}

//h function
bool h()
	{
	bool hf=(LFSR[3] & LFSR[64])^(LFSR[46] & LFSR[64])^(LFSR[63] & LFSR[64])^(LFSR[46] & LFSR[64] & LFSR[3])^(LFSR[46] & NFSR[63] & LFSR[3])^(LFSR[46] & NFSR[63] & LFSR[25])^(LFSR[46] & NFSR[63] & LFSR[64])^LFSR[25]^NFSR[63]^NFSR[1]^NFSR[2]^NFSR[4]^NFSR[10]^NFSR[31]^NFSR[43]^NFSR[56];
	return hf;
	}


int main()
	{
	char in='y';
	while (in=='y')
		{
		
		// Initialisation of key;
		for (int i=0;i<80;i++)
			{
			NFSR[i]=(i%3);
			}
		
		//initialisation of IV
		LFSR[0]=NFSR[0];
		for (int i=1,j=1;i<64;i++,j++)
			{
			if (i%8==0)
				j=j+2;
			LFSR[i]=NFSR[j];
			}
		for (int i=64;i<80;i++)
			LFSR[i]=1; 

		// Main functions 
		bool *ks=new bool[80];
		bool st,bt,hi;
		st=fSt();
		bt=fBt();
		hi=h();
		//cout<<hi<<"\n";
		for (int i=0;i<159;i++)
			{
			for (int i=0;i<79;i++)
				{
				LFSR[i]=LFSR[i+1];
				}
			LFSR[79]=st^hi;
			for (int i=0;i<79;i++)
				{
				NFSR[i]=NFSR[i+1];
				}	
			NFSR[79]=LFSR[0]^hi^bt;
			st=fSt();
			bt=fBt();
			hi=h();
			//cout<<hi<<"\t";
			}	

		//keystream and encryption and decription
		string msg;
		cin>>msg;
		int msglen=msg.length();
		bool cipher[msglen*8];
		for (int i=0;i<msglen;i++)
			{
			int a=(int)msg[i];
			bool *bin=new bool[8];
			int j=7;
			while (a!=0)
				{
				if (a%2==0)
					bin[j]=0;
				else
					bin[j]=1;
				j--;
				a=a/10;
				}	
			for (int j=0;j<8;j++)
				{
				for (int m=0;m<79;m++)
					{
					LFSR[m]=LFSR[m+1];
					}
				LFSR[79]=st;
				for (int k=0;k<79;k++)
					{
					NFSR[k]=NFSR[k+1];
					}
				NFSR[79]=LFSR[0]^bt;
				cipher[i*8+j]=bin[j]^hi;
				st=fSt();
				bt=fBt();
				hi=h();
				}
			}
		
		//display cipher text
		for (int i=0;i<msglen*8;i++)
			{
			cout<<cipher[i];
			if (i%8==7)
				cout<<" ";
			}

		cout<<endl<<"Do you want to continue:[Y/N]";
		cin>>in;
		}

	cout<<endl;
	return 0;
	}





// Display IV and key
// for (int i=0;i<80;i++)
// 	{
// 	cout<<NFSR[i]<<"\t"<<LFSR[i]<<endl;
// 	}
		