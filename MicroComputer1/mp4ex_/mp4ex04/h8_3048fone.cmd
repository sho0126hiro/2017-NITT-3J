@echo off
rem �ėp�R���p�C���R�}���h�@�����̃\�[�X�t�@�C������MOT�t�@�C�������C
rem �}�C�N���R���s���[�^�ɓ]�����܂�
rem H8�p�����]���ŃR���p�C��ver2�̃Z�b�g�ɑΉ����Ă��܂��B
rem MOT�t�@�C���̓]���ɂ́Ch8w.exe�iyamasan���j���g���܂��B
rem
rem C�̃\�[�X�t�@�C��(.c)�Casm�\�[�X�t�@�C��(.src)�Cobj�t�@�C��(.obj)
rem �����lib�t�@�C��(.lib)�������֌W�Ƀh���b�O���h���b�v�ł��܂��B
rem 
rem �I������Ă���t�@�C���̂����h���b�v���ꂽ�t�@�C���i�R�}���h���C��
rem �ł͐擪�̃t�@�C���j�Ńt���b�V���������������݌`���t�@�C���i.mot�j
rem �̖��O�����܂�܂��B
rem ����MOT�t�@�C��������cmd�Ƀh���b�O���h���b�v����Ƃ����t���b�V����
rem �����������݂��n�܂�B
rem �ʂ�cmd�t�@�C������C����cmd���t�@�C�����X�g�t�ŌĂяo���ƕ֗��ł��B
rem ��@h8_3048fone.cmd aaa.c bbb.c ccc.c ddd.src eee.src fff.obj ggg.lib

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

rem *************** �J�X�^�}�C�Y�̈� begin *******************
rem ���R���p�C����ƂɕK�v�ȃp�X�̒ǉ����s���܂��B
 set mypath=%HOMEDRIVE%\Program Files\h8v2\bin
rem ���X�^�[�g�A�b�v���[�`�����L�q���܂��B
 set startuproutine=%HOMEDRIVE%\Progra~1\h8v2\lib\start3048.obj
rem ��H8�̃��C�u�������w�肵�܂��B
 set h8library=%HOMEDRIVE%\Progra~1\h8v2\lib\c38ha.lib
rem �������J�X�N���v�g.sub���w�肵�܂��B
 set linksub=h8_3048fone.sub
rem ���t���b�V���������������ݒ��O�ɏ������݂��邩�ǂ����₢���킹���܂�
rem YES:�₢���킹��@NO:�₢���킹�Ȃ�
 set downloadready=NO
rem ���t���b�V���������������݃��C�^h8w.exe�̃p�X��ݒ肵�܂��B
 set h8wpath=%HOMEDRIVE%\Program Files\h8v2\WRITER\H8W
rem ���t���b�V���������������݃��C�^h8w.exe�̏������݃c�[����ݒ肵�܂��B
 set h8wtool=3048B_F25M_P384.MOT
rem ���t���b�V���������������݂̂��߂�COM�|�[�g�ԍ���ݒ肵�܂�
 set ComPortNumber=1
rem ������Ƀt���b�V���������������݂��I�������ꍇ�͂��̂܂܏I������
rem YES:���̂܂܏I������@NO:���̂܂܏I��������~
 set downloadquit=NO
rem *************** �J�X�^�}�C�Y�̈�  end  *******************

rem ----------------------------------------------------------------------------
rem �J�����g�h���C�u�E�J�����g�f�B���N�g���ֈړ�
%~d1
cd %~p1

rem �R���p�C���̃p�X�̐ݒ�
path=%path%;%mypath%
set h8inc=%HOMEDRIVE%\Progra~1\h8v2\include
set h8lib=%HOMEDRIVE%\Progra~1\h8v2\lib

rem ����MOT�t�@�C�����h���b�O���h���b�v���ꂽ��C�t���b�V���������������݂����s�Ȃ�
if %~x1==.mot goto DOWNLOAD
if %~x1==.MOT goto DOWNLOAD

rem ������t�@�C�����h���b�v���ꂽ���C�P�Ȃ�_�u���N���b�N�ŋN�������ꍇ�͉������Ȃ�
if exist %~n1.c goto COMPILE
if not exist %~n1.src goto NO_SOURCE_ERROR

:COMPILE
rem ----------------------------------------------------------------------------
rem �R���p�C���@�`.obj�̍쐬
for %%p in (%*) do call %~n0%~x0 MAKEOBJ %%p

:LINK
rem �����N�@�`.abs���X�g�̍쐬
set inputs=
for %%p in (%*) do call %~n0%~x0 MAKELLIST %%p

rem �����N�@�`.lib���X�g�̍쐬
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
rem S�t�H�[�}�b�g�ɕϊ� �`.mot�̍쐬
cnvs %~n1.abs
del %~n1.abs
echo;

rem mot�t�@�C���̓]��
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
echo *** error *** �R���p�C���G���[�ł��B
ch38 -cpu=300ha -include=%h8inc% -OUTCODE=SJIS -CODE=ASMCODE %~n2.c >tmptmptmp 2>nul
find "CANNOT OPEN SOURCE FILE" tmptmptmp >nul
if %ERRORLEVEL%==1 goto COMPILE_ERROR1
echo *** error *** �t�@�C�����ɃA���t�@�x�b�g�Ɛ����ȊO�̕������g���Ă��܂���
echo *** error *** ��ƒ��̃t�H���_���ɃA���t�@�x�b�g�Ɛ����ȊO�̕�����
echo *** error *** �g���Ă��܂���
echo.
:COMPILE_ERROR1
del tmptmptmp
goto TERMINAL

:ASM_ERROR
echo *** error *** �A�Z���u���G���[�ł��B
goto TERMINAL

:NO_SOURCE_ERROR
echo *** error *** �b�̃\�[�X�t�@�C�����w�肳��Ă��܂���B
goto TERMINAL

:LINK_ERROR
echo *** error *** �����N�G���[�ł��B
goto TERMINAL

:TERMINAL
echo Pushing any key leads the exit.
pause >nul
exit
