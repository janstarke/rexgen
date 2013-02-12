/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <sstream>
#include <librexgen/parser/rexgenparsercontext.h>
#include <librexgen/regex/regex.h>
using namespace std;

int rexgen_parse(RexgenParserContext* context);

Regex* parse_regex(const char* regex, bool ignoreCase)
{
  const string re(regex);
    
  istringstream is(re);
  
  RexgenParserContext context(&is, ignoreCase);
  if (rexgen_parse(&context) != 0) {
    return NULL;
  }
#warning this must be handled with normal syntax error reporting
  assert(! context.hasInvalidGroupReferences());
  //IteratorState* state = new IteratorState(context.getGroups());
  //Iterator* iter = context.result->iterator(state);
  return context.result;
}