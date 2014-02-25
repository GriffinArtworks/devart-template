
## Test Device ##

I ordered a Powermate to test with:

![image](../project_images/control/spin.png?raw=true "image")

The build quality is good and the software doesn't require any coding to integrate as it allows for the various actions such as: turn left,turn right and press down, to map to keystrokes that get picked up by the application.

## Performance ##

**Grow the fractal over time to maintain interactive rates**

Using this smooth rotating movement as the control mechanism to change the fractal means that the application would have run at interactive rates (about 30 fps) in order to keep up.

Drawing a few million instances, which would be the amount to fill the canvas and complete the image, drops the framerate way down to the point where it's unusable.  So I eventually settled on a system that draws the first N instances as a preview for the user while there is movement.  If they stop turning the control dial then it continues draws the rest of the instances, again N instances per draw call, to animate the fractal towards completion. Since we're still drawing at an interactive framerates this process the user can rotate the controls at any point and receive an instant change onscreen.

In this video I've hooked up control(turn left/right) to change the rotation of the sub nodesand it seems to work well:

https://www.youtube.com/watch?v=dy3ch2RAmVE

**Result:**

10,000 instances per draw update runs smoothly at 30 fps. 

For reference I'm using a nvidia 570gtx card. The latest generation equivalent 770gtx should offer twice the performance (since we're GPU bound in this case).


