### Contents

- Original "Morris worm" (1988)
- Code Red worm (2001)
- Stuxnet (2005 ~ 2010)
- Heartbleed (2012 ~ 2014)
- More...
  + Most of Chrome/Firefox/Safari exploits
  + Most iOS Jailbreak, Android rooting

---

### The original Morris Worm (1988)

- Exploited a few vulnerabilities to spread
  + Early versions of the finger server (fingerd) used **gets()** to read the argument sent by the client:<br>
    `finger byoungyoung@snu.ac.kr`
  + Worm attacked the fingerd server by spending phony argument:<br>
    `finger "exploit-code padding new-return-address"`
    * Exploit code  : executed a root shell on the victim machine with a direct TCP connection to the attacker.
- Once on a machine, scanned for other machines to attack
  + invaded ~6,000 computers in hours (10% of the Internet)
  + see June 1989 article in Coom. of the ACM

### Stuxnet

1. The malicious computer worm probably entered the computer system - which is normally cut off from the ouside world - at the uranium enrichment facility in Natanz
  via a removable USB mempry stick.
2. The virus is controlled from servers in Denmark and Malaysia with the help of two Internet addresses, both registered to false names. The virus infects some
  100,000 computers around the world.
3. Suxnet spreads through the system until it finds computers running the Slemens control software Step 7, which is responsible for regulating the rotational speed of
  the contrifuges.
4. The computer worm varies the rotational speed of the centrifuges. this can destry the contrifuges and impair uranium enrichment.
5. The stuxnet attacks start in June 2009. From this point on, the number of inoperative centrifuges increases sharply.

### Heartbleed

- Request computer to give the data with such length.
- Even though the length specified is longer than the actual data length, still computer returns the whole length of data, which might be contain critical datas.

---

> All of these attacks are based on Buffer Over Flow!
