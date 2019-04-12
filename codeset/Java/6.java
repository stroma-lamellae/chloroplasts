
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package cps616.lab.pkg7;
/**
 *
 * @author minim_000
 */
public class Lab7 {

    public static class Symbol {

        private char value;
        private int frequency;
        private String codeword;
        private int number;

        public Symbol(char v, int f) {
            value = v;
            frequency = f;
            codeword = "";
            number = 0;
        }

        public void setNumber(int n) {
            number = n;
        }

        public char getKey() {
            return value;
        }

        public int getFrequency() {
            return frequency;
        }

        public void updateCodeword(String s) {
            codeword = s + codeword;
        }

        public int getNumber() {
            return number;
        }

        public String getCodeword() {
            return codeword;
        }
    }

    public static class Tree {

        private final Tree leftTree;
        private final Tree rightTree;
        private final Symbol leftSymbol;
        private final Symbol rightSymbol;
        private final int totalFrequency;
        private final int type;
        private final int number;

        public Tree(Tree lt, Tree rt, int num) {
            leftTree = lt;
            rightTree = rt;
            leftSymbol = null;
            rightSymbol = null;
            totalFrequency = lt.getFrequency() + rt.getFrequency();
            type = 1;
            number = num;
        }

        public Tree(Tree lt, Symbol rs, int num) {
            leftTree = lt;
            rightTree = null;
            leftSymbol = null;
            rightSymbol = rs;
            totalFrequency = lt.getFrequency() + rs.getFrequency();
            type = 2;
            number = num;
        }

        public Tree(Symbol ls, Tree rt, int num) {
            leftTree = null;
            rightTree = rt;
            leftSymbol = ls;
            rightSymbol = null;
            totalFrequency = ls.getFrequency() + rt.getFrequency();
            type = 3;
            number = num;
        }

        public Tree(Symbol ls, Symbol rs, int num) {
            leftTree = null;
            rightTree = null;
            leftSymbol = ls;
            rightSymbol = rs;
            totalFrequency = ls.getFrequency() + rs.getFrequency();
            type = 4;
            number = num;
        }

        public int getFrequency() {
            return totalFrequency;
        }

        public Tree treeLeft() {
            return leftTree;
        }

        public Tree treeRight() {
            return rightTree;
        }

        public Symbol symbolLeft() {
            return leftSymbol;
        }

        public Symbol symbolRight() {
            return rightSymbol;
        }

        public int getType() {
            return type;
        }

        public int getNumber() {
            return number;
        }

        public String getTree() {
            String s = " " + Integer.toString(totalFrequency);
            switch (type) {
                case 1:
                    s = s + " N" + leftTree.getNumber() + " N" + rightTree.getNumber();
                    break;
                case 2:
                    s = s + " N" + leftTree.getNumber() + " L" + rightSymbol.getNumber();
                    break;
                case 3:
                    s = s + " L" + leftSymbol.getNumber() + " N" + rightTree.getNumber();
                    break;
                case 4:
                    s = s + " L" + leftSymbol.getNumber() + " L" + rightSymbol.getNumber();
                    break;
                default:
                    break;
            }
            return s;
        }

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ArrayList<Symbol> s;
        ArrayList<Tree> t;
        Scanner sc = new Scanner(System.in);
        char[] input = sc.nextLine().toCharArray();
        HashMap<Character, Integer> hmap = new HashMap();
        for (int x = 0; x < input.length; x++) {
            if (hmap.containsKey(input[x])) {
                hmap.put(input[x], hmap.get(input[x]) + 1);
            } else {
                hmap.put(input[x], 1);
            }
        }
        Map<Character, Integer> map = sortValue(hmap);

        s = sortKey(map);
        t = buildTree(s);
        for (int x = 0; x < s.size(); x++) {
            Symbol y = s.get(x);
            y.setNumber(x);
            System.out.println("L" + y.getNumber() + " " + y.getKey() + " " + y.getFrequency() + " " + y.getCodeword());
        }
        System.out.println();
        for (int x = 0; x < t.size(); x++) {
            Tree y = t.get(x);
            System.out.println("N" + x + y.getTree());
        }
    }

