This C program simulates a Customer Service Desk System that allows customers and employees to manage complaints through a Deque (Double-Ended Queue). The program is designed for customer complaints to be added, viewed, and processed. Key features include:

User Management:

Users can sign up as employees or customers, with unique IDs generated automatically (employee IDs prefixed with "EMP" and customer IDs starting from 1000).
Login functionality differentiates between employees and customers, allowing access to appropriate features based on user type.
Complaint Management:

Deque Structure: Complaints are managed as a deque, allowing additions to the front (for product complaints) or the rear (for service complaints).
Display and Process Complaints: Employees can view and process complaints from both ends (front or rear) based on urgency.
Customer and Employee Roles:

Customers can add product or service-related complaints and view their complaint history.
Employees can process complaints, search for complaints by customer ID, and logout to secure the system.
Data Structures Used:

Linked Lists for user management.
Deque for complaint management, allowing flexible handling of customer complaints.
This program is intended for scenarios where a help desk system is required to prioritize complaint handling dynamically. The use of linked lists and dynamic memory allocation makes it scalable without predefined limits on the number of users or complaints.
