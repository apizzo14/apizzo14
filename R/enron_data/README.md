## Enron dataset

In this project, I worked with enron directories containing folders for many employees containing sent emails and other information.
I created an Email class that returns the sender and reciever of a certain email from an input txt file containing all contents of the email.
The Employee class member functions return the number of emails an employee sent, the email content of an email specified by index.
I constructed a matrix that specifies the number of emails sent by one employee to another employee across all pairs of 5 employees. Using the package igraph, I converted the matrix into a graph.
