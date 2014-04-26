import java.io.*;

class position
{
	int x,y;
}
public class Rover {
	static int MAXNORTH;
	static int MAXEAST;
	static int TotalMap[][];
	
	Rover(int MN, int ME)
	{
		TotalMap = new int[MN][ME];
	}
	public static void main(String args[])
	{	
		position pos = new position();
		String inputFile="";
		int dir = 0;
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
		    int lineCount = 0;
		    int RoverNum = 0;
		    while ((strLine = br.readLine()) != null)   {
		    	if(lineCount == 0)
		    	{
		    		/* First line contains Top right Point */
		    		String[] parts = strLine.split(" ");
		    		MAXNORTH = Integer.parseInt(parts[0]);
		    		MAXEAST = Integer.parseInt(parts[1]);
		    		//Rover myRover = new Rover(MAXNORTH, MAXEAST);
		    		lineCount++;
		    		continue;
		    	}
		    	if(lineCount%2 ==1)
		    	{
		    		/* Position Line */
		    		if(RoverNum > 0)
		    		{
		    			displayDetails(RoverNum, pos, dir);
		    		}
		    		String[] parts = strLine.split(" ");
		    		pos.x = Integer.parseInt(parts[0]);
		    		pos.y = Integer.parseInt(parts[1]);
		    		switch(parts[2].charAt(0))
		    		{
		    			case 'E':
		    				dir = 0;
		    				break;
		    			case 'N':
		    				dir = 1;
		    				break;
		    			case 'W':
		    				dir = 2;
		    				break;
		    			case 'S':
		    				dir = 3;
		    				break;
		    		}
		    		RoverNum++;
		    		lineCount++;
		    		//System.out.printf("%s %d %d %d\n", "Init", pos.x, pos.y, dir);
		    		continue;
		    	} else {
		    		/* Sequence Line */
		    		lineCount++;
		    		for(int i =0; i<strLine.length(); i++)
		    		{
		    			if(strLine.charAt(i) == 'M')
		    			{
		    				pos = getNewPosition( pos, dir);
		    				//System.out.printf("%s %d %d \n", "Init", pos.x, pos.y);
		    			} else {
		    				dir = getNewDirection(dir, strLine.charAt(i));
		    			}
		    		}
		    	}
		    }
		    displayDetails(RoverNum, pos, dir);
			
		} catch (Exception e) {
			
		}
	}
	
	public static position getNewPosition (position pos, int dir)
	{
		switch(dir)
		{
			case 0:
				pos.x = pos.x+1;
				break;
			case 1:
				pos.y = pos.y+1;
				break;
			case 2:
				pos.x = pos.x-1;
				break;
			case 3:
				pos.y = pos.y-1;
				break;
		}
		return pos;
	}
	
	public static int getNewDirection (int dir, char LOR)
	{
		switch(LOR)
		{
			case 'L':
				dir++;
				dir = dir%4;
				break;
			case 'R':
				if(dir == 0)
					dir = 3;
				else 
					dir = dir-1;
				break;
		}
		return dir;
	}
	
	public static void displayDetails(int RoverNum, position pos, int dir)
	{
		char temp = 'U';
		switch(dir)
		{
			case 0:
				temp = 'E';
				break;
			case 1:
				temp = 'N';
				break;
			case 2:
				temp = 'W';
				break;
			case 3:
				temp = 'S';
				break;
		}
		System.out.printf("%s %d is at %d %d %c\n", "Rover #", RoverNum, pos.x, pos.y, temp);
	}
}

