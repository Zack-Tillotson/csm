package com.notatrick.csm.applalgos.finalproj;

import java.io.FileNotFoundException;

public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        int sizeX = 0;
        int sizeY = 0;
        int numF = 0;

        sizeX = 25;
        sizeY = 15;

        for (int sizeM = 2500 - 1; sizeX < 2500;) {

            sizeX *= sizeM;
            sizeY *= sizeM;

            for (numF = 1; numF != -1; numF = (numF == 1 ? 3 : (numF == 3 ? 10 : (numF == 10 ? 30 : -1)))) {
                // MultiplicativeUpdate.runMe(sizeX, sizeY, numF);
                AdditiveUpdate.runMe(sizeX, sizeY, numF);
                // AlternatingLeastSquares.runMe(sizeX, sizeY, numF);
            }
        }

    }
}
