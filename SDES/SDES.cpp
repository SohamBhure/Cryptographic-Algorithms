#include<bits/stdc++.h>
using namespace std;

class DES
{
    private:
        vector<int> plain_text, IP, IPInv;
        vector<int> P10, P8, E_P;
        vector<int> key, key2, KEY1, KEY2, CIPHER;
        vector<vector<int>> S0, S1;


    public:

        DES()
        {   
            /*
            int temp;
            cout<<"\nEnter Key (Binary Values): ";
            for(int i=0; i<10; i++)
            {
                cin>>temp;
                key.push_back(temp);
                key2.push_back(temp);
            }
            */
            key = {0,0,1,0,0,1,0,1,1,1};
            //key = {1,0,1,0,0,0,0,0,1,0};
            key2 = {1,0,1,0,0,0,0,0,1,0};


            //Other definitions
            P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
            IP = {2, 6, 3, 1, 4, 8, 5, 7};
            IPInv = {4, 1, 3, 5, 7, 2, 8, 6};
            E_P = {4,1,2,3,2,3,4,1};

            S0 = {
                {1,0,3,2},
                {3,2,1,0},
                {0,2,1,3},
                {3,1,3,2}
            };

            S1 = {
                {0,1,2,3},
                {2,0,1,3},
                {3,0,1,0},
                {2,1,0,3}
            };

        }

        void inputData()
        {
            cout<<"\n\n\n\n==============INPUT DATA==============";
            /*
            cout<<"\nEnter Plain Text Data (Binary): ";
            for(int i=0; i<8; i++)
            {
                int temp;
                cin>>temp;
                plain_text.push_back(temp);
            }
            */
            plain_text = {1, 0, 1, 0, 0, 1, 0, 1};
            //IP = {2, 6, 3, 1, 4, 8, 5, 7};
            //IPInv = {4, 1, 3, 5, 7, 2, 8, 6};

        }


        void keyGeneration()
        {
            /*
            cout<<"\nEnter values for P10: ";
            for(int i=0; i<10; i++)
            {
                int temp;
                cin>>temp;
                P10.push_back(temp);
            }
            */
            //P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

            cout<<"\nP10: ";
            for(int i=0; i<10; i++)
            {
                key2[i] = key[P10[i]-1];
                cout<<key2[i]<<" ";
            }


            //LS-1
            for(int i=0; i<4; i++)
            {
                key[i] = key2[i+1];
                key[i+5] = key2[i+6];
            }
            key[4] = key2[0];
            key[9] = key2[5];

            cout<<"\nAfter LS-1: ";
            for(int i=0; i<10; i++)
            {
                cout<<key[i]<<" ";
            }


            //taking only 8 bits out of 10
            /*
            random_shuffle(P10.begin(), P10.end());
            cout<<"\n\nP8: ";
            for(int i=0; i<8; i++)
            {
                P8.push_back(P10[i]);
                cout<<P8[i]<<" ";
            }
            */
            P8.clear();
            P8 = {6,3,7,4,8,5,10,9};


            cout<<"\nFinal Key 1: ";
            for(int i=0; i<8; i++)
            {
                KEY1.push_back(key[P8[i]-1]);
                cout<<KEY1[i]<<" ";
            }


            //LS-2
            for(int i=0; i<4; i++)
            {
                key2[i] = key[i+2];
                key2[i+5] = key[i+7];
            }
            key2[4] = key[1];
            key2[3] = key[0];
            key2[9] = key[6];
            key2[8] = key[5];

            cout<<"\nAfter LS-2: ";
            for(int i=0; i<10; i++)
            {
                cout<<key2[i]<<" ";
            }

            //P8
            cout<<"\nFinal Key 2: ";
            for(int i=0; i<8; i++)
            {
                KEY2.push_back(key2[P8[i]-1]);
                cout<<KEY2[i]<<" ";
            }
            
            
        }

        

