
### Adding Colour - Part 1

Some screenshots below after adding in some colour.  This was done by sampling from a 2D texture map, using the node ix (along x) and depth (along y) to calculate the position. Examples below all sample from the same test image.

![image](../project_images/noflow/i1.jpg?raw=true "image")

![image](../project_images/noflow/i2.PNG?raw=true "image")

![image](../project_images/noflow/i3.PNG?raw=true "image")

![image](../project_images/noflow/i4.PNG?raw=true "image")

![image](../project_images/noflow/i5.PNG?raw=true "image")

I like the interlaced string feel of the last one.  It's interesting to think that it's generated from the same well-defined recursive structure as the rest but has a completely different feel to it.

### todo 1 - Custom Search API

The goal is to eventually use the Google Custom Search API to find image for use as colour maps to sample from.  More on this later!


### todo 2 - Mapping

The next thing to tackle regarding colour is come up with a more flexible way of mapping the node (index & depth) to the sample location on the map.
