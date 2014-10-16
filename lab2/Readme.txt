Matric Number: A0105408 
Name: Yin Yumeng
Draw: sloar system and Hello Kitty

Primitives and transformations you have used:
Primitives : GL_POLYGON,GL_LINE_STRIP 
Transformation: 1. Translation
             2. Rotation
		  3. Scaling

Methods:
main mathod:
drawStar(); draw all stars and manage the blinking function
drawCenter(); draw the center sun
drawPlanet(); draw all the planets and also call the drawHelloKitty to draw the hellokitty.


helper mathod:
drawSpiral()     :draw the spiral
drawWholeSpiral():draw a heart
background()     :set the background color and add all hearts in
                  the top
drawArc(double cx, double cy, float r,float rx, float ry, int startDeg, int endDeg): helper function to draw a whole or part of
                    cycle or a oval
drawArm()        :draw the arm of hello kitty
drawLeftHand()   :draw the left hand of hello kitty
drawRightHand()  :draw the right hand of hello kitty
drawWing()       :draw the wing of hello kitty using three
                  ovals
drawWand()       :draw a wand for hello kitty
drawBody()       :draw the body for hello kitty
drawAcce()       :draw the red bow on its head
drawFace()       :draw the face of hello kitty
display()        :call other draw functions in order
reshape()        :loadIdentity
init()           :clear screen
keyboard()       :set keyboard function


Coolest Thing: Ramdonly create 40 stars and all stars will blink according to the clock.
can use t to toggle the clock mode.