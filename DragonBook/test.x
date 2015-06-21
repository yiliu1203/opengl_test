xof 0302txt 0032
Header {
 1;
 0;
 1;
}
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

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template FrameTransformMatrix {
 <F6F23F41-7686-11cf-8F52-0040333594A3>
 Matrix4x4 frameMatrix;
}

template Frame {
 <3D82AB46-62DA-11cf-AB39-0020AF71E433>
 [...]
}
template FloatKeys {
 <10DD46A9-775B-11cf-8F52-0040333594A3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <F406B180-7B3B-11cf-8F52-0040333594A3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10DD46A8-775B-11cf-8F52-0040333594A3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}

template AnimationOptions {
 <E2BF56C0-840F-11cf-8F52-0040333594A3>
 DWORD openclosed;
 DWORD positionquality;
}

template Animation {
 <3D82AB4F-62DA-11cf-AB39-0020AF71E433>
 [...]
}

template AnimationSet {
 <3D82AB50-62DA-11cf-AB39-0020AF71E433>
 [Animation]
}
Frame pCube1 {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh pCube11 {
 98;
7.740084;-4.458856;-1.672502;,
7.740084;-4.458856;9.007038;,
7.498711;-4.458856;9.007038;,
7.457107;-4.458856;-1.672502;,
-7.456925;4.620142;-1.672502;,
-7.764612;4.620142;-1.672502;,
-7.764612;4.620142;9.007038;,
-7.498302;4.620142;9.007038;,
7.740084;4.620142;-1.672502;,
7.740084;4.620142;9.007038;,
7.740084;4.346560;9.007038;,
7.740084;4.293977;-1.672502;,
-7.764612;4.331359;9.007038;,
-7.764612;4.620142;9.007038;,
-7.764612;4.620142;-1.672502;,
-7.764612;4.332983;-1.672502;,
7.740084;-4.458856;9.007038;,
7.740084;-4.170011;9.007038;,
7.476776;-4.176732;9.007038;,
7.498711;-4.458856;9.007038;,
-7.764612;4.620142;9.007038;,
-7.764612;4.331359;9.007038;,
-7.501303;4.338018;9.007038;,
-7.498302;4.620142;9.007038;,
7.740084;4.620142;9.007038;,
7.443327;4.620142;9.007038;,
7.476776;4.338018;9.007038;,
7.740084;4.346560;9.007038;,
7.476776;-4.176732;-1.672506;,
-7.501303;-4.176732;-1.672506;,
-7.501303;-4.176732;9.007038;,
7.476776;-4.176732;9.007038;,
-7.501303;4.338018;-1.672506;,
7.476776;4.338018;-1.672506;,
7.476776;4.338018;9.007038;,
-7.501303;4.338018;9.007038;,
-7.501303;-4.176732;-1.672506;,
-7.501303;4.338018;-1.672506;,
-7.501303;4.338018;9.007038;,
-7.501303;-4.176732;9.007038;,
7.476776;4.338018;-1.672506;,
7.476776;-4.176732;-1.672506;,
7.476776;-4.176732;9.007038;,
7.476776;4.338018;9.007038;,
7.476776;-4.176732;-1.672506;,
7.740084;-4.143190;-1.672502;,
7.740084;-4.458856;-1.672502;,
7.740084;-4.458856;-1.672502;,
7.457107;-4.458856;-1.672502;,
7.476776;-4.176732;-1.672506;,
-7.764612;4.332983;-1.672502;,
-7.764612;4.620142;-1.672502;,
-7.456925;4.620142;-1.672502;,
-7.456925;4.620142;-1.672502;,
-7.501303;4.338018;-1.672506;,
-7.764612;4.332983;-1.672502;,
-7.501303;4.338018;-1.672506;,
-7.456925;4.620142;-1.672502;,
7.474245;4.620142;-1.672502;,
7.476776;4.338018;-1.672506;,
7.476776;4.338018;-1.672506;,
7.740084;4.293977;-1.672502;,
-7.479277;-4.458856;-1.672502;,
-7.764612;-4.458856;-1.672502;,
-7.764612;-4.199859;-1.672502;,
-7.501303;-4.176732;-1.672506;,
-7.501303;-4.176732;-1.672506;,
-7.501303;-4.176732;-1.672506;,
-7.764612;4.332983;-1.672502;,
-7.501303;4.338018;-1.672506;,
-7.501303;4.338018;-1.672506;,
7.476776;4.338018;-1.672506;,
7.476776;-4.176732;-1.672506;,
-7.501303;-4.176732;-1.672506;,
7.740084;4.620142;-1.672502;,
7.740084;4.293977;-1.672502;,
7.740084;4.293977;-1.672502;,
7.476776;4.338018;-1.672506;,
-7.764612;-4.458856;-1.672502;,
-7.764612;-4.458856;9.007038;,
-7.764612;-4.208323;9.007038;,
-7.764612;-4.199859;-1.672502;,
-7.764612;-4.458856;9.007038;,
-7.491856;-4.458856;9.007038;,
-7.501303;-4.176732;9.007038;,
-7.764612;-4.208323;9.007038;,
7.443327;4.620142;9.007038;,
7.474245;4.620142;-1.672502;,
-7.491856;-4.458856;9.007038;,
-7.764612;-4.458856;9.007038;,
-7.764612;-4.458856;-1.672502;,
-7.479277;-4.458856;-1.672502;,
7.740084;-4.170011;9.007038;,
7.740084;-4.458856;9.007038;,
7.740084;-4.458856;-1.672502;,
7.740084;-4.143190;-1.672502;,
7.740084;4.620142;9.007038;,
7.740084;4.620142;-1.672502;;

 66;
3;0,1,2;,
3;2,3,0;,
3;4,5,6;,
3;6,7,4;,
3;8,9,10;,
3;10,11,8;,
3;12,13,14;,
3;14,15,12;,
3;16,17,18;,
3;18,19,16;,
3;20,21,22;,
3;22,23,20;,
3;24,25,26;,
3;26,27,24;,
3;28,29,30;,
3;30,31,28;,
3;32,33,34;,
3;34,35,32;,
3;36,37,38;,
3;38,39,36;,
3;40,41,42;,
3;42,43,40;,
3;44,45,46;,
3;47,48,49;,
3;50,51,52;,
3;53,54,55;,
3;56,57,58;,
3;58,59,56;,
3;60,61,45;,
3;45,44,60;,
3;62,63,64;,
3;64,65,62;,
3;48,62,66;,
3;66,49,48;,
3;67,64,68;,
3;68,69,67;,
3;70,71,72;,
3;70,72,73;,
3;58,74,75;,
3;76,77,58;,
3;78,79,80;,
3;80,81,78;,
3;82,83,84;,
3;84,85,82;,
3;22,26,25;,
3;25,23,22;,
3;86,87,4;,
3;4,7,86;,
3;88,89,90;,
3;90,91,88;,
3;85,84,22;,
3;22,21,85;,
3;81,80,12;,
3;12,15,81;,
3;92,93,94;,
3;94,95,92;,
3;18,84,83;,
3;83,19,18;,
3;3,2,88;,
3;88,91,3;,
3;96,97,87;,
3;87,86,96;,
3;26,18,17;,
3;17,27,26;,
3;11,10,92;,
3;92,95,11;;
MeshMaterialList {
 1;
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
 0.000000;0.000000;0.000000;1.000000;;
16.000002;
 0.952941;0.952941;0.952941;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"test_0.bmp";
}
 }
}

 MeshNormals {
 98;
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000015;0.000000;-1.000000;,
0.000015;0.000000;-1.000000;,
0.000015;0.000000;-1.000000;,
0.000000;-0.000014;-1.000000;,
0.000000;-0.000014;-1.000000;,
0.000000;-0.000014;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
-0.000015;0.000016;-1.000000;,
-0.000015;0.000016;-1.000000;,
-0.000015;0.000016;-1.000000;,
0.000000;0.000014;-1.000000;,
0.000000;0.000014;-1.000000;,
0.000004;0.000010;-1.000000;,
0.000000;0.000014;-1.000000;,
0.000015;0.000000;-1.000000;,
0.000015;0.000000;-1.000000;,
-0.000005;-0.000010;-1.000000;,
0.000000;0.000000;-1.000000;,
-0.000010;-0.000005;-1.000000;,
-0.000014;-0.000015;-1.000000;,
0.000000;-0.000014;-1.000000;,
-0.000015;0.000000;-1.000000;,
-0.000015;0.000000;-1.000000;,
-0.000015;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000017;0.000014;-1.000000;,
0.000017;0.000014;-1.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
1.000000;0.000000;0.000000;,
0.000000;1.000000;0.000000;,
0.000000;1.000000;0.000000;;

 66;
3;0,1,2;,
3;2,3,0;,
3;4,5,6;,
3;6,7,4;,
3;8,9,10;,
3;10,11,8;,
3;12,13,14;,
3;14,15,12;,
3;16,17,18;,
3;18,19,16;,
3;20,21,22;,
3;22,23,20;,
3;24,25,26;,
3;26,27,24;,
3;28,29,30;,
3;30,31,28;,
3;32,33,34;,
3;34,35,32;,
3;36,37,38;,
3;38,39,36;,
3;40,41,42;,
3;42,43,40;,
3;44,45,46;,
3;47,48,49;,
3;50,51,52;,
3;53,54,55;,
3;56,57,58;,
3;58,59,56;,
3;60,61,45;,
3;45,44,60;,
3;62,63,64;,
3;64,65,62;,
3;48,62,66;,
3;66,49,48;,
3;67,64,68;,
3;68,69,67;,
3;70,71,72;,
3;70,72,73;,
3;58,74,75;,
3;76,77,58;,
3;78,79,80;,
3;80,81,78;,
3;82,83,84;,
3;84,85,82;,
3;22,26,25;,
3;25,23,22;,
3;86,87,4;,
3;4,7,86;,
3;88,89,90;,
3;90,91,88;,
3;85,84,22;,
3;22,21,85;,
3;81,80,12;,
3;12,15,81;,
3;92,93,94;,
3;94,95,92;,
3;18,84,83;,
3;83,19,18;,
3;3,2,88;,
3;88,91,3;,
3;96,97,87;,
3;87,86,96;,
3;26,18,17;,
3;17,27,26;,
3;11,10,92;,
3;92,95,11;;
 }
