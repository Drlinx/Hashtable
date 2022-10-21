Currently all the implementations are fairly straightforward. I know these can
be hard to read so if you skim over this at least read this: INPUTING THE WRONG
PATHWAY WILL CRASH THE PROGRAM. 

I did have problems converting information from text files as I haven't used
an entire line before rather used white spaces as sperators or character by.
character. As such I had to do a few expiremental attempts with it. Originally
I had a prototype which read the entire file and then after that we would use
the newlines it copied out into seperate items and insert it. However, this 
was very memory intensive and creates problems once we hit a certain character
amount. 
    With the new implementation I have it read line by line with a max of 127 chars
As most code is meant to be within 80 lines for readability. It'd make sense
we'd stay in the same bounds for text files. TLDR: DO NOT HAVE A LINE LONGER THAN
127 CHARACTERS. it'll cause problems with the reading.