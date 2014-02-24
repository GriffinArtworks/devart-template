## Composition Part 1

Fractal tree recursion seems like a suitable starting point as it can create lots of variation and is simple to calculate the coordinate space at each node. It can be built using 2 things:

+ A root coordinate space R to define the starting point, this being relative to canvas coordinate space. 
+ A number of child coordinate spaces C[i] relative to R. In the example below there are 2 children.

![image](../project_images/overview_coordspaces.png?raw=true "image")

The idea then is to keep recursing using the same child coordinates spaces to form a tree structure, stopping when reaching a target depth.

![image](../project_images/overview_recursion.png?raw=true "image")

The transform matrix of the each of the 4 leaf nodes (depth 2) would then be:

```M0 = R * C[0] * C[0] ```

```M1 = R * C[0] * C[1] ```

```M2 = R * C[1] * C[0] ```

```M3 = R * C[1] * C[1] ```

where ```Mx```,```R```,```C[i]``` are all 3x3 matrices. 

Code snippet below of the shader implementation:

```
int instanceix = startInstanceID + gl_InstanceID;
mat3 M = mat3(1.0);
int divisor = 1;
for(int i =MAX_DEPTH; i>= 1;--i)
{
	if(fractalDepth >= i)
	{
		M = M*(childrenMats[(instanceix / divisor) % nChildren]);
		divisor *= nChildren;
	}
}
M = RootMat*M;
```

# Results: #

2 child nodes, with slight scaling, 5 depths.  Looks quite normal:

![image](../project_images/comp/fractal1.png?raw=true "image")

.. with 10 depths, starting to look a bit more complex, bit it's still quite uniform:

![image](../project_images/comp/fractal2.png?raw=true "image")

.. let's introduce some scaling:

![image](../project_images/comp/fractal3.png?raw=true "image")

.. that's a bit better, then add some more child nodes, up it to 4, and apply a slightly different transform to each child node:

![image](../project_images/comp/fractal4.png?raw=true "image")

.. let's mix it up a bit more, playing the rotation:

![image](../project_images/comp/fractal5.png?raw=true "image")

.. and then some more, render depth 2 onwards:

![image](../project_images/comp/fractal6.png?raw=true "image")

.. the wireframe:

![image](../project_images/comp/wireframe1.PNG?raw=true "image")


.. another variation, zoomed in slightly:

![image](../project_images/comp/fractal7.png?raw=true "image")

.

