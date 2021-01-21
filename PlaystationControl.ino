#include <Keyboard.h>
#include <Mouse.h>

const int Wbutton = 7;
const int Abutton = 6;
const int Sbutton = 4;
const int Dbutton = 5;
const int joystickVRx = A0;
const int joystickVRy = A1;
const int joystickButton = 3;
const int mouseVelocity = 20;
const int joystickTolerance = mouseVelocity/6;
const int joystickCenter = mouseVelocity/2;
const int FPS = 60;

void wasdButtonsControl(int wbutton, int abutton, int sbutton, int dbutton);
void mouseMovementControl(int joystickvrx, int joystickvry, int mousevelocity, 
                          int joysticktolerance, int joystickCenter);
void mouseClicksControl(int leftClick);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Wbutton, INPUT_PULLUP);
  pinMode(Abutton, INPUT_PULLUP);
  pinMode(Sbutton, INPUT_PULLUP);
  pinMode(Dbutton, INPUT_PULLUP);
  pinMode(joystickButton, INPUT_PULLUP);

  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  wasdButtonsControl(Wbutton, Abutton, Sbutton, Dbutton);
  mouseMovementControl(joystickVRx, joystickVRy, mouseVelocity, joystickTolerance, joystickCenter);
  mouseClicksControl(joystickButton);
  delay(1000/FPS);
}

void wasdButtonsControl(int wbutton, int abutton, int sbutton, int dbutton){
  if(!digitalRead(wbutton)){
    Keyboard.press('w');
    //Keyboard.print('w');
    //Keyboard.write('w');
  } 
  
  else{
    Keyboard.release('w');
  }
  
  if(!digitalRead(abutton)){
    Keyboard.press('a');
    //Keyboard.write('a');
  }
  else{
    Keyboard.release('a');
  }
  
  if(!digitalRead(sbutton)){
    Keyboard.press('s');
    //Keyboard.write('s');
  }
  else{
    Keyboard.release('s');
  }

  if(!digitalRead(dbutton)){
    Keyboard.press('d');
    //Keyboard.write('d');
  }
  else{
    Keyboard.release('d');
  }
}

void mouseMovementControl(int joystickvrx, int joystickvry, int mousevelocity, 
                          int joysticktolerance, int joystickcenter){
  int VRxlecture = analogRead(joystickvrx);
  int VRylecture = analogRead(joystickvry);

  //Comprueba si hay algún error en la lectura
  if(VRxlecture>=0 && VRxlecture<=1024 && VRylecture>=0 && VRylecture<=1024){
    int xMove = map(VRxlecture, 0, 1024, 0, mousevelocity);
    int yMove = map(VRylecture, 0, 1024, 0, mousevelocity);

    xMove = xMove - joystickcenter;
    yMove = yMove - joystickcenter;

    if(abs(xMove) < joysticktolerance){
      xMove = 0;
    }

    if(abs(yMove) < joysticktolerance){
      yMove = 0;
    }
    
    //El tercer argumento es el scroll
    Mouse.move(xMove, yMove, 0);
  }
}


void mouseClicksControl(int leftClick){
  if(!digitalRead(leftClick)){
    Mouse.click(MOUSE_LEFT);
  }
}
