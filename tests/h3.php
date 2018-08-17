<?php

$index = geoToH3(40.689167, -74.044444, 10);

var_dump($index);

var_dump(h3GetResolution($index));

var_dump(h3GetBaseCell($index));

var_dump(h3ToString($index, 0));

var_dump($index);

var_dump(h3IsValid($index));

var_dump(h3IsResClassIII($index));

var_dump(h3IsPentagon($index));

var_dump(kRing($index, 5));

var_dump(maxKringSize(5));

var_dump(kRingDistances($index, 5));

echo "hello world\n";
