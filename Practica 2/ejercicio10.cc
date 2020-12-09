/*
1.
[cursoredes@localhost ej10]$ touch link
[cursoredes@localhost ej10]$ ln -s link linklink
[cursoredes@localhost ej10]$ mkdir link2
[cursoredes@localhost ej10]$ ln -s link2 link2link
[cursoredes@localhost ej10]$ ls -li
total 0
 3125634 drwxrwxr-x 2 cursoredes cursoredes 6 Dec  9 19:13 link2
51269358 lrwxrwxrwx 1 cursoredes cursoredes 5 Dec  9 19:13 link2link -> link2
51269356 -rw-rw-r-- 1 cursoredes cursoredes 0 Dec  9 19:12 link
51269357 lrwxrwxrwx 1 cursoredes cursoredes 4 Dec  9 19:13 linklink -> link

Los directorios tiene una d y los enlaces simbolicos una l

2.
[cursoredes@localhost ej10]$ touch rigido
[cursoredes@localhost ej10]$ ln hola rigidorigido
[cursoredes@localhost ej10]$ mkdir rigido2
[cursoredes@localhost ej10]$ ln rigido2 rigido2rigido
ln: ‘rigido2’: hard link not allowed for directory
[cursoredes@localhost ej10]$ ls -li
total 0
18709578 drwxrwxr-x 2 cursoredes cursoredes 6 Dec  9 19:19 rigido2
51269356 -rw-rw-r-- 2 cursoredes cursoredes 0 Dec  9 19:18 rigido
51269356 -rw-rw-r-- 2 cursoredes cursoredes 0 Dec  9 19:18 rigidorigido

[cursoredes@localhost ej10]$ stat rigido
  File: ‘rigido’
  Size: 0         	Blocks: 0          IO Block: 4096   regular empty file
Device: fd00h/64768d	Inode: 51269356    Links: 2
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:18:47.891182717 +0100
Modify: 2020-12-09 19:18:47.891182717 +0100
Change: 2020-12-09 19:18:58.865118080 +0100
 Birth: -

[cursoredes@localhost ej10]$ stat rigidorigido 
  File: ‘rigidorigido’
  Size: 0         	Blocks: 0          IO Block: 4096   regular empty file
Device: fd00h/64768d	Inode: 51269356    Links: 2
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:18:47.891182717 +0100
Modify: 2020-12-09 19:18:47.891182717 +0100
Change: 2020-12-09 19:18:58.865118080 +0100
 Birth: -

Los links son iguales.
3.
[cursoredes@localhost ej10]$ rm rigidorigido
[cursoredes@localhost ej10]$ stat rigido
  File: ‘rigido’
  Size: 0         	Blocks: 0          IO Block: 4096   regular empty file
Device: fd00h/64768d	Inode: 51269356    Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:18:47.891182717 +0100
Modify: 2020-12-09 19:18:47.891182717 +0100
Change: 2020-12-09 19:22:20.023933739 +0100
 Birth: -

El numero de links decrementa en 1 si se borra un enlace rigido.

[cursoredes@localhost ej10]$ stat link
  File: ‘link’
  Size: 0         	Blocks: 0          IO Block: 4096   regular empty file
Device: fd00h/64768d	Inode: 51269356    Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:23:55.584372182 +0100
Modify: 2020-12-09 19:23:55.584372182 +0100
Change: 2020-12-09 19:23:55.584372182 +0100
 Birth: -
 
[cursoredes@localhost ej10]$ stat linklink
  File: ‘linklink’ -> ‘link’
  Size: 4         	Blocks: 0          IO Block: 4096   symbolic link
Device: fd00h/64768d	Inode: 51269357    Links: 1
Access: (0777/lrwxrwxrwx)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:24:02.438331905 +0100
Modify: 2020-12-09 19:24:02.438331905 +0100
Change: 2020-12-09 19:24:02.438331905 +0100
 Birth: -

[cursoredes@localhost ej10]$ rm link
[cursoredes@localhost ej10]$ stat linklink
  File: ‘linklink’ -> ‘link’
  Size: 4         	Blocks: 0          IO Block: 4096   symbolic link
Device: fd00h/64768d	Inode: 51269357    Links: 1
Access: (0777/lrwxrwxrwx)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2020-12-09 19:24:02.438331905 +0100
Modify: 2020-12-09 19:24:02.438331905 +0100
Change: 2020-12-09 19:24:02.438331905 +0100
 Birth: -

Si se borra un enlace simbolico, el enlace simbolico deja de apuntar al archivo.
Si se borra el fichero original, el enlace simbolico seguira apuntando al fichero original hasta que se cree de nuevo o se borre el enlace simbolico. 
Los links no se decrementan en ninguno de los dos casos.
*/