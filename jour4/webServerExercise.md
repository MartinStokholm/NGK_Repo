# Part 1 ( Web server )

## What the server must be able to do  

Create a web server, that will act as a weather station which contains information about the weather
For this first part the server must simple return a static html page with some hardcoded weatherdata.

The hardcoded data found in the first version of the webserver should be:

| ID	 	  | 1		 |
| Date		  | 20211105 |
| Time	 	  | 12:15	 |
| Place  	  | 		 |
| Name   	  | Aarhus N |
| Lat	 	  | 13.692   |
| Lon	 	  | 19.438	 |
| Temperature | 13.1	 |
| Humidity	  | 70%		 |


The values above are instansiated in the main function before being passed to the serverhandler in
the call to restinio::run(). This way the server will contain data in its weatherDataCollection struct.

## Routing of http method and URL

## Implementing the method  

## Testing the server

In order to test the webserver we will be using the program Postman to simulate the client part,
and send a GET request matching the end point we create in our weatherStation server.

# Part 2 ( Creating a Web API )

## What the API must be able to do

### Create new weatherData
Through the use of the API a user must be able to add new data to the server.

### Fetching weatherData from the server
The the use of the API a user must be able to fetch the three latest weatherData entries from the server.
Furthermore be able to fetch weatherData based on the date. 
Lastly the user should be able to fetch all weatherData entries from the server.

### Updating existing weatherData
The user should be able to update existing weatherData, which will then be stored in the server, so
other clients will be able to see the new data. 

## Adding more routing

## Implementing methods for POST, GET and PUT.

## Testing the API

In order to test the webservers API we will again be using the program Postman to simulate the client part,
and this time send both GET, PUT and POST requests matching the end points we added.

# Part 3 ( Upgrading the connection to webSocket protocol )

## What the webSocket connection should be able to do
Clients should be able to connect and receive live updates every time the server receives new data.
The client will be implemented using HTML, JavaScript (using axios library). 

Furthermore, the webSocket connecetion should be able to handle the all CRUD operations 
(Create, Read, Update and Delete) so the client program can have a table for the data and some 
indication to show what operation has been done. 

### Creating the client with a listener
Client will be in a html file. The client creates an instance of socket and tries to connect to the
servers websocket. There will be an event listener attached to the socket instance, that will on 
succefull connection enable the client and server to start communicating. 

## Adding the webSocket functionality to the server

## Testing the webSocket connectivity and functiionality. 




 
