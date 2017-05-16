
public class Stack<E> {
	private SinglyLinkedList<E> list = new SinglyLinkedList<>();
	public Stack() {}
	public int size() {
		return list.size();
	}
	public boolean isEmpty() {
		return list.isEmpty();
	}
	public void push(E element) {
		list.addFirst(element);
	}
	public E pop() {
		return list.removeFirst();
	}
	public E top() {
		return list.first();
	}
	

}
