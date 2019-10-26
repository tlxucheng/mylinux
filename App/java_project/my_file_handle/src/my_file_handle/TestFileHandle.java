package my_file_handle;

import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter; 
import java.io.IOException;

class MyFileHandle {
	public void Read(String m_dir, String m_file_name) {
		
	}
	
	public void Write(String m_file_name, String m_content) {
		try {
			File file = new File(m_file_name);
			
	        if(!file.exists()){
	        	file.createNewFile();
	 
	        }
	        
	        FileWriter fileWritter = new FileWriter(file.getName(),true);
	        BufferedWriter bufferWritter = new BufferedWriter(fileWritter);
	        bufferWritter.write(m_content);
	        bufferWritter.close();
	        System.out.println("finish");
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	
	private String file_name;
	private String dir;
}


public class TestFileHandle {
	public static void main( String[] args ) {
		MyFileHandle test = new MyFileHandle();
		test.Write("my_test_file_handle.txt", "hell world!");
	}
}
