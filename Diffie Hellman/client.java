import java.net.*; 
import java.io.*; 
  
public class ClientProgram 
{ 

    public double FME(int base, int power, int mod)
    {
        double ans = 1;
        base = base % mod;

        if (base == 0)
            return 0;

        while (power > 0)
        {
            if (power %2 == 1)
            {
                ans = (ans*base) % mod;
            }
            
            power = power>>1;
            base = (base*base) % mod;
        }
        
        return ans;
    }

    public double FME(double base, int power, int mod)
    {
        double ans = 1;
        base = base % mod;

        if (base == 0)
            return 0;

        while (power > 0)
        {
            if (power %2 == 1)
            {
                ans = (ans*base) % mod;
            }
            
            power = power>>1;
            base = (base*base) % mod;
        }
        
        return ans;
    }


    public static void main(String[] args) throws IOException
    { 
        try 
        {  
            int port = 8081; 
  
            //select P and G
            int p = 353; 
            int g = 3; 
            

            //Calculating Private and Public Keys
            int privateA = 97;
            ClientProgram cl = new ClientProgram();
            double publicA = cl.FME(g, privateA, p);
            

            // Trying to Connect
            System.out.println("Connecting to Server..."); 
            Socket client = new Socket("localhost", port); 
            System.out.println("Connected to Server!!\n"); 
  


            // Sends the data to client 
            OutputStream outToServer = client.getOutputStream(); 
            DataOutputStream out = new DataOutputStream(outToServer); 
            

            //Sending P and Q
            String temp;
            temp = Integer.toString(p); 
            out.writeUTF(temp); 
            temp = Integer.toString(g); 
            out.writeUTF(temp); 
  

            //Sending Public key of A
            temp = Double.toString(publicA); 
            out.writeUTF(temp); 
  

            // Accepts the data 
            DataInputStream in = new DataInputStream(client.getInputStream()); 
            

            double final_key, publicB;
            publicB = Double.parseDouble(in.readUTF()); 
            final_key = cl.FME(publicB, privateA, p);


            System.out.println("===========Client===========\nPrivate Key: " + privateA); 
            System.out.println("\n===========Server===========\nPublic Key: " + publicB); 
            System.out.println("\nFINAL KEY: " + final_key); 

            client.close(); 
        }   
        catch (Exception e) 
        { 
            e.printStackTrace(); 
        } 
    } 
} 