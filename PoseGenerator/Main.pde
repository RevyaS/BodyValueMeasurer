BoxGuide tl, tr, bl, br; //Top Left, Top Right, Bottom Left, Bottom Right
BoxGuide[] boxes;

void setup()
{
  size(900, 900, P3D);
  //ortho();
  boxes = new BoxGuide[4];
  
  tl = new BoxGuide(width/4, height/4, BoxType.TORSO);
  boxes[0] = tl;
  
  tr = new BoxGuide(width/2 + width/4, height/4, BoxType.ARM);
  boxes[1] = tr;

  bl = new BoxGuide(width/4, height/2 + height/4, BoxType.ARM);
  boxes[2] = bl;

  br = new BoxGuide(width/2 + width/4, height/2 + height/4, BoxType.TORSO);
  boxes[3] = br;
}

void draw()
{
  background(0);
  drawHUD();
  //drawBoxTR();
  for(BoxGuide box : boxes)
  {
    box.draw();
  }
}


void drawHUD()
{
  int padding = 30;
  //Draw Lines
  fill(255);
  stroke(255);
  line(0, height/2, -1, width, height/2, -1);
  line(width/2, 0, -1, width/2, height, -1);
  //Draw Text
  textSize(30);
  text("Torso", padding/2, padding); //Top Left
  text("Arm", width/2 + padding/2, padding); //Top Right
  text("Left Thigh", padding/2, height/2 + padding); //Bottom Left
  text("Right Thigh", width/2 + padding/2, height/2 + padding); //Bottom Left
  
  //Button
  int buttonWidth = 200, buttonHeight = 50;
  fill(255);
  rect(width/2 - buttonWidth/2, height - buttonHeight, buttonWidth, buttonHeight);
  fill(0);
  text("Generate", width/2 - buttonWidth/2 + padding, height - buttonHeight + padding, 1);
}