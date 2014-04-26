
import java.io.*;
import java.util.*;


class myGraph
{
	int numOfVertices;
	static int edgeCount = 0;
	private int myGraphMatrix[][];
	private int MST[][];
	static Hashtable<String, Integer> hashNodes = new Hashtable<String, Integer>();
	private int edgeWeights[] = new int [30];
	private String edges[] = new String [30];
	public int[] visited = new int [20]; 
	int superd[];
	static int visitCount = 0;
	static int differentRouteCount = 0;
	static int tripCount = 0;
	
	myGraph()
	{
		
	}
	myGraph(int vertices)
	{
		this.numOfVertices = vertices;
		myGraphMatrix = new int[numOfVertices + 1][numOfVertices + 1];
		MST = new int [numOfVertices + 1][numOfVertices + 1];
		visited = new int [numOfVertices+1];
		superd = new int [numOfVertices+1];
		for(int i =0;i < numOfVertices + 1; i++)
		{
			for(int j =0; j< numOfVertices + 1; j++)
			{
				myGraphMatrix[i][j] = 32000;
				MST[i][j] = 32000;
			}
		}
	}
	
	public int parseVertices(String str)
	{
		int numOfNodes = 0;
		for(int i=0; i< str.length();i++)
 	   	{
 		   char curr = str.charAt(i);
 		   if(curr>='A' && curr<='Z')
 		   {
 			   
 			   if(hashNodes.containsKey("" + curr))
 			   {
 				   continue;
 			   }
 			   //System.out.print(curr);
 			   hashNodes.put("" + curr, numOfNodes);
 			   numOfNodes++;
 		   }
 	   }
		numOfVertices = numOfNodes;
		myGraphMatrix = new int[numOfVertices + 1][numOfVertices + 1];
		for(int i =0;i < numOfVertices + 1; i++)
		{
			for(int j =0; j< numOfVertices + 1; j++)
			{
				if(i == j)
					myGraphMatrix[i][j] = 0;
				else
					myGraphMatrix[i][j] = 32000;
			}
		}
		return numOfNodes;
	}
	
	public void addEdge(String Edge)
	{
		int Src = hashNodes.get(""+Edge.charAt(1));
		int Dst = hashNodes.get(""+Edge.charAt(2));
		int weight = Integer.parseInt(""+Edge.charAt(3));
		myGraphMatrix[Src][Dst] = weight;
		edgeWeights[edgeCount] = weight;
		edges[edgeCount++] = Edge;
	}
	
	public void displayAdjMatrix()
	{
		for(int i = 0; i<numOfVertices + 1;i++)
		{
			for(int j = 0; j<numOfVertices + 1;j++)
			{
				System.out.print(myGraphMatrix[i][j]);
				System.out.print('\t');
			}
			System.out.print('\n');
		}
	}
	
	public void checkRoute(String str)
	{
		String myStr = str.substring(0, str.length()-1);
		String parts[] = myStr.split("-");
		int Src;
		int Dst;
		int i, dist = 0;
		for(i=0;i<parts.length-1;i++)
		{
			Src = hashNodes.get(parts[i]);
			Dst = hashNodes.get(parts[i+1]);
			if(myGraphMatrix[Src][Dst]>0 && myGraphMatrix[Src][Dst] <32000)
			{
				dist += myGraphMatrix[Src][Dst];
				continue;
			} else {
				break;
			}
		}
		if(i == parts.length-1)
		{
			System.out.printf("%s\t%d\n", myStr, dist);
			
		} else {
			System.out.printf("%s\t%s\n", myStr, "No Route");
		}
		//System.out.printf("%s\t%d\n", myStr, visited[i]);
	}
	
	public void getTrips(String str)
	{
		int Src, Dst;
		int lore = 0, limit = 0, exact =0;
		String[] divi = str.split(" ");
		for(int i=0; i<divi.length; i++)
		{
			if(divi[i].equals("exactly"))
			{
				lore = 1;
				String exac[] =  str.split("exactly ");
				exact = Integer.parseInt("" +exac[1].charAt(0));
				//System.out.print(exact);
			}
			else if(divi[i].equals("maximum"))
			{
				lore = 2;
				String[] maxi = str.split("maximum of ");
				limit = Integer.parseInt(maxi[1].charAt(0) + "");
				//System.out.print(limit);
			}
		}
		String[] parts = str.split("at ");
		Src = hashNodes.get(""+parts[1].charAt(0));
		Dst = hashNodes.get("" + parts[2].charAt(0));
		tripCount = 0;
		visitCount = 0;
		if(lore == 2){
			getTotalTripsUnderLimit(Src, Dst, limit, 0);
		} else if(lore==1) {
			getTotalTripsExact(Src, Dst, exact, 0);
		}
		System.out.printf("\t%d \n", tripCount);
	}
	
