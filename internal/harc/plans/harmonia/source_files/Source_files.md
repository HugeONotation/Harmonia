# Harmonia Source Code 

## File Extension
Harmonia source files shall have the `.hm` file extension.

Harmonia interface files shall have the `.hmi` file extension.

## File Encoding
Harmonia source files shall be UTF-8 encoded.

Symbol names shall be subject to NFC normalization.

If a source file is not valid UTF-8, then compilation of the source file shall 
fail.

Harmonia recognizes a subset of the codepoints specified by the Unicode 15.1 
specification. Unrecognized codepoints are permitted within string literals, 
single-line comments, multi-line comments, and documentation strings. 
Outside of these contexts, only recognized codepoints are permitted. A 
source file containing an unrecognized codepoint outside of these conditions 
shall fail compilation.

### Recognized Codepoints
The set of recognized codepoints is as follows:
* codepoints with the `ID_Start` property as defined by the aforementioned 
  Unicode standard, herein referred to as "starting identifier codepoints"
* codepoints with the `ID_Continue` property as defined by the aforementioned 
  Unicode standard, herein referred to as "identifier codepoints"
* codepoints with the `White_Space` property as defined by the aforementioned 
  Unicode standard, herein referred to as "white space"
* `U+0021` herein referred to as "exclamation mark"
* `U+0022` herein referred to as "double quotes"
* `U+0025` herein referred to as "percent sign"
* `U+0026` herein referred to as "ampersand"
* `U+0027` herein referred to as "single quote"
* `U+0028` herein referred to as "left parenthesis"
* `U+0029` herein referred to as "right parenthesis"
* `U+0030` herein referred to as "asterisk"
* `U+0031` herein referred to as "plus sign"
* `U+0032` herein referred to as "comma"
* `U+0033` herein referred to as "minus sign"
* `U+0034` herein referred to as "dot"
* `U+0035` herein referred to as "forward slash"
* `U+003A` herein referred to as "colon"
* `U+003B` herein referred to as "semicolon"
* `U+003C` herein referred to as "left angle bracket"
* `U+003D` herein referred to as "equals sign"
* `U+003E` herein referred to as "right angle bracket"
* `U+005B` herein referred to as "left square bracket"
* `U+005C` herein referred to as "backslash"
* `U+005D` herein referred to as "right square bracket"
* `U+005E` herein referred to as "caret"
* `U+007B` herein referred to as "left curly bracket"
* `U+007C` herein referred to as "pipe"
* `U+007D` herein referred to as "right curly bracket"
* `U+007E` herein referred to as "tilde"
