import java.io.*;



public class tax {
	static int taxp;
	int price;
	
	tax()	{
		taxp = 0;
	}
	public static void main(String args[])
	{			    
		float totalp = 0;
		int input = 0;
		float totalt = 0;
		String inputFile="";
		if (args.length > 0) {
		    try {
		        inputFile = args[0];
		    } catch (NumberFormatException e) {
		        System.err.println("Argument" + " must be supplied");
		        System.exit(1);
		    }
		}
		try {
			FileInputStream fstream = new FileInputStream(inputFile);
		    DataInputStream in = new DataInputStream(fstream);
		    BufferedReader br = new BufferedReader(new InputStreamReader(in));
		     
		    String strLine;
		    
		    while ((strLine = br.readLine()) != null)   {
		    	if(strLine.length()<8)
		    		continue;
		    	if(strLine.length()==8)
		    	{
		    		if(input>0)
		    		{
		    			displayTotalTax(totalt, totalp);
		    			
		    		}
		    		totalp = 0;
		    		totalt = 0;
		    		input++;
		    		System.out.printf("%s : %d\n", "Output #", input);
		    		continue;
		    	}
		    	taxp = 0;
		    	if(isImported(strLine))
		    	{
		    		//System.out.println(strLine);
		    		taxp += 5;
		    	}
		    	if(isNotBookFoodMedi(strLine))
		    	{
		    		taxp += 10;
		    	}
		    	
		    	//System.out.printf("%s\t%d", "Taxp", taxp);
		    	
		    	strLine = strLine.replace(" at "," : ");
		    	
		    	
		    	String price[] = strLine.split(":");
		    	float currp = Float.parseFloat(price[1]);
		    	System.out.print(price[0]);
		    	float rounded_tax = roundoff(currp*taxp);
		    	System.out.printf("%s %.2f\n", " : ", currp+rounded_tax);
		    	totalp += currp;
		    	totalt += rounded_tax;
		    }
			
		} catch (Exception e){//Catch exception if any
		     System.err.println("Error: " + e.getMessage());
		}
		displayTotalTax(totalt, totalp);
	}
	
	public static boolean isImported (String str)
	{
		String[] parts = str.split(" ");
		for(int i=0;i<parts.length;i++)
		{
			if(parts[i].equals("imported"))
			{
				return true;
			}
		}
		return false;
	}
	
	public static boolean isNotBookFoodMedi (String str)
	{
		String[] parts = str.split(" ");
		for(int i=0;i<parts.length;i++)
		{	
			if(parts[i].equals("book") || parts[i].equals("chocolate") || parts[i].equals("pills") ||
					parts[i].equals("chocolates"))
			{
				return false;
			}
		}
		return true;
	}
	
	public static float roundoff (float num)
	{
		int a = (int)(num*10);
		float temp = a;
		//System.out.print(temp);	
		if(a%100 <25) {
			//System.out.print("<25");
			return ((temp-a%100)/1000);
		} else if (a%100 >= 25 && a%100 < 75){
			//System.out.print("<75");
			return ((temp-a%100)/1000+ (float).05);
		} else {
			//System.out.print(">75");
			return ((temp-(a%100)+100)/1000);
		}
	}
	
	public static void displayTotalTax(float totalt, float totalp)
	{
		System.out.printf("%s\t%.2f\n", "Total Sales tax", totalt);
		System.out.printf("%s\t%.2f\n", "Total price", totalp+totalt);
	}
}

