#NeptunJS

Project website: [http://neptunjs.de](http://neptunjs.de)<br>
Code repository: [https://github.com/MoritzWillig/neptunjs](https://github.com/MoritzWillig/neptunjs)<br>
Author: Moritz Willig [http://rise-of-light.de](http://rise-of-light.de)<br>
#### Developement stopped!
Due to the high rate of v8 releases i have stopped working on this project. Other JS implementations using v8 provide a much larger module library (but up to this point in time do not allow code security features like this implementation) and are supported by an constantly active community. However the current code state is compilable and can be used to run code safely. The current code structure needs an bigger update and has to be adapted to run with a current v8 release. If you are interested in furter developement of this project you can contact me at the adresses named above.


<br><br>
NeptunJS is a server-side JavaScript content processor, to provide dynamically generated data resources. NeptunJS is based on the V8 engine with interfaces for file and database access.

## Security system
All addins provide an access-token based security model for any reading, writing or execution of external resources. This allows your script to downgrade rights and restrict accessible paths for any permission object and pass these to untrustworthy or even unknown code without any security risks.

## Server-side use
NeptunJS is designed to start from the console and also includes an CGI mode (pass the `-cgi`-parameter to NeptunJS at startup) for an direct integration into running web-servers.

### tag-mode ( `<?js ... ?>` )
By default all code-files are interpreted as JavaScript code. For special purposes, like text files or web pages with small amounts of code, this behaviour can be turned off by passing `-t` to NeptunJS. By turning on tag-mode neptunjs echos any text and executes only code enclosed in <?js-taggs.

## Build
The repository contains an compiled binary for linux 64bit under /bin/. Furthermore an compiled version of the [v8 engine](http://code.google.com/p/v8/) and the [MySqlConnector for C++](http://dev.mysql.com/downloads/connector/cpp/) are required. Private copies of both repositories are linked as submodules under /libs/ and have to be compiled before compiling NeptunJS itself. Currently the project structure is automatically generated and managed by [Netbeans for C++](https://netbeans.org/features/cpp/). Therefore I would ask you to use Netbeans when committing new code since it generates makefiles automatically, which leads to an more uniform code structure.

## Copyright

The NeptunJS project is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License](http://creativecommons.org/licenses/by-nc-sa/3.0/)

### Author & contact
If you have any suggestions for improvement or found a bug you can contact me under moritz.willig (at) gmail.com.
