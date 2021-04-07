# QuizzApp
Implement a multithreading server that supports as many clients. The server coordinates the clients that answer one set of questions in a row, in the order in which they registered. Each customer is asked a question and has a number of seconds to answer the question. The server checks the answer given by the client and if it is correct it will remember the score for that client. The server also synchronizes all clients with each other and gives everyone a time of n seconds to respond. Communication between server and client will be done using sockets. All the logic is done in the server, the client only answers questions. The questions with the answer options are stored in a SQLite database. The server manages the situations in which one of the participants leaves the game so that the game continues without problems.

###Additional activities implemented:
  ● customer registration,\n
  ● uploading questions from the format mentioned above by the server
  ● question addressed to clients in the order of their registration, the client will choose from the options offered in a number of seconds n
  ● leaving a client will cause him to be removed from the question rounds
  ● end of the game when the questions have been completed -> winner announcement to all customers.
