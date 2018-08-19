#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_h3.h"
#include <h3/h3api.h>

PHP_FUNCTION(h3Distance)
{
    zval *origin_resource_zval;
    zval *h3_resource_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "rr", &origin_resource_zval, &h3_resource_zval) == FAILURE) {
        return;
    }

    H3Index *origin = (H3Index *) Z_RES_VAL_P(origin_resource_zval);
    H3Index *h3 = (H3Index *) Z_RES_VAL_P(h3_resource_zval);

    int distance = h3Distance(*origin, *h3);

    RETURN_LONG(distance);
}
