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

decoder calls a function in encoder and calls a function to record the message in between the headers. when decoded message, encoder gets the decoded msgs and compares them for error checking reencodes, records voice/plays recorded msg and then calls the chargen which plays a crawl text and encoded audio.
