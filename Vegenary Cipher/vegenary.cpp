#include<bits/stdc++.h>
using namespace std;


class vegenary
{
    private:
        string message;
        string secure;
        queue<int> key;
        int key_length;

    public:

        vegenary()
        {
            cout<<"\nEnter Message: ";
            cin>>message;
            secure = message;

            cout<<"Enter key length: ";
            cin>>key_length;
            cout<<"Enter key sequence: ";
            for(int i=0; i<key_length; i++)
            {
                int temp;
                cin>>temp;
                key.push(temp);
            }
        }

        void encode()
        {
            for(int i=0; i<message.size(); i++)
            {
                if(message[i] + key.front() > 122)
                {
                    char diff = message[i] + key.front() - 123;
                    secure[i] = 97 + diff;
                }
                else
                {
                    secure[i] = message[i] + key.front();
                }

                key.push(key.front());
                key.pop();
            }
        }

        void display()
        {
            cout<<"\nOriginal Msg: "<<message;
            cout<<"\nCipher: "<<secure;
        }

};


int main()
{
    vegenary V;
    V.encode();
    V.display();

}