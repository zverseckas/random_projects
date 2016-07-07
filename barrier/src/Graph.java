/**
 * Multi-graph model
 * Created by zilvinas on 16.3.4.
 */
public class Graph {
    // Adjacency matrix
    private int[][] adjMatrix;
    // True/False depending on the directionality of a graph
    private boolean isDirectional;
    // Number of rows and cols in a matrix
    private int rows, cols;
    // Barrier instance
    private Barrier barrier;
    // Number of vertices
    private volatile int vertices;

    /** Worker class which does the summing
     * Of each row range independently
     */
    class Summator extends Thread {
        // Range
        int fromRow, toRow;
        public Summator(int fromRow, int toRow) {
            this.fromRow = fromRow;
            this.toRow = toRow;
        }
        @Override
        public void run() {
            // Wait till the barrier allows to run
            barrier.waitBarrier();
            vertices += getRowsSum(fromRow, toRow);
        }
    }

    /**
     * Initializes the graph model
     * @param adjMatrix - adjacency matrix
     * @param isDirectional - graph directionality property
     */
    public Graph(int[][] adjMatrix, boolean isDirectional) {
        this.adjMatrix = adjMatrix;
        this.rows = adjMatrix.length;
        this.cols = adjMatrix[0].length;
        this.isDirectional = isDirectional;
        // Initialize a barrier with a row number
        this.barrier = new Barrier(rows);
        // Set the vertices to "undefined"
        this.vertices = -1;
    }

    /**
     * Returns the number of vertices
     * @return number of vertices
     */
    public int getVertices() {
        // Return the cache if present
        if (vertices > -1) { return vertices; }
        // Proceed to summation
        vertices = 0;
        Summator[] summators = new Summator[rows];
        // Sum the matrix rows
        for(int i = 0; i < rows; i++) {
            summators[i] = new Summator(i, i);
            summators[i].start();
        }
        // Wait for the threads to finish
        for(int i = 0; i < rows; i++) {
            try { summators[i].join(); }
            catch (InterruptedException e) { e.printStackTrace(); }
        }
        return vertices;
    }

    /**
     * Returns the number of edges
     * @return number of edges
     */
    public int getEdges() {
        return isDirectional ? getVertices() : getVertices() / 2;
    }

    /**
     * Returns the adjacency matrix
     * @return the adjacency matrix
     */
//    public int[][] getAdjMatrix() {
//        return adjMatrix;
//    }

    /**
     * Computes the graph density
     * @return the graph density
     */
    public double getDensity() {
        return (double) getEdges() / (getVertices() * (getVertices() - 1));
    }

    /**
     * Return the sum of a row range
     * @param fromRow starting row
     * @param toRow ending row
     * @return sum of a row range
     */
    public int getRowsSum(int fromRow, int toRow) {
        int result = 0;
        for(int i = fromRow; i <= toRow; i++) {
            for (int j = 0; j < cols; j++) {
                result += adjMatrix[i][j];
            }
        }
        return result;
    }

    @Override
    public String toString() {
        String result = "";
        for(int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result += adjMatrix[i][j] + " ";
            }
            if (!(i == rows - 1)) { result += "\n"; }
        }
        return result;
    }
}