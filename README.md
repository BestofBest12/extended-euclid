# extended-euclid
Implemented extended euclidean algorithm /w openssl/bn.h<br>
<pre>
<code>
/path/to/openssl/extended-euclid $ gcc xeuclid.c -L.. -lcrypto -I../include/crypto -o xeuclid
</code>
</pre>
<pre>
<code>
Usage: ./xeuclid [num1] [num2]
Example: ./xeuclid 123123123111 1293109238019381121
</code>
</pre>
