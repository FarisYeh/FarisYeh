import java.net.Socket;
import java.util.Scanner;
import java.util.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.text.DateFormat;


public class TimeClient{

	public static void main(String args[]){
	String k;
	PrintWriter write;
	BufferedReader buff;
	Socket sc;
	BufferedReader bf;

	try{
	sc=new Socket("192.168.244.128",7778);
	Date u = new Date();
	String d_format = "HH";
	DateFormat df = new SimpleDateFormat(d_format);
	String newFormat = df.format(u);
	System.out.println("----client-server connected----");
	buff=new BufferedReader(new InputStreamReader(System.in));
	write=new PrintWriter(sc.getOutputStream(),true);
	write.println(newFormat);
	bf=new BufferedReader(new 
InputStreamReader(sc.getInputStream()));
	String msg=bf.readLine();

	System.out.println(msg);
	sc.close();
	}catch(Exception ex){

	System.out.println("Connection refused");

}

}}