MeshTextureCoords {
 98;
0.001992;0.998151;,
0.239843;0.998151;,
0.239843;0.992775;,
0.001992;0.991848;,
0.485606;0.659688;,
0.485606;0.652835;,
0.247755;0.652835;,
0.247755;0.658766;,
0.401235;0.311265;,
0.401235;0.073414;,
0.395142;0.073414;,
0.393971;0.311265;,
0.414001;0.073414;,
0.407569;0.073414;,
0.407569;0.311265;,
0.413965;0.311265;,
0.493323;0.998151;,
0.499756;0.998151;,
0.499606;0.992286;,
0.493323;0.992775;,
0.695527;0.652835;,
0.689096;0.652835;,
0.689244;0.658700;,
0.695527;0.658766;,
0.695527;0.998151;,
0.695527;0.991541;,
0.689244;0.992286;,
0.689434;0.998151;,
0.558249;0.648844;,
0.558249;0.315257;,
0.320397;0.315257;,
0.320397;0.648844;,
0.760157;0.315257;,
0.760157;0.648844;,
0.998008;0.648844;,
0.998008;0.315257;,
0.124624;0.648844;,
0.314262;0.648844;,
0.314262;0.410993;,
0.124624;0.410993;,
0.001992;0.407001;,
0.191630;0.407001;,
0.191630;0.169150;,
0.001992;0.169150;,
0.897782;0.992286;,
0.897035;0.998151;,
0.904065;0.998151;,
0.904065;0.998151;,
0.904065;0.991848;,
0.897782;0.992286;,
0.708256;0.652835;,
0.701861;0.652835;,
0.701861;0.659688;,
0.701861;0.659688;,
0.708144;0.658700;,
0.708256;0.652835;,
0.708144;0.658700;,
0.701861;0.659688;,
0.701861;0.992230;,
0.708144;0.992286;,
0.708144;0.992286;,
0.709125;0.998151;,
0.904065;0.659190;,
0.904065;0.652835;,
0.898297;0.652835;,
0.897782;0.658700;,
0.897782;0.658700;,
0.897782;0.658700;,
0.708256;0.652835;,
0.708144;0.658700;,
0.564384;0.315257;,
0.564384;0.648844;,
0.754022;0.648844;,
0.754022;0.315257;,
0.701861;0.998151;,
0.709125;0.998151;,
0.709125;0.998151;,
0.708144;0.992286;,
0.609773;0.311265;,
0.609773;0.073414;,
0.604194;0.073414;,
0.604005;0.311265;,
0.493323;0.652835;,
0.493323;0.658910;,
0.499606;0.658700;,
0.498903;0.652835;,
0.247755;0.991541;,
0.485606;0.992230;,
0.239843;0.658910;,
0.239843;0.652835;,
0.001992;0.652835;,
0.001992;0.659190;,
0.205464;0.073414;,
0.199031;0.073414;,
0.199031;0.311265;,
0.206062;0.311265;,
0.247755;0.998151;,
0.485606;0.998151;;
}
}
 }
