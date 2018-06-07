@echo off
rem 汎用コンパイルコマンド　複数のソースファイルからMOTファイルを作り，
rem マイクロコンピュータに転送します
rem H8用日立評価版コンパイラver2のセットに対応しています。
rem MOTファイルの転送には，h8w.exe（yamasan氏）を使います。
rem
rem Cのソースファイル(.c)，asmソースファイル(.src)，objファイル(.obj)
rem およびlibファイル(.lib)を個数無関係にドラッグ＆ドロップできます。
rem 
rem 選択されているファイルのうちドロップされたファイル（コマンドライン
rem では先頭のファイル）でフラッシュメモリ書き込み形式ファイル（.mot）
rem の名前が決まります。
rem もしMOTファイルをこのcmdにドラッグ＆ドロップするとすぐフラッシュメ
rem モリ書き込みが始まる。
rem 別のcmdファイルから，このcmdをファイルリスト付で呼び出すと便利です。
rem 例　h8_3048fone.cmd aaa.c bbb.c ccc.c ddd.src eee.src fff.obj ggg.lib

if %1 NEQ MAKEOBJ goto PP3
if exist %~n2.c if exist %~n2.src del %~n2.src
if not exist %~n2.src goto PP1
if exist %~n2.obj del %~n2.obj
goto PP2
:PP1
if not exist %~n2.c goto :EOF
if exist %~n2.obj del %~n2.obj
find "#pragma asm" %~n2.c >nul
if errorlevel 1 goto NOASMCCODE
echo on
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE %~n2.c
@echo off
if not exist %~n2.src goto COMPILE_ERROR
:PP2
echo on
asm38 %~n2.src
@echo off
if not exist %~n2.obj goto ASM_ERROR
del %~n2.lst
if exist %~n2.c del %~n2.src
goto :EOF
:NOASMCCODE
echo on
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS %~n2.c
@echo off
if not exist %~n2.obj goto COMPILE_ERROR
del %~n2.lst
goto :EOF
:PP3

if %1 NEQ MAKELLIST goto PP4
if exist %~n2.obj set inputs=%inputs% %~n2
goto :EOF
:PP4

if %1 NEQ MAKELIBLIST goto PP5
if exist %~n2.lib set liblist=%liblist% %~n2%~x2
goto :EOF
:PP5

if %1 NEQ CLEAROBJ goto PP6
if exist %~n2.c if exist %~n2.obj del %~n2.obj
if exist %~n2.src if exist %~n2.obj del %~n2.obj
goto :EOF
:PP6

echo Compile, link and convert command for H8 C-programing with V2 ver2.00
echo Copyright(c) 24Nov2011 T.kosaka CS TNCT
echo Copyright(c) 28Jun2002 T.kosaka CS TNCT

rem *************** カスタマイズ領域 begin *******************
rem ★コンパイル作業に必要なパスの追加を行います。
 set mypath=%HOMEDRIVE%\Program Files\h8v2\bin
rem ★スタートアップルーチンを記述します。
 set startuproutine=%HOMEDRIVE%\Progra~1\h8v2\lib\start3048.obj
rem ★H8のライブラリを指定します。
 set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib
rem ★リンカスクリプト.subを指定します。
 set linksub=h8_3048fone.sub
rem ★フラッシュメモリ書き込み直前に書き込みするかどうか問い合わせします
rem YES:問い合わせる　NO:問い合わせない
 set downloadready=NO
rem ★フラッシュメモリ書き込みライタh8w.exeのパスを設定します。
 set h8wpath=%HOMEDRIVE%\Program Files\h8v2\WRITER\H8W
rem ★フラッシュメモリ書き込みライタh8w.exeの書き込みツールを設定します。
 set h8wtool=3048B_F25M_P384.MOT
rem ★フラッシュメモリ書き込みのためのCOMポート番号を設定します
 set ComPortNumber=1
rem ★正常にフラッシュメモリ書き込みが終了した場合はそのまま終了する
rem YES:そのまま終了する　NO:そのまま終了せず停止
 set downloadquit=NO
