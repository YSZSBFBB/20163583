package search;

import java.util.Scanner;
 
public class HotelDemo 
{
 //д�������棬��ÿ�����������Է��ʵ��������˲������ݵķ�����
 static int h=5,w=10;
 static String[][] rooms=new String[5][10];
 public static void main(String[] args) 
 {
  @SuppressWarnings("resource")
  Scanner s=new Scanner(System.in);
  while(true)
  {
   System.out.println("������ in,out,search,quit:");
   String temp=s.next();
   int room=0;
   if("in".equals(temp))
   {//��ֹ���ֿ�ָ���쳣��
    System.out.println("���뷿��ţ�");
    room=s.nextInt();
    System.out.println("�������֣�");
    String name=s.next();
    if(in(room,name)) System.out.println("��ס��ɣ�");
    System.out.println("room"+room+"name"+name);
   }
   else if("out".equals(temp))
   {
    System.out.println("���뷿��ţ�");
    room=s.nextInt();
    if(out(room)) System.out.println("�˷���ɣ�");
    System.out.println("out"+room);
   }
   else if("search".equals(temp))
   {
    System.out.println("���뷿��ţ�-1����ȫ������");
    room=s.nextInt();
    search(room);
   }
   else if("quit".equals(temp)||"exit".equals(temp))
   {
    break;
   }
   else
   {
    System.out.println("�������");
   }
  }
 }
 
 private static boolean search(int room) 
 {
  if(room==-1){
   //��ӡ���е���Ϣ��
   for(int i=0;i<h;i++)
   {
    for(int j=0;j<w;j++)
    {
     int room2=(i+1)*100+j+1;
     System.out.print(room2+"\t");
    }
    System.out.println();
    for(int k=0;k<w;k++)
    {
     System.out.print(rooms[i][k]==null?"empty":rooms[i][k]);
     System.out.print("\t");
    }
    System.out.println();
    System.out.println();
   }
   return true;
    
  }
  else
  {
   int r=room/100-1;
   int c=room%100-1;
   if(r<0||r>=h||c<0||c>=w)
   {
    System.out.println("����Ŵ���");
    return false;
   }
   System.out.println(rooms[r][c]==null?"empty":rooms[r][c]);
   return true;
  }
 }
 
 private static boolean out(int room)
 {
  int r=room/100-1;
  int c=room%100-1;
  if(r<0||r>=h||c<0||c>=w)
  {
   System.out.println("����Ŵ���");
   return false;
  }
  if(rooms[r][c]==null||"".equals(rooms[r][c]))
  {//
   System.out.println("�˷���û���ˣ�");
   return false;
  }
  rooms[r][c]=null;
  return true;
 }
 
 private static boolean in(int room, String name) 
 {
  int r=room/100-1;
  int c=room%100-1;
  if(r<0||r>=h||c<0||c>=w)
  {
   System.out.println("����Ŵ���");
   return false;
  }
  if(rooms[r][c]!=null)
  {//
   System.out.println("�˷����Ѿ����ˣ�");
   return false;
  }
 
  rooms[r][c]=name;
  return true;
  
 }
 
}