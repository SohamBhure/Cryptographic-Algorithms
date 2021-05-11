#include<bits/stdc++.h>
using namespace std;


class RSA
{
    private:
        long long int plain_text, encrypted, decrypted;
        long long int P, Q;
        long long int N, phiN, e, d;

    public:
        RSA()
        {
            P = 11;
            Q = 17;

            N = P*Q;
            phiN = (P-1)*(Q-1);

            e = 2;
            while(e<phiN)
            {
                if(__gcd(e, phiN)==1)
                    break;
                else
                    e++;
            }
            
            // d * e = 1 mod phiN
            e = 7;
            //d = 23;

            long long int temp = phiN+1;
            while(1)
            {
                if(temp%e==0)
                {
                    d = temp/e;
                    break;
                }
                else
                {
                    temp = temp + phiN;
                }
            }

            
            cout<<"\n================= KEYS ===================";
            cout<<"\nPublic Keys: ";
            cout<<"\ne: "<<e<<"\nN: "<<N;            
            cout<<"\n\nPrivate Key: ";
            cout<<"\nd: "<<d<<"\nP: "<<P<<"\nQ: "<<Q;
            
            cout << "\n\n\n======= Encryption & Decryption =======";
            cout << "\n\nEnter the message (plain text): ";
            cin >> plain_text;
        }            

        long long int FME(long long int base, long long int power, long long int mod)
        {
            long long int ans = 1;
            base = base % mod;

            if (base == 0)
            {    
                return 0;
            }

            while (power > 0)
            {
                if (power & 1)
                {
                    ans = (ans*base) % mod;
                }
                
                power = power>>1;
                base = (base*base) % mod;
            }
            
            return ans;
        }

        void encrypt()
        {   
            encrypted = FME(plain_text, e, N);
            cout<<"\nCipher Text: "<<encrypted<<endl;
        }

        void decrypt()
        {
            decrypted = FME(encrypted, d, N);
            cout<<"\nDecrypted: "<<decrypted<<endl;
        }          

};


int main()
{
    RSA O;
    O.encrypt();
    O.decrypt();

}