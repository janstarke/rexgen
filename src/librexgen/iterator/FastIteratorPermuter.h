//
// Created by Jan Starke on 2019-03-27.
//

#ifndef PROJECT_FASTITERATORPERMUTER_H
#define PROJECT_FASTITERATORPERMUTER_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/iterator/iteratorcontainer.h>

namespace rexgen {
  class Regex;

  class FastIteratorPermuter : public IteratorContainer {

  public:
    void value(SimpleString *dst) const;

    FastIteratorPermuter(const Regex &re, IteratorState &is, unsigned int occurs);

    bool next();

    void init();
  };
}


#endif //PROJECT_FASTITERATORPERMUTER_H
