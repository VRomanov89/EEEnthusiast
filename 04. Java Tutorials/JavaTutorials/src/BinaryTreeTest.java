
public class BinaryTreeTest<T> {
	public interface Location<T> {
		T getElement() throws IllegalStateException;
	}
	protected static class Node<T> implements Location {
		private T element;
		private Node<T> parent;
		private Node<T> left;
		private Node<T> right;
		public Node(T ele, Node<T> parentNode, Node<T> leftChild, Node<T> rightChild) {
			element = ele;
			parent = parentNode;
			left = leftChild;
			right = rightChild;
		}
		public T getElement() {
			return element;
		}
		public Node<T> getParent() {
			return parent;
		}
		public Node<T> getLeftChild() {
			return left;
		}
		public Node<T> getRightChild() {
			return right;
		}
		public void setElement(T ele) {
			element = ele;
		}
		public void setParent(Node<T> parentNode) {
			parent = parentNode;
		}
		public void setLeft(Node<T> leftChild) {
			left = leftChild;
		}
		public void setRight(Node<T> rightChild) {
			right = rightChild;
		}
	}
	
	protected Node<T> createNode(T ele, Node<T> parent, Node<T> left, Node<T> right) {
		return new Node<T>(ele, parent, left, right);
	}
	
	protected Node<T> root = null;
	private int size = 0;
	public BinaryTreeTest() { }
	
	protected Node<T> validate(Location<T> loc) throws IllegalArgumentException {
		if(!(loc instanceof Node)) {
			throw new IllegalArgumentException("Not a valid location type");
		}
		Node<T> node = (Node<T>) loc;
		if (node.getParent() == node) {
			throw new IllegalArgumentException("loc is not in the tree");
		}
		return node;
	}
	
	public int size() {
		return size;
	}
	public boolean isEmpty() { 
		return size() == 0; 
	}
	public Location<T> root() {
		return root;
	}
	public Location<T> parent(Location<T> loc) throws IllegalArgumentException {
		Node<T> node = validate(loc);
		return node.getParent();
	}
	public Location<T> left(Location<T> loc) throws IllegalArgumentException {
		Node<T> node = validate(loc);
		return node.getLeftChild();
	}
	public Location<T> right(Location<T> loc) throws IllegalArgumentException {
		Node<T> node = validate(loc);
		return node.getRightChild();
	}

	public Location<T> addRoot(T ele) throws IllegalStateException {
		if(!isEmpty()) throw new IllegalStateException("Tree isn't empty!");
		root = createNode(ele, null, null, null);
		size = 1;
		return root;
	}
	
	public Location<T> addLeft(Location<T> loc, T ele) throws IllegalArgumentException {
		Node<T> parent = validate(loc);
		if (parent.getLeftChild() != null) {
			throw new IllegalArgumentException("This node already has a left child!");
		}
		Node<T> child = createNode(ele, parent, null, null);
		parent.setLeft(child);
		size++;
		return child;
	}
	
	public Location<T> addRight(Location<T> loc, T ele) throws IllegalArgumentException {
		Node<T> parent = validate(loc);
		if(parent.getLeftChild() != null) {
			throw new IllegalArgumentException("This node already has a right child!");
		}
	}
	
	
}
