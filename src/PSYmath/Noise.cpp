/******************************************************************************

    PSYGEN - Procedural Synthesis Graphics Engine
    http://psygen.sourceforge.net

    Copyright (c) 2007 by Carlucio Santos Cordeiro
    email:      carlucio@gmail.com

    This file is part of PSYGEN

    PSYGEN is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    PSYGEN is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PSYGEN. If not, see <http://www.gnu.org/licenses/>

-------------------------------------------------------------------------------
*//**
    *  \file
    *  \brief
    *  \ingroup PSYmath
    *
    *//***********************************************************************/
#include "PSYGEN/PSYmath/Noise.hpp"


namespace psy
{



float Noise::noise(vec2 vec)
{
    int bx0, bx1, by0, by1, b00, b10, b01, b11;
    float  rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v, result;
    int i, j;



    setup(vec.x, bx0,bx1, rx0,rx1, t);
    setup(vec.y, by0,by1, ry0,ry1, t);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    sx = spline(rx0);
    sy = spline(ry0);

    q = g[ b00 ];       /* get random gradient */
    u = at2(rx0,ry0, q);   /* get weight on lo x side (lo y) */
    q = g[ b10 ];
    v = at2(rx1,ry0, q);   /* get weight on hi x side (lo y) */
    a = lerp(u, v, sx); /* get value at distance sx between u & v */

                /* similarly at hi y... */
    q = g[ b01 ];   u = at2(rx0,ry1, q);
    q = g[ b11 ];   v = at2(rx1,ry1, q);
    b = lerp(u, v, sx);

    result = 1.5f * lerp(a, b, sy);  /* interpolate in y */

    return (result);
}


float Noise::noise(vec3 vec)
{
    int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
    float rx0, rx1, ry0, ry1, rz0, rz1, *q, sx, sy, sz, t;
    float a, b, c, d, u, v;
    int i, j;



    setup(vec.x, bx0,bx1, rx0,rx1, t);
    setup(vec.y, by0,by1, ry0,ry1, t);
    setup(vec.z, bz0,bz1, rz0,rz1, t);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    sx = spline(rx0);
    sy = spline(ry0);
    sz = spline(rz0);

    q = g[ b00 + bz0 ]; u = at3(rx0,ry0,rz0, q);
    q = g[ b10 + bz0 ]; v = at3(rx1,ry0,rz0, q);
    a = lerp(u, v, sx);

    q = g[ b01 + bz0 ]; u = at3(rx0,ry1,rz0, q);
    q = g[ b11 + bz0 ]; v = at3(rx1,ry1,rz0, q);
    b = lerp(u, v, sx);

    c = lerp(a, b, sy);     /* interpolate in y at lo z */

    q = g[ b00 + bz1 ]; u = at3(rx0,ry0,rz1, q);
    q = g[ b10 + bz1 ]; v = at3(rx1,ry0,rz1, q);
    a = lerp(u, v, sx);

    q = g[ b01 + bz1 ]; u = at3(rx0,ry1,rz1, q);
    q = g[ b11 + bz1 ]; v = at3(rx1,ry1,rz1, q);
    b = lerp(u, v, sx);

    d = lerp(a, b, sy);     /* interpolate in y at hi z */

    return 1.5f * lerp(c, d, sz);    /* interpolate in z */
}


int Noise::BM = 0xf;

int Noise::N = 0x100;

int Noise::p[] =
{
    0,
    1,
    129,
    3,
    21,
    84,
    47,
    7,
    46,
    14,
    25,
    142,
    6,
    13,
    144,
    15,
    206,
    17,
    73,
    32,
    155,
    4,
    8,
    214,
    247,
    10,
    80,
    27,
    86,
    170,
    202,
    204,
    150,
    33,
    114,
    82,
    162,
    138,
    186,
    39,
    64,
    44,
    111,
    126,
    41,
    45,
    19,
    190,
    79,
    49,
    211,
    158,
    5,
    53,
    245,
    55,
    99,
    57,
    230,
    59,
    205,
    61,
    71,
    88,
    234,
    65,
    203,
    67,
    209,
    140,
    141,
    154,
    240,
    18,
    117,
    152,
    42,
    77,
    68,
    232,
    182,
    81,
    26,
    83,
    52,
    102,
    62,
    87,
    160,
    89,
    50,
    91,
    181,
    93,
    43,
    95,
    35,
    146,
    163,
    242,
    191,
    101,
    85,
    220,
    196,
    105,
    207,
    107,
    145,
    109,
    76,
    110,
    168,
    113,
    171,
    115,
    34,
    222,
    108,
    119,
    54,
    121,
    78,
    248,
    208,
    125,
    94,
    127,
    130,
    2,
    0,
    131,
    31,
    133,
    169,
    148,
    96,
    137,
    37,
    139,
    250,
    70,
    11,
    143,
    244,
    58,
    97,
    180,
    135,
    149,
    218,
    151,
    75,
    153,
    200,
    20,
    118,
    157,
    51,
    159,
    188,
    161,
    224,
    98,
    195,
    165,
    120,
    212,
    103,
    238,
    29,
    116,
    100,
    173,
    252,
    175,
    30,
    177,
    217,
    179,
    147,
    192,
    72,
    183,
    194,
    185,
    228,
    187,
    63,
    189,
    12,
    104,
    92,
    193,
    249,
    164,
    172,
    197,
    24,
    199,
    28,
    201,
    48,
    174,
    132,
    60,
    176,
    210,
    22,
    122,
    106,
    90,
    167,
    213,
    23,
    215,
    128,
    178,
    124,
    219,
    112,
    216,
    74,
    223,
    136,
    225,
    166,
    227,
    246,
    229,
    254,
    231,
    38,
    233,
    235,
    40,
    56,
    237,
    134,
    239,
    36,
    241,
    236,
    243,
    9,
    226,
    16,
    198,
    123,
    184,
    69,
    251,
    66,
    253,
    156,
    255,
    0,
    1,
    129,
    3,
    21,
    84,
    47,
    7,
    46,
    14,
    25,
    142,
    6,
    13,
    144,
    15,
    206,
    17,
    73,
    32,
    155,
    4,
    8,
    214,
    247,
    10,
    80,
    27,
    86,
    170,
    202,
    204,
    150,
    33,
    114,
    82,
    162,
    138,
    186,
    39,
    64,
    44,
    111,
    126,
    41,
    45,
    19,
    190,
    79,
    49,
    211,
    158,
    5,
    53,
    245,
    55,
    99,
    57,
    230,
    59,
    205,
    61,
    71,
    88,
    234,
    65,
    203,
    67,
    209,
    140,
    141,
    154,
    240,
    18,
    117,
    152,
    42,
    77,
    68,
    232,
    182,
    81,
    26,
    83,
    52,
    102,
    62,
    87,
    160,
    89,
    50,
    91,
    181,
    93,
    43,
    95,
    35,
    146,
    163,
    242,
    191,
    101,
    85,
    220,
    196,
    105,
    207,
    107,
    145,
    109,
    76,
    110,
    168,
    113,
    171,
    115,
    34,
    222,
    108,
    119,
    54,
    121,
    78,
    248,
    208,
    125,
    94,
    127,
    130,
    2,
    0,
    131,
    31,
    133,
    169,
    148,
    96,
    137,
    37,
    139,
    250,
    70,
    11,
    143,
    244,
    58,
    97,
    180,
    135,
    149,
    218,
    151,
    75,
    153,
    200,
    20,
    118,
    157,
    51,
    159,
    188,
    161,
    224,
    98,
    195,
    165,
    120,
    212,
    103,
    238,
    29,
    116,
    100,
    173,
    252,
    175,
    30,
    177,
    217,
    179,
    147,
    192,
    72,
    183,
    194,
    185,
    228,
    187,
    63,
    189,
    12,
    104,
    92,
    193,
    249,
    164,
    172,
    197,
    24,
    199,
    28,
    201,
    48,
    174,
    132,
    60,
    176,
    210,
    22,
    122,
    106,
    90,
    167,
    213,
    23,
    215,
    128,
    178,
    124,
    219,
    112,
    216,
    74,
    223,
    136,
    225,
    166,
    227,
    246,
    229,
    254,
    231,
    38,
    233,
    235,
    40,
    56,
    237,
    134,
    239,
    36,
    241,
    236,
    243,
    9,
    226,
    16,
    198,
    123,
    184,
    69,
    251,
    66,
    253,
    156,
    255,
    0,
    1,
};

float Noise::g[][3] =
{
    {0.881927f, 0.00933256f, -0.471294f},
    {0.783613f, 0.523784f, 0.334067f},
    {0.16021f, -0.224294f, 0.961262f},
    {0.476773f, -0.630021f, 0.612994f},
    {-0.299992f, -0.549216f, 0.779979f},
    {-0.437603f, -0.389943f, 0.810215f},
    {0.474441f, -0.809644f, -0.345517f},
    {0.250258f, 0.896758f, 0.36496f},
    {0.664083f, -0.723553f, 0.188322f},
    {-0.955856f, -0.00391744f, -0.293808f},
    {0.430173f, -0.337663f, -0.837219f},
    {-0.608608f, 0.107774f, 0.786118f},
    {-0.161776f, 0.0276203f, 0.986441f},
    {-0.900782f, 0.407496f, -0.15013f},
    {0.67719f, -0.735235f, -0.0290224f},
    {0.435259f, 0.383347f, 0.814613f},
    {0.990155f, 0.0594093f, -0.12674f},
    {-0.0900124f, 0.565078f, -0.820113f},
    {0.877974f, 0.321742f, -0.354462f},
    {-0.292866f, -0.348273f, -0.89047f},
    {-0.493484f, -0.626647f, 0.603148f},
    {-0.018251f, -0.748291f, 0.66312f},
    {0.442048f, -0.191684f, 0.876271f},
    {-0.039175f, -0.415255f, -0.908861f},
    {-0.375172f, -0.875401f, 0.304827f},
    {0.816216f, -0.575061f, 0.0556511f},
    {0.688177f, 0.478367f, -0.545506f},
    {-0.519943f, -0.0310413f, 0.853637f},
    {0.732517f, 0.677232f, -0.0691053f},
    {-0.387999f, -0.383872f, 0.837913f},
    {-0.495871f, 0.602129f, -0.625742f},
    {-0.557869f, -0.825864f, -0.0820395f},
    {-0.252615f, 0.959939f, -0.121255f},
    {0.656728f, -0.682583f, 0.320607f},
    {-0.0722408f, 0.995318f, -0.0642141f},
    {0.0264206f, 0.970958f, 0.237786f},
    {0.566363f, -0.257857f, -0.782779f},
    {-0.79241f, 0.608663f, -0.0401947f},
    {-0.61328f, -0.789435f, -0.026097f},
    {0.621471f, -0.777896f, 0.0930093f},
    {0.179964f, 0.439912f, -0.879824f},
    {0.920163f, -0.387437f, 0.0565012f},
    {0.731388f, 0.427997f, 0.530933f},
    {0.696311f, -0.575795f, 0.428499f},
    {0.714037f, 0.409693f, -0.567718f},
    {-0.954945f, 0.296734f, 0.00539517f},
    {-0.261215f, 0.931668f, -0.252508f},
    {-0.0466522f, 0.419869f, 0.906385f},
    {0.901551f, -0.353311f, -0.249754f},
    {-0.0734223f, -0.682827f, -0.726881f},
    {0.789875f, 0.490128f, -0.368608f},
    {-0.842201f, -0.191409f, 0.504044f},
    {0.768506f, 0.286146f, 0.572292f},
    {0.659914f, -0.611391f, -0.436708f},
    {0.637383f, -0.174766f, 0.750467f},
    {0.0181811f, -0.645428f, -0.763605f},
    {0.903195f, 0.428914f, -0.0164967f},
    {-0.680163f, 0.216645f, -0.700316f},
    {0.157334f, 0.875823f, 0.456267f},
    {-0.725857f, 0.488843f, -0.483905f},
    {-0.268821f, -0.604847f, -0.749597f},
    {-0.206278f, 0.56349f, -0.799955f},
    {-0.759064f, -0.586905f, 0.281715f},
    {-0.626585f, 0.779282f, -0.0105308f},
    {0.453898f, 0.841373f, 0.293373f},
    {0.335068f, -0.687101f, -0.644687f},
    {0.605501f, -0.70011f, 0.378438f},
    {0.368652f, 0.741971f, 0.559978f},
    {0.200715f, -0.0821105f, 0.976203f},
    {0.870031f, -0.487923f, 0.0705431f},
    {0.657558f, -0.307665f, -0.687721f},
    {-0.803072f, 0.317494f, -0.504255f},
    {-0.940811f, -0.338894f, 0.00505812f},
    {0.945164f, -0.219413f, -0.241917f},
    {0.543321f, -0.628883f, 0.556155f},
    {0.117745f, -0.781828f, 0.612275f},
    {-0.162865f, 0.35381f, -0.921029f},
    {0.625338f, 0.695941f, -0.353013f},
    {0.823315f, 0.476656f, 0.308141f},
    {-0.586069f, -0.138442f, 0.798346f},
    {-0.991332f, 0.097024f, -0.0885871f},
    {-0.781887f, -0.414443f, 0.465714f},
    {-0.370439f, -0.928134f, -0.0366369f},
    {0.371806f, 0.87668f, -0.305273f},
    {0.0246669f, -0.999011f, -0.0370004f},
    {-0.777502f, -0.622795f, -0.0872707f},
    {0.881495f, -0.25652f, -0.39644f},
    {0.32106f, 0.840871f, -0.435724f},
    {-0.908547f, -0.204628f, -0.364237f},
    {-0.18656f, -0.457919f, -0.869198f},
    {-0.0928068f, 0.625437f, -0.774735f},
    {-0.80303f, -0.499758f, -0.324629f},
    {0.467011f, -0.862955f, -0.192896f},
    {-0.844156f, 0.427559f, 0.32341f},
    {-0.366754f, -0.171152f, 0.914439f},
    {-0.37027f, -0.590118f, -0.717398f},
    {-0.327903f, -0.595403f, 0.733468f},
    {0.0786493f, 0.992192f, -0.0967992f},
    {0.470555f, 0.796323f, 0.380063f},
    {-0.778758f, -0.0450149f, -0.625707f},
    {0.287529f, 0.406964f, 0.867011f},
    {-0.935035f, -0.21864f, 0.279115f},
    {-0.333575f, -0.942711f, 0.00483442f},
    {-0.487224f, -0.861555f, -0.142602f},
    {0.524416f, 0.348022f, 0.77709f},
    {-0.315749f, -0.874779f, 0.367511f},
    {0.718447f, 0.662256f, -0.212724f},
    {-0.108332f, 0.526184f, -0.843442f},
    {-0.312189f, 0.70359f, 0.638357f},
    {0.719518f, -0.575614f, -0.388539f},
    {-0.116052f, 0.98644f, -0.116052f},
    {0.835012f, -0.0392024f, -0.548834f},
    {-0.263718f, -0.61403f, 0.743922f},
    {0.662808f, -0.14685f, 0.734248f},
    {-0.567505f, 0.823282f, -0.0119895f},
    {0.0315202f, -0.737572f, -0.674532f},
    {-0.463101f, 0.767773f, 0.44279f},
    {0.760856f, -0.502826f, -0.4102f},
    {-0.884402f, 0.136062f, -0.446453f},
    {-0.820505f, -0.0444609f, 0.569908f},
    {0.261755f, 0.251285f, -0.931848f},
    {0.538347f, 0.507289f, -0.672934f},
    {-0.833848f, -0.489191f, -0.255713f},
    {-0.981969f, 0.0892699f, -0.166637f},
    {0.567306f, 0.669131f, -0.480029f},
    {0.471825f, 0.845723f, -0.249266f},
    {0.178178f, -0.0633521f, 0.981957f},
    {0.531368f, -0.315365f, 0.786252f},
    {0.568053f, 0.0272665f, -0.82254f},
    {-0.660161f, 0.746849f, -0.0800196f},
    {-0.743197f, 0.276539f, 0.609249f},
    {-0.121776f, -0.748052f, 0.652371f},
    {0.90717f, 0.415575f, -0.0658838f},
    {0.899211f, -0.333993f, -0.282609f},
    {-0.929721f, 0.164693f, -0.329387f},
    {-0.301401f, -0.943517f, -0.137596f},
    {0.572063f, -0.631428f, 0.523491f},
    {0.960138f, 0.262223f, 0.0968206f},
    {0.956128f, -0.0670967f, -0.285161f},
    {0.492877f, -0.341223f, -0.800399f},
    {-0.0509833f, -0.846322f, -0.530226f},
    {-0.119676f, 0.977353f, 0.174527f},
    {0.579728f, -0.614119f, 0.535512f},
    {-0.0165382f, 0.70701f, 0.70701f},
    {0.776577f, -0.496146f, -0.388288f},
    {-0.267511f, -0.312852f, -0.911351f},
    {0.043586f, -0.966156f, -0.254251f},
    {-0.619005f, -0.706807f, 0.342428f},
    {0.34909f, 0.934329f, -0.0718715f},
    {-0.207273f, 0.288556f, -0.934759f},
    {0.191337f, 0.569106f, 0.799692f},
    {0.706407f, -0.307333f, -0.637601f},
    {-0.549731f, -0.768827f, 0.326652f},
    {-0.597983f, -0.776328f, 0.199328f},
    {0, 0.21279f, 0.977098f},
    {0.836218f, 0.380099f, -0.395303f},
    {-0.347158f, -0.586415f, -0.731846f},
    {-0.74361f, 0.358621f, -0.5643f},
    {-0.119613f, 0.967308f, -0.223625f},
    {0.521332f, 0.392343f, -0.757813f},
    {0.333037f, -0.636249f, 0.695898f},
    {-0.736632f, -0.0687523f, -0.67279f},
    {-0.368305f, -0.830733f, 0.417413f},
    {0.802572f, 0.401286f, 0.441415f},
    {0.618643f, -0.520566f, -0.588466f},
    {0.340475f, -0.89686f, 0.282345f},
    {0.416618f, 0.901255f, -0.119034f},
    {0.980928f, -0.159461f, -0.11114f},
    {-0.874596f, -0.477977f, -0.0813578f},
    {0.617716f, 0.677112f, -0.399932f},
    {-0.719814f, 0.482602f, 0.498962f},
    {0.312856f, -0.483006f, 0.817818f},
    {0.319034f, -0.0294493f, 0.947286f},
    {-0.691378f, -0.550129f, 0.468353f},
    {-0.435125f, 0.255549f, -0.863343f},
    {-0.484711f, -0.803235f, 0.346222f},
    {0.170271f, 0.887471f, -0.428256f},
    {0.112697f, -0.798272f, 0.59166f},
    {-0.790477f, -0.560622f, 0.246674f},
    {0.145604f, -0.208006f, -0.967229f},
    {0.125644f, -0.225292f, -0.966156f},
    {0.685839f, 0.719918f, -0.106497f},
    {-0.501538f, -0.3869f, -0.773801f},
    {0.416413f, 0.904898f, -0.0880874f},
    {-0.615626f, -0.619649f, -0.486867f},
    {0.669855f, 0.525021f, 0.525021f},
    {-0.270705f, 0.0887557f, 0.958562f},
    {-0.184426f, -0.493999f, 0.849678f},
    {0.207925f, -0.855237f, -0.474696f},
    {-0.35043f, -0.133075f, 0.927087f},
    {-0.890682f, -0.356273f, 0.282411f},
    {0.39093f, 0.349045f, 0.85167f},
    {0.346808f, -0.579477f, 0.737516f},
    {0.677666f, 0.687347f, 0.261386f},
    {0.448941f, 0.104405f, -0.887441f},
    {-0.769922f, -0.558906f, 0.307969f},
    {0.863871f, 0.497192f, -0.0807937f},
    {0.88277f, -0.387558f, -0.265549f},
    {0.316139f, 0.724484f, -0.612519f},
    {-0.156561f, -0.305093f, 0.939365f},
    {-0.863919f, 0.493668f, -0.0996829f},
    {-0.399274f, 0.432948f, 0.808169f},
    {-0.201097f, -0.827772f, -0.523788f},
    {0.649832f, -0.69096f, -0.31669f},
    {0.58329f, -0.762109f, -0.281001f},
    {-0.0146116f, 0.0535757f, -0.998457f},
    {0.0301203f, 0.85843f, 0.512046f},
    {0.122289f, -0.778574f, -0.615522f},
    {-0.6378f, -0.621855f, -0.454432f},
    {0.572703f, -0.381802f, 0.725423f},
    {0.283725f, -0.671761f, -0.684278f},
    {0.482124f, 0.583624f, 0.653405f},
    {-0.464375f, -0.883445f, 0.0622942f},
    {-0.343074f, 0.810902f, 0.474066f},
    {0.362148f, 0.354905f, -0.861912f},
    {0.245597f, -0.30927f, 0.918713f},
    {0.404371f, 0.269581f, 0.873963f},
    {0.104848f, 0.986809f, 0.123351f},
    {0.600225f, -0.104626f, -0.792958f},
    {-0.27876f, -0.931313f, 0.234412f},
    {0, 0.987007f, -0.160676f},
    {-0.570647f, -0.723605f, 0.388276f},
    {0.865457f, 0.397092f, -0.305455f},
    {0.619109f, 0.754539f, -0.217656f},
    {-0.112209f, -0.0290913f, -0.993259f},
    {-0.481007f, -0.15838f, -0.862292f},
    {-0.805298f, 0.592131f, -0.0296065f},
    {-0.101503f, -0.882635f, 0.45897f},
    {-0.84889f, 0.523013f, 0.0764403f},
    {-0.0694843f, -0.67499f, 0.734548f},
    {-0.0984886f, 0.977007f, 0.189098f},
    {0.823002f, 0.564805f, 0.0605149f},
    {-0.996435f, -0.08052f, 0.0251625f},
    {0.319592f, -0.834754f, -0.448382f},
    {0.798493f, 0.550685f, 0.243219f},
    {-0.265283f, -0.631625f, 0.728474f},
    {-0.678481f, 0.325353f, 0.658642f},
    {0.729404f, 0.070763f, -0.680414f},
    {-0.95973f, 0.280536f, -0.0147651f},
    {-0.866431f, -0.404334f, -0.292936f},
    {-0.528207f, 0.803314f, 0.275108f},
    {-0.459883f, 0.27593f, -0.84402f},
    {-0.164752f, 0.804749f, -0.570295f},
    {0.616383f, 0.273302f, 0.738497f},
    {-0.122193f, 0.882944f, -0.453297f},
    {-0.643681f, 0.760714f, 0.083595f},
    {-0.0738983f, 0.468023f, 0.880621f},
    {0.314462f, -0.612935f, 0.724862f},
    {-0.35677f, 0.932466f, 0.0567588f},
    {0.511392f, -0.146711f, -0.846731f},
    {-0.185801f, 0.170318f, 0.967714f},
    {-0.171952f, -0.96137f, -0.214941f},
    {-0.81662f, 0.361197f, 0.450188f},
    {-0.0538588f, 0.65977f, 0.749535f},
    {0.317011f, -0.926956f, -0.20064f},
    {0.190026f, 0.740102f, -0.645089f},
    {0.881927f, 0.00933256f, -0.471294f},
    {0.783613f, 0.523784f, 0.334067f},
    {0.16021f, -0.224294f, 0.961262f},
    {0.476773f, -0.630021f, 0.612994f},
    {-0.299992f, -0.549216f, 0.779979f},
    {-0.437603f, -0.389943f, 0.810215f},
    {0.474441f, -0.809644f, -0.345517f},
    {0.250258f, 0.896758f, 0.36496f},
    {0.664083f, -0.723553f, 0.188322f},
    {-0.955856f, -0.00391744f, -0.293808f},
    {0.430173f, -0.337663f, -0.837219f},
    {-0.608608f, 0.107774f, 0.786118f},
    {-0.161776f, 0.0276203f, 0.986441f},
    {-0.900782f, 0.407496f, -0.15013f},
    {0.67719f, -0.735235f, -0.0290224f},
    {0.435259f, 0.383347f, 0.814613f},
    {0.990155f, 0.0594093f, -0.12674f},
    {-0.0900124f, 0.565078f, -0.820113f},
    {0.877974f, 0.321742f, -0.354462f},
    {-0.292866f, -0.348273f, -0.89047f},
    {-0.493484f, -0.626647f, 0.603148f},
    {-0.018251f, -0.748291f, 0.66312f},
    {0.442048f, -0.191684f, 0.876271f},
    {-0.039175f, -0.415255f, -0.908861f},
    {-0.375172f, -0.875401f, 0.304827f},
    {0.816216f, -0.575061f, 0.0556511f},
    {0.688177f, 0.478367f, -0.545506f},
    {-0.519943f, -0.0310413f, 0.853637f},
    {0.732517f, 0.677232f, -0.0691053f},
    {-0.387999f, -0.383872f, 0.837913f},
    {-0.495871f, 0.602129f, -0.625742f},
    {-0.557869f, -0.825864f, -0.0820395f},
    {-0.252615f, 0.959939f, -0.121255f},
    {0.656728f, -0.682583f, 0.320607f},
    {-0.0722408f, 0.995318f, -0.0642141f},
    {0.0264206f, 0.970958f, 0.237786f},
    {0.566363f, -0.257857f, -0.782779f},
    {-0.79241f, 0.608663f, -0.0401947f},
    {-0.61328f, -0.789435f, -0.026097f},
    {0.621471f, -0.777896f, 0.0930093f},
    {0.179964f, 0.439912f, -0.879824f},
    {0.920163f, -0.387437f, 0.0565012f},
    {0.731388f, 0.427997f, 0.530933f},
    {0.696311f, -0.575795f, 0.428499f},
    {0.714037f, 0.409693f, -0.567718f},
    {-0.954945f, 0.296734f, 0.00539517f},
    {-0.261215f, 0.931668f, -0.252508f},
    {-0.0466522f, 0.419869f, 0.906385f},
    {0.901551f, -0.353311f, -0.249754f},
    {-0.0734223f, -0.682827f, -0.726881f},
    {0.789875f, 0.490128f, -0.368608f},
    {-0.842201f, -0.191409f, 0.504044f},
    {0.768506f, 0.286146f, 0.572292f},
    {0.659914f, -0.611391f, -0.436708f},
    {0.637383f, -0.174766f, 0.750467f},
    {0.0181811f, -0.645428f, -0.763605f},
    {0.903195f, 0.428914f, -0.0164967f},
    {-0.680163f, 0.216645f, -0.700316f},
    {0.157334f, 0.875823f, 0.456267f},
    {-0.725857f, 0.488843f, -0.483905f},
    {-0.268821f, -0.604847f, -0.749597f},
    {-0.206278f, 0.56349f, -0.799955f},
    {-0.759064f, -0.586905f, 0.281715f},
    {-0.626585f, 0.779282f, -0.0105308f},
    {0.453898f, 0.841373f, 0.293373f},
    {0.335068f, -0.687101f, -0.644687f},
    {0.605501f, -0.70011f, 0.378438f},
    {0.368652f, 0.741971f, 0.559978f},
    {0.200715f, -0.0821105f, 0.976203f},
    {0.870031f, -0.487923f, 0.0705431f},
    {0.657558f, -0.307665f, -0.687721f},
    {-0.803072f, 0.317494f, -0.504255f},
    {-0.940811f, -0.338894f, 0.00505812f},
    {0.945164f, -0.219413f, -0.241917f},
    {0.543321f, -0.628883f, 0.556155f},
    {0.117745f, -0.781828f, 0.612275f},
    {-0.162865f, 0.35381f, -0.921029f},
    {0.625338f, 0.695941f, -0.353013f},
    {0.823315f, 0.476656f, 0.308141f},
    {-0.586069f, -0.138442f, 0.798346f},
    {-0.991332f, 0.097024f, -0.0885871f},
    {-0.781887f, -0.414443f, 0.465714f},
    {-0.370439f, -0.928134f, -0.0366369f},
    {0.371806f, 0.87668f, -0.305273f},
    {0.0246669f, -0.999011f, -0.0370004f},
    {-0.777502f, -0.622795f, -0.0872707f},
    {0.881495f, -0.25652f, -0.39644f},
    {0.32106f, 0.840871f, -0.435724f},
    {-0.908547f, -0.204628f, -0.364237f},
    {-0.18656f, -0.457919f, -0.869198f},
    {-0.0928068f, 0.625437f, -0.774735f},
    {-0.80303f, -0.499758f, -0.324629f},
    {0.467011f, -0.862955f, -0.192896f},
    {-0.844156f, 0.427559f, 0.32341f},
    {-0.366754f, -0.171152f, 0.914439f},
    {-0.37027f, -0.590118f, -0.717398f},
    {-0.327903f, -0.595403f, 0.733468f},
    {0.0786493f, 0.992192f, -0.0967992f},
    {0.470555f, 0.796323f, 0.380063f},
    {-0.778758f, -0.0450149f, -0.625707f},
    {0.287529f, 0.406964f, 0.867011f},
    {-0.935035f, -0.21864f, 0.279115f},
    {-0.333575f, -0.942711f, 0.00483442f},
    {-0.487224f, -0.861555f, -0.142602f},
    {0.524416f, 0.348022f, 0.77709f},
    {-0.315749f, -0.874779f, 0.367511f},
    {0.718447f, 0.662256f, -0.212724f},
    {-0.108332f, 0.526184f, -0.843442f},
    {-0.312189f, 0.70359f, 0.638357f},
    {0.719518f, -0.575614f, -0.388539f},
    {-0.116052f, 0.98644f, -0.116052f},
    {0.835012f, -0.0392024f, -0.548834f},
    {-0.263718f, -0.61403f, 0.743922f},
    {0.662808f, -0.14685f, 0.734248f},
    {-0.567505f, 0.823282f, -0.0119895f},
    {0.0315202f, -0.737572f, -0.674532f},
    {-0.463101f, 0.767773f, 0.44279f},
    {0.760856f, -0.502826f, -0.4102f},
    {-0.884402f, 0.136062f, -0.446453f},
    {-0.820505f, -0.0444609f, 0.569908f},
    {0.261755f, 0.251285f, -0.931848f},
    {0.538347f, 0.507289f, -0.672934f},
    {-0.833848f, -0.489191f, -0.255713f},
    {-0.981969f, 0.0892699f, -0.166637f},
    {0.567306f, 0.669131f, -0.480029f},
    {0.471825f, 0.845723f, -0.249266f},
    {0.178178f, -0.0633521f, 0.981957f},
    {0.531368f, -0.315365f, 0.786252f},
    {0.568053f, 0.0272665f, -0.82254f},
    {-0.660161f, 0.746849f, -0.0800196f},
    {-0.743197f, 0.276539f, 0.609249f},
    {-0.121776f, -0.748052f, 0.652371f},
    {0.90717f, 0.415575f, -0.0658838f},
    {0.899211f, -0.333993f, -0.282609f},
    {-0.929721f, 0.164693f, -0.329387f},
    {-0.301401f, -0.943517f, -0.137596f},
    {0.572063f, -0.631428f, 0.523491f},
    {0.960138f, 0.262223f, 0.0968206f},
    {0.956128f, -0.0670967f, -0.285161f},
    {0.492877f, -0.341223f, -0.800399f},
    {-0.0509833f, -0.846322f, -0.530226f},
    {-0.119676f, 0.977353f, 0.174527f},
    {0.579728f, -0.614119f, 0.535512f},
    {-0.0165382f, 0.70701f, 0.70701f},
    {0.776577f, -0.496146f, -0.388288f},
    {-0.267511f, -0.312852f, -0.911351f},
    {0.043586f, -0.966156f, -0.254251f},
    {-0.619005f, -0.706807f, 0.342428f},
    {0.34909f, 0.934329f, -0.0718715f},
    {-0.207273f, 0.288556f, -0.934759f},
    {0.191337f, 0.569106f, 0.799692f},
    {0.706407f, -0.307333f, -0.637601f},
    {-0.549731f, -0.768827f, 0.326652f},
    {-0.597983f, -0.776328f, 0.199328f},
    {0, 0.21279f, 0.977098f},
    {0.836218f, 0.380099f, -0.395303f},
    {-0.347158f, -0.586415f, -0.731846f},
    {-0.74361f, 0.358621f, -0.5643f},
    {-0.119613f, 0.967308f, -0.223625f},
    {0.521332f, 0.392343f, -0.757813f},
    {0.333037f, -0.636249f, 0.695898f},
    {-0.736632f, -0.0687523f, -0.67279f},
    {-0.368305f, -0.830733f, 0.417413f},
    {0.802572f, 0.401286f, 0.441415f},
    {0.618643f, -0.520566f, -0.588466f},
    {0.340475f, -0.89686f, 0.282345f},
    {0.416618f, 0.901255f, -0.119034f},
    {0.980928f, -0.159461f, -0.11114f},
    {-0.874596f, -0.477977f, -0.0813578f},
    {0.617716f, 0.677112f, -0.399932f},
    {-0.719814f, 0.482602f, 0.498962f},
    {0.312856f, -0.483006f, 0.817818f},
    {0.319034f, -0.0294493f, 0.947286f},
    {-0.691378f, -0.550129f, 0.468353f},
    {-0.435125f, 0.255549f, -0.863343f},
    {-0.484711f, -0.803235f, 0.346222f},
    {0.170271f, 0.887471f, -0.428256f},
    {0.112697f, -0.798272f, 0.59166f},
    {-0.790477f, -0.560622f, 0.246674f},
    {0.145604f, -0.208006f, -0.967229f},
    {0.125644f, -0.225292f, -0.966156f},
    {0.685839f, 0.719918f, -0.106497f},
    {-0.501538f, -0.3869f, -0.773801f},
    {0.416413f, 0.904898f, -0.0880874f},
    {-0.615626f, -0.619649f, -0.486867f},
    {0.669855f, 0.525021f, 0.525021f},
    {-0.270705f, 0.0887557f, 0.958562f},
    {-0.184426f, -0.493999f, 0.849678f},
    {0.207925f, -0.855237f, -0.474696f},
    {-0.35043f, -0.133075f, 0.927087f},
    {-0.890682f, -0.356273f, 0.282411f},
    {0.39093f, 0.349045f, 0.85167f},
    {0.346808f, -0.579477f, 0.737516f},
    {0.677666f, 0.687347f, 0.261386f},
    {0.448941f, 0.104405f, -0.887441f},
    {-0.769922f, -0.558906f, 0.307969f},
    {0.863871f, 0.497192f, -0.0807937f},
    {0.88277f, -0.387558f, -0.265549f},
    {0.316139f, 0.724484f, -0.612519f},
    {-0.156561f, -0.305093f, 0.939365f},
    {-0.863919f, 0.493668f, -0.0996829f},
    {-0.399274f, 0.432948f, 0.808169f},
    {-0.201097f, -0.827772f, -0.523788f},
    {0.649832f, -0.69096f, -0.31669f},
    {0.58329f, -0.762109f, -0.281001f},
    {-0.0146116f, 0.0535757f, -0.998457f},
    {0.0301203f, 0.85843f, 0.512046f},
    {0.122289f, -0.778574f, -0.615522f},
    {-0.6378f, -0.621855f, -0.454432f},
    {0.572703f, -0.381802f, 0.725423f},
    {0.283725f, -0.671761f, -0.684278f},
    {0.482124f, 0.583624f, 0.653405f},
    {-0.464375f, -0.883445f, 0.0622942f},
    {-0.343074f, 0.810902f, 0.474066f},
    {0.362148f, 0.354905f, -0.861912f},
    {0.245597f, -0.30927f, 0.918713f},
    {0.404371f, 0.269581f, 0.873963f},
    {0.104848f, 0.986809f, 0.123351f},
    {0.600225f, -0.104626f, -0.792958f},
    {-0.27876f, -0.931313f, 0.234412f},
    {0, 0.987007f, -0.160676f},
    {-0.570647f, -0.723605f, 0.388276f},
    {0.865457f, 0.397092f, -0.305455f},
    {0.619109f, 0.754539f, -0.217656f},
    {-0.112209f, -0.0290913f, -0.993259f},
    {-0.481007f, -0.15838f, -0.862292f},
    {-0.805298f, 0.592131f, -0.0296065f},
    {-0.101503f, -0.882635f, 0.45897f},
    {-0.84889f, 0.523013f, 0.0764403f},
    {-0.0694843f, -0.67499f, 0.734548f},
    {-0.0984886f, 0.977007f, 0.189098f},
    {0.823002f, 0.564805f, 0.0605149f},
    {-0.996435f, -0.08052f, 0.0251625f},
    {0.319592f, -0.834754f, -0.448382f},
    {0.798493f, 0.550685f, 0.243219f},
    {-0.265283f, -0.631625f, 0.728474f},
    {-0.678481f, 0.325353f, 0.658642f},
    {0.729404f, 0.070763f, -0.680414f},
    {-0.95973f, 0.280536f, -0.0147651f},
    {-0.866431f, -0.404334f, -0.292936f},
    {-0.528207f, 0.803314f, 0.275108f},
    {-0.459883f, 0.27593f, -0.84402f},
    {-0.164752f, 0.804749f, -0.570295f},
    {0.616383f, 0.273302f, 0.738497f},
    {-0.122193f, 0.882944f, -0.453297f},
    {-0.643681f, 0.760714f, 0.083595f},
    {-0.0738983f, 0.468023f, 0.880621f},
    {0.314462f, -0.612935f, 0.724862f},
    {-0.35677f, 0.932466f, 0.0567588f},
    {0.511392f, -0.146711f, -0.846731f},
    {-0.185801f, 0.170318f, 0.967714f},
    {-0.171952f, -0.96137f, -0.214941f},
    {-0.81662f, 0.361197f, 0.450188f},
    {-0.0538588f, 0.65977f, 0.749535f},
    {0.317011f, -0.926956f, -0.20064f},
    {0.190026f, 0.740102f, -0.645089f},
    {0.881927f, 0.00933256f, -0.471294f},
    {0.783613f, 0.523784f, 0.334067f},
};



}
