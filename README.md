# CMakeLists.txt generator

## 環境
- macOS High Sierra
- GCC9.1.0
- VSCode(C/C++1.1.3, CMake0.0.17, CMake tools1.5.3)

## 注意
- サブサブディレクトリに非対応
project/src/subdir/subsubdirなどできない

## 機能
- 複数ソースファイル対応
- 複数サブディレクトリ対応 project/src/subdir

## ビルド
1. vscode開く
2. Add Folder to Workspaceでcmakelists-generatorを追加
3. command+Shift+PでCommand Palette開く
4. cmake build実行
5. 実行ファイル生成されるcmakelists-generator/build/src/cmakelists-generator

## CMakeLists.txt自動生成
### 前提条件
- project/srcディレクトリがある
- project/src/main.cppがある
### 使い方
0. シンボリックリンクを貼ったほうが良さそう
1. $ ./cmakelists-generator {project_path}  
```
ex) $ ./cmakelists-generator ../../../project
```  
2. project内の各サブディレクトリにCMakeLists.txtが生成される
3. projectをvscodeでビルド
4. 実行
```
ex) $ cd project/build/src
ex) $ ./project
```
