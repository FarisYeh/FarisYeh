
import java.net.Socket;
import java.util.*;
import java.io.*;

public class Client{
	public static void main(String args[]){
	String k;
	PrintWriter write;
	BufferedReader buff;
	Socket sc;
	BufferedReader bf;
	try{
	sc=new Socket("192.168.244.128",6786);
	System.out.println("----client-server connected----");
	buff=new BufferedReader(new InputStreamReader(System.in));
	System.out.println("What do you want to say : ");
	k=buff.readLine();
	write=new PrintWriter(sc.getOutputStream(),true);
	bf=new BufferedReader(new InputStreamReader(sc.getInputStream()));
	write.println(k);
	System.out.println("Someone said : "+bf.readLine());
	}catch(Exception ex){
	System.out.println("Connection refused");
}
}}
