import java.io.*;
import java.util.Arrays;

class read_input 
{
   public static void main(String args[])
  {
  try{
  
      FileInputStream fstream = new FileInputStream("input1");
      DataInputStream in = new DataInputStream(fstream);
      BufferedReader br = new BufferedReader(new InputStreamReader(in));
      
      String strLine;
  
  
      while ((strLine = br.readLine()) != null)   {
          System.out.println (strLine);
          String[] parts = strLine.split(",");
          System.out.println(Arrays.toString( parts ));
      }
  
      in.close();
  } catch (Exception e){//Catch exception if any
    System.err.println("Error: " + e.getMessage());
  }
  }
}
