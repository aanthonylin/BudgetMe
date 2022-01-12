Setup Guide for BudgetMe

Along with Qt being installed, the projects also required MySQL server , curl, curlpp and other libraries 
*If you have MySQL installed, skip to 3)*

1) make sure your linux environment is up to date.

	sudo apt update
	sudo apt upgrade
	
2) install the MySQL server on your machine.

	sudo apt install mysql-server
	mysql --version
	
3) start the MySQL server. 
   *you need to do this everytime you shutdown your pc or environment.*
   *closing your WSL terminal does not constitute a shutdown.*
   *but don't worry, the BudgetMe program will remind you to start the server if you forgot.*
   
	sudo service mysql start
	
4) login to your MySQL server as root.

	sudo mysql -u root
	
	(if prompted, enter the password of your linux environment)
	
5) create a user for BudgetMe which will be used when connecting to the database.

	CREATE USER 'budgetme'@'localhost' IDENTIFIED BY 'mysql_BUDGETME_123';
	GRANT ALL ON budgetme_database.* TO 'budgetme'@'localhost';
	FLUSH PRIVILEGES;
	
6) exit MySQL.

	exit
	
7) install the required libraries.

	sudo apt-get install libmysqlclient-dev
	sudo apt install libqt5charts5-dev
	sudo apt-get install libcurlpp-dev
	sudo apt-get install libcurl4-openssl-dev

*Compiling the program*

a) Generate a Makefile, using the following command in the project's root:

	qmake budgetme.pro

b) Run the Makefile:

	make

c) Run the app:																				

	./bin/BudgetMe

When starting the app, you will have to go through a login process. You can log in as a guest, 
which will give you limited access, and your data will not be saved.
Alternately, you can click the Register button and create a new user 
after which you will automatically be logged in. After you've created a user, you can re-log in
with that user credentials and any data previously entered with that account will be loaded in.
Either way of logging in might take some time to switch to the main window, 
so please allow for some time before the next window appears.

When using the app, you must first enter dollar values for estimated spending and annual income
on the StarterBudget screen and finalize it by clicking the "Submit" button. 
For now, there is nothing to let the user know that it succeded, 
so just continue using the app after completing this step.

Once the StarterBudget is generated in the above step, you can select the different icons 
in the toolbar to see all the different features that were implemented.

In order to have PreviewBudget graphs displayed with information, you need to add an item 
to the PreviewBudget section. It's the icon that looks like a coin with a dollar sign on it.

To have transaction information displayed on the section with the receipt icon, 
you need to add multiple transactions in the EnterTransaction section (it has the credit card icon).

If when entering estimated spending in the StarterBudget screen, 
or a transaction in the EnterTransaction screen, a warning will pop up if you exceed your budget.
Go to the SummryOverspending page to access a button to hide it.
(SummaryOverspending page, second icon from the end of the toolbar).
This feature was not present in the user cases, but was added to handle the warning, 
but time ran out before it could be fully implemented.
