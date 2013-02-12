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


#include "rexgenparsercontext.h"
#include <algorithm>

using namespace std;

void RexgenParserContext::updateAllGroupReferences()
{
  for_each(groups.cbegin(), groups.cend(), [this](pair<int,Regex*> p) {
    updateGroupReferences(p.second);
  });
}

void RexgenParserContext::updateGroupReferences(const Regex* re)
{
  fprintf(stderr, "updateGroupReferences()\n");
  for_each(groupRefs.begin(), groupRefs.end(), [re](pair<int,GroupReference*> gr) {
    fprintf(stderr, "comparing: %d == %d?\n", gr.first, re->getGroupId());
    if (gr.first == re->getGroupId()) {
      fprintf(stderr, "updating %d -> %d\n", gr.first, re->getId());
      gr.second->setRegex(re);
    }
  });
}

bool RexgenParserContext::hasInvalidGroupReferences() const
{
  bool invalids = false;
  for_each(groupRefs.cbegin(), groupRefs.cend(), 
    [&invalids](pair<int,GroupReference*> gr) { invalids |= (gr.second->getRegex() == NULL); });
  return invalids;
}

