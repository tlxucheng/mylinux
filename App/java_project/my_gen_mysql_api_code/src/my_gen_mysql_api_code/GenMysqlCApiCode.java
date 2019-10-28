package my_gen_mysql_api_code;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

class FileHandle {
	void WirteFile(String m_file_name, String m_content) throws Exception {
		File file = new File(m_file_name);
		
		if(!file.exists()){
			file.createNewFile();	 
	    }
		
        FileWriter fileWritter = new FileWriter(file.getName(),true);
        BufferedWriter bufferWritter = new BufferedWriter(fileWritter);
        bufferWritter.write(m_content);
        bufferWritter.close();
        System.out.println("finish");
	}
	
	void ReadFile() {
		
	}
}

class ExcelHandle {
	void ReadExcel() throws Exception {
		Workbook workbook = Workbook.getWorkbook(new File("create_table_sql.xls"));
		Sheet sheet = workbook.getSheet(0);	
		int row_num = sheet.getRows();
		int col_num = sheet.getColumns();
	
		Cell cell = sheet.getCell(0, 0);		
		System.out.print(cell.getContents()+" ");
		cell = sheet.getCell(1, 0);
		String m_file_name = cell.getContents();
		System.out.println(m_file_name);
		
		FileHandle filehandle = new FileHandle();
		
		String c_file = m_file_name+".c";;
		String h_file = m_file_name+".h";;
		
		filehandle.WirteFile(c_file, "hello world!");
		filehandle.WirteFile(h_file, "hello world!");

		workbook.close();
	}
	
	void WriteExcel() {
		
	}
}

public class GenMysqlCApiCode {
	public static void main(String[] args) throws Exception {
		ExcelHandle excelhandle = new ExcelHandle();		
	
		excelhandle.ReadExcel();		
	}
}
