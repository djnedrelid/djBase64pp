## djBase64++

Jeg skrev litt kode for Base64 enkoding og dekoding hvor jeg tok utgangspunkt i [wikipedia artikkelen](https://en.wikipedia.org/wiki/Base64) om Base64.  

Koden er kjapt skrevet og jeg har iblant vurdert å skrive den i mer idiomatisk c++, men har verken hatt tid eller ork siden jeg holdt på med det.  

**Resultat hvor jeg enkoder og dekoder et bilde samt en streng med nordiske tegn, for å illustrere at det handler kun om bits og bytes.**  
```
C:\Users\dj\source\repos\djBase64++\x64\Release>djBase64++.exe  

Enkoder ani.gif og skriver dekodet output til ani_out.gif ...  
Ferdig med filtest, sjekk resultat.  

Skal enkode: æøåÆØÅ er fine norske bokstaver. (64 bytes).  
Enkodet streng: 5gD4AOUAxgDYAMUAIABlAHIAIABmAGkAbgBlACAAbgBvAHIAcwBrAGUAIABiAG8AawBzAHQAYQB2AGUAcgAuAA==  

Dekoder 3x sammensatt streng på ett kall for å teste padding:  
æøåÆØÅ er fine norske bokstaver.æøåÆØÅ er fine norske bokstaver.æøåÆØÅ er fine norske bokstaver. (192 bytes).
```  
   
ani.gif orginalbilde. 2,44 MB (2 563 212 byte)  
![Example UI_1](ani.gif)  

Etter turen i kverna. 2,44 MB (2 563 212 byte).  
![Example UI_1](ani_out.gif)  
