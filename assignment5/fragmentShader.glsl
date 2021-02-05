#version 430 core

#define SUN 0
#define MERCURY 1
#define VENUS 2
#define EARTH 3
#define MARS 4
#define JUPITER 5
#define SATURN 6
#define URANUS 7
#define NEPTUNE 8

uniform uint object;
uniform vec4 sunColor,
             mercuryColor,
             venusColor,
             earthColor,
             marsColor,
             jupiterColor,
             saturnColor,
             uranusColor,
             neptuneColor;

out vec4 colorsOut;

void main(void)
{
   if (object == SUN) colorsOut = sunColor;
   if (object == MERCURY) colorsOut = mercuryColor;
   if (object == VENUS) colorsOut = venusColor;
   if (object == EARTH) colorsOut = earthColor;
   if (object == MARS) colorsOut = marsColor;
   if (object == JUPITER) colorsOut = jupiterColor;
   if (object == SATURN) colorsOut = saturnColor;
   if (object == URANUS) colorsOut = uranusColor;
   if (object == NEPTUNE) colorsOut = neptuneColor;
}

