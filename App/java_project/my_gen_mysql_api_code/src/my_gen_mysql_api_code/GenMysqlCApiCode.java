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
	
	public void WriteFieldsEnum (List<String> fields_str) throws Exception {
		String 		start_str = "\r\n\r\nenum\r\n{\r\n";
		String 		end_str = "};";
		String     	source_file_name  = GenSourceFileName();
		FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, start_str);
			
		for(int i = 0; i < fields_str.size(); i++) {
			filehandle.WriteFile(source_file_name, "    "+m_table_name.toUpperCase()+"_"+fields_str.get(i).toUpperCase()+",\r\n");
		}
		
		filehandle.WriteFile(source_file_name, end_str);
	}
	
	public void GenFieldsEnum(List<String> fields_str, List<String> out_fields_str) {
		for(int i = 0; i < fields_str.size(); i++) {
			out_fields_str.add(m_table_name.toUpperCase()+"_"+fields_str.get(i).toUpperCase());
		}
	}
	
	/* 未测试if分支 */
    public String GenColNamesStaticVar() {
    	String str_table_type;
    	
    	/* CM的表 */
    	if(0 == m_table_name.compareTo("cc_talk"))
    	{
    		str_table_type = "CcTalk";
    	}
    	/* CR的表 */
    	else
    	{
    		str_table_type = "Cm";
    	}
    	
    	return str_table_type;
    }
    
    /* 增加一个处理字符串的类，方便进行需要生成代码字符串的特殊处理 */
    public String TranStringFirstCharToUpper(String inputStr) {
    	return inputStr.substring(0,1).toUpperCase() + inputStr.substring(1);
    }
    
    /* student_info ---> StudentInfo */
    public String GenTableNameCamelCase() {
    	String[] table_name_split = m_table_name.split("_");
    	String table_name_camel_case = TranStringFirstCharToUpper(table_name_split[0])
    			                         + TranStringFirstCharToUpper(table_name_split[1]);

    	return table_name_camel_case;
    }
	
    /* static DATABASE_CLOUMN_NAMES CmStudentInfoColumns[] = */
	public void WriteFielsColNames (List<String> fields_str) throws Exception {
		String 		start_str = "\r\n\r\nstatic DATABASE_CLOUMN_NAMES " + GenColNamesStaticVar()
		                        + GenTableNameCamelCase() + "Columns[] =\r\n";
		String      left_parenthesis = "{\r\n";
		String      end_str = "};\r\n\r\n";
		
		FileHandle 	filehandle = new FileHandle();
		String     	source_file_name  = GenSourceFileName();
		filehandle.WriteFile(source_file_name, start_str);  
		filehandle.WriteFile(source_file_name, left_parenthesis);  
		
		/* 产生{STUDENT_INFO_ID, "id", 0}, 暂时不考虑第三列的属性生成 */
		List<String> out_fields_str = new ArrayList<>();
		GenFieldsEnum(fields_str, out_fields_str);
		
		for(int i = 0; i < out_fields_str.size(); i++) {
			String colunm_name_fields_str = "    {"+ out_fields_str.get(i) + ", " + "\""+fields_str.get(i) + "\"" +", " + "0},\r\n";
			filehandle.WriteFile(source_file_name, colunm_name_fields_str);  
		}
		
		filehandle.WriteFile(source_file_name, end_str);  
	}
	
	public String GenColNameFunctionName() {
		return "Static char *" + GenColNamesStaticVar() + GenTableNameCamelCase() + "ColumnName" + "(int *seq)\r\n";
	}
	
	public String GenColNameFunctionBody() {
		return "    if(seq >= 0 || seq < sizeof(" + GenColNamesStaticVar() + GenTableNameCamelCase() + "Columns)"
			  + "/sizeof(DATABASE_CLOUMN_NAMES))\r\n" 
			  + "        return"+ GenColNamesStaticVar() + GenTableNameCamelCase() + "Columns[seq].name;\r\n"
			  + "    retur NULL;\r\n";
	}
	
	public void GenColNameFunction() throws Exception {
		String     	source_file_name  = GenSourceFileName();
		String      function_name = GenColNameFunctionName();
		String      left_parenthesis = "{\r\n";
		String      function_body = GenColNameFunctionBody();
		String      right_parenthesis = "}\r\n\r\n";
	    FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, function_name);  
		filehandle.WriteFile(source_file_name, left_parenthesis);  
		filehandle.WriteFile(source_file_name, function_body);  
		filehandle.WriteFile(source_file_name, right_parenthesis);  
	}
	
	public void GenInsertmMethodFunction(String method_str) throws Exception {
		String     	source_file_name  = GenSourceFileName();
		String      left_parenthesis = "{\r\n";
		String      right_parenthesis = "}\r\n\r\n";
	    FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, method_str+"\r\n");
		filehandle.WriteFile(source_file_name, left_parenthesis);
		filehandle.WriteFile(source_file_name, right_parenthesis);
	}

	public void GenDeleteMethodFunction(String method_str) throws Exception {
		String     	source_file_name  = GenSourceFileName();
		String      left_parenthesis = "{\r\n";
		String      right_parenthesis = "}\r\n\r\n";
	    FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, method_str+"\r\n");
		filehandle.WriteFile(source_file_name, left_parenthesis);
		filehandle.WriteFile(source_file_name, right_parenthesis);
	}
	
	public void GenUpdateMethodFunction(String method_str) throws Exception {
		String     	source_file_name  = GenSourceFileName();
		String      left_parenthesis = "{\r\n";
		String      right_parenthesis = "}\r\n\r\n";
	    FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, method_str+"\r\n");
		filehandle.WriteFile(source_file_name, left_parenthesis);
		filehandle.WriteFile(source_file_name, right_parenthesis);
	}
	
	public void GenGetMethodFunction(String method_str) throws Exception {
		String     	source_file_name  = GenSourceFileName();
		String      left_parenthesis = "{\r\n";
		String      right_parenthesis = "}\r\n\r\n";
	    FileHandle 	filehandle = new FileHandle();

		filehandle.WriteFile(source_file_name, method_str+"\r\n");
		filehandle.WriteFile(source_file_name, left_parenthesis);
		filehandle.WriteFile(source_file_name, right_parenthesis);
	}
	
	/* java定义枚举类型 0: insert, 1: delete, 2: update, 3: get */
	/* 是否可以用多态实现数据库操作函数 */
	public void GenMethodFunction(List<String> fields_str) throws Exception {
		
		for (int i = 0; i < fields_str.size(); i++) {
			String method_str = fields_str.get(i);
			switch(method_str)
			{
				case "insert":
					GenInsertmMethodFunction(method_str);
					break;
				case "delete":
					GenDeleteMethodFunction(method_str);
					break;
				case "update":
					GenUpdateMethodFunction(method_str);
					break;
				case "get":
					GenGetMethodFunction(method_str);
					break;
				default:
					break;
			}
		}
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
		List<String> Methods = ReadExcelMethods();
			
		/* 表名+表字段 */
		cfilehandle.WriteFieldsEnum(Fields);
		cfilehandle.WriteFielsColNames(Fields);
		cfilehandle.GenColNameFunction();
		cfilehandle.GenMethodFunction(Methods);
		
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

	int GetExcelFieldNum() throws Exception {
		Workbook workbook = Workbook.getWorkbook(new File("create_table_sql.xls"));
		Sheet sheet = workbook.getSheet(0);
		int row_num = sheet.getRows();
		int filed_num = 0;
		
		/* 第一行为表名 */
		for(int i = 1; i < row_num; i++) {
			/* getCell(x,y)   第y行的第x列 */
			Cell cell = sheet.getCell(0, i);
			if("" == cell.getContents()) {
				break;
			}
			filed_num++;
		}
		
		workbook.close();
		
		return filed_num;
	}
	
	List<String> ReadExcelFields() throws Exception {
		List<String> Fields = new ArrayList<>();	
		
		for(int i = 1 ; i <= GetExcelFieldNum() ; i++) {
			Fields.add(ReadExcelByIndex(0, i));
		}
			
		return Fields;
	}	
	
	/* 第11行开始读取4行方法 */
	List<String> ReadExcelMethods() throws Exception {
		List<String> Methods = new ArrayList<>();	

		/* 先固定在11~14行 */
		for(int i = 10 ; i < 14 ; i++) {
			Methods.add(ReadExcelByIndex(0, i));
		}		
		return Methods;
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