Frame polySurfac {
   FrameTransformMatrix {
1.000000,0.000000,0.000000,0.000000,
0.000000,1.000000,0.000000,0.000000,
0.000000,0.000000,1.000000,0.000000,
0.000000,0.000000,0.000000,1.000000;;
 }
Mesh polySurfac1 {
 30;
-7.768028;4.660744;9.274059;,
-7.768028;-4.422930;9.274059;,
7.722267;-4.422930;9.274059;,
7.745147;4.660744;9.274059;,
-7.813790;4.683624;9.274059;,
-7.768028;4.660744;9.031581;,
-7.813790;4.683624;9.031581;,
7.745147;4.660744;9.031581;,
7.722267;-4.422930;9.031581;,
-7.768028;-4.422930;9.031581;,
-7.768028;-4.422930;9.274059;,
-7.768028;4.660744;9.274059;,
-7.768028;4.660744;9.031581;,
-7.768028;-4.422930;9.031581;,
7.722267;-4.422930;9.274059;,
-7.768028;-4.422930;9.274059;,
-7.768028;-4.422930;9.031581;,
7.722267;-4.422930;9.031581;,
7.745147;4.660744;9.274059;,
7.722267;-4.422930;9.274059;,
7.722267;-4.422930;9.031581;,
7.745147;4.660744;9.031581;,
-7.813790;4.683624;9.274059;,
7.745147;4.660744;9.274059;,
7.745147;4.660744;9.031581;,
-7.813790;4.683624;9.031581;,
-7.768028;4.660744;9.274059;,
-7.813790;4.683624;9.274059;,
-7.813790;4.683624;9.031581;,
-7.768028;4.660744;9.031581;;

 16;
3;0,1,2;,
3;0,2,3;,
3;0,3,4;,
3;5,6,7;,
3;5,7,8;,
3;5,8,9;,
3;10,11,12;,
3;12,13,10;,
3;14,15,16;,
3;16,17,14;,
3;18,19,20;,
3;20,21,18;,
3;22,23,24;,
3;24,25,22;,
3;26,27,28;,
3;28,29,26;;
MeshMaterialList {
 1;
 16;
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
 0.000000;0.000000;0.000000;1.000000;;
16.000002;
 0.952941;0.952941;0.952941;;
 0.000000;0.000000;0.000000;;
TextureFilename {
"test_1.bmp";
}
 }
}

 MeshNormals {
 30;
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
0.000000;0.000000;-1.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
-1.000000;0.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.000000;-1.000000;0.000000;,
0.999997;-0.002519;0.000000;,
0.999997;-0.002519;0.000000;,
0.999997;-0.002519;0.000000;,
0.999997;-0.002519;0.000000;,
0.001471;0.999999;0.000000;,
0.001471;0.999999;0.000000;,
0.001471;0.999999;0.000000;,
0.001471;0.999999;0.000000;,
-0.447191;-0.894438;0.000000;,
-0.447191;-0.894438;0.000000;,
-0.447191;-0.894438;0.000000;,
-0.447191;-0.894438;0.000000;;

 16;
3;0,1,2;,
3;0,2,3;,
3;0,3,4;,
3;5,6,7;,
3;5,7,8;,
3;5,8,9;,
3;10,11,12;,
3;12,13,10;,
3;14,15,16;,
3;16,17,14;,
3;18,19,20;,
3;20,21,18;,
3;22,23,24;,
3;24,25,22;,
3;26,27,28;,
3;28,29,26;;
 }
MeshTextureCoords {
 30;
0.001471;0.997059;,
0.585294;0.997059;,
0.585294;0.001471;,
0.001471;0.000000;,
0.000000;1.000000;,
0.001471;0.997059;,
0.000000;1.000000;,
0.001471;0.000000;,
0.585294;0.001471;,
0.585294;0.997059;,
0.585294;0.997059;,
0.001471;0.997059;,
0.001471;0.997059;,
0.585294;0.997059;,
0.585294;0.001471;,
0.585294;0.997059;,
0.585294;0.997059;,
0.585294;0.001471;,
0.001471;0.000000;,
0.585294;0.001471;,
0.585294;0.001471;,
0.001471;0.000000;,
0.000000;1.000000;,
0.001471;0.000000;,
0.001471;0.000000;,
0.000000;1.000000;,
0.001471;0.997059;,
0.000000;1.000000;,
0.000000;1.000000;,
0.001471;0.997059;;
}
}
 }
