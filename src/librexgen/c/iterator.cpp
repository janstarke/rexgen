/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/c/iterator.h>
#include <librexgen/c/ApiContext.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/topiterator.h>
#include <librexgen/librexgen.h>
#include <librexgen/parser/syntaxerror.h>
#include <librexgen/version.h>
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT
c_iterator_ptr c_regex_iterator(c_regex_ptr regex) {
  if (regex == c_regex_none) {
    return c_iterator_none;
  }
  return ApiContext::instance().addIterator(
          std::make_unique<rexgen::TopIterator>(
                  ApiContext::instance().getRegex(regex)));
}

static callback_fp CALLBACK_WCWRAPPER = NULL;
static wchar_t callback_buffer[BUFSIZ];
static size_t callback_wc_wrapper(char* dst, const size_t buffer_size) {
  CALLBACK_WCWRAPPER(&callback_buffer[0],
                     sizeof(callback_buffer) / sizeof(callback_buffer[0]));
  return wcstombs(dst, callback_buffer, buffer_size);
}

EXPORT
c_iterator_ptr c_regex_iterator_cb(
  const char* regex_str,
  int ignore_case = 0,
  callback_fp callback = NULL) {
  rexgen::RexgenOptions options;
  options.ignore_case = static_cast<bool>(ignore_case);
  options.infile = NULL;

  CALLBACK_WCWRAPPER = callback;
  options.stream_callback = callback_wc_wrapper;

  try {
    return ApiContext::instance().addIterator(regex_iterator(regex_str, options));
  } catch (SyntaxError& error) {
    c_rexgen_set_last_error(error.getMessage());
    return c_regex_none;
  }
}

EXPORT
c_iterator_ptr c_regex_iterator_cb_mb(
        const char* regex_str,
        int ignore_case = 0,
        callback_fp_mb callback = NULL) {
  rexgen::RexgenOptions options;
  options.ignore_case = static_cast<bool>(ignore_case);
  options.infile = NULL;
  options.stream_callback = callback;

  try {
    return ApiContext::instance().addIterator(regex_iterator(regex_str, options));
  } catch (SyntaxError& error) {
    c_rexgen_set_last_error(error.getMessage());
    return c_iterator_none;
  }
}

EXPORT
int c_iterator_next(c_iterator_ptr iter) {
  return ApiContext::instance().getIterator(iter)->next();
}

EXPORT
void c_iterator_value(c_iterator_ptr iter, c_simplestring_ptr dst) {
  ApiContext::instance().value(iter, dst);
}


EXPORT
void c_iterator_delete(c_iterator_ptr i) {
  ApiContext::instance().deleteIterator(i);
}

EXPORT
void c_iterator_get_state(c_iterator_ptr i, char** dstptr) {
  auto dst = std::make_shared<vector<SerializableState::stateword_t>>();
  auto state = ApiContext::instance().getIterator(i)->getCurrentState();
  state->serialize(dst);
  std::string sDst = "RXS" JS_REGEX_RELEASE;
  char cpTmp[18];
  for (auto d: *dst) {
    snprintf(cpTmp, sizeof(cpTmp)/sizeof(cpTmp[0]), ",%d", d);
    sDst += cpTmp;
  }
  *dstptr = static_cast<char*>(malloc(sDst.length()+1));
  memset(*dstptr, 0, sDst.length()+1);
  strncpy(*dstptr, sDst.c_str(), sDst.length());
}

EXPORT
void c_iterator_delete_state_buffer(char* srcptr) {
  if (srcptr != NULL) {
    free(srcptr);
  }
}

EXPORT
void c_iterator_set_state(c_iterator_ptr i, char* srcptr) {
  if (strncmp(srcptr, "RXS" JS_REGEX_RELEASE ",", 7)) {
    fprintf(stderr, "Warning!  Can not resume state in rexgex library\n");
    return;
  }

  size_t words = 0;
  int count = 0;
  char* cp = strchr(srcptr, ',');
  while (cp) {
    ++cp;
    ++count;
    cp = strchr(cp, ',');
  }
  SerializableState::stateword_t* stp =
          new SerializableState::stateword_t[count];
  cp = strchr(srcptr, ',');
  count = 0;
  while (cp) {
    sscanf(cp, ",%d", &stp[count++]);
    cp = strchr(cp+1, ',');
  }
  auto state = std::make_shared<SerializableState>(
    (SerializableState::stateword_t*)stp, &words);
  ApiContext::instance().getIterator(i)->setCurrentState(state);
}

#ifdef __cplusplus
}
#endif

