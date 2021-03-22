#include<bits/stdc++.h>
using namespace std;

class AES
{
    private:
        vector<int> plain_text, cipher;        
        vector<int> key, P;
        vector<int> W0, W1, W2, W3, W4, W5;
        vector<int> K1, K2, K3;

        map<vector<int>, vector<int>> SBOX, INVSBOX;

    public:

        AES()
        {   
            key = {0,1,0,0, 1,0,1,0, 1,1,1,1, 0,1,0,1 };

            SBOX[{0,0,0,0}] = {1,0,0,1};    SBOX[{1,0,0,0}] = {0,1,1,0};
            SBOX[{0,0,0,1}] = {0,1,0,0};    SBOX[{1,0,0,1}] = {0,0,1,0};
            SBOX[{0,0,1,0}] = {1,0,1,0};    SBOX[{1,0,1,0}] = {0,0,0,0};
            SBOX[{0,0,1,1}] = {1,0,1,1};    SBOX[{1,0,1,1}] = {0,0,1,1};
            SBOX[{0,1,0,0}] = {1,1,0,1};    SBOX[{1,1,0,0}] = {1,1,0,0};
            SBOX[{0,1,0,1}] = {0,0,0,1};    SBOX[{1,1,0,1}] = {1,1,1,0};
            SBOX[{0,1,1,0}] = {1,0,0,0};    SBOX[{1,1,1,0}] = {1,1,1,1};
            SBOX[{0,1,1,1}] = {0,1,0,1};    SBOX[{1,1,1,1}] = {0,1,1,1};


            INVSBOX[{1,0,0,1}] = {0,0,0,0};    INVSBOX[{0,1,1,0}] = {1,0,0,0};
            INVSBOX[{0,1,0,0}] = {0,0,0,1};    INVSBOX[{0,0,1,0}] = {1,0,0,1};
            INVSBOX[{1,0,1,0}] = {0,0,1,0};    INVSBOX[{0,0,0,0}] = {1,0,1,0};
            INVSBOX[{1,0,1,1}] = {0,0,1,1};    INVSBOX[{0,0,1,1}] = {1,0,1,1};
            INVSBOX[{1,1,0,1}] = {0,1,0,0};    INVSBOX[{1,1,0,0}] = {1,1,0,0};
            INVSBOX[{0,0,0,1}] = {0,1,0,1};    INVSBOX[{1,1,1,0}] = {1,1,0,1};
            INVSBOX[{1,0,0,0}] = {0,1,1,0};    INVSBOX[{1,1,1,1}] = {1,1,1,0};
            INVSBOX[{0,1,0,1}] = {0,1,1,1};    INVSBOX[{0,1,1,1}] = {1,1,1,1};
            
        }

        void print_vec(vector<int>V)
        {
            for(int i=0; i<V.size(); i++)
            {
                cout<<V[i]<<" ";
            }
        }

        int binary_to_decimal(vector<int>T)
        {   
            int temp=0, j=0;
            for(int i=T.size()-1; i>=0; i--)
            {
                temp = temp + T[i]*pow(2,j);
                j++;
            }
            return temp;
        }

        vector<int> decimal_to_binary(int x)
        {
            vector<int> temp;
            while(x>0)
            {
                temp.push_back(x&1);
                x = x>>1;
            }

            while(temp.size()<4)
            {
                temp.push_back(0);
            }

            reverse(temp.begin(), temp.end());
            /*
            cout<<"\n\nConverted: ";
            for(int i=0; i<temp.size(); i++)
            {
                cout<<temp[i]<<" ";
            }
            */
            return temp;
        }

        vector<int> poly_reducer(int a, int b)
        {
            vector<int> t1 = decimal_to_binary(a);
            vector<int> t2 = decimal_to_binary(b);
            
            //cout<<"\na: "; print_vec(t1);
            //cout<<"\nb: "; print_vec(t2);

            vector<int> Mul = {0,0,0,0,0,0,0};

            int p=0;
            for(int i=t1.size()-1; i>=0; i--)
            {
                int q=0;
                for(int k=t2.size()-1; k>=0; k--)
                {
                    if(t1[i]==1 && t2[k]==1)
                    {
                        Mul[p+q] = Mul[p+q] ^ 1;
                    }
                    q++;
                }
                p++;
            }
            
            while(Mul[Mul.size()-1]==0)
                Mul.pop_back();

            reverse(Mul.begin(), Mul.end());
            
            
            cout<<"\n\nMUL: ";
            for(int i=0; i<Mul.size(); i++)
            {
                cout<<Mul[i]<<" ";
            }
            
            t1 = {1,0,0,1,1};


            while(Mul.size()>4)
            {
                for(int i=0; i<t1.size(); i++)
                {
                    Mul[i] = Mul[i]^t1[i];
                }

                reverse(Mul.begin(), Mul.end());

                while(Mul[Mul.size()-1]==0)
                    Mul.pop_back();

                reverse(Mul.begin(), Mul.end());

            }

            while(Mul.size()!=4)
            {
                reverse(Mul.begin(), Mul.end());
                Mul.push_back(0);
                reverse(Mul.begin(), Mul.end());
            }
            
            cout<<"\n\nMUL2: ";
            for(int i=0; i<Mul.size(); i++)
            {
                cout<<Mul[i]<<" ";
            }
            

            return Mul;
        }

