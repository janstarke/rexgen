/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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


#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <set>

using namespace std;

class Observable
{
public:
  void addObserver(Observer* observer) {
    if (observers.find(observer) == observers.end()) {
      observers.insert(observer);
    }
  }
  
  void notifyObservers() {
    for_each(observers.begin(), observers.end(),
      [this](Observer* o){o->notify(this);});
  }
  
  void removeObserver(Observer*) {
    auto iter = observers.find(observer);
    if (iter != observers.end()) {
      observers.erase(iter);
    }
  }
  
private:
  set<Oberver*> observers;
};

#endif // OBSERVABLE_H
