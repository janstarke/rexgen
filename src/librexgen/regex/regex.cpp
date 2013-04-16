/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#include <librexgen/regex/regex.h>

int Regex::next_id = 0;

void Regex::xmlEncapsulate(
    SimpleString& dst, const char* clazz, int level) const {
  dst .push_back('<')
      .append(clazz)
      .append(" id=\"")
      .append(getId())
      .append("\" min=\"")
      .append(getMinOccurs())
      .append("\" max=\"")
      .append(getMaxOccurs())
      .append("\">")
      .newline();
  appendContent(dst, level+1);
  appendSpace(dst, level);
  dst .append("</")
      .append(clazz)
      .append(">")
      .newline();
}

void Regex::appendSpace(SimpleString& dst, int count) const {
  while (count > 0) {
    dst.push_back(' ');
    --count;
  }
}
