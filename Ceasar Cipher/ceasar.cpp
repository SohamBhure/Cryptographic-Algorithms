#include<bits/stdc++.h>
using namespace std;

class cipher
{
    private:
        string message;
        string secure;
        int key, attempts=0;

    public:

/*
        cipher()
        {
            cout<<"\nEnter Message: ";
            cin>>message;
            secure = message;

            cout<<"Enter key value: ";
            cin>>key;
            key = key%27;
        }
*/
        void encode()
        {
            for(int i=0; i<message.size(); i++)
            {
                if(message[i] + key > 122)
                {
                    char diff = message[i] + key - 123;
                    secure[i] = 97 + diff;
                }
                else
                {
                    secure[i] = message[i] + key;
                }
            }
        }

        void display()
        {
            cout<<"\nOriginal Msg: "<<message;
            cout<<"\nCipher: "<<secure;
        }
/*
        void bruteForceDecode()
        {
            for(int i=0; i<27; i++)
            {
                if(secure[0]+1 >122)
                {
                    secure[0] = 'a';
                    attempts++;
                }

                if(secure[0]++ == message[0])
                {
                    break;
                }
                attempts++;
            }

            cout<<"\n\nNo of attempts required to brute force ceasar cipher: "<<attempts<<endl;
        }
*/        
};


int main()
{
    cipher C;
    C.encode();
    C.display();
    C.bruteForceDecode();
}