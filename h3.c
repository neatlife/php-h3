/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_h3.h"
#include <h3/h3api.h>

/* If you declare any globals in php_h3.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(h3)
*/

/* True global resources - no need for thread safety here */
static int le_h3;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("h3.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_h3_globals, h3_globals)
    STD_PHP_INI_ENTRY("h3.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_h3_globals, h3_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
PHP_FUNCTION(degsToRads)
{
    zend_long resolution;
    double lat, lon;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddl", &lat, &lon, &resolution) == FAILURE) {
        return;
    }

    GeoCoord location;
    location.lat = degsToRads(lat);
    location.lon = degsToRads(lon);

    H3Index indexed = geoToH3(&location, resolution);

    zend_resource *index_resource;
    index_resource = zend_register_resource(&indexed, le_h3_index);

    RETURN_RES(index_resource);
}

PHP_FUNCTION(h3ToGeoBoundary)
{
    zval *index_resource_zval = NULL;
    zend_long resolution;
    double lat, lon;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &index_resource_zval) == FAILURE) {
        return;
    }

    H3Index indexed = (H3Index) Z_RES_VAL_P(index_resource_zval);
    // Get the vertices of the H3 index.
    GeoBoundary boundary;
    h3ToGeoBoundary(indexed, &boundary);

    zval boundary_arr;
    ZVAL_NEW_PERSISTENT_ARR(&boundary_arr);
    zend_hash_init(Z_ARRVAL(boundary_arr), boundary.numVerts, NULL, ZVAL_PTR_DTOR, 1);
    // Indexes can have different number of vertices under some cases,
    // which is why boundary.numVerts is needed.
    for (int v = 0; v < boundary.numVerts; v++) {
        zval *lat = NULL, *lon = NULL;
        ZVAL_LONG(lat, boundary.verts[v].lat);
        ZVAL_LONG(lon, boundary.verts[v].lon);

        zval lat_lon_arr;
        ZVAL_NEW_PERSISTENT_ARR(&lat_lon_arr);
        zend_hash_init(Z_ARRVAL(lat_lon_arr), 2, NULL, ZVAL_PTR_DTOR, 1);
        zend_hash_index_add(Z_ARRVAL(lat_lon_arr), v, lat);
        zend_hash_index_add(Z_ARRVAL(lat_lon_arr), v, lon);

        zend_hash_index_add(Z_ARRVAL(boundary_arr), v, &lat_lon_arr);
    }

    RETURN_ARR(Z_ARRVAL(boundary_arr));
}

PHP_FUNCTION(h3ToGeo)
{
    zval *index_resource_zval = NULL;
    zend_long resolution;
    double lat, lon;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &index_resource_zval) == FAILURE) {
        return;
    }

    H3Index indexed = (H3Index) Z_RES_VAL_P(index_resource_zval);

    // Get the center coordinates.
    GeoCoord center;
    h3ToGeo(indexed, &center);

    lat = radsToDegs(center.lat);
    lon = radsToDegs(center.lon);

    zval *lat_zval = NULL, *lon_zval = NULL;
    ZVAL_DOUBLE(lat_zval, radsToDegs(center.lat));
    ZVAL_DOUBLE(lon_zval, radsToDegs(center.lon));

    zval lat_lon_arr;
    ZVAL_NEW_PERSISTENT_ARR(&lat_lon_arr);
    zend_hash_init(Z_ARRVAL(lat_lon_arr), 2, NULL, ZVAL_PTR_DTOR, 1);
    zend_hash_index_add(Z_ARRVAL(lat_lon_arr), 0, lat_zval);
    zend_hash_index_add(Z_ARRVAL(lat_lon_arr), 1, lon_zval);

    RETURN_ARR(Z_ARRVAL(lat_lon_arr));
}
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_h3_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_h3_init_globals(zend_h3_globals *h3_globals)
{
    h3_globals->global_value = 0;
    h3_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(h3)
{
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    le_h3_index = zend_register_list_destructors_ex(NULL, NULL, "h3_index", module_number);
    le_h3_boundary = zend_register_list_destructors_ex(NULL, NULL, "h3_boundary", module_number);
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(h3)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(h3)
{
#if defined(COMPILE_DL_H3) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(h3)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(h3)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "h3 support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/* {{{ h3_functions[]
 *
 * Every user visible function must have an entry in h3_functions[].
 */
const zend_function_entry h3_functions[] = {
    PHP_FE(degsToRads,    NULL)
    PHP_FE(h3ToGeoBoundary,    NULL)
    PHP_FE(h3ToGeo,    NULL)
    PHP_FE_END    /* Must be the last line in h3_functions[] */
};
/* }}} */

/* {{{ h3_module_entry
 */
zend_module_entry h3_module_entry = {
    STANDARD_MODULE_HEADER,
    "h3",
    h3_functions,
    PHP_MINIT(h3),
    PHP_MSHUTDOWN(h3),
    PHP_RINIT(h3),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(h3),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(h3),
    PHP_H3_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_H3
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(h3)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
