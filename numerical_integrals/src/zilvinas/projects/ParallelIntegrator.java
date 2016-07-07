package zilvinas.projects;

/**
 * Integrates a function partially using Threads.
 * Can be both synchronized and not synchronized
 * Created by zilvinas on 16.2.21.
 */
public class ParallelIntegrator {

    /**
     * Instance fields
     * Integral integral = instance of a processed integral
     * int threads       = number of threads calculating the integral
     * boolean sync      = determines whether the threads are synced
     */
    private final Integral integral;
    private int threads;
    private boolean sync;

    /**
     * Inner working class extends Thread
     * does the partial integration
     */
    private class Worker extends Thread {
        /**
         * Instance fields
         * double a..b = integration range lower and upper respectively
         * int steps   = number of approximation trapezoids
         * NOTE: differs from Integral instance fields because
         * does the PARTIAL integration
         */
        private double a, b;
        private int steps;

        /**
         * Instance constructor
         * @param a     = integration lower bound
         * @param b     = integration upper bound
         * @param steps = number of approximation trapezoids
         */
        public Worker(double a, double b, int steps) {
            this.a = a; this.b = b;
            this.steps = steps;
        }

        @Override
        public void run() {
            if (sync) {
                synchronized (integral) {
                    // CRITICAL section
                    integral.resize(a, b, steps);
                    integral.integrate();
                    // End of CRITICAL section
                }
            } else {
                // CRITICAL section
                integral.resize(a, b, steps);
                integral.integrate();
                // End of CRITICAL section
            }
        }
    }

    /**
     * Instance constructor
     * @param integral = instance of a processed integral
     * @param threads  = number of threads calculating the integral
     * @param sync     = determines whether the threads are synced
     */
    public  ParallelIntegrator(Integral integral, int threads, boolean sync) {
        this.integral = integral;
        this.threads = threads;
        this.sync = sync;
    }

    /**
     * Does the work. Splits the process to a given number of threads
     * and calculates.
     */
//    public void work() {
//
//        // Partial gap
//        double gap = integral.getRange() / threads;
//        // Partial pace
//        double pace = integral.getRangeArray()[0];
//
//        // Array of workers
//        Worker[] workerList = new Worker[threads];
//
//        for(int i = 0; i < threads; i++) {
//            workerList[i] = new Worker(pace, pace += gap, integral.getSteps());
//            workerList[i].start();
//            try {
//                workerList[i].join();
//            } catch (InterruptedException exception) {
//                  System.err.println("Thread interrupted " + exception);
//            }
//        }
//    }

    /**
     * THIS IS A BAD THING BUT ASKED AT UNIVERSITY
     * Pretends that the threads work but actually
     * demonstrates bad synchronization
     */
    public void pretendYouWork() {

        double gap = integral.getRange() / 2;
        double pace = integral.getRangeArray()[0];

        try {
            Worker w1 = new Worker(pace, pace += gap, integral.getSteps());
            w1.start();
            Worker w2 = new Worker(pace, pace + gap, integral.getSteps());
            w2.start();
            w1.join(); w2.join();
        } catch (InterruptedException exception) {
            System.err.println("Thread interrupted " + exception);
        }
    }
}
