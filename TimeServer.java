import java.net.Socket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.UnknownHostException;
import java.io.*;



public class TimeServer{
	public static void main(String [] args)
	{
	Socket sc;
	BufferedReader bf;
	ServerSocket ss;
	String k;
	PrintWriter write;
	try
	{	

		System.out.println("Listening to the client ..");
		ss=new ServerSocket(7778);
		sc=ss.accept();
		System.out.println("-----connected-----");
		bf=new BufferedReader(new InputStreamReader(sc.getInputStream()));
		write=new PrintWriter(sc.getOutputStream(),true);

		//String u = bf.readLine();
		//System.out.println(u);
		//char option1=u.charAt(15);
		//char option2=u.charAt(15);
	
		int u = Integer.parseInt(bf.readLine());		
		if(u<12)
		write.println("good morning");

		else if(u>=12&&u<13)
		write.println("good afternoon");
			
		else if(u>=13&&u<20)
		write.println("good evening");
		
		else
		write.println("good night");
		sc.close();
	}

	catch(Exception ex){}	

	



}}
