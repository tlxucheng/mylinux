package my_excel_read;

import java.io.File;

import jxl.Cell;
import jxl.Sheet;
import jxl.Workbook;

public class ReadExcel {
	public static void main(String[] args) throws Exception {
		Workbook workbook = Workbook.getWorkbook(new File("test.xls"));
		Sheet sheet = workbook.getSheet(0);	
		int row_num = sheet.getRows();
		int col_num = sheet.getColumns();
		
		System.out.println("ÐÐ: "+row_num);
		System.out.println("ÁÐ: "+col_num);
		
		for(int i = 0; i < row_num; i++) {
			for(int j = 0; j < col_num; j++) {
				Cell cell = sheet.getCell(j, i);
				System.out.print(cell.getContents()+" ");
			}
			System.out.println();
		}
		
		workbook.close();
	}
}
