PROGRAM
ID Programa3
;
VAR
ID Num1
,
ID Num2
,
ID Sum
:
ID Integer
;
BEGIN
WRITE
(
STRING 'Digite Num1:'
)
;
ID Readln
(
ID Num1
)
;
ID Num2
:=
NUM 123
*
NUM_FLOAT 1.23E+4
-
NUM_FLOAT .25
*
NUM_FLOAT 40.
+
NUM 555
;
ID Sum
:=
ID Num1
+
ID Num2
*
NUM 1
;
ID Writeln
(
ID Sum
)
;
ID Readln
END
.
