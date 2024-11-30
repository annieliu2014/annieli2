# Riddle Me This 2

- Namespace:
- Type: remote-make
- Category: Cryptography
- Points: 40
- MaxUsers: 0

## Description

Okay, maybe that last encryption was a bit weak. But this time, I'm not
telling you how long the key is, only that it's less than 16 bytes. Now the
cipher's unbreakable! But if you do manage to figure out the key, I'll let you
know what the flag is.

## Details
You can download the source code {{url_for('Vigenere.c', 'here')}} and the
compiled program {{url_for('Vigenere', 'here')}}.

You can connect to the problem at `telnet {{server}} {{port}}` or `nc {{server}} {{port}}`.

## Hints
- There are [multiple ways](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Cryptanalysis)
to determine the length of a Vigenère key.

- [This link](https://github.com/piersy/ascii-char-frequency-english) provides
you with the frequency of ASCII characters, which might be useful for the
Friedman test. But before you try that, you might want to take a closer look at
the ciphertext to see if you can find any patterns.

- With the exception of newlines, the plaintext consists of printable ASCII
characters. 

## Solution Overview

There are many possible approaches to figuring out the length of the cipher key.
The most straightforward way is to use brute force and try decrypting the
ciphertext with key lengths of 2, 3, 4, and so on. 

I deliberately chose a plaintext with repeating phrases and a key length that
ensured repeated sequences showed up in ciphertext, giving the competitor a
chance to solve the problem without having to resort to Friedman's test. If
they're observant, they might notice a sequence that repeats every 24 bytes and
realize that the key length is a multiple of 24.

I'll admit that I myself haven't tried Friedman's test for this particular
ciphertext due to time constraints, and the nature of the plaintext might skew
the distribution of ASCII characters, but it might provide insight into the key
length.

Once the key length is known, the process is similar to that of the first Riddle
Me This (and will be slightly easier, due to the longer ciphertext).

## Attributes

- author: Annie Liu
