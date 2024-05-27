/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
   This file is part of
   Embedded bootstraps : prbs library
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

/**
 * @file prbs.c
 * @brief PRBS library descriptor
 */


#include "prbs/prbs.h"
#include "prbs/config.h"

#ifndef SWIG
#include <ucdm/descriptor.h>


/** @brief PRBS Library Version Descriptor */
static descriptor_custom_t prbs_descriptor = {NULL, DESCRIPTOR_TAG_LIBVERSION, 
    sizeof(PRBS_VERSION), DESCRIPTOR_ACCTYPE_PTR, {PRBS_VERSION}};


void prbs_install_descriptor(void)
{
    descriptor_install(&prbs_descriptor);
}

#endif
