package my_excel_prase;

import java.io.File;
import java.io.IOException;

import jxl.Workbook;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import jxl.write.biff.RowsExceededException;

/**
 * @author xc
 *
 */
public class CreateExcel {
	 public static void main(String[] args) 
			 throws IOException, RowsExceededException, WriteException {
	         
		 //1:����excel�ļ�
		 File file=new File("test.xls");
	     file.createNewFile();
	     
         //2:����������
         WritableWorkbook workbook=Workbook.createWorkbook(file);
	     //3:����sheet,���õڶ�����..��sheet���������Ƽ���
	    
         WritableSheet sheet=workbook.createSheet("�û�����", 0);
         
	     //4������titles
	     String[] titles={"���","�˺�","����"};
	     //5:��Ԫ��
	     Label label=null;
	     //6:����һ����������
	     for(int i=0;i<titles.length;i++){
	    	 //x,y,��һ�е�����
	    	 label=new Label(i,0,titles[i]);
	         //7����ӵ�Ԫ��
	    	 sheet.addCell(label);
	    	 }
	     //8��ģ�����ݿ⵼������
	     for(int i=1;i<10;i++){
	    	 //��ӱ�ţ��ڶ��е�һ��
	    	 label=new Label(0,i,i+"");
	    	 sheet.addCell(label);
	    	 
	    	 //����˺�
	    	 label=new Label(1,i,"10010"+i);
	    	 sheet.addCell(label);
	    	 
	    	 //�������
	    	 label=new Label(2,i,"123456");
	    	 sheet.addCell(label);
	    	 }
	     
	     //д�����ݣ�һ���ǵ�д�����ݣ���Ȼ�㶼��ʼ���������ˣ�excel����ɶ��û��
	     workbook.write();
	     //���һ�����رչ�����
	     workbook.close();
	     }
}
