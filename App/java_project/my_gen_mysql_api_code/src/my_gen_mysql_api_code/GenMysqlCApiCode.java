package my_gen_mysql_api_code;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

class FileHandle {
	void WriteFile(String m_file_name, String m_content) throws Exception {
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

class CFileHandle extends FileHandle {
	private String m_table_name;
	
	public void SetTableName(String table_name) {
		m_table_name = table_name;		
	}
	
	public String GenHeadFileName() {
		return m_table_name + ".h";
	}
	
	public String GenSourceFileName() {
		return m_table_name + ".c";
	}
	
	public void WriteHeadFile() throws Exception {
		FileHandle filehandle = new FileHandle();
		String     head_file_name  = GenHeadFileName();
		String     content = "#include <stdio.h>";
		
		filehandle.WriteFile(head_file_name, content);
	}	
	
	public void WriteSourceFile() throws Exception {
		FileHandle filehandle = new FileHandle();
		String     head_file_name  = GenHeadFileName();
		String     source_file_name  = GenSourceFileName();
		String     content = "#include <" + head_file_name + ">";
		
		filehandle.WriteFile(source_file_name, content);
	}
}

class CppFileHandle extends FileHandle {
	
}

class JavaFileHandle extends FileHandle {
	
}

class NodeJsFileHandle extends FileHandle {
	
}

class PhpFileHandle extends FileHandle {
	
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
		
		
		CFileHandle cfilehandle = new CFileHandle();
		
		cfilehandle.SetTableName(m_file_name);
		cfilehandle.WriteHeadFile();
		cfilehandle.WriteSourceFile();
		
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
