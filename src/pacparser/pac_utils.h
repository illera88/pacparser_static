// Copyright (C) 2007 Manu Garg.
// Author: Manu Garg <manugarg@gmail.com>
//
// pac_utils.h defines some of the functions used by PAC files. This file is
// packaged with pacparser source code and is required for compiling pacparser.
// Please read README file included with this package for more information
// about pacparser.

// Note: This file is derived from "nsProxyAutoConfig.js" file that comes with
// mozilla source code. Please check out the following for initial developer
// and contributors:
//http://lxr.mozilla.org/seamonkey/source/netwerk/base/src/nsProxyAutoConfig.js
//
// This file is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.

// pacparser is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
// USA

static const char *pacUtils =
"function dnsDomainIs(host, domain) {\n"
"    return (host.length >= domain.length &&\n"
"            host.substring(host.length - domain.length) == domain);\n"
"}\n"

"function dnsDomainLevels(host) {\n"
"    return host.split('.').length-1;\n"
"}\n"

"function convert_addr(ipchars) {\n"
"    var bytes = ipchars.split('.');\n"
"    var result = ((bytes[0] & 0xff) << 24) |\n"
"                 ((bytes[1] & 0xff) << 16) |\n"
"                 ((bytes[2] & 0xff) <<  8) |\n"
"                  (bytes[3] & 0xff);\n"
"    return result;\n"
"}\n"

"function isInNet(ipaddr, pattern, maskstr) {\n"
"    var test = /^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$/(ipaddr);\n"
"    if (test == null) {\n"
"        ipaddr = dnsResolve(ipaddr);\n"
"        if (ipaddr == null)\n"
"            return false;\n"
"    } else if (test[1] > 255 || test[2] > 255 || \n"
"               test[3] > 255 || test[4] > 255) {\n"
"        return false;    // not an IP address\n"
"    }\n"
"    var host = convert_addr(ipaddr);\n"
"    var pat  = convert_addr(pattern);\n"
"    var mask = convert_addr(maskstr);\n"
"    return ((host & mask) == (pat & mask));\n"
"    \n"
"}\n"

"function convert_addr6(ipchars) {\n"
"    ipchars = ipchars.replace(/(^:|:$)/, '');\n"
"    var fields = ipchars.split(':');\n"
"    var diff = 8 - fields.length;\n"
"    for (var i = 0; i < fields.length; i++) {\n"
"        if (fields[i] == '') {\n"
"            fields[i] = '0';\n"
"            // inject 'diff' number of '0' elements here.\n"
"            for (var j = 0; j < diff; j++) {\n"
"                fields.splice(i++, 0, '0');\n"
"            }\n"
"            break;\n"
"        }\n"
"    }\n"
"    var result = [];\n"
"    for (var i = 0; i < fields.length; i++) {\n"
"        result.push(parseInt(fields[i], 16));\n"
"    }\n"
"    return result;\n"
"}\n"

"function isInNetEx6(ipaddr, prefix, prefix_len) {\n"
"    if (prefix_len > 128) {\n"
"        return false;\n"
"    }\n"
"    prefix = convert_addr6(prefix);\n"
"    ip = convert_addr6(ipaddr);\n"
"    // Prefix match strategy:\n"
"    //   Compare only prefix length bits between 'ipaddr' and 'prefix'\n"
"    //   Match in the batches of 16-bit fields \n"
"    prefix_rem = prefix_len % 16;\n"
"    prefix_nfields = (prefix_len - prefix_rem) / 16;\n"
"\n"
"    for (var i = 0; i < prefix_nfields; i++) {\n"
"        if (ip[i] != prefix[i]) {\n"
"            return false;\n"
"        }\n"
"    }\n"
"    if (prefix_rem > 0) {\n"
"        // Compare remaining bits\n"
"        prefix_bits = prefix[prefix_nfields] >> (16 - prefix_rem);\n"
"        ip_bits = ip[prefix_nfields] >> (16 - prefix_rem);\n"
"        if (ip_bits != prefix_bits) {\n"
"            return false;\n"
"        }\n"
"    }\n"
"    return true;\n"
"}\n"

"function isInNetEx4(ipaddr, prefix, prefix_len) {\n"
"    if (prefix_len > 32) {\n"
"        return false;\n"
"    }\n"
"    var netmask = [];\n"
"    for (var i = 1; i < 5; i++) {\n"
"        var shift_len = 8 * i - prefix_len;\n"
"        if (shift_len <= 0) {\n"
"            netmask.push(255)\n"
"        } else {\n"
"            netmask.push((0xff >> shift_len) << shift_len);\n"
"        }\n"
"    }\n"
"    return isInNet(ipaddr, prefix, netmask.join('.'));\n"
"}\n"

