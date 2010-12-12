package com.notatrick.csm.applalgos.finalproj;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import Jama.Matrix;

public class MultiplicativeUpdate {

    private static double MIN_ALLOWABLE_DIFF = .02;
    private static double MIN_CHANGE_CUTOFF = .01;
    private static double EPSILON = .00000000001;

    /**
     * @param v
     *            The data matrix of size
     * @param numFeatures
     *            The number of features to find
     * @return The weights and feature matrices
     */
    public List<Matrix> buildMatrix(Matrix v, int numFeatures, int maxNumIter) {

        // Start with random values
        Matrix w = Matrix.random(v.getRowDimension(), numFeatures);
        Matrix h = Matrix.random(numFeatures, v.getColumnDimension());

        double lastDiff = Double.MAX_VALUE;

        for (int i = 0; i < maxNumIter; i++) {

            double diff = calcMSE(v, w.times(h));

            // System.out.println(i + " : " + diff);

            if (diff < MIN_ALLOWABLE_DIFF || i >= maxNumIter || Math.abs(diff - lastDiff) < MIN_CHANGE_CUTOFF) {
                break;
            }

            lastDiff = diff;

            // Update date feature and weights matrices
            Matrix hn = w.transpose().times(v);
            Matrix hd = w.transpose().times(w).times(h);

            for (int a = 0; a < h.getRowDimension(); a++) {
                for (int b = 0; b < h.getColumnDimension(); b++) {
                    h.set(a, b, h.get(a, b) * hn.get(a, b) / hd.get(a, b) + EPSILON);
                }
            }

            Matrix wn = v.times(h.transpose());
            Matrix wd = w.times(h).times(h.transpose());

            for (int a = 0; a < w.getRowDimension(); a++) {
                for (int b = 0; b < w.getColumnDimension(); b++) {
                    w.set(a, b, w.get(a, b) * wn.get(a, b) / wd.get(a, b) + EPSILON);
                }
            }

        }

        return Arrays.asList(new Matrix[] { w, h });

    }

    public double calcMSE(Matrix a, Matrix b) {

        if (a.getColumnDimension() != b.getColumnDimension() || a.getRowDimension() != b.getRowDimension()) {
            throw new Error("Matrices not the same size");
        }

        double diff = 0;
        int count = 0;
        for (int i = 0; i < a.getRowDimension(); i++) {
            for (int j = 0; j < a.getColumnDimension(); j++) {
                if (a.get(i, j) != 0) {
                    count++;
                    diff += Math.pow(a.get(i, j) - b.get(i, j), 2);
                }
            }
        }

        return diff / count;

    }

    public double[][] loadFromFile(String fileName) throws FileNotFoundException {

        Scanner in = new Scanner(new File(fileName));

        int docNum = in.nextInt();
        int wordNum = in.nextInt();

        in.nextInt(); // Number of word instances

        double[][] values = new double[docNum][wordNum];

        while (in.hasNext()) {
            values[in.nextInt() - 1][in.nextInt() - 1] = in.nextInt();
        }

        return values;

    }

    public double[][] createRandomSynthetic(int x, int y) {

        double[][] ret = new double[x][y];

        Random r = new Random();

        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                ret[i][j] = (int) (Math.abs(r.nextGaussian()) * (i + j) * 5. / (x + y));
            }
        }

        return ret;
    }

    public static void runMe(int sizeX, int sizeY, int numF) throws FileNotFoundException {

        MultiplicativeUpdate mu = new MultiplicativeUpdate();

        // Load the data into mem
        Matrix dataMatrix = new Matrix(mu.loadFromFile(System.getProperty("user.dir") + "\\data\\docword.kos.txt"));
        // Matrix dataMatrix = new Matrix(mu.createRandomSynthetic(sizeX, sizeY));

        // Run the algo
        Long startTime = System.currentTimeMillis();
        List<Matrix> model = mu.buildMatrix(dataMatrix, numF, 100);
        Long endTime = System.currentTimeMillis();

        System.out.println(sizeX + ", " + sizeY + ", " + numF + ", mu, " + mu.calcMSE(dataMatrix, model.get(0).times(model.get(1))) + ", " + (endTime - startTime) / 1000.);

    }

}
=======
package com.notatrick.csm.applalgos.finalproj;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

import Jama.Matrix;

public class MultiplicativeUpdate {

    private static double MIN_ALLOWABLE_DIFF = .02;
    private static double MIN_CHANGE_CUTOFF = .01;
    private static double EPSILON = .00000000001;

    /**
     * @param v
     *            The data matrix of size
     * @param numFeatures
     *            The number of features to find
     * @return The weights and feature matrices
     */
    public List<Matrix> buildMatrix(Matrix v, int numFeatures, int maxNumIter) {

        // Start with random values
        Matrix w = Matrix.random(v.getRowDimension(), numFeatures);
        Matrix h = Matrix.random(numFeatures, v.getColumnDimension());

        double lastDiff = Double.MAX_VALUE;

        for (int i = 0; i < maxNumIter; i++) {

            Matrix wh = w.times(h);

            double diff = calcDiff(v, wh);

            System.out.println(i + " : " + diff);

            if (diff < MIN_ALLOWABLE_DIFF || i >= maxNumIter || Math.abs(diff - lastDiff) < MIN_CHANGE_CUTOFF) {
                break;
            }

            lastDiff = diff;

            // Update date feature and weights matrices
            Matrix hn = w.transpose().times(v);
            Matrix hd = w.transpose().times(w).times(h);

            for (int a = 0; a < h.getRowDimension(); a++) {
                for (int b = 0; b < h.getColumnDimension(); b++) {
                    h.set(a, b, h.get(a, b) * hn.get(a, b) / hd.get(a, b) + EPSILON);
                }
            }

            Matrix wn = v.times(h.transpose());
            Matrix wd = w.times(h).times(h.transpose());

            for (int a = 0; a < w.getRowDimension(); a++) {
                for (int b = 0; b < w.getColumnDimension(); b++) {
                    w.set(a, b, w.get(a, b) * wn.get(a, b) / wd.get(a, b) + EPSILON);
                }
            }

        }

        return Arrays.asList(new Matrix[] { w, h });

    }

    private double calcDiff(Matrix a, Matrix b) {

        if (a.getColumnDimension() != b.getColumnDimension() || a.getRowDimension() != b.getRowDimension()) {
            throw new Error("Matrices not the same size");
        }

        double diff = 0;
        for (int i = 0; i < a.getRowDimension(); i++) {
            for (int j = 0; j < a.getColumnDimension(); j++) {
                diff += Math.pow(a.get(i, j) - b.get(i, j), 2);
            }
        }

        return diff;

    }

    private static double[][] loadFromFile(String fileName) throws FileNotFoundException {

        Scanner in = new Scanner(new File(fileName));

        int docNum = in.nextInt();
        int wordNum = in.nextInt();

        in.nextInt(); // Number of word instances

        double[][] values = new double[docNum][wordNum];

        while (in.hasNext()) {
            values[in.nextInt() - 1][in.nextInt() - 1] = in.nextInt();
        }

        return values;

    }

    public static void main(String[] args) throws FileNotFoundException {

        MultiplicativeUpdate mu = new MultiplicativeUpdate();

        // Load the data into mem
        Matrix dataMatrix = new Matrix(mu.loadFromFile(System.getProperty("user.dir") + "\\data\\docword.kos.txt"));

        // Run the algo
        List<Matrix> model = mu.buildMatrix(dataMatrix, 30, 100);

    }

}
