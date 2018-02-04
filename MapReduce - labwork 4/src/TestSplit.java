///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///**
// *
// * @author long
// */
//public class TestSplit {
//
//    public static String replaceCharAt(String s, int pos, char c) {
//        return s.substring(0, pos) + c + s.substring(pos + 1);
//    }
//
//    public static void main(String[] args) {
//        StringBuilder testBuider = new StringBuilder("a          b c  d, e  f. g\nh i k l");
//        String test;
//        for (int i = 0; i < testBuider.length(); i++) {
//            if ((testBuider.charAt(i) == ' ') && (testBuider.charAt(1 + i) == ' ')) {
//                testBuider.deleteCharAt(i);
//                i--;
//            }
//        }
//        System.out.println(testBuider);
//        test = testBuider.toString();
//        String splited[];
//        
//        splited = test.split(" ");
//        int i=0;
//        System.out.println(test);
//        for (String string : splited) {
////            string.replaceAll("\\s+", "a");
//            System.out.println("string "+i+" : "+string);
//            i++;
//        }
//    }
//}
