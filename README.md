# 3D_Parabola
C project to convert parabolic functions into 3D printable STL files.

Must run in terminal

Running

1.  Enter type of parabolic shape to be created:  
	-Triangular  
	-Rectangular  
	-Square  
  
2.  Enter the desired name of the output file  
	-Don't worry about adding the file extension.  

3. Enter your values for the relevant variables given  
	-Sloped intesecting lines are not compatable yet with this program.  
	-The angle for the triangular shape is the angle of the bottom edge on either side, the shape will always be isosceles.  
	-The resolution can be as high as you want but no lower than 20.  
	-Cuts indicate layers in which to cut the object. Only 10 are allowed in this implimentation. Cuts must be entered in order from least to greatest for accurate rendering. The locatoin of a cut cannot exceed the size of the resolution.  

4.  The STL file will appear in the folder containing the program. STL is importable to almost any 3D modelling or printing software.
