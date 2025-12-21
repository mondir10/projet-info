set terminal png size 1200,800
set datafile separator ";"

set style data histograms
set style fill solid 0.8 border -1
set boxwidth 0.8
set grid ytics

set xtics rotate by -45
set ylabel "Volume (M.m3)"

set title TITLE
set output OUTPUT

plot INPUT using 2:xtic(1) every ::1::COUNT notitle
