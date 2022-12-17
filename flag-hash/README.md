# flag-hash
## Description
> PHP is safe i've heard...

*Author: [@sichej](https://github.com/sichej)*
## Solution
In order to get the flag, we must enter something whose md5sum computes to the same of the flag 
(in cryptography this is called a [hash collision](https://en.wikipedia.org/wiki/Hash_collision)).

Since the check is performed with a [loose comparison](https://www.php.net/manual/en/types.comparisons.php)
(i.e. two equals instead of three) we can abuse 
[PHP's type juggling](https://www.php.net/manual/en/language.types.type-juggling.php) to trick the program 
to give us the flag, without performing a time-consuming collision attack (which is kinda feasible with md5).

If we look at the md5 provided by the website, we can observe that it looks like this: it starts with `0e`
and is followed by a bunch of numbers.

If we provide another input whose md5 follows the same properties, the PHP's type juggling system will
mistake the flag's md5 (`0e367389443115895145880699408670`) and our input's md5 (`0esomething`) for numbers
written in exponential form (0 to the power of 367389... and 0 to the power of something). 

Since 0 to the power of `n` (when `n` > 0) always returns 0, each side of the comparison 
computes to 0 and the check will pass.

An input value that follows these properties can be computer with a bruteforce or can be found 
[here](https://security.stackexchange.com/questions/261975/do-we-know-a-md5-collision-exploiting-php-loose-type-comparision-0123e2-123e).

```
md5(flag) = 0e367389443115895145880699408670
md5("QLTHNDT") = 0e405967825401955372549139051580
0e367389443115895145880699408670 => 0^367389443115895145880699408670 == 0
0e405967825401955372549139051580 => 0^405967825401955372549139051580 == 0
0==0 returns true
```
## Flag
`havceCTF{never_trust_PHP_WplAhwAxDnr}`
