
This dataset includes the original HDR image series for the Stanford
Memorial Church radiance map from the paper:

Paul E. Debevec and Jitendra Malik. Recovering High Dynamic Range
Radiance Maps from Photographs. In SIGGRAPH 97, August 1997.

The .png images were taken from PhotoCD scans of film pictures taken
on Kodak Gold 100 ASA film.  The scans were decoded to 512x768 pixel
resolution.  The pictures were manually registered using feature
points and homographies using the Facade photogrammetric modeling
system.  The pure blue color indicates shifted image border areas and
should not be used in the HDR assembly process.

The .hdr_image_list.txt file indicates the shooting parameters for
each picture.  Gain doubles the exposure amount when it goes up by 3
decibels.  f/stop quadruples the exposure amount each time it goes
DOWN by a factor of two.  No neutral density filters were used in this
sequence.

The .hdr image is the assembled radiance maps, in Greg Larson's
RADIANCE high dynamic range image file format.  Software to display,
manipulate, and convert this image type can be found at:
http://www.hdrshop.com/

Paul Debevec
paul@debevec.org
http://www.debevec.org/Research/HDR/