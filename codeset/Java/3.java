import java.util.Iterator;
import java.util.NoSuchElementException;

/**
This class implements a hash set using separate chaining.
*/
public class HashTable
{
  private Node[] buckets;
  private int currentSize;
  private float loadFactor;


  /**
  Constructs a hash table.
  @param bucketsLength the length of the buckets array
  */

  public HashTable(int bucketsLength)
  {
    buckets = new Node[bucketsLength];
    currentSize = 0;
  }


  private int hashCode(int value)
  {
    return Math.abs(value) % elements.length;
  }

  /**
  Tests for set membership.
  @param x an object
  @return true if x is an element of this set
  */

  public boolean contains(Object x)
  {
    int h = x.hashCode();
    if (h < 0) { h = -h; }
    h = h % buckets.length;
    Node current = buckets[h];
    while (current != null)
    {
      if (current.data.equals(x)) { return true; }
      current = current.next;
    }
    return false;
  }

  /**
  Adds an element to this set.
  @param x an object
  @return true if x is a new object, false if x was
  already in the set
  */

  public boolean add(Object x)
  {
    int h = x.hashCode();
    if (h < 0) { h = -h; }
    h = h % buckets.length;

    Node current = buckets[h];
    while (current != null)
    {
      if (current.data.equals(x)) { return false; }
      // Already in the set
      current = current.next;
    }
    Node newNode = new Node();
    newNode.data = x;
    newNode.next = buckets[h];
    buckets[h] = newNode;
    currentSize++;
    return true;
  }

  /**
  Removes an object from this set.
  @param x an object
  @return true if x was removed from this set, false
  if x was not an element of this set
  */

  public boolean remove(Object x)
  {
    int h = x.hashCode();
    if (h < 0) { h = -h; }
    h = h % buckets.length;

    Node current = buckets[h];
    Node previous = null;
    while (current != null)
    {
      if (current.data.equals(x))
      {
        if (previous == null) { buckets[h] = current.next; }
        else { previous.next = current.next; }
        currentSize--;
        return true;
      }
      previous = current;

      current = current.next;
    }
    return false;
  }

  private void rehash() {
    int[] old = elements;
    elements = new int[2 * old.length];
    size = 0;
    for (int value : old) {
        if (value != 0 && value != REMOVED) {
            add(value);
        }
    }
  }

  public void addRehash(int value) {
    if ((double) size / elements.length >= 0.75) {
        rehash();
    }
  }

  /**
  Returns an iterator that traverses the elements of this set.
  @return a hash set iterator
  */

  public Iterator iterator()
  {
    return new HashSetIterator();
  }

  /**
  Gets the number of elements in this set.
  @return the number of elements
  */

  public int size()
  {
    return currentSize;
  }

  class Node
  {
    public Object data;
    public Node next;
  }

  class HashSetIterator implements Iterator
  {
  private int bucket;
  private Node current;

  /**
  Constructs a hash set iterator that points to the
  first element of the hash set.
  */
  public HashSetIterator()
  {
    current = null;
    bucket = -1;
  }

  public boolean hasNext()
  {
    if (current != null && current.next != null) { return true; }
    for (int b = bucket + 1; b < buckets.length; b++)
    {
      if (buckets[b] != null) { return true; }
    }
    return false;
  }

  public Object next()
  {
    if (current != null && current.next != null)
    {
      current = current.next; // Move to next element in bucket
    }
    else // Move to next bucket
    {
      do
      {
        bucket++;
        if (bucket == buckets.length)
        {
          throw new NoSuchElementException();
        }
        current = buckets[bucket];
      }
      while (current == null);
    }
    return current.data;
  }

  public void remove()
  {
    throw new UnsupportedOperationException();
  }
 }
}