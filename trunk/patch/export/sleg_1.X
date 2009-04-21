xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Animation {
 <3d82ab4f-62da-11cf-ab39-0020af71e433>
 [...]
}

template AnimationSet {
 <3d82ab50-62da-11cf-ab39-0020af71e433>
 [Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]
}

template FloatKeys {
 <10dd46a9-775b-11cf-8f52-0040333594a3>
 DWORD nValues;
 array FLOAT values[nValues];
}

template TimedFloatKeys {
 <f406b180-7b3b-11cf-8f52-0040333594a3>
 DWORD time;
 FloatKeys tfkeys;
}

template AnimationKey {
 <10dd46a8-775b-11cf-8f52-0040333594a3>
 DWORD keyType;
 DWORD nKeys;
 array TimedFloatKeys keys[nKeys];
}


Frame Bone02 {
 

 FrameTransformMatrix {
  0.999995,0.003117,-0.000000,0.000000,-0.003117,0.999995,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,21.837116,0.000000,-0.000003,1.000000;;
 }
}

AnimationSet Anim-1 {
 

 Animation Anim-Bone02 {
  
  { Bone02 }

  AnimationKey {
   0;
   2;
   0;4;-0.999999,0.000000,0.000000,0.001558;;,
   3200;4;-0.999999,0.000000,0.000000,0.001558;;;
  }

  AnimationKey {
   1;
   2;
   0;3;1.000000,1.000000,1.000000;;,
   3200;3;1.000000,1.000000,1.000000;;;
  }

  AnimationKey {
   2;
   2;
   0;3;21.837116,0.000000,-0.000003;;,
   3200;3;21.837116,0.000000,-0.000003;;;
  }
 }
}