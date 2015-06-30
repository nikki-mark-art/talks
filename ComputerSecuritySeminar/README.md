# Computer Security seminar

To compile the `vulnerable.c` program:
```
gcc -Wall -ggdb3 -fno-stack-protector vulnerable.c -o vulnerable -Llibc
```

# Files
newgadgets.txt contains the gadgets I collected by parsing libC copy on my Debian *Jessie* x86-64 which means that YMMV.

vulnerable.c is the source code for the vulnerable program I used to exploit in my talk. It's contents is inspired by Hovav Shacham's paper[1] on effective ROP methods. The major difference is that the `strcpy()` was replaced with `read()` in order to be able to sneak in NUL-bytes for the demo purposes.

[1] Shacham, Hovav. "The geometry of innocent flesh on the bone: Return-into-libc without function calls (on the x86)." Proceedings of the 14th ACM conference on Computer and communications security. ACM, 2007.

# License
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
