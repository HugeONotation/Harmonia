# Literals

## Escape Sequences
When used within a codepoint literal or string literal, the following 
substitutions shall apply.

`\0` -> `U+0000` Null
`\n` -> `U+000A` Line feed
`\r` -> `U+000D` Carriage return
`\t` -> `U+0009` Character tabulation
`\v` -> `U+000B` Line tabulation
`\'` -> `U+0027` Apostrophe
`\"` -> `U+0022` Quotation mark
`\\` -> `U+005c` Backslash

When used within a string literal, the following substitutions shall apply.

`\U+{xxxxx}`

## Numeric Literals
A numeric literal shall begin with a decimal digit codepoint. Subsequent 
codepoints may be any English alphabet codepoint or decimal digit codepoint. 

A numeric literal may be suffixed by a colon codepoint, followed by a type 
expression.

## Codepoint Literals
A codepoint literal shall be identified by a pair of enclosing single quotes.

The contents of a codepoint literal may be any singular UTF-8 codepoint.

The contents of a codepoint literal may be `U+` followed by up to six 
hexadecimal digit codepoints.

## String Literals
A string literal shall be identified by a pair of enclosing double quotes. 

The contents of a string literal may be any set of bytes which are valid and 
complete UTF-8 representations of Unicode codepoints, recognized or otherwise.

All codepoints which do not comprise an escape sequence shall be copied 
byte-wise into the storage allocated for containing the string literal's 
contents.
