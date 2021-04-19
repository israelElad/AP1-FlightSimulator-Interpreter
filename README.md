# AP1-FlightSimulator-Interpreter
Second year first semester- "Advanced programming 1" course, first milestone- Interpreter: C++

<p float="left">
  <img src="https://user-images.githubusercontent.com/45766976/115225247-894fe880-a116-11eb-9206-1a0b2e2ecdd2.png" width="300">
  <img src="https://user-images.githubusercontent.com/45766976/115225239-87862500-a116-11eb-9ed2-2504696813c3.png" width="300">
  <img src="https://user-images.githubusercontent.com/45766976/115225227-83f29e00-a116-11eb-826a-3b7be488072f.png" width="300">
</p>

Implementation of an interpreter for the FlightGear simulator (for more details about the FlightGear simulator click [here](https://www.flightgear.org/about/)).<br />
The program gets a script file that contains various commands. By using a [lexer](https://en.wikipedia.org/wiki/Lexical_analysis), the program splits the script into strings that can be interpreted, and then interprets them by using an [interpreter](https://en.wikipedia.org/wiki/Interpreter_(computing)), with the help of the [Command design pattern](https://en.wikipedia.org/wiki/Command_pattern).<br />

### The project contains the following elements:<br />

* Use of design patterns (such as Command and Object Adapter patterns) and architecture.<br />
* Communication and Client-Server Architecture.<br />
* Use of data structures and database.<br />
* Data Streaming (files & communication).<br />
* Parallel programming using threads.<br /><br />

### Running the code (in Linux environment):
First, you need to [download](https://www.flightgear.org/download/) the FlightGear simulator.<br />
Add the [generic_small.xml](https://github.com/YamitCohenTsedek/flight-simulator-interpreter/blob/main/generic_small.xml) file to the /data/Protocol directory where you installed the simulator.<br />
Open the FlightGear simulator and add the following settings in the "Settings" tab:<br />
```
--telnet=socket,in,10,127.0.0.1,5402,tcp --httpd=8080
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
```

```--telnet=socket,in,10,127.0.0.1,5402,tcp``` tells the simulator to open in the background a server that any telnet client can connect to it.
The server is established on a socket with the IP 127.0.0.1 (i.e. local host - on the same computer), and the port 5402, and it will read the data at a rate of 10 times per second, over TCP/IP protocol. ```--httpd=8080``` will open a web server on port 8080.<br />  
```--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small``` tells the simulator to connect as a client to the server through a socket with the IP 127.0.0.1 and the port 5400, and it will send data at a rate of 10 times per second by the format of generic_small.xml file. We will need to open our server before opening the simulator, so that it can connect to it as a client.<br />
The simulator will send at a rate of 10 times per second the sampled values, separated by a comma just like in CSV (and in the order defined in generic_small.xml).<br /><br />

To **compile** the code, open a terminal, route to the directory where you downloaded the code and run the following command:
```
g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
To **run** the code, run the following command:
```
./a.out Script.txt 
```
Then, the program will wait for the FlightGear simulator to connect to the data server.<br />

Click on the 'Fly!' button in the FlightGear simulator and wait for the simulator to connect and the GUI to load.<br />
When the interpreter will start to interpret the script, the plane will take off and fly.
