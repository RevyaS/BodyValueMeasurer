//For default positioning
public enum BoxType {TORSO, ARM, LEFTTHIGH, RIGHTTHIGH};

class BoxGuide
{
  public BoxGuide(int posX, int posY, BoxType type){
    this.posX = posX;
    this.posY = posY;
    box = loadShape(boxPath);
    //box.rotateX(radians(-60));
    //box.rotateY(radians(-30));
    
    switch(type)
    {
      case TORSO:
      case LEFTTHIGH:
        box.rotateX(radians(-90));
        box.rotateY(radians(-90));
        break;
      case ARM:
      case RIGHTTHIGH:
        box.rotateX(radians(-90));
        box.rotateY(radians(90));
        break;
    }
  }
  
  public void draw()
  {
    pushMatrix();
    translate(posX, posY, 0);
    scale(20);
    
    shape(box);
    popMatrix();
  }
  
  PShape box;
  int posX, posY; 
  String boxPath = "Box.obj";
}