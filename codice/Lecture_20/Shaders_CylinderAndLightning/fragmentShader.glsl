#version 430 core

#define CYLINDER 0
#define DISC 1

// Material's properties
in vec4 frontAmbDiffExport, frontSpecExport, backAmbDiffExport, backSpecExport;
// texture coordinates
in vec2 texCoordsExport;

// samplers for the textures
uniform sampler2D canLabelTex;
uniform sampler2D canTopTex;

uniform uint object;

out vec4 colorsOut;

vec4 texColor;

void main(void)
{
    // check which object we are currently drawing
    if (object == CYLINDER) texColor = texture(canLabelTex, texCoordsExport);
    if (object == DISC) texColor = texture(canTopTex, texCoordsExport);

    // set color of the fragment
    colorsOut = gl_FrontFacing? (frontAmbDiffExport * texColor + frontSpecExport) :
                               (backAmbDiffExport * texColor + backSpecExport);
}
