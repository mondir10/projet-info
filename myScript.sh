#!/bin/bash

start=$(date +%s)


if [ $# -lt 2 ]; then

  echo "Erreur: arguments insuffisants"

  exit 1

fi


if [ ! -f bin/water ]; then

  make || exit 2

fi


./bin/water "$@"

ret=$?


end=$(date +%s)

echo "Durée: $((end-start)) secondes"

exit $ret