        void encryption()
        {      
            cout<<"\n\n\n\n==============ENCRYPTION==============";

            vector<int> TEMP = {0, 0, 0, 0, 0, 0, 0, 0};
            
            for(int i=0; i<plain_text.size(); i++)
            {
                TEMP[i] = plain_text[IP[i]-1];

            }

            cout<<"\nMixed PT: ";
            for(int i=0; i<TEMP.size(); i++)
            {
                cout<<TEMP[i]<<" ";
            }
            


            //
            //============FK1============
            //
            vector<int> LEFT, RIGHT, AEP;
            vector<int> SK = {1, 1, 1, 0};
            //E_P = {4,1,2,3,2,3,4,1};

            for(int i=0; i<4; i++)
            {
                LEFT.push_back(TEMP[i]);
                RIGHT.push_back(TEMP[i+4]);
            }
            
            
            //Applying E/P
            cout<<"\n\nAfter E/P: ";
            for(int i=0; i<8; i++)
            {
                AEP.push_back(RIGHT[E_P[i]-1]);
                cout<<AEP[i]<<" ";
            }


            //XOR Key 1
            cout<<"\n\nAfter XOR with Key 1: ";
            for(int i=0; i<8; i++)
            {
                AEP[i] = AEP[i]^KEY1[i];
                cout<<AEP[i]<<" ";
            }

            
            /*
            //SO and S1
            S0 = {
                {1,0,3,2},
                {3,2,1,0},
                {0,2,1,3},
                {3,1,3,2}
            };

            S1 = {
                {0,1,2,3},
                {2,0,1,3},
                {3,0,1,0},
                {2,1,0,3}
            };
            */

            //Mapping S0 and S1
            int t1 = 2*AEP[0] + AEP[3];
            int t2 = 2*AEP[1] + AEP[2];
            int selectedS0 = S0[t1][t2];
            t1 = selectedS0/2;
            t2 = selectedS0%2;


            int k1 = 2*AEP[4] + AEP[7];
            int k2 = 2*AEP[5] + AEP[6];
            int selectedS1 = S1[k1][k2];
            k1 = selectedS1/2;
            k2 = selectedS1%2;

            vector<int> IPP4 = {t1,t2,k1,k2};
            vector<int> temp, P4 = {2,4,3,1};

            //Applying P4
            cout<<"\nApplying P4: ";
            for(int i=0; i<4; i++)
            {
                temp.push_back(IPP4[P4[i]-1]);
                cout<<temp[i]<<" ";
            }

            //XOR P4 with LEFT
            cout<<"\nAFTER XOR- LEFT: ";
            for(int i=0; i<4; i++)
            {
                LEFT[i] = LEFT[i]^temp[i];
                cout<<LEFT[i]<<" ";
            }
            cout<<"\nRIGHT: ";
            for(int i=0; i<4; i++)
            {
                cout<<RIGHT[i]<<" ";
            }


            //swapping left and right
            temp = LEFT;
            LEFT = RIGHT;
            RIGHT = temp;

            cout<<"\nAfter Swapping: ";
            for(int i=0; i<4; i++)
            {
                cout<<LEFT[i]<<" ";
            }
            for(int i=0; i<4; i++)
            {
                cout<<RIGHT[i]<<" ";
            }



            //
            //============FK2============
            //

            //E_P = {4,1,2,3,2,3,4,1};
            
            AEP.clear();
            cout<<"\nAfter 2nd E/P: ";
            for(int i=0; i<8; i++)
            {
                AEP.push_back(RIGHT[E_P[i]-1]); 
                cout<<AEP[i]<<" ";
            }


            //XOR with KEY 2
            cout<<"\n\nAfter XOR with Key 2: ";
            for(int i=0; i<8; i++)
            {
                AEP[i] = AEP[i]^KEY2[i];
                cout<<AEP[i]<<" ";
            }

            //Mapping S0 and S1
            t1 = 2*AEP[0] + AEP[3];
            t2 = 2*AEP[1] + AEP[2];
            selectedS0 = S0[t1][t2];
            t1 = selectedS0/2;
            t2 = selectedS0%2;


            k1 = 2*AEP[4] + AEP[7];
            k2 = 2*AEP[5] + AEP[6];
            selectedS1 = S1[k1][k2];
            k1 = selectedS1/2;
            k2 = selectedS1%2;

            IPP4 = {t1,t2,k1,k2};
            cout<<"\nAfter Matrix Mapping: "<<t1<<" "<<t2<<" "<<k1<<" "<<k2;

            //P4 = {2,4,3,1};
            
            //Applying P4
            temp.clear();
            cout<<"\nApplying P4 : ";
            for(int i=0; i<4; i++)
            {
                temp.push_back(IPP4[P4[i]-1]);
                cout<<temp[i]<<" ";
            }

            //XOR P4 with LEFT
            cout<<"\nAFTER XOR- LEFT: ";
            for(int i=0; i<4; i++)
            {
                LEFT[i] = LEFT[i]^temp[i];
                cout<<LEFT[i]<<" ";
            }


            //After XORING
            TEMP.clear();
            cout<<"\nAfter XORING: ";
            for(int i=0; i<4; i++)
            {
                TEMP.push_back(LEFT[i]);
                cout<<TEMP[i]<<" "; 
            }
            for(int i=0; i<4; i++)
            {
                TEMP.push_back(RIGHT[i]);
                cout<<TEMP[i+4]<<" ";
            }



            //Applying IP inverse
            //IPInv = {4, 1, 3, 5, 7, 2, 8, 6};
            cout<<"\nFINAL CIPHER TEXT: ";
            for(int i=0; i<8; i++)
            {
                CIPHER.push_back(TEMP[IPInv[i]-1]);
                cout<<CIPHER[i]<<" ";
            }
        }


