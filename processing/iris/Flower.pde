class Flower
{

    // Init
    int size = 150;

    // Attributes
    String species;
    int sampleSize;
    int attrDim = 4;

    // Stats
    float[] minVal;
    float[] maxVal;
    float[] sumVal;

    Flower(String species)
    {

        this.species = species;
        sampleSize = 0;

        minVal = new float[attrDim];
        maxVal = new float[attrDim];
        sumVal = new float[attrDim];

        for(int i = 0 ; i < attrDim ; i++)
        {
            minVal[i] = MAX_FLOAT;
            maxVal[i] = MIN_FLOAT;
            sumVal[i] = 0;
        }

    }

    String getSpecies() { return species; }
    float getMinVal(int attr) { return minVal[attr]; }
    float getMaxVal(int attr) { return maxVal[attr]; }
    float getMeanVal(int attr) { return sumVal[attr] / sampleSize; }

    void addSample(float[] attrs)
    {

        if(attrs.length != attrDim) return;

        sampleSize++;

        for(int i = 0 ; i < attrDim ; i++)
        {
            if(attrs[i] < minVal[i]) minVal[i] = attrs[i];
            if(attrs[i] > maxVal[i]) maxVal[i] = attrs[i];
            sumVal[i] += attrs[i];
        }

    }

}