# flag-hash
## Description
> PHP is safe I've heard...

## Flag
`havceCTF{never_trust_PHP_WplAhwAxDnr}`

## Soluzione

In questa challenge ci vengono fortini il sito e anche il sorgente, dal sorgnete si capisce che per prendere la flag c'è da inserire un qualocosa che abbia lo stesso md5 della flag in modo da pasare il controllo e farci restituire la flag. Come sappiamo non si puo passare dall'MD5 di un qualcosa a quella cosa ma solo il contrario, quindi bisogna trovare un altra strada per passare il controllo. Il controllo a riga 30 viene fatto con solamente due uguali, gia questo dovrebbe farci capire che c'è qualcosa che non va in quel controllo. In più guardando bene l'hash della flag si può notare che è abbastanza strano come hash, nel senso che comincia con '0e' e poi la sequenza normale di caratteri è formata da soli numeri. Facendo il controllo con solamente due uguali PHP vedendo un qualcosa che comincia con 0e e poi solamente numeri fa la conversione in intero e esegue la potenza, quindi 0 elevato a tutto il resto, che farà sempre uno. Quindi per passare il controllo basta trovare qualcosa che hashato sia uguale a 0e e poi numeri.
[https://security.stackexchange.com/questions/261975/do-we-know-a-md5-collision-exploiting-php-loose-type-comparision-0123e2-123e]() qui si può vedere come ```QLTHNDT``` questa stringa hashata con md5 ritorni ```0e405967825401955372549139051580```, quindi inserendo questa stringa nel campo PHP controllerà che 1 == 1 e quindi il controllo andrà a buon fine e il sito ci restituerà la flag.