        void decrypt()
        {
            cout<<"\n\n\n===============DECRYPTION===============";

            vector<int> temp;
            //IP = {2, 6, 3, 1, 4, 8, 5, 7};
            cout<<"\nAFTER IP: ";
            for(int i=0; i<8; i++)
            {
                temp.push_back(CIPHER[IP[i]-1]);
                cout<<temp[i]<<" ";
            }


            vector<int> LEFT, RIGHT;
            //E_P = {4,1,2,3,2,3,4,1};

            for(int i=0; i<4; i++)
            {
                LEFT.push_back(temp[i]);
                RIGHT.push_back(temp[i+4]);
            }
            

            //E_P of RIGHT
            temp.clear();
            cout<<"\n\nAfter E/P: ";
            for(int i=0; i<8; i++)
            {
                temp.push_back(RIGHT[E_P[i]-1]);
                cout<<temp[i]<<" ";
            }

            //XOR with Key 2
            cout<<"\nAfter XOR: ";
            for(int i=0; i<8; i++)
            {
                temp[i] = temp[i]^KEY2[i];
                cout<<temp[i]<<" ";
            }

            /*
            //SO and S1
            S0 = {
                {1,0,3,2},
                {3,2,1,0},
                {0,2,1,3},
                {3,1,3,2}
            };

            S1 = {
                {0,1,2,3},
                {2,0,1,3},
                {3,0,1,0},
                {2,1,0,3}
            };
            */

            //Mapping S0 and S1
            int t1 = 2*temp[0] + temp[3];
            int t2 = 2*temp[1] + temp[2];
            int selectedS0 = S0[t1][t2];
            t1 = selectedS0/2;
            t2 = selectedS0%2;


            int k1 = 2*temp[4] + temp[7];
            int k2 = 2*temp[5] + temp[6];
            int selectedS1 = S1[k1][k2];
            k1 = selectedS1/2;
            k2 = selectedS1%2;


            vector<int> IPP4 = {t1,t2,k1,k2};
            vector<int> P4 = {2,4,3,1};
            cout<<"\nAfter Matrix Mapping: "<<t1<<" "<<t2<<" "<<k1<<" "<<k2;
            
            //Applying P4
            temp.clear();
            cout<<"\nApplying P4: ";
            for(int i=0; i<4; i++)
            {
                temp.push_back(IPP4[P4[i]-1]);
                cout<<temp[i]<<" ";
            }


            //XOR P4 with LEFT
            cout<<"\nAFTER XOR- LEFT: ";
            for(int i=0; i<4; i++)
            {
                LEFT[i] = LEFT[i]^temp[i];
                cout<<LEFT[i]<<" ";
            }
            cout<<"\nRIGHT: ";
            for(int i=0; i<4; i++)
            {
                cout<<RIGHT[i]<<" ";
            }


            //swapping left and right
            temp = LEFT;
            LEFT = RIGHT;
            RIGHT = temp;

            cout<<"\nAfter Swapping: ";
            for(int i=0; i<4; i++)
            {
                cout<<LEFT[i]<<" ";
            }
            for(int i=0; i<4; i++)
            {
                cout<<RIGHT[i]<<" ";
            }



            //
            //============FK2============
            //

            //E_P = {4,1,2,3,2,3,4,1};
            
            temp.clear();
            cout<<"\nAfter 2nd E/P: ";
            for(int i=0; i<8; i++)
            {
                temp.push_back(RIGHT[E_P[i]-1]); 
                cout<<temp[i]<<" ";
            }


            //XOR with KEY 1
            cout<<"\n\nAfter XOR with Key 1: ";
            for(int i=0; i<8; i++)
            {
                temp[i] = temp[i]^KEY1[i];
                cout<<temp[i]<<" ";
            }

            //Mapping S0 and S1
            t1 = 2*temp[0] + temp[3];
            t2 = 2*temp[1] + temp[2];
            selectedS0 = S0[t1][t2];
            t1 = selectedS0/2;
            t2 = selectedS0%2;


            k1 = 2*temp[4] + temp[7];
            k2 = 2*temp[5] + temp[6];
            selectedS1 = S1[k1][k2];
            k1 = selectedS1/2;
            k2 = selectedS1%2;

            IPP4 = {t1,t2,k1,k2};
            cout<<"\nAfter Matrix Mapping: "<<t1<<" "<<t2<<" "<<k1<<" "<<k2;
            
            //P4 = {2,4,3,1};
            
            //Applying P4
            temp.clear();
            cout<<"\nApplying P4 : ";
            for(int i=0; i<4; i++)
            {
                temp.push_back(IPP4[P4[i]-1]);
                cout<<temp[i]<<" ";
            }

            //XOR P4 with LEFT
            cout<<"\nAFTER XOR- LEFT: ";
            for(int i=0; i<4; i++)
            {
                LEFT[i] = LEFT[i]^temp[i];
                cout<<LEFT[i]<<" ";
            }

            
            //After XORING
            temp.clear();
            cout<<"\nAfter XORING: ";
            for(int i=0; i<4; i++)
            {
                temp.push_back(LEFT[i]);
                cout<<temp[i]<<" "; 
            }
            for(int i=0; i<4; i++)
            {
                temp.push_back(RIGHT[i]);
                cout<<temp[i+4]<<" ";
            }

            //Applying IP inverse
            //IPInv = {4, 1, 3, 5, 7, 2, 8, 6};
            cout<<"\nPLAIN TEXT: ";
            for(int i=0; i<8; i++)
            {
                cout<<temp[IPInv[i]-1]<<" ";
                //cout<<CIPHER[i]<<" ";
            }

        }

};


int main()
{
    DES O;
    O.keyGeneration();
    O.inputData();
    O.encryption();
    O.decrypt();

}
