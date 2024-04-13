# Application tutorial

[TOC]

## Run executable

Starting from the root directory of the program, go to `sidera/os/bin` and run the `sidera` executable file.

<div class="tabbed">

- <b class="tab-title">Windows</b>
    ```bash
    #starting from root repo
    cd sidera/windows/bin
    start sidera.exe
    ```

- <b class="tab-title">Linux</b>
    ```bash
    #starting from root repo
    cd sidera/linux/bin
    ./sidera
    ```

</div>

![](./media/sidera-startup.png)

---

## Camera properties and text-based interface

You can move around the 3d universe using the `WASD` keys. To set the camera speed, press the keys from `1` to `5`. To change the fov angle (in radians), use the `Z` (increse) and `X` keys. To save current the camera properties (position, rotation, fov, etc.) press `LEFT_CTRL + F`. To load the last saved camera interface, press `LEFT_CTRL + L`. 

You can read the camera properties in real time by opening the `sidera/interface.smd` file with your favourite text editor:

```
	GAIA MODEL INTERFACE


	CAMERA PROPERTIES


FLOAT32    ^^ 1    !! camera_right_ascension___rad    --> -0.003308     ***
FLOAT32    ^^ 1    !! camera_declination_______rad    --> -0.006512     ***
FLOAT32    ^^ 3    !! camera_position___________pc    --> 0.0 0.0 0.0   ***
FLOAT32    ^^ 1    !! camera_fov_______________rad    --> 45.000000     ***
```

The camera position is in parsecs (`pc`).

---

## Edit source settings

