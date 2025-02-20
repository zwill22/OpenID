Usage
=====

The C++ API may be used to sign-up, verify and authenticate a user
to the client. Here are some examples of these:

Signing-Up
----------

.. literalinclude:: ../examples/SignUp.cpp
    :language: cpp

Authentication
--------------

.. literalinclude:: ../examples/Authenticate.cpp
    :language: cpp

Delete a user
-------------

.. literalinclude:: ../examples/DeleteUser.cpp
    :language: cpp

Once the Authentication is initialised it can be used to
authenticate the user with AWS Cognito.
