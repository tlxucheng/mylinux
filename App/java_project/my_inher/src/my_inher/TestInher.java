package my_inher;

class father_print {
	void print() {
		System.out.println("father_print class.");
	}
}

class son_print extends father_print {
	void print() {
		System.out.println("son_print class.");
	}
}

public class TestInher {
	public static void main(String[] args) {
		father_print a = new father_print();
		a.print();
		
		son_print b = new son_print();
		b.print();
	}
}
