import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class client_code {
	public static void main(String[] args) throws Exception {
        //System.out.println(InetAddress.getLocalHost());
        try
        {
        Socket s = new Socket(InetAddress.getByName("192.168.43.208"), 3500);
	System.out.println("connected");	
        
        OutputStream out = s.getOutputStream();
        PrintStream pout = new PrintStream(out);
       
        
        
        
      
		File file = new File("cpe_header_recv.txt");

		// if file doesnt exists, then create it
		if (!file.exists()) {
			file.createNewFile();
			//System.out.println("file created");
		}

		FileWriter fw = new FileWriter(file.getAbsoluteFile());
		BufferedWriter bw = new BufferedWriter(fw);
		
        
        
        
        
        InputStream in = s.getInputStream();
	//System.out.println("pppppp");
        BufferedReader d = new BufferedReader(new InputStreamReader(in));
        
        String line = d.readLine();		//reads headers
	//System.out.println("got this from server :" +line);
        bw.write(line + "\n");




	Socket s1 = new Socket(InetAddress.getByName("192.168.43.208"), 3501);
	InputStream in1 = s1.getInputStream();
        BufferedReader d1 = new BufferedReader(new InputStreamReader(in1));







	ProcessBuilder launcher3 = new ProcessBuilder("g++","-std=c++11", "generate_gmh.cpp", "-o", "generate_gmh");
	//final Process process3 = 	
	launcher3.start();
	
	//System.out.println("generate compiled");
	ProcessBuilder launcher4 = new ProcessBuilder("generate_gmh");








	BufferedReader read_payload_buf = null;
	String payload1 = "", received = "";
	try {
		
		read_payload_buf = new BufferedReader(new FileReader("cpe_payload.txt"));			
		//payload1 = br4.readLine();							
		//System.out.println(sCurrentLine);	
	   	} 
        catch (IOException e) {
		//e.printStackTrace();
	    } 

		File rec_file = new File("cpe_rec.txt");

		// if file doesnt exists, then create it
		if (!rec_file.exists()) {
			rec_file.createNewFile();
			//System.out.println("file created");
		}

		FileWriter fw_rec = new FileWriter(rec_file.getAbsoluteFile());
		//System.out.println("jjjjj");
		BufferedWriter write_buf = new BufferedWriter(fw_rec);
		PrintWriter pw_rec = new PrintWriter(write_buf);
	

	String op_freq = "";
	String gmh_str = "",ucs_gmh_str="";
	gmh_str = make_gmh();
	String crc = "00000000000000000000000000000000";
	int cur_frame_no = 1;
	int no_down_burst=2,no_up_burst=2,cur_down_burst,cur_up_burst,dir=1;  //dir=1 downstreeam   dir = 2 upstream
	while(cur_frame_no<=3)
		{
			System.out.println("______________________________________________");
			cur_down_burst = 0;
			cur_up_burst = 0;
			while(true)
			{
				if(dir==1)
				{
					if(cur_down_burst%2==1)
					{
						received = d.readLine();	
						System.out.println("|    frame no " + Integer.toString(cur_frame_no) + " received=" + received.substring(32,received.length()-32) + "               |");
						pw_rec.println(received + "\n");
					}
					/*else
					{
						received= d.readLine();
						System.out.println("frame no " + Integer.toString(cur_frame_no) + " received=" + received.substring(32,received.length()-32) + "\n");
						pw_rec.println(received + "\n");
					}*/
					cur_down_burst++;
					if(cur_down_burst==no_down_burst)
					{
						dir = 2;
					}	
				}
				else
				{
					if(cur_up_burst%2==1)
					{
	
						
						payload1 = read_payload_buf.readLine();
						System.out.println("|    frame no " + Integer.toString(cur_frame_no) + " sent=" + payload1 + "                  |");
						if(cur_frame_no == 2)
						{
						
							ucs_gmh_str = gmh_str.substring(0,11)+"1"+gmh_str.substring(12,gmh_str.length());
							//System.out.println(ucs_gmh_str);
							pout.println(ucs_gmh_str  + payload1 + crc);
						}
						else
						{
							pout.println(gmh_str  + payload1 + crc);
						}
					}
					/*else
					{
						payload1 = read_payload_buf.readLine();
						System.out.println("frame no " + Integer.toString(cur_frame_no) + " sent=" + payload1 + "\n");
						pout.println(gmh_str  + payload1 + crc);
					}*/
					cur_up_burst++;
					if(cur_up_burst==no_up_burst)
					{
						op_freq = d1.readLine();
						if(op_freq.compareTo("Ok")==0)
						{
						}
						else
						{
							System.out.println("|    Switching to channel " + op_freq.substring(25, op_freq.length()) + "                  |");
						}
						dir = 1;
						cur_frame_no++; 
						System.out.println("|____________________________________________|" + "\n\n"); 
						break;
					}
				}
			}
		}

        
	//fw_rec.close();
	write_buf.close();
	pw_rec.close();	
        bw.close();

	while(true)
	{
	}
        
        }
        catch(Exception e)
        {
        	System.out.println(e.toString());
        }
       
	}



	public static String make_gmh()
	{	
		String s;
		String output4 = "";
		s = "";
		try
		{
			ProcessBuilder launcher4 = new ProcessBuilder("generate_gmh");
			Process process4 = launcher4.start();
			BufferedReader reader4 = new BufferedReader(new InputStreamReader(process4.getInputStream()));
			StringBuilder builder4 = new StringBuilder();
			
			while ( (output4 = reader4.readLine()) != null) {
					
					s = s + output4;
					
			}
		
			process4.waitFor();
			
			/*if(process4.isAlive())
				System.out.println(true);
			else
				System.out.println(false);
			process4.destroy();*/
			throw new InterruptedException("Exception encountered");
			
		}catch(IOException | InterruptedException ex)
		{
			//System.out.println(ex.toString());
			//throw ex;
		}	
	//System.out.println(s);		
		return s;
		
	}


}


