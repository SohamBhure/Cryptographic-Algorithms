import java.net.*; 
import java.io.*; 
  
public class ServerProgram { 
    
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
        try { 
            int port = 8081; 
  
            // Private Key of Server
            int privateB = 233; 
  

            // Established the Connection 
            ServerSocket serverSocket = new ServerSocket(port); 
            System.out.println("Waiting for client..."); 
            Socket server = serverSocket.accept(); 
            System.out.println("Just connected!!"); 
  
  
            // Accepts the data from client 
            DataInputStream in = new DataInputStream(server.getInputStream()); 
            double publicA, publicB, final_key; 
            int P = Integer.parseInt(in.readUTF()); 
            int G = Integer.parseInt(in.readUTF()); 
            publicA = Double.parseDouble(in.readUTF()); 
  

            ServerProgram sl = new ServerProgram();
            publicB = sl.FME(G, privateB, P);
            String Bstr = Double.toString(publicB); 
  

            // Sending data
            OutputStream outToclient = server.getOutputStream(); 
            DataOutputStream out = new DataOutputStream(outToclient); 
            out.writeUTF(Bstr); 
  

            final_key = sl.FME(publicA, privateB, P);  


            System.out.println("\n===========Server===========\nPrivate Key: " + privateB); 
            System.out.println("\n===========Client===========\nP: " + P); 
            System.out.println("G: " + G); 
            System.out.println("Public Key: " + publicA); 
            System.out.println("\nFINAL KEY: " + final_key); 
            
            server.close(); 
        } 
  
        catch (SocketTimeoutException s) { 
            System.out.println("Socket timed out!"); 
        } 
        catch (IOException e) { 
        } 
    } 
}