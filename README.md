# Baby RevEng crackme project
I made this "Baby crackme" project to introduce myself to reverse engineering concepts, IDA, and assembly code. I first wrote a tiny password program `crackme.cpp` that prompts the user to enter a password in their terminal. If they enter 'password' then it prints 'Access granted!' otherwise 'Access denied!'. 

Then I opened the executable for that program in IDA and found this block of assembly instructions:

```
.text:000000014000BF10                 sub     rsp, 88h
.text:000000014000BF17                 mov     [rsp+88h+var_4], 0
.text:000000014000BF22                 lea     rcx, ?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A ; struct basic_ostream<char,std::char_traits<char> > *
.text:000000014000BF29                 lea     rdx, aEnterPassword ; "Enter password: "
.text:000000014000BF30                 call    j_??$?6U?$char_traits@D@std@@@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@0@AEAV10@PEBD@Z ; std::operator<<<std::char_traits<char>>(std::ostream &,char const *)
.text:000000014000BF35                 lea     rdx, [rsp+88h+Str1] ; __int64
.text:000000014000BF3A                 lea     rcx, ?cin@std@@3V?$basic_istream@DU?$char_traits@D@std@@@1@A ; char *
.text:000000014000BF41                 mov     r8d, 64h ; 'd'
.text:000000014000BF47                 call    j_?getline@?$basic_istream@DU?$char_traits@D@std@@@std@@QEAAAEAV12@PEAD_J@Z ; std::istream::getline(char *,__int64)
.text:000000014000BF4C                 lea     rcx, [rsp+88h+Str1] ; Str1
.text:000000014000BF51                 lea     rdx, Str2       ; "password"
.text:000000014000BF58                 call    j_strcmp
.text:000000014000BF5D                 cmp     eax, 0
.text:000000014000BF60                 jnz     short loc_14000BF77
```

This assembly prompts the user for input and compares the input to Str2 (Ida thinks this is "password" I believe due to the symbolic info in the .pdb file). If the compare is not zero, the program short jumps to loc_14000BF77, to the branch where the program will continue and eventually print "Access granted!". If it is zero, it will continue without jumping to the "wrong password" branch where it will eventually print "Access denied!".

To reverse this, I simply changed the code from jnz (0x1575) to jz (0x1574) to reverse the control flow. You can see that if you run `crackme.exe` and enter the correct password (password) it will print "Access denied!" which is opposite of the original logic (saved in `crackme.bak.exe`).


This was a fun project and took me down a lot of deep dives regarding op codes, registers, and the fundamentals of how a computer works!