#NeptunJS

Project website: [http://neptunjs.de](http://neptunjs.de)<br>
Code repository: [https://github.com/MoritzWillig/neptunjs](https://github.com/MoritzWillig/neptunjs)<br>
Author: Moritz Willig [http://rise-of-light.de](http://rise-of-light.de)

<br><br>
NeptunJS is a server-side JavaScript content processor, to provide dynamically generated data resources. NeptunJS is based on the V8 engine with interfaces for file and database access.

## Security system
All addins provide an access-token based security model for any reading, writing or execution of external resources. This allows your script to downgrade rights and restrict accessible paths for any permission object and pass these to untrustworthy or even unknown code without any security risks.

## Server-side use
NeptunJS is designed to start from the console and also includes an CGI mode (pass the `-cgi`-parameter to NeptunJS at startup) for an direct integration into running web-servers.

### tag-mode ( `<?js ... ?>` )
By default all code-files are interpreted as JavaScript code. For special purposes, like text files or web pages with small amounts of code, this behaviour can be turned off by passing `-t` to NeptunJS. By turning on tag-mode neptunjs echos any text and executes only code enclosed in <?js-taggs.

## Copyright

The NeptunJS project is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-nc-sa/3.0/)

### Author & contact
If you have any suggestions for improvement or found a bug you can contact me under moritz.willig (at) gmail.com.