        void inputData()
        {
            cout<<"\n\n\n\n==============INPUT DATA==============";
            /*
            cout<<"\nEnter Plain Text Data (Binary): ";
            for(int i=0; i<16; i++)
            {
                int temp;
                cin>>temp;
                plain_text.push_back(temp);
            }
            */
            plain_text = {1,1,0,1, 0,1,1,1, 0,0,1,0, 1,0,0,0 };
            P = plain_text;
        }

        void key_generation()
        {
            for(int i=0; i<8; i++)
            {
                W0.push_back(key[i]);
            }
            for(int i=8; i<16; i++)
            {
                W1.push_back(key[i]);
            }

            cout<<"\n\nW0: ";
            print_vec(W0);
            cout<<"\nW1: ";
            print_vec(W1);

            K1 = key;
            
            
            // W2 = W0 XOR 1000 0000 XOR SubNib(RotNib(W1))
            vector<int> temp = {1,0,0,0,0,0,0,0};
            vector<int> TempW, tmp; 

            // Rotating Nibble
            TempW = W1;
            for(int i=0; i<4; i++)
            {
                swap(TempW[i], TempW[i+4]);
            }
            cout<<"\nRotated W1: ";
            print_vec(TempW);


            //SubNib
            for(int i=0; i<4; i++)
            {
                tmp.push_back(TempW[i]);
            }
            tmp = SBOX[tmp];
            
            for(int i=0; i<4; i++)
            {
                TempW[i] = tmp[i];
            }

            tmp.clear();
            for(int i=4; i<8; i++)
            {
                tmp.push_back(TempW[i]);
            }
            tmp = SBOX[tmp];
            for(int i=4; i<8; i++)
            {
                TempW[i] = tmp[i-4];
            }

            cout<<"\nAfter SubNib: ";
            print_vec(TempW);


            for(int i=0; i<8; i++)
            {
                W2.push_back(W0[i]^temp[i]^TempW[i]);
            }
            cout<<"\nW2: ";
            print_vec(W2);

                
            //W3 = W2 XOR W1
            for(int i=0; i<8; i++)
            {
                W3.push_back(W2[i]^W1[i]);
            }
            cout<<"\n\nW3: ";
            print_vec(W3);


            //W4 = W2 XOR 00110000 XOR SubNib(RotNib(W3))
            temp = {0,0,1,1,0,0,0,0};

            // Rotating Nibble
            TempW = W3;
            for(int i=0; i<4; i++)
            {
                swap(TempW[i], TempW[i+4]);
            }
            cout<<"\nRotated W3: ";
            print_vec(TempW);


            //SubNib
            tmp.clear();
            for(int i=0; i<4; i++)
            {
                tmp.push_back(TempW[i]);
            }
            tmp = SBOX[tmp];
            
            for(int i=0; i<4; i++)
            {
                TempW[i] = tmp[i];
            }

            tmp.clear();
            for(int i=4; i<8; i++)
            {
                tmp.push_back(TempW[i]);
            }
            tmp = SBOX[tmp];
            for(int i=4; i<8; i++)
            {
                TempW[i] = tmp[i-4];
            }

            cout<<"\nAfter SubNib: ";
            print_vec(TempW);


            for(int i=0; i<8; i++)
            {
                W4.push_back(W2[i]^temp[i]^TempW[i]);
            }
            cout<<"\n\nW4: ";
            print_vec(W4);

            //W5 = W4 XOR W3
            for(int i=0; i<8; i++)
            {
                W5.push_back(W4[i]^W3[i]);
            }
            cout<<"\n\nW5: ";
            print_vec(W5);


            //keys
            for(int i=0; i<W2.size(); i++)
                K2.push_back(W2[i]);
            for(int i=0; i<W3.size(); i++)
                K2.push_back(W3[i]);

            for(int i=0; i<W4.size(); i++)
                K3.push_back(W4[i]);
            for(int i=0; i<W5.size(); i++)
                K3.push_back(W5[i]);    


            cout<<"\n\n\n===================KEYS===================";
            cout<<"\nK1: ";
            print_vec(K1);
            cout<<"\nK2: ";
            print_vec(K2);
            cout<<"\nK3: ";
            print_vec(K3);

        }