rem *************** カスタマイズ領域  end  *******************

rem ----------------------------------------------------------------------------
rem カレントドライブ・カレントディレクトリへ移動
%~d1
cd %~p1

rem コンパイラのパスの設定
path=%path%;%mypath%
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem もしMOTファイルがドラッグ＆ドロップされたら，フラッシュメモリ書き込みだけ行なう
if %~x1==.mot goto DOWNLOAD
if %~x1==.MOT goto DOWNLOAD

rem 誤ったファイルがドロップされたか，単なるダブルクリックで起動した場合は何もしない
if exist %~n1.c goto COMPILE
if not exist %~n1.src goto NO_SOURCE_ERROR

:COMPILE
rem ----------------------------------------------------------------------------
rem コンパイル　～.objの作成
for %%p in (%*) do call %~n0%~x0 MAKEOBJ %%p

:LINK
rem リンク　～.absリストの作成
set inputs=
for %%p in (%*) do call %~n0%~x0 MAKELLIST %%p

rem リンク　～.libリストの作成
set liblist=
for %%p in (%*) do call %~n0%~x0 MAKELIBLIST %%p

echo INPUT %startuproutine% %inputs% >tmp8523.sub
echo LIB %h8library% %liblist%>>tmp8523.sub
echo OUTPUT %~n1 >>tmp8523.sub
echo PRINT %~n1 >>tmp8523.sub
type %linksub% >>tmp8523.sub

echo on
lnk -subcommand=tmp8523.sub >q9j2h5c4k6b1.txt
@echo off
for %%p in (%*) do call %0 CLEAROBJ %%p
del tmp8523.sub
type q9j2h5c4k6b1.txt
find "**" q9j2h5c4k6b1.txt >nul
echo;
if errorlevel 1 goto CONVERT
del q9j2h5c4k6b1.txt
del %~n1.abs
goto LINK_ERROR

:CONVERT
del q9j2h5c4k6b1.txt
rem ----------------------------------------------------------------------------
rem Sフォーマットに変換 ～.motの作成
cnvs %~n1.abs
del %~n1.abs
echo;

rem motファイルの転送
if %downloadready%==NO goto DOWNLOAD
echo Please set AKI-H8 ready and hit any key / push 'Ctrl+C' if you want
pause >nul
:DOWNLOAD
echo h8w.exe
echo [AutoPgm] >myAutoPgm.ini
echo AutoStart=1 >>myAutoPgm.ini
echo AutoExit=1 >>myAutoPgm.ini
echo CtrlProgam=%h8wtool% >>myAutoPgm.ini
echo ComPortNo=%ComPortNumber% >>myAutoPgm.ini
echo UserMotPath=%~n1.mot >>myAutoPgm.ini
"%h8wpath%\h8w.exe" -GO .\myAutoPgm.ini
if %ERRORLEVEL%==0 echo succeeded in MOT file writing
if not %ERRORLEVEL%==0 echo failed in writing
del myAutoPgm.ini
rem if exist %~n1.map del %~n1.map
if %downloadquit%==YES exit
goto TERMINAL

:COMPILE_ERROR
echo.
echo *** error *** コンパイルエラーです。
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE %~n2.c >tmptmptmp 2>nul
find "CANNOT OPEN SOURCE FILE" tmptmptmp >nul
if %ERRORLEVEL%==1 goto COMPILE_ERROR1
echo *** error *** ファイル名にアルファベットと数字以外の文字が使われていませんか
echo *** error *** 作業中のフォルダ名にアルファベットと数字以外の文字が
echo *** error *** 使われていませんか
echo.
:COMPILE_ERROR1
del tmptmptmp
goto TERMINAL

:ASM_ERROR
echo *** error *** アセンブルエラーです。
goto TERMINAL

:NO_SOURCE_ERROR
echo *** error *** Ｃのソースファイルが指定されていません。
goto TERMINAL

:LINK_ERROR
echo *** error *** リンクエラーです。
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
