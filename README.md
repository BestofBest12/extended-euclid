# extended-euclid
Implemented extended euclidean algorithm /w openssl/bn.h<br>

Usage: ./xeuclid [num1] [num2]<br>
Example: ./xeuclid 123123123111 1293109238019381121<br>
<br>
<pre>
<code>
/path/to/openssl/extended-euclid $ gcc xeuclid.c -L.. -lcrypto -I../include/crypto -o xeuclid
</code>
</pre>
