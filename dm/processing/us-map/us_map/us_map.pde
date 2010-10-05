//Zack Tillotson
// on page 64

PImage mapImage;

Table locationTable;
int rowCount;

Table valueTable;
float minVal;
float maxVal;

Table namesTable;

void setup() 
{
  
  size(640, 400);
  mapImage = loadImage("map.png");
  
  // Make a data table from a file that contains
  // the coordinates of each state.
  locationTable = new Table("locations.tsv");
  rowCount = locationTable.getRowCount();
  
  // These are random locations
  valueTable = new Table("random.tsv");
 
  // Set the min and max values
  minVal = -10;
  maxVal = 10;
  
  // The font to show mouse over text with
  PFont font = loadFont("narkisim.vlw");
  textFont(font);
  
  // These are the full state names
  namesTable = new Table("names.tsv");
  
}

void draw() 
{
  
  background(255);
  image(mapImage, 0, 0);
  
  // Drawing attributes for the ellipses.
  smooth();
  fill(192, 0, 0);
  noStroke();
  
  // The centers of each state
  for (int row = 0; row < rowCount; row++) 
  {
    
    String state = locationTable.getRowName(row); // column 0
    float x = locationTable.getFloat(row, 1);     // column 1
    float y = locationTable.getFloat(row, 2);     // column 2
    
    drawIt(x, y, state);
    
  }
  
  drawMouseOverText();
  
}

void drawIt(float x, float y, String state)
{
  
  // Get value for state
  float value = valueTable.getFloat(state, 1);  
  boolean isNeg = value < 0 ? true : false;
  float magnitude = isNeg ? value * -1 : value;
  
  // Size of circle
  float radius = map(magnitude, minVal, maxVal, 1.5, 15);
  
  // Color of circle
  color colorValue = isNeg ? #FF0000 : #0000DD;
  float transparencyValue = map(magnitude, minVal, maxVal, 0, 255);
  
  // Draw it
  fill(colorValue, transparencyValue);
  ellipseMode(RADIUS);
  ellipse(x, y, radius, radius);

}

void drawMouseOverText()
{
  
  // The centers of each state
  int closestRow = 0;
  float closestDist = MAX_FLOAT;
  
  for (int row = 0; row < rowCount; row++) 
  {
    
    String state = locationTable.getRowName(row); // column 0
    float x = locationTable.getFloat(row, 1);     // column 1
    float y = locationTable.getFloat(row, 2);     // column 2
    
    String fullState = namesTable.getString(row, 1);
    
    float value = valueTable.getFloat(state, 1);
    float magnitude = value < 0 ? value * -1 : value;
    float radius = map(magnitude, minVal, maxVal, 1.5, 15);
    
    float rowDist = dist(x, y, mouseX, mouseY);
  
    if(rowDist < radius)
    {
      
      if(rowDist < closestDist)
      {
        closestRow = row;
        closestDist = rowDist;
      }
    
    }
    
  }
  
  if(closestDist < MAX_FLOAT)
  {
    
    int row = closestRow;
  
    String state = locationTable.getRowName(row); // column 0
    float x = locationTable.getFloat(row, 1);     // column 1
    float y = locationTable.getFloat(row, 2);     // column 2
    
    String fullState = namesTable.getString(row, 1);
    
    float value = valueTable.getFloat(state, 1);
    float magnitude = value < 0 ? value * -1 : value;
    float radius = map(magnitude, minVal, maxVal, 1.5, 15);
      
    fill(0);
    textAlign(CENTER);
    text("[" + fullState + "] " + nfp(value, 0, 2), x, y - radius - 4);
    
  }
  
}

void keyPressed()
{ 
  if(key == ' ') updateTable();
}

void updateTable()
{
  
  valueTable = new Table("http://benfry.com/writing/map/random.cgi");
  
}
