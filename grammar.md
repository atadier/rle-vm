identifier = [alphanumeric]
comment = "#" any
mnemonic = identifier
line = (mnemonic " " )? (comment)? "\n"

file = (line)+
