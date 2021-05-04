# polygon specific area message encoding
plans for the program:
- - [ ] make some type of user interface.
- - [ ] include a char gen.
- - [ ] properly encode decodeable messages.
- - [ ] make a decoder.
- - [ ] have an inline video stream.

### plans for the overall structure:  
Encoder - dll

Decoder - dll 

Chargen - dll

main/ui - exe

decoder calls a function in encoder when decoded message, encoder gets the decoded msgs and compares them for error checking reencodes and then calls the chargen
