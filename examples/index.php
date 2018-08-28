<?php

// map official examples/index.c
$resolution = 10;
$indexed = geoToH3(40.689167, -74.044444, $resolution);
printf("The index resource is: %d\n", $indexed);

// Get the vertices of the H3 index.
$boundaries = h3ToGeoBoundary($indexed);
// Indexes can have different number of vertices under some cases,
// which is why boundary.numVerts is needed.
foreach ($boundaries as $index => $boundary) {
    printf("Boundary vertex #%d: %lf, %lf\n", $index,
           radsToDegs($boundary[0]),
           radsToDegs($boundary[1]));
}

// Get the center coordinates.
$center = h3ToGeo($indexed);
printf("Center coordinates: %lf, %lf\n", radsToDegs($center[0]),
       radsToDegs($center[1]));
