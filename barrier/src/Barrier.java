/**
 * Cyclic barrier
 * Created by zilvinas on 16.3.5.
 */

import java.util.ArrayList;

public class Barrier {
    // Modes for a thread
    private enum Mode { WAIT_MODE, RUN_MODE }
    // Array list for waiting threads
    private ArrayList<Thread> waitQueue;
    // Array list for ready to run threads
    private ArrayList<Thread> runQueue;
    // Current thread mode WAIT_MODE or RUN_MODE
    private Mode currentMode;
    // Number of one cycle threads
    private int numThreads;

    /**
     * Initializes a barrier instance
     * @param numThreads - number of threads per cycle
     */
    public Barrier(int numThreads) {
        this.waitQueue = new ArrayList<>();
        this.runQueue = new ArrayList<>();
        this.numThreads = numThreads;
        this.currentMode = Mode.WAIT_MODE;
    }

    /**
     * Handle all the waiting and releasing
     * of the barrier threads
     */
    public synchronized void waitBarrier() {
        // Capture a requesting thread
        Thread thread = Thread.currentThread();

        // It the barrier has been releasing the stack
        // of threads wait till it finishes
        while (currentMode == Mode.RUN_MODE) {
            try { this.wait_rand(); }
            catch (InterruptedException e) { e. printStackTrace(); }
        }

        // If the cycle is full of waiting threads release them
        if (waitQueue.size() == numThreads - 1) {

            // Make the wait queue become the run queue
            ArrayList<Thread> tmp;
            tmp = waitQueue;
            waitQueue = runQueue;
            runQueue = tmp;

            // Flag the mode as RUN_MoDE
            currentMode = Mode.RUN_MODE;

            // Release the waiting threads
            this.notifyAll();

            // Wait till all the threads get out of the queue
            while (runQueue.size() > 0) {
                try { this.wait_rand(); }
                catch (InterruptedException e) { e.printStackTrace(); }
            }
            // Run queue is now empty. Go on waiting mode
            currentMode = Mode.WAIT_MODE;

            // Notify any threads waiting for MODE_WAIT
            this.notifyAll();

            // numTreads - 1 have passed. Now does the current one
            return;
        }

        // Push a thread on a waiting list
        waitQueue.add(thread);

        // Wait until current mode changes
        while (currentMode == Mode.WAIT_MODE) {
            try { this.wait_rand(); }
            catch (InterruptedException e) { e.printStackTrace(); }
        }

        // Remove the last thread from the run queue
        runQueue.remove(runQueue.lastIndexOf(thread));

        // Release the last thread which was left waiting
        // For the run queue to get empty
        if (runQueue.size() == 0){
            this.notifyAll();
        }
    }

    /**
     * Dummy function imitating the spurious wake up
     * @throws InterruptedException
     */
    private synchronized void wait_rand() throws InterruptedException {
        if (Math.random() > 0.5) {
            wait();
        }
    }
}
