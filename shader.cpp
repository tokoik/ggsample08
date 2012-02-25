#include <iostream>
#include <fstream>
#include <vector>

#include "gg.h"
using namespace gg;

#include "shader.h"

//
// シェーダオブジェクトのコンパイル結果を表示する
//
//   shader: シェーダオブジェクト名
//   str: コンパイルエラーが発生した場所を示す文字列
//   戻り値: コンパイルに成功していたら GL_TRUE
//
static GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  // コンパイル結果を取得する
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

  // シェーダのコンパイル時のログの長さを取得する
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1)
  {
    // シェーダのコンパイル時のログの内容を取得する
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }

  return static_cast<GLboolean>(status);
}

//
// プログラムオブジェクトのリンク結果を表示する
//
//   program: プログラムオブジェクト名
//   戻り値: リンクに成功していたら GL_TRUE
//
static GLboolean printProgramInfoLog(GLuint program)
{
  // リンク結果を取得する
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

  // シェーダのリンク時のログの長さを取得する
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1)
  {
    // シェーダのリンク時のログの内容を取得する
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }

  return static_cast<GLboolean>(status);
}

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
GLuint createProgram(const char *vsrc, const char *pv, const char *fsrc, const char *fc,
  const char *vert, const char *frag)
{
  // 空のプログラムオブジェクトを作成する
  const GLuint program(glCreateProgram());

  if (vsrc != NULL)
  {
    // バーテックスシェーダのシェーダオブジェクトを作成する
    const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(vobj, 1, &vsrc, NULL);
    glCompileShader(vobj);

    // バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
    if (printShaderInfoLog(vobj, vert))
      glAttachShader(program, vobj);
    glDeleteShader(vobj);
  }

  if (fsrc != NULL)
  {
    // フラグメントシェーダのシェーダオブジェクトを作成する
    const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(fobj, 1, &fsrc, NULL);
    glCompileShader(fobj);

    // フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
    if (printShaderInfoLog(fobj, frag))
      glAttachShader(program, fobj);
    glDeleteShader(fobj);
  }

  // プログラムオブジェクトをリンクする
  glBindAttribLocation(program, 0, pv);
  glBindFragDataLocation(program, 0, fc);
  glLinkProgram(program);

  // 作成したプログラムオブジェクトを返す
  if (printProgramInfoLog(program))
    return program;

  // プログラムオブジェクトが作成できなければ 0 を返す
  glDeleteProgram(program);
  return 0;
}

//
// シェーダのソースファイルを読み込んだメモリを返す
//
//   name: シェーダのソースファイル名
//   戻り値: ソースファイルを読み込んだメモリのポインタ
//
static GLchar *readShaderSource(const char *name)
{
  // ファイル名が NULL なら NULL を返す
  if (name == NULL) return NULL;

  // ソースファイルを開く
  std::ifstream file(name, std::ios::binary);
  if (file.fail())
  {
    // 開けなかった
    std::cerr << "Error: Can't open source file: " << name << std::endl;
    return NULL;
  }

  // ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
  file.seekg(0L, std::ios::end);
  GLsizei length(static_cast<GLsizei>(file.tellg()));

  // ファイルサイズのメモリを確保
  GLchar *buffer(new(std::nothrow) GLchar[length + 1]);
  if (buffer == NULL)
  {
    // メモリが足らなかった
    std::cerr << "Error: Too large file: " << name << std::endl;
    file.close();
    return NULL;
  }

  // ファイルを先頭から読み込む
  file.seekg(0L, std::ios::beg);
  file.read(buffer, length);
  buffer[length] = '\0';

  if (file.bad())
  {
    // うまく読み込めなかった
    std::cerr << "Error: Could not read souce file: " << name << std::endl;
    delete[] buffer;
    buffer = NULL;
  }
  file.close();

  // 読み込んだソースプログラム
  return buffer;
}

//
// シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
//
//   vert: バーテックスシェーダのソースファイル名
//   pv: バーテックスシェーダのソースプログラム中の in 変数名の文字列
//   frag: フラグメントシェーダのソースファイル名
//   fc: フラグメントシェーダのソースプログラム中の out 変数名の文字列
//   戻り値: プログラムオブジェクト名
//
GLuint loadProgram(const char *vert, const char *pv, const char *frag, const char *fc)
{
  // シェーダのソースファイルを読み込む
  const GLchar *vsrc(readShaderSource(vert));
  const GLchar *fsrc(readShaderSource(frag));

  // プログラムオブジェクトを作成する
  const GLuint program(createProgram(vsrc, pv, fsrc, fc));

  // 読み込みに使ったメモリを解放する
  delete vsrc;
  delete fsrc;

  // 作成したプログラムオブジェクトを返す
  return program;
}
