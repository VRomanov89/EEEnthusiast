
public class main {

	public static void main(String[] args) {
		SinglyLinkedList<String> MyList = new SinglyLinkedList<String>();
		MyList.addFirst("element 1");
		MyList.addFirst("element 2");
		MyList.addFirst("element 3");
		MyList.addLast("element 4");
		MyList.addLast("element 5");
		MyList.addLast("element 6");
		MyList.reverseList();
		MyList.removeElement("element 4");
		while(!MyList.isEmpty()) {
			MyList.removeFirst();
		}
	}

}
