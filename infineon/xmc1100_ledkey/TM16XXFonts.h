/*
TM16XXFonts.h - Font definition for TM16XX.

Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


The bits are displayed by mapping bellow
 -- 0 --
|       |
5       1
 -- 6 --
4       2
|       |
 -- 3 --  .7

*/

#ifndef TM16XXFonts_h
#define TM16XXFonts_h

// definition for standard hexadecimal numbers
static const uint8_t NUMBER_FONT[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

// definition for standard hexadecimal numbers
static const uint8_t HEXNUMBER_FONT[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001  // F
};

static const uint8_t MINUS = 0b01000000;

// definition for error
static const uint8_t ERROR_DATA[] = {
  0b01111001, // E
  0b01010000, // r
  0b01010000, // r
  0b01011100, // o
  0b01010000, // r
  0,
  0,
  0
};

// definition for the displayable ASCII chars
static const uint8_t FONT_DEFAULT[] = {
  0b00000000, // [0] (32)  <space>
  0b10000110, // [1] (33)	!
  0b00100010, // [2] (34)	"
  0b01111110, // [3] (35)	#
  0b01101101, // [4] (36)	$
  0b00000000, // [5] (37)	%
  0b00000000, // [6] (38)	&
  0b00000010, // [7] (39)	'
  0b00110000, // [8] (40)	(
  0b00000110, // [9] (41)	)
  0b01100011, // [10] (42)	*
  0b00000000, // [11] (43)	+
  0b00000100, // [12] (44)	,
  0b01000000, // [13] (45)	-
  0b10000000, // [14] (46)	.
  0b01010010, // [15] (47)	/
  0b00111111, // [16] (48)	0
  0b00000110, // [17] (49)	1
  0b01011011, // [18] (50)	2
  0b01001111, // [19] (51)	3
  0b01100110, // [20] (52)	4
  0b01101101, // [21] (53)	5
  0b01111101, // [22] (54)	6
  0b00100111, // [23] (55)	7
  0b01111111, // [24] (56)	8
  0b01101111, // [25] (57)	9
  0b00000000, // [26] (58)	:
  0b00000000, // [27] (59)	;
  0b00000000, // [28] (60)	<
  0b01001000, // [29] (61)	=
  0b00000000, // [30] (62)	>
  0b01010011, // [31] (63)	?
  0b01011111, // [32] (64)	@
  0b01110111, // [33] (65)	A
  0b01111111, // [34] (66)	B
  0b00111001, // [35] (67)	C
  0b00111111, // [36] (68)	D
  0b01111001, // [37] (69)	E
  0b01110001, // [38] (70)	F
  0b00111101, // [39] (71)	G
  0b01110110, // [40] (72)	H
  0b00000110, // [41] (73)	I
  0b00011111, // [42] (74)	J
  0b01101001, // [43] (75)	K
  0b00111000, // [44] (76)	L
  0b00010101, // [45] (77)	M
  0b00110111, // [46] (78)	N
  0b00111111, // [47] (79)	O
  0b01110011, // [48] (80)	P
  0b01100111, // [49] (81)	Q
  0b00110001, // [50] (82)	R
  0b01101101, // [51] (83)	S
  0b01111000, // [52] (84)	T
  0b00111110, // [53] (85)	U
  0b00101010, // [54] (86)	V
  0b00011101, // [55] (87)	W
  0b01110110, // [56] (88)	X
  0b01101110, // [57] (89)	Y
  0b01011011, // [58] (90)	Z
  0b00111001, // [59] (91)	[
  0b01100100, // [60] (92)	\ (this can't be the last char on a line, even in comment or it'll concat)
  0b00001111, // [61] (93)	]
  0b00000000, // [62] (94)	^
  0b00001000, // [63] (95)	_
  0b00100000, // [64] (96)	`
  0b01011111, // [65] (97)	a
  0b01111100, // [66] (98)	b
  0b01011000, // [67] (99)	c
  0b01011110, // [68] (100)	d
  0b01111011, // [69] (101)	e
  0b00110001, // [70] (102)	f
  0b01101111, // [71] (103)	g
  0b01110100, // [72] (104)	h
  0b00000100, // [73] (105)	i
  0b00001110, // [74] (106)	j
  0b01110101, // [75] (107)	k
  0b00110000, // [76] (108)	l
  0b01010101, // [77] (109)	m
  0b01010100, // [78] (110)	n
  0b01011100, // [79] (111)	o
  0b01110011, // [80] (112)	p
  0b01100111, // [81] (113)	q
  0b01010000, // [82] (114)	r
  0b01101101, // [83] (115)	s
  0b01111000, // [84] (116)	t
  0b00011100, // [85] (117)	u
  0b00101010, // [86] (118)	v
  0b00011101, // [87] (119)	w
  0b01110110, // [88] (120)	x
  0b01101110, // [89] (121)	y
  0b01000111, // [90] (122)	z
  0b01000110, // [91] (123)	{
  0b00000110, // [92] (124)	|
  0b01110000, // [93] (125)	}
  0b00000001, // [94] (126)	~
};

#endif
