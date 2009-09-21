// Zack Tillotson
// This code will graph flowers, color coded by species and using 2 attributes.

////////////////////////////////////////////////////////////////////////////////

// Display Variables
int plotX = 500;
int plotY = 500;
int plotPadding = 10;
int plotXMargin = 200;
int plotYMargin = 10;

int[] colors = { #ff0000, #0000ff, #009900 };

// The data object
float[][] samples;
int bouquetSize = 3;
int flowerCount = 150;
int attrDims = 5;

int attr1 = 1;
int attr2 = 0;

String[] attrs = { "Sepal Length", "Sepal Width", "Petal Length", "Petal Width", "Species"};
String[] species = { "Iris-setosa", "Iris-versicolor", "Iris-virginica" };

PFont fontMain;
PFont fontDetail;

// The input file
String file = "iris.tsv";

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
    samples = parseFile(file);

}

float[][] parseFile(String file)
{

    float[][] flowers = new float[flowerCount][attrDims];

    // Open the file
    Table tab = new Table(file);

    //For each flower measurement
    int f = 0;
    for(int i = 0 ; i < tab.getRowCount() ; i++)
    {

        // Convert the species of flower to a number
        int fI = -1;
        for(int j = 0 ; j < bouquetSize ; j++)
            if(species[j].equals(tab.getString(i, 4))) fI = j;
        if(fI < 0) continue;

        // Populate flowers array
        flowers[f][0] = tab.getFloat(i, 0);
        flowers[f][1] = tab.getFloat(i, 1);
        flowers[f][2] = tab.getFloat(i, 2);
        flowers[f][3] = tab.getFloat(i, 3);
        flowers[f][4] = fI;
        f++;

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

    float scaleBot = 0;
    float scaleTop = 0;

    // Top of scale will be largest max value, rounded up to nearest 3
    for(int i = 0 ; i < flowerCount ; i++)
        for(int j = 0 ; j < attrDims - 1 ; j++)
            if(samples[i][j] > scaleTop) scaleTop = samples[i][j];
    scaleTop += (3 - scaleTop % 3);

    // Graph scale
    fill(0); // black
    for(float i = scaleTop ; i > scaleBot ; i--)
    {
        line(plotXMargin + plotPadding - 3, plotYMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0), plotXMargin + plotPadding + 5, plotYMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0));
        text(nf(i, 0, 0), plotXMargin + plotPadding + 8, plotYMargin + plotPadding + 4 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0));
    }
    for(float i = scaleTop - 1 ; i >= scaleBot ; i--)
    {
        line(plotXMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0), plotYMargin + plotPadding + plotY - 3, plotXMargin + plotPadding + 0 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0), plotYMargin + plotPadding + plotY + 3);
        text(nf(scaleTop - i, 0, 0), plotXMargin + plotPadding - 3 + plotY - (i + 0) * plotY / (scaleTop - scaleBot + 0), plotYMargin + plotPadding + plotY - 6);
    }

    // Map Description
    fill(0);    // black
    text(attrs[attr2], 50 - attrs[attr2].length() / 2 * 6, plotYMargin + 10);
    text("vs", 40, plotYMargin + 20);
    text(attrs[attr1], 50 - attrs[attr2].length() / 2 * 6, plotYMargin + 30);

    // Y axis
    fill(0);    // black
    text("Y Axis", 10, plotYMargin + 100);

    for(int i = 0 ; i < attrDims - 1 ; i++)
    {

        fill(255);  // white
        stroke(0);  // black

        if(attr2 == i) fill(155);   // gray
        else if(mouseX >= 10 && mouseX <= 150 && mouseY >= plotYMargin + 110 + i * 15 && mouseY <= plotYMargin + 110 + i * 15 + 15)
        {
            fill(0, 192, 0);    // green
        }

        rect(10, plotYMargin + 110 + i * 15, 140, 15);

        stroke(0);
        fill(0);

        text(attrs[i], 15, plotYMargin + 110 + i * 15 + 11);
        line(10, plotYMargin + 110 + i * 15, 150, plotYMargin + 110 + i * 15);
        line(150, plotYMargin + 110 + i * 15, 150, plotYMargin + 125 + i * 15);
        line(150, plotYMargin + 125 + i * 15, 10, plotYMargin + 125 + i * 15);
        line(10, plotYMargin + 125 + i * 15, 10, plotYMargin + 110 + i * 15);

    }

    // X axis
    fill(0);    // black
    text("X Axis", 10, plotYMargin + 200);

    for(int i = 0 ; i < attrDims - 1 ; i++)
    {

        fill(255);  // white
        stroke(0);  // black

        if(attr1 == i) fill(155);   // gray
        else if(mouseX >= 10 && mouseX <= 150 && mouseY >= plotYMargin + 210 + i * 15 && mouseY <= plotYMargin + 210 + i * 15 + 15)
        {
            fill(0, 192, 0);    // green
        }

        rect(10, plotYMargin + 210 + i * 15, 140, 15);

        stroke(0);
        fill(0);

        text(attrs[i], 15, plotYMargin + 210 + i * 15 + 11);
        line(10, plotYMargin + 210 + i * 15, 150, plotYMargin + 210 + i * 15);
        line(150, plotYMargin + 210 + i * 15, 150, plotYMargin + 225 + i * 15);
        line(150, plotYMargin + 225 + i * 15, 10, plotYMargin + 225 + i * 15);
        line(10, plotYMargin + 225 + i * 15, 10, plotYMargin + 210 + i * 15);

    }

    // Legend
    fill(0);
    text("Legend", 10, 333);
    line(10, 335, 150, 335);
    for(int i = 0 ; i < bouquetSize ; i++)
    {
        fill(colors[i]);
        text(species[i], 10, 350 + 15 * i);
    }

    // For each sample
    for(int i = 0 ; i < flowerCount ; i++)
    {

        String specVal = species[(new Float(samples[i][4])).intValue()];
        float attr1Val = samples[i][attr1];
        float attr2Val = samples[i][attr2];

        float mapAttrX = map(attr1Val, scaleBot, scaleTop, plotXMargin + plotPadding + plotX, plotXMargin + plotPadding - 8); // X axis
        float mapAttrY = map(attr2Val, scaleBot, scaleTop, plotYMargin + plotPadding, plotYMargin + plotPadding + plotY + 8); // Y axis

        stroke(colors[(new Float(samples[i][4])).intValue()]);
        line(mapAttrX - 3, mapAttrY, mapAttrX + 3, mapAttrY);
        line(mapAttrX, mapAttrY - 3, mapAttrX, mapAttrY + 3);

        stroke(0);

    }

}

void mouseReleased()
{
    for(int i = 0 ; i < attrDims - 1 ; i++)
    {
        if(mouseX >= 10 && mouseX <= 150 && mouseY >= plotYMargin + 110 + i * 15 && mouseY <= plotYMargin + 110 + i * 15 + 15)  attr2 = i;
        if(mouseX >= 10 && mouseX <= 150 && mouseY >= plotYMargin + 210 + i * 15 && mouseY <= plotYMargin + 210 + i * 15 + 15)  attr1 = i;
    }
}
