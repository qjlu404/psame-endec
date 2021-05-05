# polygon specific area message encoding
plans for the program:
- - [ ] make some type of user interface.
- - [ ] include a char gen.
- - [ ] properly encode decodeable messages.
- - [ ] make a decoder.
- - [ ] have an inline video stream.

#### plans for the overall structure:  
Encoder - dll

Decoder - dll 

main/ui - exe < encoder & decoder

Character gen - exe

### On Encode:
Encoder encodes the headers then calls the character gen with information like what alert type and stuff.

### On Decode:
Decoder compsares the 3 eas header tones and compares them for error checking and reencodes data and records the message in between the header and EOM. Encoder will replay the audible data as it's being recorded for lower latency.
