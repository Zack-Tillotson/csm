// Zack Tillotson
// This code will display the mean and range for each class and variable
// of the Iris dataset.

////////////////////////////////////////////////////////////////////////////////

// Display Variables
int plotX = 500;
int plotY = 300;
int plotPadding = 10;
int plotXMargin = 10;
int plotYMargin = 30;

int barWidth = 100;

int[] colors = { #ffcc44, #ffff33, #ccff33 };

// The data object
Flower[] blumen;
int bouquetSize = 3;
int activeAttr = 0;
String[] attrs;

PFont fontMain;
PFont fontDetail;

// The input file
String file = "iris.tsv";
int attrDims = 4;

////////////////////////////////////////////////////////////////////////////////

// Setup
void setup()
{

    // The output box
    size(plotXMargin + plotX + plotPadding * 3, plotYMargin + plotY + plotPadding * 3);

    fontMain = loadFont("MiriamFixed-12.vlw");
    fontDetail = loadFont("LucidaSans-10.vlw");
    textFont(fontMain);

    // Create the data object
    blumen = parseFile(file);

    attrs = new String[attrDims];
    attrs[0] = "Petal Length";
    attrs[1] = "Petal Width";
    attrs[2] = "Sepal Length";
    attrs[3] = "Sepal Width";

}

Flower[] parseFile(String file)
{

    Flower[] flowers = new Flower[bouquetSize];
    int f = -1;

    // Open the file
    Table tab = new Table(file);

    //For each flower measurement
    for(int i = 0 ; i < tab.getRowCount() ; i++)
    {

        if(f == -1 || !flowers[f].getSpecies().equals(tab.getString(i, 4)))
            flowers[++f] = new Flower(tab.getString(i, 4));

        float[] attrs = new float[attrDims];
        for(int j = 0 ; j < attrDims ; j++)
            attrs[j] = tab.getFloat(i, j);

        flowers[f].addSample(attrs);

    }

    return flowers;

}

////////////////////////////////////////////////////////////////////////////////

// Draw it
void draw()
{

    // Draw the background
    fill(255); // white
    rect(0, 0, plotXMargin + 3 * plotPadding + plotX, plotYMargin + 3 * plotPadding + plotY);
    fill(200); // gray
    rect(plotXMargin, plotYMargin, 2 * plotPadding + plotX, 2 * plotPadding + plotY);
    fill(255); // white
    rect(plotXMargin + plotPadding, plotYMargin + plotPadding, plotX, plotY);
    fill(0);   // black
    textFont(fontMain);
    text("Press space to cycle through attributes", plotXMargin + plotPadding, 20);
    text(attrs[activeAttr], plotXMargin + plotPadding + plotX - attrs[activeAttr].length() * 7, 20);

    float scaleBot = 0;
    float scaleTop = 0;

    // Top of scale will be largest max value, rounded up to nearest 3
    for(int i = 0 ; i < bouquetSize ; i++)
        for(int j = 0 ; j < attrDims ; j++)
            if(blumen[i].getMaxVal(j) > scaleTop) scaleTop = blumen[i].getMaxVal(j);
    scaleTop += (3 - scaleTop % 3);

    fill(0); // black
    for(float i = scaleTop ; i >= scaleBot ; i--)
    {
        line(plotXMargin + plotPadding - 3, plotYMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0), plotXMargin + plotPadding + 5, plotYMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0));
        text(nf(i, 0, 0), plotXMargin + plotPadding + 8, plotYMargin + plotPadding + 4 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0));
    }

    // Draw the flower stats
    for(int i = 0 ; i < bouquetSize ; i++)
    {

        float minVal = blumen[i].getMinVal(activeAttr);
        float maxVal = blumen[i].getMaxVal(activeAttr);
        float meanVal = blumen[i].getMeanVal(activeAttr);
        float rangeVal = maxVal - minVal;

        float mapMinVal = map(minVal, scaleBot, scaleTop, plotYMargin + plotPadding + plotY, plotYMargin + plotPadding);
        float mapMaxVal = map(maxVal, scaleBot, scaleTop, plotYMargin + plotPadding + plotY, plotYMargin + plotPadding);
        float mapMeanVal = map(meanVal, scaleBot, scaleTop, plotYMargin + plotPadding + plotY, plotYMargin + plotPadding);

        float xStart = plotXMargin + plotPadding + (i * barWidth) + (plotX - bouquetSize * barWidth) / (bouquetSize + 1) * (i + 1);
        float xEnd = xStart + barWidth;

        // Draw the range rectangle
        fill(colors[i]); // one color per flower
        rect(xStart, mapMaxVal, barWidth, mapMinVal - mapMaxVal);        

        // Draw the mean line
        fill(0);    // black
        line(xStart, mapMeanVal, xEnd, mapMeanVal);

        // Draw the species
        fill(0);    // black
        textFont(fontMain);
        text(blumen[i].getSpecies(), xStart, plotYMargin + plotPadding + 15);

        // If the mouse is over this flower, display the real values
        if(mouseX >= xStart && mouseX <= xEnd && mouseY >= mapMaxVal && mouseY <= mapMinVal)
        {
            textFont(fontDetail);
            text("Min, Max [" + nf(blumen[i].getMinVal(activeAttr), 0, 2) + "," + nf(blumen[i].getMaxVal(activeAttr), 0, 2) + "]", xStart + 1, mapMaxVal - 1);
            text("Mean  [" + nf(blumen[i].getMeanVal(activeAttr), 0, 2) + "]", xStart + 1, mapMeanVal - 1);
            text("Range [" + nf(rangeVal, 0, 2) + "]", xStart + 1, mapMinVal + 10);
        }
            

    }

}

void keyPressed()
{
    if(key == ' ')
        activeAttr = ++activeAttr % attrDims;
}
