/**
 * \file urlblacklistfilter.h
 * \brief URL blacklist detector for Nemea -- header file
 * \author Roman Vrana, xvrana20@stud.fit.vutbr.cz
 * \author Erik Sabik, xsabik02@stud.fit.vutbr.cz
 * \date 2013
 * \date 2014
 * \date 2016
 */

/*
 * Copyright (C) 2013,2014,2016 CESNET
 *
 * LICENSE TERMS
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is'', and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef URLBLACKLISTFILTER_H
#define URLBLACKLISTFILTER_H

#include <map>
#include <string>
#include <vector>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <unirec/unirec.h>
#include <nemea-common.h>

/**
 * Constant returned if everything is ok.
 */
#define ALL_OK 0

/**
 * Static mode ID.
 */
#define BL_STATIC_MODE 1

/**
 * Dynamic mode ID. 
 */
#define BL_DYNAMIC_MODE 2

/**
 * Initial size of the blacklist.
 */
#define BLACKLIST_DEF_SIZE 50000

/**
 * Consatnt returned by loading function if directory cannot be accessed
 */
#define BLIST_LOAD_ERROR -1

/**
 * Constant retuned by checking function if URL is prsent on blacklist.
 */
#define BLACKLISTED 1

/**
 * Constant retuned by checking function if URL is clear.
 */
#define URL_CLEAR 0


#define BL_NAME_MAX_LENGTH 100
unsigned int TIMEOUT_ACTIVE = 300;
unsigned int TIMEOUT_INACTIVE = 30;


const char *URL_REGEX =
   // Protocol
   //"((https?)://)?"
   "(" // Host part
    // IP
   "([1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])"
   "(\\.(1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}"
   "(\\.([1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))"
   "|" // OR
    // Domain name
   "(([a-z0-9]-*)*[a-z0-9]+)"
   "(\\.([a-z0-9]-*)*[a-z0-9]+)*"
   "(\\.([a-z]{2,}))"
   ")"
   // URL part
   "(/|\\w|\\.|\\?|_|=|;|&|-)*"
   // Strip last slash and/or last comma
   "[^/,]"
   ;


/*
   //"^"
   // protocol identifier
   "(?:(?:https?|ftp)://)"
   // user:pass authentication
   "(?:\\S+(?::\\S*)?@)?" 
   "(?:"
   // IP address exclusion
   // private & local networks
   "(?!(?:10|127)(?:\\.\\d{1,3}){3})"
   "(?!(?:169\\.254|192\\.168)(?:\\.\\d{1,3}){2})"
   "(?!172\\.(?:1[6-9]|2\\d|3[0-1])(?:\\.\\d{1,3}){2})"
   // IP address dotted notation octets
   // excludes loopback network 0.0.0.0
   // excludes reserved space >= 224.0.0.0
   // excludes network & broacast addresses
   // (first & last IP address of each class)
   "(?:[1-9]\\d?|1\\d\\d|2[01]\\d|22[0-3])"
   "(?:\\.(?:1?\\d{1,2}|2[0-4]\\d|25[0-5])){2}"
   "(?:\\.(?:[1-9]\\d?|1\\d\\d|2[0-4]\\d|25[0-4]))"
   "|"
   // host name
   "(?:(?:[a-z\\u00a1-\\uffff0-9]-*)*[a-z\\u00a1-\\uffff0-9]+)"
   // domain name
   "(?:\\.(?:[a-z\\u00a1-\\uffff0-9]-*)*[a-z\\u00a1-\\uffff0-9]+)*"
   // TLD identifier
   "(?:\\.(?:[a-z\\u00a1-\\uffff]{2,}))"
   ")"
   // port number
   "(?::\\d{2,5})?"
   // resource path
   "(?:/\\S*)?"
   //"$"
   ;
*/

/*
 * Map for URL blacklist
 */
typedef std::map<std::string, uint64_t> blacklist_map_t;



/**
 * Structure of item used in update operations.
 */
typedef struct {
    /*@{*/
    std::string url; /**< URL to update */
    uint64_t bl; /**< Source blacklist of the URL */
    /*@}*/
} url_blist_t;


/**
 * Structure containing information used for configurating
 * blacklist downloader.
 */
typedef struct __attribute__ ((__packed__)) {
    char file[256];
    uint32_t delay;
    char update_mode[16];
    uint32_t line_max_len;
    uint32_t element_max_len;
    uint32_t element_max_cnt;
    char *blacklist_arr;
} downloader_config_struct_t;


typedef std::vector<url_blist_t> black_list_t;

/*
 * Function for loading update files.
 */
int load_update(black_list_t &add_upd, black_list_t &rm_upd, std::string &file);

/*
 * Function for checking records.
 */
int check_blacklist(cc_hash_table_t& blacklist, ur_template_t* in, ur_template_t* out, const void* record, void* detect);

#ifdef __cplusplus
}
#endif

#endif /* URLBLACKLISTFILTER_H */
