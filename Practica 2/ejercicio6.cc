/*
[cursoredes@localhost Documents]$ touch hola
[cursoredes@localhost Documents]$ ls -l
total 0
-rw-rw-r-- 1 cursoredes cursoredes 0 Dec  9 17:43 hola
[cursoredes@localhost Documents]$ umask g-w,o-rwx
[cursoredes@localhost Documents]$ touch adios
[cursoredes@localhost Documents]$ ls -l
total 0
-rw-r----- 1 cursoredes cursoredes 0 Dec  9 17:44 adios
-rw-rw-r-- 1 cursoredes cursoredes 0 Dec  9 17:43 hola
*/