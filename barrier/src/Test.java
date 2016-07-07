public class Test extends Thread {
    private int delay;
    private Barrier b;
    public Test(int delay, Barrier b) {
        this.delay = delay;
        this.b = b;
    }
    @Override
    public void run() {
        for(int i = 0; i < 3; i++) {
            try {
                sleep(delay);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(this.getName() + " Wait");
            b.waitBarrier();
            System.out.println(this.getName() + " Run");
        }
    }
}