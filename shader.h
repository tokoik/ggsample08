//
// プログラムオブジェクトを作成する
//
//   vsrc: バーテックスシェーダのソースプログラムの文字列
//   pv: バーテックスシェーダのソースプログラム中の in 変数名の文字列
//   fsrc: フラグメントシェーダのソースプログラムの文字列
//   fc: フラグメントシェーダのソースプログラム中の out 変数名の文字列
//   vert: バーテックスシェーダのコンパイル時のメッセージに追加する文字列
//   frag: フラグメントシェーダのコンパイル時のメッセージに追加する文字列
//   戻り値: プログラムオブジェクト名
//
extern GLuint createProgram(const char* vsrc, const char* pv, const char* fsrc, const char* fc,
  const char* vert = "vertex shader", const char* frag = "fragment shader");

//
// シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
//
//   vert: バーテックスシェーダのソースファイル名
//   pv: バーテックスシェーダのソースプログラム中の in 変数名の文字列
//   frag: フラグメントシェーダのソースファイル名
//   fc: フラグメントシェーダのソースプログラム中の out 変数名の文字列
//   戻り値: プログラムオブジェクト名
//
extern GLuint loadProgram(const char* vert, const char* pv, const char* frag, const char* fc);
