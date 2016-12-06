import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class server_code {

	static boolean switch_ = false;
	static String operating_channel = "0";

	public static void main(String[] args) throws Exception{
        System.out.println(InetAddress.getLocalHost());
	//Process p = Runtime.getRuntime().exec("cmd /c ipconfig");
	ProcessBuilder launcher1 =
    	new ProcessBuilder("g++","-std=c++11", "driver.cpp", "-o", "driver");

	final Process process1 = launcher1.start();
	
	ProcessBuilder launcher2 = new ProcessBuilder("driver");
	final Process process2 = launcher2.start();
	BufferedReader reader2 = new BufferedReader(new InputStreamReader(process2.getInputStream()));
	StringBuilder builder2 = new StringBuilder();
	System.out.println("\n");
	String output2 = null;
	while ( (output2 = reader2.readLine()) != null) {
		System.out.println(output2);
	}
	System.out.println("\n");





	ProcessBuilder launcher3 =
    	new ProcessBuilder("g++","-std=c++11", "generate_gmh.cpp", "-o", "generate_gmh");
	//final Process process3 = 	
	launcher3.start();
	
	//System.out.println("generate compiled");
	

	
	ProcessBuilder launcher4 = new ProcessBuilder("generate_gmh");
//	Process process4; 
//	launcher4.start();
	


	ProcessBuilder launcher5 = new ProcessBuilder("g++","-std=c++11", "read_gmh.cpp", "-o", "read_gmh");
	//final Process process3 = 	
	launcher5.start();


	ProcessBuilder launcher7 = new ProcessBuilder("g++", "-std=c++11", "update_channels.cpp", "-o", "update_channels");
	launcher7.start();


	ProcessBuilder launcher9 = new ProcessBuilder("g++", "-std=c++11", "gen_backup_table.cpp", "-o", "gen_backup_table");
	launcher9.start();
	

	BufferedReader br = null;
	String sCurrentLine = "";
	try {
		
		br = new BufferedReader(new FileReader("sch_out.txt"));			
		sCurrentLine = br.readLine();							
		//System.out.println(sCurrentLine);	
	    } 
        catch (IOException e) {
		//e.printStackTrace();
	    } 
	

	
        
        ServerSocket sSocket = new ServerSocket(3500);
	//ServerSocket sSocket1 = new ServerSocket(3501);	
        
	Socket channel = sSocket.accept();
	Socket channel1 = sSocket.accept();

        OutputStream out = channel.getOutputStream();
	OutputStream out1 = channel1.getOutputStream();
        PrintStream pout = new PrintStream(out);
	PrintStream pout1 = new PrintStream(out1);
        InputStream in = channel.getInputStream();
	InputStream in1 = channel1.getInputStream();
        BufferedReader d = new BufferedReader(new InputStreamReader(in));
        BufferedReader d1 = new BufferedReader(new InputStreamReader(in1));


	pout.println(sCurrentLine);
	pout1.println(sCurrentLine);
	
	Thread.sleep(1000);



	ServerSocket sSocket2 = new ServerSocket(3501);
	Socket channel3 = sSocket2.accept();
	Socket channel4 = sSocket2.accept();

        OutputStream out3 = channel3.getOutputStream();
	OutputStream out4 = channel4.getOutputStream();
        PrintStream pout3 = new PrintStream(out3);
	PrintStream pout4 = new PrintStream(out4);










	



	BufferedReader serv_send_buf1 = null, serv_send_buf2 = null;
	String payload1 = "", payload2 = "", received_cpe1 = "", received_cpe2 = "";
	try {
		
		serv_send_buf1 = new BufferedReader(new FileReader("serv_payload1.txt"));		
	   	} 
        catch (IOException e) {
		//e.printStackTrace();
	    } 
	try {
		
		serv_send_buf2 = new BufferedReader(new FileReader("serv_payload2.txt"));				
	   	} 
        catch (IOException e) {
		//e.printStackTrace();
	    }
	



	BufferedReader gmh_gen_buf = null;
	String gmh_str = "";
	try {
		gmh_gen_buf = new BufferedReader(new FileReader("gmh_binary.txt"));
				
	   	} 
        catch (IOException e) {
		//e.printStackTrace();
	    } 
	




		File serv_rec_file1 = new File("serv_rec1.txt");

		// if file doesnt exists, then create it
		if (!serv_rec_file1.exists()) {
			serv_rec_file1.createNewFile();
			//System.out.println("file created");
		}

		File serv_rec_file2 = new File("serv_rec2.txt");

		// if file doesnt exists, then create it
		if (!serv_rec_file2.exists()) {
			serv_rec_file2.createNewFile();
			//System.out.println("file created");
		}

		FileWriter fw_rec_file1 = new FileWriter(serv_rec_file1.getAbsoluteFile());
		//System.out.println("jjjjj");
		BufferedWriter write1_buf = new BufferedWriter(fw_rec_file1);
		PrintWriter pw_rec_file1= new PrintWriter(write1_buf);

		FileWriter fw_rec_file2 = new FileWriter(serv_rec_file2.getAbsoluteFile());
		//System.out.println("jjjjj");
		BufferedWriter write2_buf = new BufferedWriter(fw_rec_file2);
		PrintWriter pw_rec_file2= new PrintWriter(write2_buf);













				System.out.println("Backup channel list");
				String output11 = "";
				ProcessBuilder launcher11 = new ProcessBuilder("gen_backup_table");
							Process process11 = launcher11.start();
							BufferedReader reader11 = new BufferedReader(new InputStreamReader(process11.getInputStream()));
							StringBuilder builder11 = new StringBuilder();
							while ( (output11 = reader11.readLine()) != null) {
								System.out.println("|  " + output11 + "   |");
						
							}
							process11.waitFor();
				System.out.println("\n\n\n");













	
	int cur_frame_no = 1;
	String crc = "00000000000000000000000000000000";
	String output10 = "";
	int no_down_burst=2,no_up_burst=2,cur_down_burst,cur_up_burst,dir=1;  //dir=1 downstreeam   dir = 2 upstream
	//while(1)				----break this loop
	//{
		while(cur_frame_no<=3)
		{
		
			cur_down_burst = 0;
			cur_up_burst = 0;
			System.out.println("__________________________________________________________________________");
			while(true)
			{
				if(dir==1)
				{
					if(cur_down_burst%2==0)
					{
						gmh_str = make_gmh();
						//gmh_str.concat(gmh_str);
						//System.out.println("read="+ gmh_str);
						payload1 = serv_send_buf1.readLine();
						System.out.println("|  frame no " + Integer.toString(cur_frame_no) + " sent to 1= " + payload1 + "                                        |");
						pout.println(gmh_str + payload1 + crc);
	
					}
					else
					{
						gmh_str = make_gmh();
						//System.out.println("read="+ gmh_str);
						payload2 = serv_send_buf2.readLine();
						System.out.println("|  frame no " + Integer.toString(cur_frame_no) + " sent to 2=" + payload2 + "                                            |");
						pout1.println(gmh_str + payload2 + crc);
					}
					cur_down_burst++;
					if(cur_down_burst==no_down_burst)
					{
						System.out.println("|________________________________________________________________________|");
						dir = 2;
					}	
				}
				else
				{
					if(cur_up_burst%2==0)
					{
						//pw_rec_file1.flush();
						received_cpe1 = d.readLine();
						System.out.println("|  frame no " + Integer.toString(cur_frame_no) + " recv from 1=" + received_cpe1.substring(32, received_cpe1.length()-32) + "                                        |");
						pw_rec_file1.println(received_cpe1 + "\n" );
						read_gmh("1", cur_frame_no,received_cpe1);			//station id =1 
	
					}
					else
					{
						//pw_rec_file2.flush();
						received_cpe2 = d1.readLine();
						System.out.println("|  frame no " + Integer.toString(cur_frame_no) + " recv from 2=" + received_cpe2.substring(32, received_cpe2.length()-32) + "                                         |");
						pw_rec_file2.println(received_cpe2 + "\n");
						read_gmh("2", cur_frame_no, received_cpe2);			//station id = 2
					}
					cur_up_burst++;
					if(cur_up_burst==no_up_burst)
					{
						if(switch_)
						{
							pout3.println("New operating channel -> " + operating_channel );			
							pout4.println("New operating channel -> " + operating_channel );
							System.out.println("|   New operating channel -> " + operating_channel +"                                           |");
							

							ProcessBuilder launcher10 = new ProcessBuilder("gen_backup_table");
							Process process10 = launcher10.start();
							BufferedReader reader10 = new BufferedReader(new InputStreamReader(process10.getInputStream()));
							StringBuilder builder10 = new StringBuilder();
							while ( (output10 = reader10.readLine()) != null) {
								System.out.println("|  " + output10 + "   |");
						
							}
							process10.waitFor();

							switch_ = false;
						}
						else
						{	
							pout3.println("Ok");			
							pout4.println("Ok");
						}
						dir = 1;
						cur_frame_no++;  
						System.out.println("|________________________________________________________________________|" + "\n\n\n");
						break;
					}
				}
			}
		}
	//	cur_frame_no =1 ;		
	//}
	


	Thread.sleep(10000);
	//fw_rec_file1.close();
	write1_buf.close();
	pw_rec_file1.close();

	//fw_rec_file2.close();
	write2_buf.close();
	pw_rec_file2.close();

	while(true)
	{
	}

//	sSocket.close();
//        d.close();
//       pout.close();
//        channel.close();


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
		return s;
		
	}


	public static void read_gmh(String s, int cur_frame_no, String mac_pdu )
	{
		
		/*String output6 = "";
		String frame_no = Integer.toString(cur_frame_no);
		try
		{
			ProcessBuilder launcher6 = new ProcessBuilder("read_gmh.exe", s, frame_no);

			Process process6 = launcher6.start();
			
			BufferedReader reader6 = new BufferedReader(new InputStreamReader(process6.getInputStream()));
			StringBuilder builder6 = new StringBuilder();
			System.out.println("before output");
			while ( (output6 = reader6.readLine()) != null) {
					
					System.out.println(output6);	
			}
			process6.waitFor();
			throw new InterruptedException("Exception encountered");
			
		}catch(IOException | InterruptedException ex)
		{
			//System.out.println(ex.toString());
			//throw ex;
		}*/

		String output8 = "";
		if(mac_pdu.charAt(11)=='1')
		{
			System.out.println("|  Incumbent detected                                                    |");	
			try{
				ProcessBuilder launcher8 = new ProcessBuilder("update_channels");
				System.out.println("|  Backup and Candidate channels updated                                 |");
				Process process8 = launcher8.start();
				BufferedReader reader8 = new BufferedReader(new InputStreamReader(process8.getInputStream()));
				StringBuilder builder8 = new StringBuilder();
				while ( (output8 = reader8.readLine()) != null) {
					operating_channel = output8;
						
				}
				process8.waitFor();
	
				switch_ = true;
				
				throw new InterruptedException("Exception encountered");
			}catch(IOException | InterruptedException ex)
			{
				//System.out.println(ex.toString());
				//throw ex;
			}
		}
		
	}

}

