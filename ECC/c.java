
import java.net.*; 
import java.io.*; 
import java.util.*;
  
public class ClientProgram { 

    public HashMap<Integer, Integer> MapX = new HashMap<Integer, Integer>();
    public HashMap<Integer, Integer> MapY = new HashMap<Integer, Integer>();

    public int Minv(int e, int phi)
    {
        int ans = 0;

        for(int i=0; i<phi; i++)
        {
            if((e*i)%phi == 1)
            {
                ans = i;
                break;
            }
        }
        return ans;
    }


    public void gp()
    {
        // Eqn - y^2 mod 13 = (x^3 + 2x + 3) mod 13
        int a = 2, b=3;
        int n = 18, mod = 13;
        // G (7, 3)
        double Gx = 7, Gy = 3, t=2;

        //3x^2 + a
        int Nr = (int)(3*(Math.pow(Gx, t)) + a);
        int Dr = (int)(2*Gy); 

        int mInv = Minv(Dr, mod);
        int m = (Nr*mInv)%mod;

        // m^2 - Xp -Xq 
        int Xr = (((int)(Math.pow((double)m, t)) -7 -7))%mod;
        // m(Xp - Xr) - Yp
        int Yr = (m*(7-Xr) - 3);

        //System.out.println("\n2G : X = " + Xr);
        //System.out.println("2G : Y = " + Yr);
        MapX.put(2, Xr);
        MapY.put(2, Yr);

        for(int i=3; i<n; i++)
        {   
            // y2 - y1
            Nr = 3 - MapY.get(i-1);
            Dr = 7 - MapX.get(i-1);

            mInv = Minv(Math.abs(Dr), mod);
            m = (Math.abs(Nr)*mInv)%mod;

            if(Dr<0) m = -1*m;
            if(Nr<0) m = -1*m;

            Xr = (((int)(Math.pow((double)m, t)) -MapX.get(i-1) -7))%mod;
            Yr = (m*(MapX.get(i-1)-Xr) - MapY.get(i-1))%mod;
            
            if(Xr<0) Xr = (Xr + mod)%mod;
            if(Yr<0) Yr = (Yr + mod)%mod;

            MapX.put(i, Xr);
            MapY.put(i, Yr);
            
        }

    }


    public void generatePoints()
    {
        //MapX.put(1, 7);     MapY.put(1, 3);
        //MapX.put(5, 6);     MapY.put(5, 7);
        //MapX.put(7, 4);     MapY.put(7, 7);
        //MapX.put(10, 11);   MapY.put(10, 2);
        //MapX.put(14, 9);    MapY.put(14, 3);
        gp();
    }



    public static void main(String[] args) 
    { 
        try { 

            String serverName = "localhost"; 
            int port = 8088; 
            
            //Trying Connecting
            System.out.println("Connecting to Server..."); 
            Socket client = new Socket(serverName, port); 
            System.out.println("Connected to Server!!\n\n"); 

            
            
            // Eqn - y^2 mod 13 = (x^3 + 2x + 3) mod 13
            int a = 2, b=3;
            int n = 18;
            // G (7, 3)
            int Gx = 7, Gy = 3;
            
            ClientProgram c = new ClientProgram();
            c.generatePoints();


            // Private key 
            int Na = 7;
            // Public Key
            int pubAx = c.MapX.get(Na);
            int pubAy = c.MapY.get(Na);

            //System.out.println("Public Key A: X = " + pubAx); 
            //System.out.println("Public Key A: Y = " + pubAy); 



            // Plain Text Pm(-1,0)
            int Pmx = -1;
            int Pmy = 0;
            int k = 10;
            System.out.println("MESSAGE: (" + Pmx + ", " + Pmy + ")");


            // Data Sharing Objects
            OutputStream outToServer = client.getOutputStream(); 
            DataInputStream in = new DataInputStream(client.getInputStream()); 
            DataOutputStream out = new DataOutputStream(outToServer); 
            

            //Share Public Keys
            String publicAx = Integer.toString(pubAx); 
            out.writeUTF(publicAx);
            String publicAy = Integer.toString(pubAy); 
            out.writeUTF(publicAy);
            String kStr = Integer.toString(k); 
            out.writeUTF(kStr);


            int pubBx = Integer.parseInt(in.readUTF()); 
            System.out.println("\nPublic Key B: X = " + pubBx); 
            int pubBy = Integer.parseInt(in.readUTF()); 
            System.out.println("Public Key B: Y = " + pubBy); 
            int PB = Integer.parseInt(in.readUTF()); 
            //System.out.println("Private Key B = " + PB); 

    
            //Building the Cipher
            int cipherX = k;
            int cipherYx = (Pmx + c.MapX.get((k*PB)%n));
            int cipherYy = (Pmy + c.MapY.get((k*PB)%n));

            System.out.println("\nCipherX = " + cipherX + "G");
            System.out.println("CipherYx = " + cipherYx);
            System.out.println("CipherYy = " + cipherYy);
            System.out.println("Full Cipher: " + "(" + cipherX + "G, (" + cipherYx + ", " + cipherYy + "))");


            String CipherX = Integer.toString(cipherX); 
            out.writeUTF(CipherX);
            String CipherYx = Integer.toString(cipherYx); 
            out.writeUTF(CipherYx);
            String CipherYy = Integer.toString(cipherYy); 
            out.writeUTF(CipherYy);


                        
            client.close(); 
        } 
        catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
} 