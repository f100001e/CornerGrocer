Corner Grocer Item Tracking Program

Frank Elliott
CS 210: Project Three
Corner Grocer Item Tracking Program
4/24/26

Program Design
This program utilizes a straightforward object-oriented approach centered around the GroceryTracker class. The GroceryTracker class is designed to manage item data efficiently using a map structure, where each item is stored as a key and its purchase frequency as the corresponding value. The class encapsulates essential operations, including file input/output, calculation of item frequencies, and methods for displaying information to the user. Maps are selected for their efficient O(log n) lookup time and their ability to automatically sort keys, which supports both performance and usability.

Key Functionality
Option 1 – Individual Item Search
With this option, users can enter the name of a specific item to find out how often it appears in the purchase records. The program then displays the total occurrences of the searched item, providing straightforward feedback on individual item popularity.
 
Option 2 – Complete Frequency List
This feature allows users to view a comprehensive, formatted table that lists every item recorded in the purchase data alongside its total frequency. It offers an overview of all items and their purchase counts, making it easy to identify trends and popular products.
 Option 4 
 
– Exit
Selecting this option terminates the program loop, allowing users to exit the application safely.
Backup File Creation
When the program starts, it automatically generates a file named frequency.dat that contains all item-frequency pairs. This file serves as a backup of the frequency data and is created without any need for user action, ensuring data preservation.

Industry Best Practices
The code is thoroughly documented with in-line comments explaining all major functions and logic. Variable names adhere to camelCase conventions (such as itemFrequency and searchItem) for clarity and consistency. To enhance reliability, input validation is implemented to prevent crashes when users provide non-numeric menu entries, and comprehensive file error handling ensures that users are notified if the input file is missing.