"function isInNetEx(ipaddr, prefix) {\n"
"    prefix_a = prefix.split('/');\n"
"    if (prefix_a.length != 2) {\n"
"        return false;\n"
"    }\n"
"    var test = /^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$/.test(ipaddr);\n"
"    if (!test) {\n"
"        return isInNetEx6(ipaddr, prefix_a[0], prefix_a[1]);\n"
"    } else {\n"
"        return isInNetEx4(ipaddr, prefix_a[0], prefix_a[1]);\n"
"    }\n"
"}\n"

"function isPlainHostName(host) {\n"
"    return (host.search('\\\\.') == -1);\n"
"}\n"

"function isResolvable(host) {\n"
"    var ip = dnsResolve(host);\n"
"    return (ip != null);\n"
"}\n"

"if (typeof(dnsResolveEx) == \"function\") {\n"
  "function isResolvableEx(host) {\n"
  "    var ip = dnsResolveEx(host);\n"
  "    return (ip != null);\n"
  "}\n"
"}\n"

"function localHostOrDomainIs(host, hostdom) {\n"
"    return (host == hostdom) ||\n"
"           (hostdom.lastIndexOf(host + '.', 0) == 0);\n"
"}\n"

"function shExpMatch(url, pattern) {\n"
"   pattern = pattern.replace(/\\./g, '\\\\.');\n"
"   pattern = pattern.replace(/\\*/g, '.*');\n"
"   pattern = pattern.replace(/\\?/g, '.');\n"
"   var newRe = new RegExp('^'+pattern+'$');\n"
"   return newRe.test(url);\n"
"}\n"

"var wdays = {SUN: 0, MON: 1, TUE: 2, WED: 3, THU: 4, FRI: 5, SAT: 6};\n"

"var months = {JAN: 0, FEB: 1, MAR: 2, APR: 3, MAY: 4, JUN: 5, JUL: 6, AUG: 7, SEP: 8, OCT: 9, NOV: 10, DEC: 11};\n"

"function weekdayRange() {\n"
"    function getDay(weekday) {\n"
"        if (weekday in wdays) {\n"
"            return wdays[weekday];\n"
"        }\n"
"        return -1;\n"
"    }\n"
"    var date = new Date();\n"
"    var argc = arguments.length;\n"
"    var wday;\n"
"    if (argc < 1)\n"
"        return false;\n"
"    if (arguments[argc - 1] == 'GMT') {\n"
"        argc--;\n"
"        wday = date.getUTCDay();\n"
"    } else {\n"
"        wday = date.getDay();\n"
"    }\n"
"    var wd1 = getDay(arguments[0]);\n"
"    var wd2 = (argc == 2) ? getDay(arguments[1]) : wd1;\n"
"    return (wd1 == -1 || wd2 == -1) ? false\n"
"                                    : (wd1 <= wday && wday <= wd2);\n"
"}\n"

"function dateRange() {\n"
"    function getMonth(name) {\n"
"        if (name in months) {\n"
"            return months[name];\n"
"        }\n"
"        return -1;\n"
"    }\n"
"    var date = new Date();\n"
"    var argc = arguments.length;\n"
"    if (argc < 1) {\n"
"        return false;\n"
"    }\n"
"    var isGMT = (arguments[argc - 1] == 'GMT');\n"
"\n"
"    if (isGMT) {\n"
"        argc--;\n"
"    }\n"
"    // function will work even without explict handling of this case\n"
"    if (argc == 1) {\n"
"        var tmp = parseInt(arguments[0]);\n"
"        if (isNaN(tmp)) {\n"
"            return ((isGMT ? date.getUTCMonth() : date.getMonth()) ==\n"
"getMonth(arguments[0]));\n"
"        } else if (tmp < 32) {\n"
"            return ((isGMT ? date.getUTCDate() : date.getDate()) == tmp);\n"
"        } else { \n"
"            return ((isGMT ? date.getUTCFullYear() : date.getFullYear()) ==\n"
"tmp);\n"
"        }\n"
"    }\n"
"    var year = date.getFullYear();\n"
"    var date1, date2;\n"
"    date1 = new Date(year,  0,  1,  0,  0,  0);\n"
"    date2 = new Date(year, 11, 31, 23, 59, 59);\n"
"    var adjustMonth = false;\n"
"    for (var i = 0; i < (argc >> 1); i++) {\n"
"        var tmp = parseInt(arguments[i]);\n"
"        if (isNaN(tmp)) {\n"
"            var mon = getMonth(arguments[i]);\n"
"            date1.setMonth(mon);\n"
"        } else if (tmp < 32) {\n"
"            adjustMonth = (argc <= 2);\n"
"            date1.setDate(tmp);\n"
"        } else {\n"
"            date1.setFullYear(tmp);\n"
"        }\n"
"    }\n"
"    for (var i = (argc >> 1); i < argc; i++) {\n"
"        var tmp = parseInt(arguments[i]);\n"
"        if (isNaN(tmp)) {\n"
"            var mon = getMonth(arguments[i]);\n"
"            date2.setMonth(mon);\n"
"        } else if (tmp < 32) {\n"
"            date2.setDate(tmp);\n"
"        } else {\n"
"            date2.setFullYear(tmp);\n"
"        }\n"
"    }\n"
"    if (adjustMonth) {\n"
"        date1.setMonth(date.getMonth());\n"
"        date2.setMonth(date.getMonth());\n"
"    }\n"
"    if (isGMT) {\n"
"    var tmp = date;\n"
"        tmp.setFullYear(date.getUTCFullYear());\n"
"        tmp.setMonth(date.getUTCMonth());\n"
"        tmp.setDate(date.getUTCDate());\n"
"        tmp.setHours(date.getUTCHours());\n"
"        tmp.setMinutes(date.getUTCMinutes());\n"
"        tmp.setSeconds(date.getUTCSeconds());\n"
"        date = tmp;\n"
"    }\n"
"    return ((date1 <= date) && (date <= date2));\n"
"}\n"

