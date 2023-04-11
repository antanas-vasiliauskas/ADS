public class A {
    public static void main(String args[]){new A();}
    public A(){System.out.print("A");}
    B b1 = new B();
    static B b2 = new B();
    static A a = new A();
  }
  class B {
    public B(){System.out.print("B");}
  }
