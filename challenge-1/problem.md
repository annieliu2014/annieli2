# Riddle Me This

- Namespace: picoctf/18739f24
- Type: remote-make
- Category: Cryptography
- Points: 20
- MaxUsers: 0

## Description

Ever heard of the [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)?
Most classical encryption schemes are pretty much obsolete, but I still think
the overall idea could still work! This time, instead of limiting ourselves to
the 26 letters of the alphabet, we'll be using ASCII characters instead. I've
encrypted a short riddle for you, and if you can answer it, I'll give you the
flag.

## Details
You can download the source code {{url_for('Vigenere.c', 'here')}} and the
compiled program {{url_for('Vigenere', 'here')}}.

You can connect to the problem at `telnet {{server}} {{port}}` or `nc {{server}} {{port}}`.

## Hints

- Knowing the length of a Vigenère cipher's key makes it much easier to crack.

- With the exception of newlines, the plaintext consists of printable ASCII
characters.

## Solution Overview

Since the key length is known, the competitor should examine every 6th byte of
the ciphertext to look for patterns. Some tricks may include finding repeated
byte sequences and checking whether they match common characters (such as space
or 'e') or using patterns in the plaintext itself (guessing that the last
character in the riddle will be a newline or punctuation mark, assuming the
letters 'yo' will be followed by 'u', etc). For a more advanced strategy,
they can compare the ASCII values of letters with those of other characters to
deduce whether or not an encrypted character corresponds to a letter in
plaintext. There will likely be some degree of trial and error involved, but
it should be easy to tell whether a guess is correct or at least on the right
track.

For my solve script, I can cheat a bit because I know what the plaintext is,
and it doesn't change.

## Attributes

- author: Annie Liu
