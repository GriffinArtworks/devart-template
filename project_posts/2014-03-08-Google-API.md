### Google Predict - first steps

Google Predict is a kind of blackbox service which can be used to predict an outcome based on a training set of data. It can be used in 2 ways: regression, where the output is a number, or classification, where the output from a group of choices (e.g. Happy or Sad);

**Usage**

In our case, it's easier to deal with identifying binary user choices.  When presented with 2 choices it's far easier for someone just to pick the one they like compared to giving a quantity score to each.  The idea is to use a classification of "preferred" or "not preferred", where the system will be able to predict new preferred fractals.

**Implementation so far**

I've chosen PHP to act as the application layer for accessing the Google Predict service from the oF application.  

1. Setup an application owned account: Setup a Service Account so the requesting application is responsible for proving its identity, and the user doesn't need to be involved.

2. Installed [WAMP]( http://www.wampserver.com/en/)
requires openssl, and curl php extensions to be enabled to use Google API.  This is used for testing.


3. Downloaded [Google API for PHP]( https://code.google.com/p/google-api-php-client/) and

4. Created training data csv file to initialise the training data.

5. Make the following functions availiable via php scripts:
  * add new training data (stream)
  * get the predicted output
 
6. Use [ofxHttpUtils](https://github.com/arturoc/ofxHttpUtils) to do the HTTP requests from the app. 



