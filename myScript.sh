#!/bin/bash

# ============================
# WildWater - Script principal
# ============================

# ---- Vérification arguments ----
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <csv_file>"
    exit 1
fi

CSV="$1"

if [ ! -f "$CSV" ]; then
    echo "Erreur : fichier CSV introuvable -> $CSV"
    exit 1
fi

echo "CSV utilisé : $CSV"
echo "--------------------------"

# ---- Compilation ----
echo "Compilation..."
make clean && make
if [ $? -ne 0 ]; then
    echo "Erreur de compilation"
    exit 1
fi
echo "Compilation OK"
echo "--------------------------"

# ---- Calculs histogrammes ----
echo "Calcul des histogrammes..."
./wildwater_test "$CSV" max
./wildwater_test "$CSV" src
./wildwater_test "$CSV" real
echo "Histogrammes OK"
echo "--------------------------"

# ---- Calcul des fuites ----
echo "Calcul des pertes du réseau..."
./wildwater_test "$CSV" loss
echo "Pertes OK"
echo "--------------------------"

# ---- Graphiques ----
echo "Génération des graphiques..."
cd plots || exit 1

# Histogrammes
gnuplot -e "INPUT='../histo_max.dat'; OUTPUT='histo_max_small.png'; TITLE='50 plus petites usines (max)'; COUNT=50" histo.gnuplot
gnuplot -e "INPUT='../histo_max.dat'; OUTPUT='histo_max_big.png'; TITLE='10 plus grandes usines (max)'; COUNT=10" histo.gnuplot

gnuplot -e "INPUT='../histo_src.dat'; OUTPUT='histo_src_small.png'; TITLE='50 plus petites usines (src)'; COUNT=50" histo.gnuplot
gnuplot -e "INPUT='../histo_real.dat'; OUTPUT='histo_real_small.png'; TITLE='50 plus petites usines (real)'; COUNT=50" histo.gnuplot

# Pertes
gnuplot -e "INPUT='../losses.dat'; OUTPUT='losses_big.png'; TITLE='Plus grandes pertes du réseau'; COUNT=50" histo.gnuplot

cd ..

echo "--------------------------"
echo "TOUT EST TERMINE"
echo "Fichiers générés :"
echo "  - histo_*.dat"
echo "  - losses.dat"
echo "  - plots/*.png"

