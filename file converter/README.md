# File converter

## Download the tree
For development purpose, you can download the tree of the boats to test.
```c++
/*
working directory
	/transformation
		/3111_Tug
			/boat.ini
		/Alice Upjohn
			/boat.ini
		...
*/
```
To create this tree, run the python file **download_tree.py** with an internet connection.

## Convert the files
To convert the *ini* files into a *json* file, run the python file **main_converter.py**.<br />
If you want to convert a specific file, use the function in the file **convert2dict.py**. This file contains the function *convert2dict(filename)* that returns a dictionnary and takes the filename that you want to convert