    private static ArrayList<Tree> buildTree(ArrayList<Symbol> symbolList) {
        int x = 2;
        int tlFront = 0;
        int tlBack = 1;
        ArrayList<Tree> treeList = new ArrayList(symbolList.size() - 1);
        treeList.add(new Tree(symbolList.get(0), symbolList.get(1), 0));
        symbolList.get(0).updateCodeword("0");
        symbolList.get(1).updateCodeword("1");
        while (x < symbolList.size()) {
            Symbol s1 = symbolList.get(x);
            Tree t1 = treeList.get(tlFront);
            if (s1.getFrequency() < t1.getFrequency()) {
                if (x < symbolList.size() - 1) {
                    Symbol s2 = symbolList.get(x + 1);
                    if (s2.getFrequency() < t1.getFrequency()) {
                        treeList.add(new Tree(s1, s2, tlBack));
                        s1.updateCodeword("0");
                        s2.updateCodeword("1");
                        x++;
                    } else {
                        treeList.add(new Tree(s1, t1, tlBack));
                        s1.updateCodeword("0");
                        addCodeword(t1, "1");
                        tlFront++;
                    }
                    x++;
                } else {
                    treeList.add(new Tree(s1, t1, tlBack));
                    s1.updateCodeword("0");
                    addCodeword(t1, "1");
                    tlFront++;
                    x++;
                }
            } else {
                if (tlFront < treeList.size() - 1) {
                    Tree t2 = treeList.get(tlFront + 1);
                    if (s1.getFrequency() < t2.getFrequency()) {
                        treeList.add(new Tree(t1, s1, tlBack));
                        addCodeword(t1, "0");
                        s1.updateCodeword("1");
                        x++;
                    } else {
                        treeList.add(new Tree(t1, t2, tlBack));
                        addCodeword(t1, "0");
                        addCodeword(t2, "1");
                        tlFront++;
                    }
                    tlFront++;
                } else {
                    treeList.add(new Tree(t1, s1, tlBack));
                    addCodeword(t1, "0");
                    s1.updateCodeword("1");
                    x++;
                    tlFront++;
                }
            }
            tlBack++;
        }
        while (tlBack < symbolList.size()-1) {
            treeList.add(new Tree(treeList.get(tlFront), treeList.get(tlFront + 1), tlBack));
            addCodeword(treeList.get(tlFront), "0");
            addCodeword(treeList.get(tlFront + 1), "1");
            tlFront += 2;
            tlBack++;
        }
        return treeList;
    }

    private static void addCodeword(Tree tree, String s) {
        switch (tree.getType()) {
            case 1:
                addCodeword(tree.treeLeft(), s);
                addCodeword(tree.treeRight(), s);
                break;
            case 2:
                addCodeword(tree.treeLeft(), s);
                tree.symbolRight().updateCodeword(s);
                break;
            case 3:
                addCodeword(tree.treeRight(), s);
                tree.symbolLeft().updateCodeword(s);
                break;
            case 4:
                tree.symbolLeft().updateCodeword(s);
                tree.symbolRight().updateCodeword(s);
                break;
            default:
                break;
        }
    }

    private static ArrayList<Symbol> sortKey(Map<Character, Integer> map) {
        ArrayList<Symbol> list = new ArrayList(map.size());
        int freq;
        for (Map.Entry<Character, Integer> e : map.entrySet()) {
            freq = e.getValue();
            if (list.isEmpty()) {
                list.add(new Symbol(e.getKey(), e.getValue()));
            } else {
                for (int x = 0; x < list.size(); x++) {
                    if (x == list.size() - 1) {
                        if (freq > list.get(x).getFrequency()) {
                            list.add(new Symbol(e.getKey(), e.getValue()));
                            break;
                        }
                        if ((int) (e.getKey()) > (int) list.get(x).getKey()) {
                            list.add(new Symbol(e.getKey(), e.getValue()));
                            break;
                        }
                    }
                    if (freq < list.get(x).getFrequency()) {
                        list.add(x, new Symbol(e.getKey(), e.getValue()));
                        break;
                    }

                    if ((int) e.getKey() < (int) list.get(x).getKey() && e.getValue() == list.get(x).getFrequency()) {
                        list.add(x, new Symbol(e.getKey(), e.getValue()));
                        break;
                    }

                }
            }
        }
        return list;
    }

    private static HashMap sortValue(HashMap hmap) {
        List list = new LinkedList(hmap.entrySet());
        // Defined Custom Comparator here
        Collections.sort(list, new Comparator() {
            public int compare(Object o1, Object o2) {
                return ((Comparable) ((Map.Entry) (o1)).getValue())
                        .compareTo(((Map.Entry) (o2)).getValue());
            }
        });
        HashMap sortedHashMap = new LinkedHashMap();
        for (Iterator it = list.iterator(); it.hasNext();) {
            Map.Entry entry = (Map.Entry) it.next();
            sortedHashMap.put(entry.getKey(), entry.getValue());
        }
        return sortedHashMap;
    }
}