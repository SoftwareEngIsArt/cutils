#pragma once

/* IO utility functions */

#include "includes.h"

/*
 * Promts user to enter a key and loops untill the key is pressed.
 * In case passed an invalid character any character is used. 
 */
void wait_key_promt(char);