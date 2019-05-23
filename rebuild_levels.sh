#! /usr/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

node "${DIR}/level_creator/" "${DIR}/levels/" "${DIR}/src/levels.h"
