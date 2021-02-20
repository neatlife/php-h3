<?php

// map official examples/compact.c
$input = [
	// All with the same parent index
	stringToH3('0x8a2a1072b587fff'), stringToH3('0x8a2a1072b5b7fff'), stringToH3('0x8a2a1072b597fff'),
	stringToH3('0x8a2a1072b59ffff'), stringToH3('0x8a2a1072b58ffff'), stringToH3('0x8a2a1072b5affff'),
	stringToH3('0x8a2a1072b5a7fff'),
	// These don't have the same parent index as above.
	stringToH3('0x8a2a1070c96ffff'), stringToH3('0x8a2a1072b4b7fff'), stringToH3('0x8a2a1072b4a7fff')];

printf("Starting with %d indexes.\n", count($input));

$outs = h3Compact($input);
// An error case can occur on e.g. duplicate input.
assert(is_array($outs));

printf("Compacted:\n");
foreach ($outs as $out) {
	printf("resource id %d, long represent %s\n", $out, h3ToString($out));
}
printf("Compacted to %d indexes.\n", count($outs));

$uncompactRes = 2;
$outs2 = uncompact($outs, $uncompactRes);
// An error case could happen if the output array is too small, or indexes
// have a higher resolution than uncompactRes.
assert(is_array($outs2));

$uncompactedCount = 0;
printf("Uncompacted:\n");
foreach ($outs as $out) {
	printf("%s\n", h3ToString($out));
}
printf("Uncompacted to %d indexes.\n", count($outs));