"function timeRange() {\n"
"    var argc = arguments.length;\n"
"    var date = new Date();\n"
"    var isGMT= false;\n"
"\n"
"    if (argc < 1) {\n"
"        return false;\n"
"    }\n"
"    if (arguments[argc - 1] == 'GMT') {\n"
"        isGMT = true;\n"
"        argc--;\n"
"    }\n"
"\n"
"    var hour = isGMT ? date.getUTCHours() : date.getHours();\n"
"    var date1, date2;\n"
"    date1 = new Date();\n"
"    date2 = new Date();\n"
"\n"
"    if (argc == 1) {\n"
"        return (hour == arguments[0]);\n"
"    } else if (argc == 2) {\n"
"        return ((arguments[0] <= hour) && (hour <= arguments[1]));\n"
"    } else {\n"
"        switch (argc) {\n"
"        case 6:\n"
"            date1.setSeconds(arguments[2]);\n"
"            date2.setSeconds(arguments[5]);\n"
"        case 4:\n"
"            var middle = argc >> 1;\n"
"            date1.setHours(arguments[0]);\n"
"            date1.setMinutes(arguments[1]);\n"
"            date2.setHours(arguments[middle]);\n"
"            date2.setMinutes(arguments[middle + 1]);\n"
"            if (middle == 2) {\n"
"                date2.setSeconds(59);\n"
"            }\n"
"            break;\n"
"        default:\n"
"          throw 'timeRange: bad number of arguments'\n"
"        }\n"
"    }\n"
"\n"
"    if (isGMT) {\n"
"        date.setFullYear(date.getUTCFullYear());\n"
"        date.setMonth(date.getUTCMonth());\n"
"        date.setDate(date.getUTCDate());\n"
"        date.setHours(date.getUTCHours());\n"
"        date.setMinutes(date.getUTCMinutes());\n"
"        date.setSeconds(date.getUTCSeconds());\n"
"    }\n"
"    return ((date1 <= date) && (date <= date2));\n"
"}\n"

"function findProxyForURL(url, host) {\n"
"    if (typeof FindProxyForURLEx == 'function') {\n"
"        return FindProxyForURLEx(url, host);\n"
"    } else {\n"
"        return FindProxyForURL(url, host);\n"
"    }\n"
"}\n";


// You must free the result if result is non-NULL.
char *str_replace(const char *orig, char *rep, char *with) {
    char *tmporig = malloc(strlen(orig) + 1); // Copy of orig that we work with
    tmporig = strcpy(tmporig, orig);

    char *result;  // the return string
    char *ins;     // the next insert point
    char *tmp;     // varies
    int count;     // number of replacements
    int len_front; // distance between rep and end of last rep
    int len_rep  = strlen(rep);
    int len_with = strlen(with);

    // Get the count of replacements
    ins = tmporig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(tmporig) + (len_with - len_rep) * count + 1);

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in tmporig
    //    tmporig points to the remainder of tmporig after "end of rep"
    while (count--) {
        ins = strstr(tmporig, rep);
        len_front = ins - tmporig;
        tmp = strncpy(tmp, tmporig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        tmporig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, tmporig);
    return result;
}