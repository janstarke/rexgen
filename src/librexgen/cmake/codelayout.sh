#!/bin/bash

find ./ -type f -name '*.cpp' -exec astyle --style=java --indent=spaces=2 {} \;