Editing the gaia universe model source settings means reading new data and different celestial body properties. Open the settings file located at `sidera/smd/settings.smd` file (for more information about the smd file format, visit the [`smd repository`](https://github.com/mrsinho/smd)).

### Change number of celestial bodies

You can increase or decrease the number of celestial bodies to read, and the amount of data to render on the screen. You can achieve this by changing one variable in the `settings.smd` file:

```
    SOURCE SETTINGS

UINT32    ^^ 1    !! data_release            --> GEDR3      *** ignored, only option available
UINT32    ^^ 1    !! celestial_body_count    --> 1000000    ***
                                                 ^
                                                 |
                                                (change here)
```

Save the file and refresh the application source settings with `LEFT_CTRL + R` (`R` stands for reload).

![](./media/30million.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: teff; shade type: animated; 30 million celestial bodies_

![](./media/1million.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: teff; shade type: animated; 1 million celestial bodies_

### Customize xyz parameters

You can submit to the GPU at maximum three default celestial body parameters, which will be then plotted in the 3d environment. By default, the celestial body right ascension, declination and barycentric distance will be respectively set at x, y, and z parameters.

You can setup the celestial body xyz parameters through the `settings.smd` file. 

```
set xyz parameters, choose between
    RA,                          
    DEC,                         
    BARYCENTRIC_DISTANCE,        
    PMRA,                        
    PMDEC,                       
    RADIAL_VELOCITY,             
    MAG_G,                       
    MAG_BP,                      
    MAG_RP,                      
    MAG_RVS,                     
    V_I,                         
    MEAN_ABSOLUTE_V,             
    AG,                          
    AV,                          
    TEFF,                        
    LOGG,                        
    FEH,                         
    ALPHAFE,                     
    MBOL,                        
    AGE,                         
    MASS,                        
    RADIUS,                      
    VSINI,                       
    POPULATION,                  
    NC,                          
    NT,                          
    SEMIMAJOR_AXIS,              
    ECCENTRICITY,                
    INCLINATION,                 
    LONGITUDE_ASCENDING_NODE,    
    ORBIT_PERIOD,                
    VARIABILITY_AMPLITUDE,       
    VARIABILITY_PERIOD,          
    VARIABILITY_PHASE       

STR1024   ^^ 1    !! x_parameter_type    --> RA                    ***
STR1024   ^^ 1    !! y_parameter_type    --> DEC                   ***
STR1024   ^^ 1    !! z_parameter_type    --> BARYCENTRIC_DISTANCE  ***
                                             ^
                                             |
                                            (change here)
```

To change the mode data is projected in the 3d world, see the [`set-view-mode`](#41-set-view-mode) chapter.


Save the file and refresh the application source settings with `LEFT_CTRL + R`.

### Customize color filter

The color filter of a celestial body is an extra parameter submitted to the GPU, which affects the color of each celestial body depending on its value. Higher values will increase the green and blue channels of the celestial body color. Here you can find the supported color filter parameters:

```
set color filter, choose between 
    RANDOM_COLOR_SEED     (just a random color)
    BARYCENTRIC_DISTANCE, (in pc)
    TEFF,                 (effective temperature in K, the stars are represented in a kelvin scale)
    LOGG,                 (surface gravity)
    FEH,                  (metallicity: magnitude of atoms of Fe / magnitude of atoms of H)
    ALPHAFE,              (magnitude of alpha particles / magnitude of atoms of Fe)
    AGE,                  (in billions of years)
    MASS,                 (in solar masses)
    RADIUS,               (in solar radiuses, mean value for pulsating stars)
    VSINI                 (rotational velocity in km/s)
                                         
STR1024   ^^ 1    !! color_filter    --> TEFF    ***
                                         ^
                                         |
                                        (change here)
```

Save the file and refresh the application source settings with `LEFT_CTRL + R`.

![](./media/logg_cf_pixel.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: logg; shade type: pixel_

![](./media/radius_cf_pixel.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: radius; shade type: pixel_

![](./media/random_color_seedcf.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: random color; shade type: pixel_


---

## Edit graphics settings

When you change the gaia universe model graphics settings you are not reading new celestial bodies parameters, but you're only changing the way the same data appears on the screen. Open the settings file located at `sidera/smd/settings.smd` file (for more information about the smd file format, visit the [`smd repository`](https://github.com/mrsinho/smd)).

### Set view mode

A polar projection mode is optimal when reading right ascension, declination and barycentric distance as xyz parameters. This way what you see on the screen is actually the true representation of the night sky. Plotting data on a cartesian diagram allows finding out some correlation between the xyz celestial body parameters:

```
view mode, choose between:
    CARTESIAN, (values are plotted in a xyz coordinates system)
    POLAR      (values are projected in a spherical environment, xyz parameter types are respectevely interpreted as right ascension, declination, and distance)

STR1024   ^^ 1    !! view_mode     --> POLAR    ***
                                       ^
                                       |
                                      (change here)
```

Save the file and refresh the application graphics settings with `LEFT_CTRL + G` (`G` stands for graphics).

![](./media/age_mass_feh__fehcf_cartesian.png)
_x: age; y: mass; z: feh; view mode: cartesian; color filter: feh; shade type: pixel. As you can see, there is a correlation between a star's mass, age, and abundance of Fe particles, and only some combinations of parameters are possible (there are colorful and dark regions)_

### Change shading mode

This is pure aestetics. Stars can be represented as dots (pixels), circles, clouds, or animated clouds:

```
choose between (to compare each pipeline's speed, see the profiling.smd file)
    PIXEL,     (fastest, each celestial body is a pixel)
    CIRCLE,    (fast, each celestial body is represented as a circle)
    CLOUD,     (expensive, each star is represented as a star-looking cloudy object, there's no volumetric rendering btw)
    ANIMATED   (most expensive, each star is represented as a star-looking animated object)

STR1024   ^^ 1    !! shade_type    --> ANIMATED    ***
                                       ^
                                       |
                                      (change here)
```

Save the file and refresh the application graphics settings with `LEFT_CTRL + G`.

![](./media/logg_cf.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: logg; shade type: animated_

![](./media/age_cf.png)
_x: right ascension; y: declination; z: barycentric distance; view mode: polar; color filter: age; shade type: animated_

---