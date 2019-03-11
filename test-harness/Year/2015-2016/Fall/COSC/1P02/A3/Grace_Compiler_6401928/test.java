package Ex4;
import BasicIO.*;

 /**
    * @author  Admiral Grace Compiler
    * @studentNum 64013928
    */


public class test {

  private ASCIIDisplayer display;

  public test(){
    display = new ASCIIDisplayer();
    Node list, list2, p, q, r;
    list = new Node(5, null);
    p = list;
    for (int i=4; i>0; i--){
      p.prev = new Node(i,p);
      p= p.prev;
      list = p;
    }
    p = list;
    while(p.next!=null){
      p=p.next;

    }

    list2 = new Node(p.item,null);
    while (p.prev!=null){
      p=p.prev;
      list2 = new Node(p.item,list2);
    }

    p = list;
    q = list2;

    while(p!=null){
    display.writeInt(p.item);
    display.newLine();
    p = p.next;
    }

    while(q!=null){
    display.writeInt(q.item);
    display.newLine();
    q = q.next;
    }
    display.close();
  }

    public static void main (String[] args) {test t= new test();};
}


