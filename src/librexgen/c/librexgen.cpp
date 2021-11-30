/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#include <librexgen/c/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/regex.h>
#include <librexgen/librexgen.h>
#include <librexgen/c/ApiContext.h>
#include <wchar.h>

static const char* c_rexgen_last_error = NULL;

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
const char* c_rexgen_get_last_error() {
  return c_rexgen_last_error;
}
void c_rexgen_set_last_error(const char* msg) {
  c_rexgen_last_error = msg;
}

static callback_fp CALLBACK_WCWRAPPER = NULL;
static wchar_t callback_buffer[BUFSIZ];
static size_t callback_wc_wrapper(char* dst, const size_t buffer_size) {
  CALLBACK_WCWRAPPER(&callback_buffer[0],
                     sizeof(callback_buffer) / sizeof(callback_buffer[0]));
  return wcstombs(dst, callback_buffer, buffer_size);
}

EXPORT
c_regex_ptr __c_regex_cb_mb(
    const char* regex_str,
    callback_fp_mb cb) {
  return c_regex_cb_mb(regex_str, cb, NULL);
}

EXPORT
c_regex_ptr c_regex_cb_mb(
    const char* regex_str,
    callback_fp_mb cb,
    void (*parser_error)(const char* msg)) {
  rexgen::RexgenOptions options;
  options.stream_callback = cb;
  options.parser_error = parser_error;

  auto regex = parse_regex(regex_str, options);
  if (regex == nullptr) {
    return c_regex_none;
  }

  return ApiContext::instance().addRegex(regex);
}

EXPORT
c_regex_ptr c_regex_cb(
        const char* regex_str,
        callback_fp cb) {
  rexgen::RexgenOptions options;
  CALLBACK_WCWRAPPER = cb;
  options.stream_callback = callback_wc_wrapper;

  return ApiContext::instance().addRegex(parse_regex(regex_str, options));
}

EXPORT
void c_regex_delete(c_regex_ptr regex) {
  ApiContext::instance().deleteRegex(regex);
}

EXPORT
int c_regex_uses_callback(c_regex_ptr i) {
  auto r = ApiContext::instance().getRegex(i);
  assert (r != nullptr);
  return r->usesCallback();
}

#ifdef __cplusplus
}
#endif
