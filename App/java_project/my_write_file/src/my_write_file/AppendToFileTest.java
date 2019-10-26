package my_write_file;

import java.io.File;

import java.io.FileWriter;
 
import java.io.BufferedWriter;
 
import java.io.IOException;

public class AppendToFileTest
{
	public static void main( String[] args )
	{
		try{
			String content = "my second java program";
			File file =new File("test_appendfile.txt");
 
	        if(!file.exists()){
	        	file.createNewFile();
	 
	        }
	        //使用true，即进行append file
	        FileWriter fileWritter = new FileWriter(file.getName(),true);
	 
	        BufferedWriter bufferWritter = new BufferedWriter(fileWritter);
	 
	        bufferWritter.write(content);
	 
	        bufferWritter.close();
	 
	        System.out.println("finish");
	        
		}catch(IOException e){
			e.printStackTrace();
    	}
	}
}
