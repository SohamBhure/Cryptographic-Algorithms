import java.net.*; 
import java.io.*; 
import java.util.*;  

public class ServerProgram { 
    
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

    public static void main(String[] args) throws IOException 
    { 
        try { 
            int port = 8088; 
            
            // Established the Connection 
            ServerSocket serverSocket = new ServerSocket(port); 
            System.out.println("Waiting for client..."); 
            Socket server = serverSocket.accept(); 
            System.out.println("Just connected !!\n\n"); 


            //Eqn - y^2 mod 13 = (x^3 + 2x + 3) mod 13
            int a = 2, b=3;
            int n = 18;
            // G (7, 3)
            int Gx = 7, Gy = 3;

            
            ServerProgram s = new ServerProgram();
            s.generatePoints();


            // Private Key
            int Nb = 5;
            // Public Key
            int pubBx = s.MapX.get(Nb);
            int pubBy = s.MapY.get(Nb);

            //System.out.println("X = " + pubBx); 
            //System.out.println("Y = " + pubBy); 

            // Data Sharing Objects
            DataInputStream in = new DataInputStream(server.getInputStream()); 
            OutputStream outToclient = server.getOutputStream(); 
            DataOutputStream out = new DataOutputStream(outToclient); 

           
            //Share Public Keys
            int pubAx = Integer.parseInt(in.readUTF()); 
            System.out.println("Public Key A: X = " + pubAx); 
            int pubAy = Integer.parseInt(in.readUTF()); 
            System.out.println("Public Key A: Y = " + pubAy); 
            int k = Integer.parseInt(in.readUTF()); 
            //System.out.println("K = " + k); 

            String publicBx = Integer.toString(pubBx);
            out.writeUTF(publicBx);
            String publicBy = Integer.toString(pubBy);
            out.writeUTF(publicBy);
            String PB = Integer.toString(Nb);
            out.writeUTF(PB);
  


            // Sharing Cipher
            int cipherX = Integer.parseInt(in.readUTF()); 
            System.out.println("\nCipher X = " + cipherX + "G"); 
            int cipherYx = Integer.parseInt(in.readUTF()); 
            System.out.println("Cipher Yx = " + cipherYx);
            int cipherYy = Integer.parseInt(in.readUTF()); 
            System.out.println("Cipher Yy = " + cipherYy);


            // Decoding
            int cipherXx = s.MapX.get(cipherX);
            int cipherXy = s.MapY.get(cipherX);
            
            cipherXx = s.MapX.get((k*Nb)%n);
            cipherXy = s.MapY.get((k*Nb)%n);

            System.out.println("\nZx = " + cipherXx);
            System.out.println("Zy = " + cipherXy);

            int decodedX = (cipherYx - cipherXx) % n;
            int decodedY = (cipherYy - cipherXy) % n;

            //System.out.println("\nDecodedx = " + decodedX);
            //System.out.println("Decodedy = " + decodedY);
            System.out.println("\nDECODED: (" + decodedX + ", " + decodedY + ")");
        
            server.close(); 

        } 
  
        catch (SocketTimeoutException s) { 
            System.out.println("Socket timed out!"); 
        } 
        catch (IOException e) { 
        } 
    } 
}