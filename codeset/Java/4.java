import java.util.*;

public class BST {
    class BSTNode {
        int data;
        BSTNode left;
        BSTNode right;
        public BSTNode(int item){
            data = item;
            left = right = null;
        }
    }
    BSTNode root;
    BST(){
        root = null;
    }

    void DeleteData(int data){
        root = deleteRec(root, data);
    }

    BSTNode deleteRec(BSTNode root, int data){
        //Empty Tree
        if (root == null){
            return root;
        }
        if (data < root.data){
            root.left = deleteRec(root.left, data);
        }else if (data > root.data){
            root.right = deleteRec(root.right, data);
        }else{
            //0-1 children
            if (root.left == null){
                return root.right;
            }else if (root.right == null){
                return root.left;
            }
            //2 children
            root.data =  minValueOfBSTNode(root.right);
            root.right = deleteRec(root.right, root.data);
        }
        return root;
    }

    int  minValueOfBSTNode(BSTNode root){
        int MinVal = root.data;
        while (root.left != null){
            MinVal = root.left.data;
            root = root.left;
        }
        return MinVal;
    }

    void insertCaller(int data){
        root = inserter(root, data);
    }

    BSTNode inserter(BSTNode root, int data){
        //Empty Tree
        if (root == null){
            root = new BSTNode(data);
            return root;
        }
        //Not Empty Tree
        if (data < root.data){
            root.left = inserter(root.left, data);
        }else if (data > root.data){
            root.right = inserter(root.right, data);
        }
        return root;
    }

    void InOrderCaller(){
        InOrder(root);
    }

    void InOrder(BSTNode root){
        if (root != null){
            InOrder(root.left);
            System.out.print(root.data + " ");
            InOrder(root.right);
        }
    }

    public static void main(String[] args){
        BST tree = new BST();

        List<Integer> AddToTree = Arrays.asList(7,5,1,6,9,4,2,3,8);
        for(int i = 0;i < AddToTree.size();i++){
            tree.insertCaller(AddToTree.get(i));
        }

        System.out.println("\nResulting BST Tree of InOrder Traversal :");
        tree.InOrderCaller();

        List<Integer> toDelete = Arrays.asList(1,2,3);
        for(int i = 0;i < toDelete.size();i++){
            tree.DeleteData(toDelete.get(i));
            System.out.println("\nResulting BST Tree of InOrder Traversal after " + toDelete.get(i) + " was deleted : ");
            tree.InOrderCaller();
        }
    }
}