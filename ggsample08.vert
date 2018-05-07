#version 150 core

// 光源
const vec4 pl = vec4(3.0, 4.0, 5.0, 1.0);           // 位置

// 頂点属性
in vec4 pv;                                         // ローカル座標系の頂点位置
in vec4 nv;                                         // 頂点の法線ベクトル
in vec2 tv;                                         // 頂点のテクスチャ座標

// 変換行列
uniform mat4 mw;                                    // 視点座標系への変換行列
uniform mat4 mc;                                    // クリッピング座標系への変換行列
uniform mat4 mg;                                    // 法線ベクトルの変換行列

// ラスタライザに送る頂点属性
out vec3 n;                                         // 頂点の法線ベクトル
out vec3 l;                                         // 光線ベクトル
out vec3 h;                                         // 中間ベクトル
out vec2 tc;                                        // テクスチャ座標

void main(void)
{
  vec4 p = mw * pv;                                 // 視点座標系の頂点の位置
  vec3 v = -normalize(p.xyz / p.w);                 // 視線ベクトル

  n = normalize((mg * nv).xyz);                     // 法線ベクトル
  l = normalize((pl * p.w - p * pl.w).xyz);         // 光線ベクトル
  h = normalize(l + v);                             // 中間ベクトル
  tc = tv;                                          // テクスチャ座標

  gl_Position = mc * pv;
}
