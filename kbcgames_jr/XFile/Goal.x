xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 102;
 0.27144;2.90000;-0.05000;,
 1.07144;2.90000;-0.05000;,
 1.07144;2.10000;-0.05000;,
 0.27144;2.10000;-0.05000;,
 1.07144;2.90000;-0.05000;,
 1.07144;2.90000;0.05000;,
 1.07144;2.10000;0.05000;,
 1.07144;2.10000;-0.05000;,
 1.07144;2.90000;0.05000;,
 0.27144;2.90000;0.05000;,
 0.27144;2.10000;0.05000;,
 1.07144;2.10000;0.05000;,
 0.27144;2.90000;0.05000;,
 0.27144;2.90000;-0.05000;,
 0.27144;2.10000;-0.05000;,
 0.27144;2.10000;0.05000;,
 1.07144;2.90000;-0.05000;,
 0.27144;2.90000;-0.05000;,
 0.27144;2.10000;-0.05000;,
 1.07144;2.10000;-0.05000;,
 0.00000;3.00000;-0.30000;,
 0.09271;3.00000;-0.28532;,
 0.09271;0.00000;-0.28532;,
 0.00000;0.00000;-0.30000;,
 0.17634;3.00000;-0.24271;,
 0.17634;0.00000;-0.24271;,
 0.24271;3.00000;-0.17634;,
 0.24271;0.00000;-0.17634;,
 0.28532;3.00000;-0.09271;,
 0.28532;0.00000;-0.09271;,
 0.30000;3.00000;0.00000;,
 0.30000;0.00000;0.00000;,
 0.28532;3.00000;0.09271;,
 0.28532;0.00000;0.09271;,
 0.24271;3.00000;0.17634;,
 0.24271;0.00000;0.17634;,
 0.17634;3.00000;0.24271;,
 0.17634;0.00000;0.24271;,
 0.09271;3.00000;0.28532;,
 0.09271;0.00000;0.28532;,
 0.00000;3.00000;0.30000;,
 0.00000;0.00000;0.30000;,
 -0.09271;3.00000;0.28532;,
 -0.09271;0.00000;0.28532;,
 -0.17634;3.00000;0.24271;,
 -0.17634;0.00000;0.24271;,
 -0.24271;3.00000;0.17634;,
 -0.24271;0.00000;0.17634;,
 -0.28532;3.00000;0.09271;,
 -0.28532;0.00000;0.09271;,
 -0.30000;3.00000;0.00000;,
 -0.30000;0.00000;0.00000;,
 -0.28532;3.00000;-0.09271;,
 -0.28532;0.00000;-0.09271;,
 -0.24271;3.00000;-0.17634;,
 -0.24271;0.00000;-0.17634;,
 -0.17634;3.00000;-0.24271;,
 -0.17634;0.00000;-0.24271;,
 -0.09271;3.00000;-0.28532;,
 -0.09271;0.00000;-0.28532;,
 0.00000;3.00000;-0.30000;,
 0.00000;0.00000;-0.30000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;3.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;,
 0.00000;0.00000;0.00000;;
 
 66;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;21,24,25,22;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 3;62,21,20;,
 3;63,24,21;,
 3;64,26,24;,
 3;65,28,26;,
 3;66,30,28;,
 3;67,32,30;,
 3;68,34,32;,
 3;69,36,34;,
 3;70,38,36;,
 3;71,40,38;,
 3;72,42,40;,
 3;73,44,42;,
 3;74,46,44;,
 3;75,48,46;,
 3;76,50,48;,
 3;77,52,50;,
 3;78,54,52;,
 3;79,56,54;,
 3;80,58,56;,
 3;81,60,58;,
 3;82,23,22;,
 3;83,22,25;,
 3;84,25,27;,
 3;85,27,29;,
 3;86,29,31;,
 3;87,31,33;,
 3;88,33,35;,
 3;89,35,37;,
 3;90,37,39;,
 3;91,39,41;,
 3;92,41,43;,
 3;93,43,45;,
 3;94,45,47;,
 3;95,47,49;,
 3;96,49,51;,
 3;97,51,53;,
 3;98,53,55;,
 3;99,55,57;,
 3;100,57,59;,
 3;101,59,61;;
 
 MeshMaterialList {
  2;
  66;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "red.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.309017;0.000000;-0.951057;,
  0.587785;0.000000;-0.809017;,
  0.809017;0.000000;-0.587785;,
  0.951057;0.000000;-0.309017;,
  1.000000;0.000000;0.000000;,
  0.951057;0.000000;0.309017;,
  0.809017;0.000000;0.587785;,
  0.587785;0.000000;0.809017;,
  0.309017;0.000000;0.951057;,
  0.000000;0.000000;1.000000;,
  -0.309017;0.000000;0.951057;,
  -0.587785;0.000000;0.809017;,
  -0.809017;0.000000;0.587785;,
  -0.951057;0.000000;0.309017;,
  -1.000000;0.000000;0.000000;,
  -0.951057;0.000000;-0.309017;,
  -0.809017;0.000000;-0.587785;,
  -0.587785;0.000000;-0.809017;,
  -0.309017;0.000000;-0.951057;,
  0.000000;-1.000000;-0.000000;;
  66;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,7,7,26;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;6,6,6;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.050000;0.000000;,
  0.050000;1.000000;,
  0.000000;1.000000;,
  0.100000;0.000000;,
  0.100000;1.000000;,
  0.150000;0.000000;,
  0.150000;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.300000;0.000000;,
  0.300000;1.000000;,
  0.350000;0.000000;,
  0.350000;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.450000;0.000000;,
  0.450000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.550000;0.000000;,
  0.550000;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.650000;0.000000;,
  0.650000;1.000000;,
  0.700000;0.000000;,
  0.700000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.850000;0.000000;,
  0.850000;1.000000;,
  0.900000;0.000000;,
  0.900000;1.000000;,
  0.950000;0.000000;,
  0.950000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.025000;0.000000;,
  0.075000;0.000000;,
  0.125000;0.000000;,
  0.175000;0.000000;,
  0.225000;0.000000;,
  0.275000;0.000000;,
  0.325000;0.000000;,
  0.375000;0.000000;,
  0.425000;0.000000;,
  0.475000;0.000000;,
  0.525000;0.000000;,
  0.575000;0.000000;,
  0.625000;0.000000;,
  0.675000;0.000000;,
  0.725000;0.000000;,
  0.775000;0.000000;,
  0.825000;0.000000;,
  0.875000;0.000000;,
  0.925000;0.000000;,
  0.975000;0.000000;,
  0.025000;1.000000;,
  0.075000;1.000000;,
  0.125000;1.000000;,
  0.175000;1.000000;,
  0.225000;1.000000;,
  0.275000;1.000000;,
  0.325000;1.000000;,
  0.375000;1.000000;,
  0.425000;1.000000;,
  0.475000;1.000000;,
  0.525000;1.000000;,
  0.575000;1.000000;,
  0.625000;1.000000;,
  0.675000;1.000000;,
  0.725000;1.000000;,
  0.775000;1.000000;,
  0.825000;1.000000;,
  0.875000;1.000000;,
  0.925000;1.000000;,
  0.975000;1.000000;;
 }
 MeshVertexColors {
  102;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;;
 }
}