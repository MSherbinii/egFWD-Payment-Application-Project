# **Payment Gateway**

This project simulates a payment gateway system that processes card transactions. The system is built using C programming language and it consists of different layers to handle different tasks such as card data validation, terminal data validation, account validation and balance checking, and transaction saving and retrieval.

**Features**

- Validation of card holder name, expiration date, and primary account number (PAN).
- Validation of transaction date, amount, and card expiration.
- Validation of account and checking of account balance.
- Saving and retrieval of transactions.
- Decline transactions if card is expired, invalid account, insufficient funds, or amount exceeds the limit.

**How to use**

- Open the project in your preferred C development environment.
- Run the **appStart()** function located in **application.c** file to start the simulation.
- Follow the prompts in the terminal to enter the card holder name, card expiration date, card PAN, transaction date, and transaction amount.
- The system will then check the validity of the entered data and simulate the transaction accordingly.
- If the transaction is approved, the transaction details and the updated account balance will be displayed in the terminal.

**Test functions**

- The project includes test functions for each module to test the functionality of each module separately.
- To use the test functions, uncomment the function call in the **appStart()** function and run the simulation.

**Files**

- **card.h** and **card.c** handle card data validation.
- **terminal.h** and **terminal.c** handle terminal data validation and transaction amount validation.
- **server.h** and **server.c** handle account validation, balance checking and transaction saving.
- **application.h** and **application.c** handle the overall simulation and calls the functions from the other modules.
- **STD\_Types.h** includes custom data types used in the project.

**Note**

This project is for simulation and educational purposes only and should not be used in a production environment.
