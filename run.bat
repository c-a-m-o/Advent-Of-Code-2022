@echo off
setlocal enabledelayedexpansion
:: Script to compile and run the solutions for the advent of code.
:: usage : run.bat <language> <day> <part>

SET lang=%1
SET day=%2
SET part=%3

IF "%lang%"=="c++" SET lang=cpp
SET input_path=".\input\day%day%.txt"

IF NOT DEFINED part GOTO not_enough_arguments
IF NOT exist %input_path% GOTO input_not_found


IF "%lang%" == "ruby" (
    SET source_path=".\ruby\day%day%_%part%.rb"
    IF NOT exist !source_path! GOTO source_not_found
    type !input_path! | ruby !source_path!
    exit
)

IF "%lang%" == "prolog" (
    SET source_path=".\prolog\day%day%_%part%.pl"
    IF NOT exist !source_path! GOTO source_not_found
    type !input_path! | swipl -s !source_path!
    exit
)

IF "%lang%" == "cpp" (
    SET source_path=".\cpp\day%day%_%part%.cpp"
    SET out_path=".\cpp\day%day%_%part%.exe"
    :: Only recompile if the source is more recent than the compiled file
    FOR /F %%i IN ('DIR /B /O:D !source_path! !out_path!') DO SET newest=%%i
    IF ".\cpp\!newest!"==!source_path! g++ -std=c++11 -O3 -o !out_path! !source_path!
    Powershell -Command "type !input_path! | !out_path!"
    exit
)

if "%lang%" == "rust" (
    SET source_path=".\rust\day%day%_%part%.rs"
    SET out_path=".\rust\day%day%_%part%.exe"
    FOR /F %%i IN ('DIR /B /O:D !source_path! !out_path!') DO SET newest=%%i
    IF ".\rust\!newest!"==!source_path! (
        rustc -C opt-level=3 -o !out_path! !source_path!
        del .\rust\*.pdb
    )
    Powershell -Command "type !input_path! | !out_path!"
    exit
)



:unknown_lang
echo The language %lang% is not supported.
exit

:input_not_found
echo The input file "input/day%day%.txt" was not found
exit

:: Need to define source path before
:source_not_found
echo The source file %source_path% does not exist
exit

:not_enough_arguments
echo Usage : "run.bat <language> <day> <part>"
exit
