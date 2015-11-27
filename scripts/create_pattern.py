import sys

# Color dictionary, in gr-g-b format.
# Color ranges from 0x0 - 0x7f. The MSB is always enabled.
color_dict = {
    'x': '0x80, 0x80, 0x80, ',  # Off
    'y': '0xff, 0xc4, 0x80, ',  # Yellow
    'o': '0xfc, 0x8c, 0x80, ',  # Orange
    'b': '0x80, 0x80, 0xff, ',  # Blue
    'w': '0xff, 0xdd, 0xbb, ',  # White
    '\n': '',
    ',': ''
}

# Transforms a simple txt file to a c-readable array.
# Contains colors for PLD8806 RGB LED strip.
result = '{\n'
with open(sys.argv[1], 'r') as pattern:
    for line in pattern:
        result += '\t{ '
        for char in line:
            result += color_dict[char]
        result = result[:-2]+ ' } ,\n'
    result = result[:-3] + '\n};'

print(result)
