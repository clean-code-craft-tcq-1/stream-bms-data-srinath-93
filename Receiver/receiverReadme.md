inputProcessor.py - Reads input generated by the sender on the console and performs formatting necessary operations.

simpleMovingAverage.py- performs  the min,max, sma of last 5 values on formatted data.

receiverTest.py-Performs the testing of receiver main functionality.

receiver-testworkflow.yml - Test the receiver .

pipe-execution.yml - Testing the receiver by piping it with the O/P generated by a 'sender' 

#**Sender Output Format: generates the file data to console.**


![image](https://user-images.githubusercontent.com/39860323/122756633-4b0cac00-d2b4-11eb-902b-8985fb2152b0.png)

#**How sender O/P is read by receiver**

![image](https://user-images.githubusercontent.com/39860323/122757626-75129e00-d2b5-11eb-885c-8882bb266438.png)
 
Receiver is reading the senders output by using sys.stdin command which reads the data from console.
It performs the necessary operations in formatInputStream required to proceed further.

#**Sender Ouput Piped to Receiver Input(and necessary processing done)**

![image](https://user-images.githubusercontent.com/39860323/122757705-92e00300-d2b5-11eb-94c9-9188a258cec2.png)

Sender executable is stored in '/Sender’ after the sender is executed successfully.
Even if the additional texts sends along with parameters the receiver code ignores the other texts and looks for parameters and process the parameters.

![image](https://user-images.githubusercontent.com/39860323/122757756-a2f7e280-d2b5-11eb-970b-c25bad0bb615.png)
![image](https://user-images.githubusercontent.com/39860323/122757793-ac814a80-d2b5-11eb-916c-8a26c283259a.png)
![image](https://user-images.githubusercontent.com/39860323/122757824-b4d98580-d2b5-11eb-947e-44e8c79dbbb8.png)
