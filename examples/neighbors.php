<?php

// map official examples/neighbors.c

$indexed = stringToH3('0x8a2a1072b59ffff');
// Distance away from the origin to find:
$k = 2;

$neighboring = kRing($indexed, $k);

printf("Neighbors:\n");
foreach ($neighboring as $neighbor) {
    // Some indexes may be 0 to indicate fewer than the maximum
    // number of indexes.
    printf("neighbor resource id %d, long represent id %s</br>", $neighbor, h3ToString($neighbor));
}