#include<bits/stdc++.h>
using namespace std;

class hill
{
    private:
        string message;
        vector<int> num_message;
        vector<int> num_secret;
        string secret;
        vector<vector<int>> KEY;

    public:

        hill()
        {   
            /*    
            int i = 98;
            char c = (char)i;
            cout<<c<<endl;
            */

            cout<<"\nEnter Message: ";
            cin>>message;

            cout<<"\nEnter values in key matrix row-wise: ";
            for(int i=0; i<2; i++)
            {
                vector<int> temp;
                for(int j=0; j<2; j++)
                {
                    int t;
                    cin>>t;
                    temp.push_back(t);
                }
                KEY.push_back(temp);
            }

            
            //cout<<"\n"<<message;
            cout<<"\nNumeric Form:\t";

            for(int i=0; i<message.size(); i++)
            {
                int t = message[i] - 97;
                num_message.push_back(t);
                cout<<t<<"\t";
            }

        }


        void encode()
        {
            int temp = 0;
            cout<<"\n\n";

            while(temp<num_message.size())
            {
                int e1 = num_message[temp++];
                int e2 = num_message[temp++];

                int f1 = (e1*KEY[0][0] + e2*KEY[1][0]) % 26;
                int f2 = (e1*KEY[0][1] + e2*KEY[1][1]) % 26;

                //cout<<" "<<f1<<" "<<f2;
                num_secret.push_back(f1);
                num_secret.push_back(f2);
                secret.push_back(f1+97);
                secret.push_back(f2+97);
            }

            cout<<"\nEncoded Msg: "<<secret;

        }


        void decode()
        {   
            vector<vector<int>> INV = KEY;
            int inv1 = (KEY[0][0]*KEY[1][1]) - (KEY[0][1]*KEY[1][0]);
            int modI;

            if(inv1<0) inv1=inv1+26;

            for (int x = 1; x < 26; x++)
            {
                if (((inv1%26) * (x%26)) % 26 == 1)
                {
                    modI = x - 26;
                    break;
                }
            }
		        
            cout<<"\n\nModI: "<<modI;

            INV[0][0] = KEY[1][1];
            INV[1][1] = KEY[0][0];
            INV[0][1] = -KEY[0][1];
            INV[1][0] = -KEY[1][0];
            cout<<"\n"<<INV[0][0]<<"\t"<<INV[0][1]<<"\t"<<INV[1][0]<<"\t"<<INV[1][1]<<"\t";


            cout<<"\n\nDecoded Msg:\t";
            int temp=0;
            while(temp<num_secret.size())
            {
                int e1 = num_secret[temp++];
                int e2 = num_secret[temp++];
                
                //cout<<"\n"<<e1<<", "<<e2;

                int f1 = (modI*(e1*INV[0][0] + e2*INV[1][0])%26) % 26;
                int f2 = (modI*(e1*INV[0][1] + e2*INV[1][1])%26) % 26;
                //cout<<"\n"<<f1<<", "<<f2;

                if(f1<0) 
                    cout<<char(f1+26+97)<<"\t";
                else
                    cout<<char(f1+97)<<"\t";

                if(f2<0)
                    cout<<char(f2+26+97)<<"\t";
                else
                    cout<<char(f2+97)<<"\t";

                

            }
        }


};



int main()
{
    hill V;
    V.encode();
    V.decode();

}