	public void getTotalTripsUnderLimit(int Src, int Dst, int limit, int curr)
	{
		if(curr>limit)
			return;
		
		if(Src == Dst && visitCount ==1)
		{
			tripCount++;
		}
		visitCount = 1;
		for(int i=0; i<numOfVertices; i++)
		{
			if(myGraphMatrix[Src][i]>0 && myGraphMatrix[Src][i] < 32000)
			{
				getTotalTripsUnderLimit(i, Dst, limit, curr+1);
			}
		}
	}
	
	public void getTotalTripsExact(int Src, int Dst, int exact, int curr)
	{
		if(curr>exact)
			return;
		
		if(Src == Dst && curr == exact)
		{
			tripCount++;
		}
		
		for(int i=0; i<numOfVertices; i++)
		{
			if(myGraphMatrix[Src][i]>0 && myGraphMatrix[Src][i] < 32000)
			{
				getTotalTripsExact(i, Dst, exact, curr+1);
			}
		}
		
	}
	
	public void getShortest(String str)
	{
		int Src, Dst, disti;
		String myStr = str.substring(0, str.length()-1);
		//System.out.printf("%s\t\n", myStr);
		String[] parts = myStr.split(" ");
		System.out.printf("%s\t%s\t", parts[parts.length-3], parts[parts.length-1]);
		for(int i =0; i < numOfVertices; i++)
		{
			visited[i] = 0;
		}
		visitCount = 0;
		Src = hashNodes.get(parts[parts.length-3]);
		Dst = hashNodes.get(parts[parts.length-1]);
		visitCount = 0;
		disti = getShortDistance(Src, Dst, 0);
		if(disti == 32000)
		{
			System.out.printf("%s", "No route \n");
		} else {
			System.out.printf("%d\n", disti);
		}
		
	}
	
	public void getDifferent(String str)
	{
		int Src, Dst;
		String[] parts = str.split("to");
		String running = "";
		//System.out.printf("%s%s\n", parts[0], parts[1]);
		Src = hashNodes.get("" + parts[0].charAt(parts[0].length()-2));
		Dst = hashNodes.get("" + parts[1].charAt(1));
		
		String[] newparts = str.split("less than ");
		int index = newparts[1].indexOf('.');
		String numstr = newparts[1].substring(0, index);
		//System.out.printf("%d%d\n", Src, Dst);
		int limit = Integer.parseInt(numstr);
		differentRouteCount = 0;
		differentRoutes(Src, Dst, limit, 0, running);
		System.out.printf("\t%d", differentRouteCount-1);
	}
	
	public void getMST()
	{
		System.out.printf("%s", "\n");
	}
	
	public int getShortDistance(int Src, int Dst, int curr)
	{
		//System.out.printf("%d to %d", Src, Dst);
		int alldist[] = new int[20];
		int min = 32000;
		int tobevisited[] = new int [20];
		int temp = 0;
		
		for(int j=0;j<20;j++)
			tobevisited[j] = 1000;
		
		if(Src==Dst && visitCount == 1)
		{
			//System.out.printf("%s", "Returning");
			return curr;
		}
		visited[Src] =1;
		if(visitCount == 0 && Src == Dst)
			visited[Src] = 0;
		
		visitCount = 1;
		for(int i =0; i<20; i++)
			alldist[i] = 32000;
	
		
		for( int i =0; i< numOfVertices; i++)
		{
			
			if(myGraphMatrix[Src][i]>0 && myGraphMatrix[Src][i] < 32000 && visited[i]==0)
			{
				//System.out.printf("  Src %d %s %d", Src, "Through", i);
				tobevisited[temp++] = i;
			} 
			
		}
		for(int j =0; j<20 && tobevisited[j] <1000;j++)
		{
			alldist[tobevisited[j]] = getShortDistance(tobevisited[j], Dst, curr+myGraphMatrix[Src][tobevisited[j]]);
		}
		
		
		for(int i =0; i<20; i++)
		{
			//System.out.printf("%d  ", alldist[i]);
			if(min>alldist[i])
				min = alldist[i];
		}
		
		return min;
	}

