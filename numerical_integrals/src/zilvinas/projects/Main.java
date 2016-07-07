package zilvinas.projects;

/**
 * A program demonstrates a basic meaning of resource used
 * by multiple threads synchronization. The numeric integral
 * calculation was used as a generic problem of a program.
 * TESTING: http://www.wolframalpha.com/widgets/view.jsp?id=8ab70731b1553f17c11a3bbc87e0b605
 */
public class Main {
    public static void main(String[] args) {
        // Create an integral that is intended to calculate
        Integral integral = new Integral(-2, 5, 100000);

        // Create an integrator instance
        ParallelIntegrator parallelIntegrator = new ParallelIntegrator(integral, 5, true);
        // Do the calculations
        parallelIntegrator.pretendYouWork();

        System.out.println("Integral of a function = " + integral.getSum());
    }
}
