# 2b2t-queue-alerter
This small python script alerts you (with a desktop notification) when the queue is less than 200. It refresh every 2 minutes.

It uses the [2b2t.io](https://2b2t.io) API to get the number of players in the queue.

# Installation
You need to have python 2.7 and pip.

Do:

```pip install requests```

```pip install plyer```

and now you are ready to launch the script with python.

## The C version
You need to install the libcurl developpement version on your computer. Unfortunately, notifications only works on linux, ATM.
The code isn't optimized, juste made it for the joke.

**Compilation**:

```gcc -o main main.c -lcurl```

**Running the program:**

```./main```