        void encryption()
        {

            cout<<"\n\n=================ENCRYPT=================";
            
            P = {1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0};

            
            //ARK1
            vector<int> ARK1, tmp, ARK1SubNib;
            for(int i=0; i<P.size(); i++)
            {
                ARK1.push_back(P[i]^K1[i]);
            }
            cout<<"\n\nARK1: ";
            print_vec(ARK1);

            
            //SubNib ARK1
            {
            for(int i=0; i<4; i++)
            {
                tmp.push_back(ARK1[i]);
            }
            tmp = SBOX[tmp];
            for(int i=0; i<tmp.size(); i++)
            {
                ARK1SubNib.push_back(tmp[i]);
            }
            tmp.clear();

            for(int i=4; i<8; i++)
            {
                tmp.push_back(ARK1[i]);
            }
            tmp = SBOX[tmp];
            for(int i=0; i<tmp.size(); i++)
            {
                ARK1SubNib.push_back(tmp[i]);
            }
            tmp.clear();

            for(int i=8; i<12; i++)
            {
                tmp.push_back(ARK1[i]);
            }
            tmp = SBOX[tmp];
            for(int i=0; i<tmp.size(); i++)
            {
                ARK1SubNib.push_back(tmp[i]);
            }
            tmp.clear();

            for(int i=12; i<16; i++)
            {
                tmp.push_back(ARK1[i]);
            }
            tmp = SBOX[tmp];
            for(int i=0; i<tmp.size(); i++)
            {
                ARK1SubNib.push_back(tmp[i]);
            }
            tmp.clear();

            cout<<"\nAfter Sub Nib ARK1: ";
            print_vec(ARK1SubNib);
            }


            //Mix Column
            vector<vector<vector<int>>> SMat;
            vector<vector<int>> Me;
            Me = {
                {1,4},
                {4,1}
            };



            {
            vector<int> t1, t2, t3, t4;
            for(int i=0; i<ARK1SubNib.size(); i++)
            {
                if(i>=0 && i<=3)
                {
                    t1.push_back(ARK1SubNib[i]);
                }
                if(i>=4 && i<=7)
                {
                    t2.push_back(ARK1SubNib[i]);
                }
                if(i>=8 && i<=11)
                {
                    t3.push_back(ARK1SubNib[i]);
                }
                if(i>=12 && i<=15)
                {
                    t4.push_back(ARK1SubNib[i]);
                }
            }
            

            SMat = {{t1, t3}, {t2, t4}};

            cout<<"\n\nS Matrix: \n";
            print_vec(SMat[0][0]);
            cout<<"\t";
            print_vec(SMat[0][1]);
            cout<<"\n";
            print_vec(SMat[1][0]);
            cout<<"\t";
            print_vec(SMat[1][1]);
            cout<<"\n";

            
            }


            //Mix Column Multiplication

            {
                vector<int> temp1, temp2, mix_col, after_sub_nib;
                vector<int> S00, S01, S10, S11;

                //Finding S00, S01, S10, S11
                {
                    int a = binary_to_decimal(SMat[0][0]);
                    //cout<<"\n\nA: "<<a;
                    if(a*Me[0][0]>15)
                    {
                        temp1 = poly_reducer(Me[0][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*Me[0][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][0]);
                    //cout<<"\nB: "<<b;
                    if(b*Me[0][1]>15)
                    {
                        temp2 = poly_reducer(Me[0][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*Me[0][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S00.push_back(temp1[i]^temp2[i]);
                        mix_col.push_back(S00[i]);
                    }
                    cout<<"\n\nS00: ";
                    print_vec(S00);

                }

                {
                    int a = binary_to_decimal(SMat[0][0]);
                    //cout<<"\n\nA: "<<a;
                    if(a*Me[1][0]>15)
                    {
                        temp1 = poly_reducer(Me[1][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*Me[1][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][0]);
                    //cout<<"\nB: "<<b;
                    if(b*Me[1][1]>15)
                    {
                        temp2 = poly_reducer(Me[1][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*Me[1][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S10.push_back(temp1[i]^temp2[i]);
                        mix_col.push_back(S10[i]);
                    }
                    cout<<"\nS10: ";
                    print_vec(S10);

                }
                
                {
                    int a = binary_to_decimal(SMat[0][1]);
                    //cout<<"\n\nA: "<<a;
                    if(a*Me[0][0]>15)
                    {
                        temp1 = poly_reducer(Me[0][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*Me[0][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][1]);
                    //cout<<"\nB: "<<b;
                    if(b*Me[0][1]>15)
                    {
                        temp2 = poly_reducer(Me[0][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*Me[0][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S01.push_back(temp1[i]^temp2[i]);
                        mix_col.push_back(S01[i]);
                    }
                    cout<<"\nS01: ";
                    print_vec(S01);

                }    
                
                {
                    int a = binary_to_decimal(SMat[0][1]);
                    //cout<<"\n\nA: "<<a;
                    if(a*Me[1][0]>15)
                    {
                        temp1 = poly_reducer(Me[1][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*Me[1][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][1]);
                    //cout<<"\nB: "<<b;
                    if(b*Me[1][1]>15)
                    {
                        temp2 = poly_reducer(Me[1][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*Me[1][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S11.push_back(temp1[i]^temp2[i]);
                        mix_col.push_back(S11[i]);
                    }
                    cout<<"\n\nS11: ";
                    print_vec(S11);

                }

                
                cout<<"\n\nMix Column: ";
                print_vec(mix_col);



                //XOR with ARK2
                temp1.clear();
                for(int i=0; i<K2.size(); i++)
                {
                    temp1.push_back(K2[i]^mix_col[i]);
                }
                cout<<"\nAfter XOR with K2: ";
                print_vec(temp1);


                //SubNib
                {
                temp2.clear();
                for(int i=0; i<4; i++)
                {
                    temp2.push_back(temp1[i]);
                }
                temp2 = SBOX[temp2];
                for(int i=0; i<4; i++)
                {
                    after_sub_nib.push_back(temp2[i]);
                }

                temp2.clear();
                for(int i=4; i<8; i++)
                {
                    temp2.push_back(temp1[i]);
                }
                temp2 = SBOX[temp2];
                for(int i=0; i<4; i++)
                {
                    after_sub_nib.push_back(temp2[i]);
                }

                temp2.clear();
                for(int i=8; i<12; i++)
                {
                    temp2.push_back(temp1[i]);
                }
                temp2 = SBOX[temp2];
                for(int i=0; i<4; i++)
                {
                    after_sub_nib.push_back(temp2[i]);
                }

                temp2.clear();
                for(int i=12; i<16; i++)
                {
                    temp2.push_back(temp1[i]);
                }
                temp2 = SBOX[temp2];
                for(int i=0; i<4; i++)
                {
                    after_sub_nib.push_back(temp2[i]);
                }
                }

                cout<<"\nSubNib: ";
                print_vec(after_sub_nib);



                // XOR with key 3

                for(int i=0; i<K3.size(); i++)
                {
                    cipher.push_back(K3[i]^after_sub_nib[i]);
                }
                cout<<"\n==========CIPHER: ";
                print_vec(cipher);
                cout<<"==========";

            }


        }

        void decryption()
        {
            cout<<"\n\n=================DECRYPT=================";

            vector<int> temp1, temp2, curANS;

            //XOR with K3
            for(int i=0; i<K3.size(); i++)
            {
                temp1.push_back(cipher[i]^K3[i]);
            }
            cout<<"\nAfter XOR with K3: ";
            print_vec(temp1);

            
            //SubNib
            {
            temp2.clear();
            for(int i=0; i<4; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=4; i<8; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=8; i<12; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=12; i<16; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            }

            cout<<"\nAfter Inv SubNib: ";
            print_vec(curANS);


            //XOR with K2
            for(int i=0; i<K2.size(); i++)
            {
                curANS[i] = curANS[i]^K2[i];
            }
            cout<<"\nAfter XOR with K2: ";
            print_vec(curANS);


            vector<vector<vector<int>>> SMat;
            vector<vector<int>> INVMe;
            INVMe = {
                {9,2},
                {2,9}
            };


            {
            vector<int> t1, t2, t3, t4;
            for(int i=0; i<curANS.size(); i++)
            {
                if(i>=0 && i<=3)
                {
                    t1.push_back(curANS[i]);
                }
                if(i>=4 && i<=7)
                {
                    t2.push_back(curANS[i]);
                }
                if(i>=8 && i<=11)
                {
                    t3.push_back(curANS[i]);
                }
                if(i>=12 && i<=15)
                {
                    t4.push_back(curANS[i]);
                }
            }
            

            SMat = {{t1, t3}, {t2, t4}};

            cout<<"\n\nS Matrix: \n";
            print_vec(SMat[0][0]);
            cout<<"\t";
            print_vec(SMat[0][1]);
            cout<<"\n";
            print_vec(SMat[1][0]);
            cout<<"\t";
            print_vec(SMat[1][1]);
            cout<<"\n";

            
            }



            //INVERSE Mix Column Multiplication

            vector<int> inv_mix_col, after_sub_nib;
            vector<int> S00, S01, S10, S11;
            {    
                vector<int> temp1, temp2;

                //Finding S00, S01, S10, S11
                {
                    int a = binary_to_decimal(SMat[0][0]);
                    //cout<<"\n\nA: "<<a;
                    if(a*INVMe[0][0]>15)
                    {
                        temp1 = poly_reducer(INVMe[0][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*INVMe[0][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][0]);
                    //cout<<"\nB: "<<b;
                    if(b*INVMe[0][1]>15)
                    {
                        temp2 = poly_reducer(INVMe[0][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*INVMe[0][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S00.push_back(temp1[i]^temp2[i]);
                        inv_mix_col.push_back(S00[i]);
                    }
                    cout<<"\n\nS00: ";
                    print_vec(S00);

                }

                {
                    int a = binary_to_decimal(SMat[0][0]);
                    //cout<<"\n\nA: "<<a<<" "<<INVMe[1][0];
                    if(a*INVMe[1][0]>15)
                    {
                        temp1 = poly_reducer(INVMe[1][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*INVMe[1][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][0]);
                    //cout<<"\nB: "<<b;
                    if(b*INVMe[1][1]>15)
                    {
                        temp2 = poly_reducer(INVMe[1][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*INVMe[1][1]);
                    }
    
                    S10.clear();
                    for(int i=0; i<4; i++)
                    {
                        S10.push_back(temp1[i]^temp2[i]);
                        inv_mix_col.push_back(S10[i]);
                    }
                    cout<<"\n\nS10: ";
                    print_vec(S10);

                }

                {
                    int a = binary_to_decimal(SMat[0][1]);
                    //cout<<"\n\nA: "<<a;
                    if(a*INVMe[0][0]>15)
                    {
                        temp1 = poly_reducer(INVMe[0][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*INVMe[0][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][1]);
                    //cout<<"\nB: "<<b;
                    if(b*INVMe[0][1]>15)
                    {
                        temp2 = poly_reducer(INVMe[0][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*INVMe[0][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S01.push_back(temp1[i]^temp2[i]);
                        inv_mix_col.push_back(S01[i]);
                    }
                    cout<<"\n\nS01: ";
                    print_vec(S01);

                }

                {
                    int a = binary_to_decimal(SMat[0][1]);
                    //cout<<"\n\nA: "<<a;
                    if(a*INVMe[1][0]>15)
                    {
                        temp1 = poly_reducer(INVMe[1][0], a);
                    }
                    else
                    {
                        temp1 = decimal_to_binary(a*INVMe[1][0]);
                    }
    
                    int b = binary_to_decimal(SMat[1][1]);
                    //cout<<"\nB: "<<b;
                    if(b*INVMe[1][1]>15)
                    {
                        temp2 = poly_reducer(INVMe[1][1], b);
                    }
                    else
                    {
                        temp2 = decimal_to_binary(b*INVMe[1][1]);
                    }
    
    
                    for(int i=0; i<4; i++)
                    {
                        S11.push_back(temp1[i]^temp2[i]);
                        inv_mix_col.push_back(S11[i]);
                    }
                    cout<<"\n\nS11: ";
                    print_vec(S11);

                }

                cout<<"\nAfter Inverse Mix Column: ";
                print_vec(inv_mix_col);

            }
            
            
            temp1 = inv_mix_col;
            temp2.clear();
            curANS.clear();
            //Inv SubNib
            {
            temp2.clear();
            for(int i=0; i<4; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=4; i<8; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=8; i<12; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            temp2.clear();
            for(int i=12; i<16; i++)
            {
                temp2.push_back(temp1[i]);
            }
            temp2 = INVSBOX[temp2];
            for(int i=0; i<4; i++)
            {
                curANS.push_back(temp2[i]);
            }
            }        

            cout<<"\nAfter SubNib: ";
            print_vec(curANS);


            //XOR with K1
            //curANS.clear();
            for(int i=0; i<K1.size(); i++)
            {
                curANS[i] = curANS[i]^K1[i];
            }
            cout<<"\n\n\nFINAL Plain Text: ";
            print_vec(curANS);

        }


};



int main()
{
    AES O;
    O.inputData();
    O.key_generation();   
    O.encryption(); 
    O.decryption();
}