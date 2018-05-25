import java.net.Socket;
import java.net.ServerSocket;
import java.io.*;

public class Server{

	public static void main(String [] args)
	{
	Socket sc;
	BufferedReader bf;
	ServerSocket ss;
	String j="assalamualaikum";
	String k;
	PrintWriter write;
		
	
	try
	{	
		System.out.println("Listening to the client ..");
		ss=new ServerSocket(6786);
		sc=ss.accept();
		System.out.println("-----connected-----");
		bf=new BufferedReader(new InputStreamReader(sc.getInputStream()));
		k=bf.readLine();
		write=new PrintWriter(sc.getOutputStream(),true);
		System.out.println("Client sent message : " + k);			
		if(k.equalsIgnoreCase(j))
		{
			write.println("Waalaikummussalam");
		}
		else
		{
			write.println("Are you muslim");
		}
	System.out.println("Replying to client......");
	System.out.println("--Connection Closed--");
	}
	catch(Exception ex){}	
	

}}
