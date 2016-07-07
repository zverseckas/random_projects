package zilvinas.projects;

/**
 * Numerical integral model with an ability to do partial
 * integration. Initializes sum to 0.0 and allows increasing.
 * Created by zilvinas on 16.2.21.
 */
public class Integral {
    /**
     * Integral fields:
     * double sum  = total sum of integration
     * double a..b = integration range lower and upper respectively
     * int steps   = number of approximation trapezoids
     */
    private double sum;
    private double a, b;
    private int steps;

    /**
     * Custom integration function
     * @param x = function argument
     * @return (double) function value at x
     */
    private double complexSine(double x) {
        return Math.sin(x * Math.sin(x*x)) * Math.cos(x) + 1;
    }

    /**
     * Validates the range and steps
     * @param a     = integration lower bound
     * @param b     = integration upper bound
     * @param steps = number of approximation trapezoids
     * @return true if valid, false if not
     */
    private boolean validate(double a, double b, int steps) {
        if (steps > 100000) {
            System.err.println("Too many steps");
            return false;
        }
        if (a > b) {
            System.err.println("Invalid range");
            return false;
        }
        if (steps < 0) {
            System.err.println("Steps must be a natural number");
            return false;
        }
        if (Math.abs(b - a) > 1000000) {
            System.err.println("Range is too big");
            return false;
        }
        return true;
    }

    /**
     * Integral constructor
     * Initializes fields
     * @param a     = integration lower bound
     * @param b     = integration upper bound
     * @param steps = number of approximation trapezoids
     */
    public  Integral(double a, double b, int steps) {
        if (validate(a, b, steps)) {
            this.a = a;
            this.b = b;
            this.steps = steps;
        }
    }

    /**
     * Resize integration properties like range and steps
     * @param a     = integration lower bound
     * @param b     = integration upper bound
     * @param steps = number of approximation trapezoids
     */
    public void resize(double a, double b, int steps) {
        if (validate(a, b, steps)) {
            this.a = a;
            this.b = b;
            this.steps = steps;
        }
    }

    /**
     * Do the integration
     */
    public void integrate() {
        // The width of a step
        double gap = getRange() / steps;
        // Current integration step
        double pace = a;
        while (pace < b) {
            // Sum trapezoids under the curve (b - a) (f(a) + f(b)) / 2
            sum += gap * (complexSine(pace) + complexSine(pace += gap)) / 2;
        }
    }

    /**
     * Get the total sum of integration
     * @return (double) total sum of integration
     */
    public double getSum() {
        return sum;
    }

    /**
     * Get the scalar range of integration |b - a|
     * @return (double) scalar range of integration |b - a|
     */
    public double getRange() {
        return Math.abs(b - a);
    }

    /**
     * Get the array representation of an integration range [a,b]
     * @return (double[]) array representation of an integration range [a,b]
     */
    public double[] getRangeArray() {
        return new double[]{ a, b };
    }

    /**
     * Get the number of steps
     * @return (int) number of steps
     */
    public int getSteps() {
        return steps;
    }
}
