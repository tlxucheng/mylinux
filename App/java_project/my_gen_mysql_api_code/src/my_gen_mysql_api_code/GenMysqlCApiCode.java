package my_gen_mysql_api_code;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

import java.util.ArrayList;
import java.util.List;

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
	
	public String GenHeadIfnDef() {
		String headnametran = m_table_name.toUpperCase() + "_" + "H_";
		
		return "#ifndef _" + headnametran + "\r" + "#define _" + headnametran;
	}
	
	public String GenEndline() {
		return "\r\n#endif";
	}
	
	public void WriteHeadFile() throws Exception {
		FileHandle filehandle = new FileHandle();
		String     head_file_name  = GenHeadFileName();
		
		filehandle.WriteFile(head_file_name, GenHeadIfnDef());
		filehandle.WriteFile(head_file_name, GenEndline());
	}	
	
	public void WriteSourceFile() throws Exception {
		FileHandle filehandle = new FileHandle();
		String     head_file_name  = GenHeadFileName();
		String     source_file_name  = GenSourceFileName();
		String     content = "#include <" + head_file_name + ">";
		
		filehandle.WriteFile(source_file_name, content);
	}
	
	public void WriteFieldsEnum (List<String> fields_str, int fields_num) throws Exception {
		String 		start_str = "\r\n\r\nenum\r\n{\r\n";
		String 		end_str = "}";
		String     	source_file_name  = GenSourceFileName();
		FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, start_str);
			
		for(int i = 0; i < fields_num; i++) {
			filehandle.WriteFile(source_file_name, "    "+m_table_name.toUpperCase()+"_"+fields_str.get(i).toUpperCase()+"\r\n");
		}
		
		filehandle.WriteFile(source_file_name, end_str);
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
	
		Cell cell = sheet.getCell(0, 0);		
		String m_file_name = cell.getContents();		
		
		CFileHandle cfilehandle = new CFileHandle();
		
		cfilehandle.SetTableName(m_file_name);
		cfilehandle.WriteHeadFile();
		cfilehandle.WriteSourceFile();

		List<String> Fields = ReadExcelFields();
			
		/* 表名+表字段 */
		cfilehandle.WriteFieldsEnum(Fields,GetExcelNum()-1);

		workbook.close();
	}
	
	String ReadExcelByIndex(int row, int col) throws Exception {
		Workbook workbook = Workbook.getWorkbook(new File("create_table_sql.xls"));
		Sheet sheet = workbook.getSheet(0);
		/* getCell(x,y)   第y行的第x列 */
		Cell cell = sheet.getCell(row, col);
		
		return cell.getContents();
	}
	
	String ReadExcelTableName() throws Exception {
		return ReadExcelByIndex(0, 0);
	}
	
	int GetExcelNum() throws Exception {
		Workbook workbook = Workbook.getWorkbook(new File("create_table_sql.xls"));
		Sheet sheet = workbook.getSheet(0);
		int row_num = sheet.getRows();
		workbook.close();
		
		return row_num;
	}
	
	List<String> ReadExcelFields() throws Exception {
		List<String> Fields = new ArrayList<>();	
		
		for(int i = 1 ; i < GetExcelNum() ; i++) {
			Fields.add(ReadExcelByIndex(0, i));
		}
			
		return Fields;
	}	
	
	void WriteExcel() {
		
	}
}

public class GenMysqlCApiCode {
	public static void main(String[] args) throws Exception {
		ExcelHandle excelhandle = new ExcelHandle();		
	
		excelhandle.ReadExcel();
		//excelhandle.ReadExcelTableName();
		
		System.out.println("finish");
	}
}
