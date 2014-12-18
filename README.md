#Introduction

The files in gr-tagutils are useful for experimenting with Stream Tags in 
GNU Radio (ver 3.7 or later).


#Installation

Naviagate to your desired install directory. This should be outside of the main
GNU Radio source code directory. From the terminal: 

  	git clone https://github.com/adamgann/gr-tagutils.git
  	cd gr-tagutils
  	mkdir build
  	cd build
  	cmake ..
  	make
  	sudo make install
  	sudo ldconfig



#Blocks

###Tag Threshold Switch

Searches for a stream tag matching the key parameter and gets its value.
If the value is above the threshold, copies the input to the 'above' port
If the value is above the threshold, copies the input to the 'below' port
User can select to which port the input is copied to when value equals threshold


### Tag To Byte

Searches the input stream for a tag with a key matching the Tag Key field. 
Outputs zeros when input does not contain a tag. Outputs ones when input
does contain a tag. Can be followed by a file sink. Useful for offline processing
when one wants to know where tags occur relative to data. 

### Add Tag At Offset

Passes data through adding a tag at a certain offset with a value and key
set in the block parameters. Useful for debugging a block that relies on 
its input having a tag at a certain sample. 

### Tag Extractor 

Similar to tag to byte. Creates a vector of zeros with non-zero elements when the input contains a tag. Instead of simply a value of one, the output when there is a tag will be equal to the tag's value. Useful for offline processing. 


