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

layout(location=0) in vec4 sunCoords;
layout(location=1) in vec4 mercuryCoords;
layout(location=2) in vec4 venusCoords;
layout(location=3) in vec4 earthCoords;
layout(location=4) in vec4 marsCoords;
layout(location=5) in vec4 jupiterCoords;
layout(location=6) in vec4 saturnCoords;
layout(location=7) in vec4 uranusCoords;
layout(location=8) in vec4 neptuneCoords;

uniform mat4 projMat;
uniform mat4 modelViewMat;
uniform uint object;

vec4 coords;

void main(void)
{
   if (object == SUN) coords = sunCoords;
   if (object == MERCURY) coords = mercuryCoords;
   if (object == VENUS) coords = venusCoords;
   if (object == EARTH) coords = earthCoords;
   if (object == MARS) coords = marsCoords;
   if (object == JUPITER) coords = jupiterCoords;
   if (object == SATURN) coords = saturnCoords;
   if (object == URANUS) coords = uranusCoords;
   if (object == NEPTUNE) coords = neptuneCoords;

   gl_Position = projMat * modelViewMat * coords;
}
