
public class SinglyLinkedList<T> {
	//Implement a Node
	private static class Node<T> {
		private T element;
		private Node<T> next;
		public Node(T e, Node<T> n) {
			element = e;
			next = n;
		}
		public T getElement() {
			return element;
		}
		public Node<T> getNext() {
			return next;
		}
		public void setNext(Node<T> n) {
			next = n;
		}
	}
	
	// List Implementation
	private Node<T> head = null;
	private Node<T> tail = null;
	private int size = 0;
	public SinglyLinkedList() {};
	public int size() {
		return size;
	}
	public boolean isEmpty() {
		return size == 0;
	}
	public T first() {
		if(isEmpty()) {
			return null;
		}
		return head.getElement();
	}
	public T last() {
		if(isEmpty()) {
			return null;
		}
		return tail.getElement();
	}
	public void addFirst(T e) {
		head = new Node<>(e, head);
		if(size == 0) {
			tail = head;
		}
		size++;
		System.out.println("Added head node with '" + head.getElement() + "' element.");
	}
	public void addLast(T e) {
		Node<T> newNode = new Node<>(e, null);
		if(isEmpty()) {
			head = newNode;
		}else{
			tail.setNext(newNode);
		}
		tail = newNode;
		size++;
		System.out.println("Added tail node with '" + tail.getElement() + "' element.");
	}
	public T removeFirst() {
		if(isEmpty()) {
			return null;
		}
		T answer = head.getElement();
		head = head.getNext();
		size--;
		if(size == 0) {
			tail = null;
		}
		System.out.println("Removed head node with '" + answer + "' element.");
		return answer;
	}
	public void reverseList() {
		if(size <= 1) {
			
		}else if(size == 2) {
			tail.setNext(head);
			head = tail;
			tail = head.getNext();
			tail.setNext(null);
		}else {
			Node<T> current = head;
			Node<T> currentNext = head.getNext();
			Node<T> currentNextNext = currentNext.getNext();
			tail = head;
			while(currentNext != null) {
				currentNext.setNext(current);
				current = currentNext;
				currentNext = currentNextNext;
				if(currentNextNext != null) {
					currentNextNext = currentNextNext.getNext();
				}
			}
			tail.setNext(null);
			head = current;
		}
		
	}
	public T removeElement(T e) {
		Node<T> current = head;
		Node<T> previous = head;
		int position = 0;
		while(current !=null && current.getElement() != e) {
			previous = current;
			current = current.getNext();
			position++;
		}
		if(current == null) {
			return null;
		}else {
			if(head == current) {
				head = current.getNext();
			}else if(tail == current) {
				tail = previous;
				tail.setNext(null);
			}else {
				previous.setNext(current.getNext());
			}
			System.out.println("Found & removed node at position " + position);
			size--;
			return current.getElement();
		}
	}
}