	public void differentRoutes(int Src, int Dst, int limit, int curr, String running)
	{
		if(curr>=limit)
			return;
		running = running + Integer.toString(Src);
		if(Src == Dst)
		{
			differentRouteCount++;
			//displayRoute(running);
		}
		
		for(int i=0; i<numOfVertices; i++)
		{
			if(myGraphMatrix[Src][i]>0 && myGraphMatrix[Src][i] < 32000)
			{
				differentRoutes(i, Dst, limit, curr+myGraphMatrix[Src][i], running);
			}
		}
	}
	
	public void displayRoute(String str)
	{
		String finalStr = "", curr = "";
		
		//System.out.printf("%s\t", str);
		for (int i =0;i<str.length();i++)
		{
			
			
			Set entrySet = hashNodes.entrySet();
			Iterator it = entrySet.iterator();
			while(it.hasNext())
			{
				curr = "";
				curr += it.next();
				String[] parts = curr.split("=");
				//System.out.printf("parts %s\t", parts[1]);
				//System.out.printf("char %s\t", "" + str.charAt(i));
				if(Integer.parseInt(parts[1]) == Integer.parseInt("" + str.charAt(i)))
				{
					//System.out.printf("%s\t", parts[0]);
					finalStr += parts[0];
				}
			}
		}
		System.out.printf("%s\t", finalStr);
	}
}


public class fileread  {
	static Set<Integer> nodes = new HashSet<Integer>();
	
	static int numOfNodes = 0;
	
	
	fileread (int size, Set<Integer> nodes)
	{
		//System.out.print("Initializing the fileread class\n");
		
	}
	
	public static void main(String args[])
	{
	   myGraph G = new myGraph();
	   int output = 0;
	   String inputFile="";
		if (args.length > 0) {
		    try {
		        inputFile = args[0];
		    } catch (NumberFormatException e) {
		        System.err.println("Argument" + " must be supplied");
		        System.exit(1);
		    }
		}
	   try{
	       FileInputStream fstream = new FileInputStream(inputFile);
	       DataInputStream in = new DataInputStream(fstream);
	       BufferedReader br = new BufferedReader(new InputStreamReader(in));
	     
	       String strLine;
	       
	   
	       while ((strLine = br.readLine()) != null)   {   
	           String[] parts = strLine.split(":");
	           if(parts[0].equals("Graph"))
	           {
	        	   /* Parse the vertices */
	        	   G.parseVertices(parts[1]);
	        	   	        	   
	        	   /* parse the edges */
	        	   String[] Edges = parts[1].split(",");
	        	   for(int j = 0; j< Edges.length; j++)
	        	   {
	        		   G.addEdge(Edges[j]);
	        	   }
	        	   //G.displayAdjMatrix();
	           } else {
	        	   String[] broken = strLine.split(" ");
	        	   for(int i = 0;i <broken.length;i++)
	        	   {
	        		   if(broken[i].equals("distance"))
	        		   {
	        			   output++;
	        			   System.out.printf("%s # %d ", "Output", output);
	        			   G.checkRoute(broken[broken.length-1]);
	        			   break;
	        		   } else if(broken[i].equals("trips")) {
	        			   output++;
	        			   System.out.printf("%s # %d ", "Output", output);
	        			   G.getTrips(strLine);
	        			   break;
	        		   } else if(broken[i].equals("shortest")) {
	        			   output++;
	        			   System.out.printf("%s # %d ", "Output", output);
	        			   G.getShortest(strLine);
	        			   break;
	        		   } else if(broken[i].equals("different")) {
	        			   output++;
	        			   System.out.printf("%s # %d ", "Output", output);
	        			   G.getDifferent(strLine);
	        			   break;
	        		   }
	        	   }
	           }
	           
	       }   
	       
	       
	       in.close();
	   } catch (Exception e){//Catch exception if any
	     System.err.println("Error: " + e.getMessage());
	   }
	}

}


