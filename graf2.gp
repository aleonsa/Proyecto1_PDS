# GRAFICA CUATRO GRAFICAS EN UNA VENTANA
# l@rry
#set term corel
set output  "Dos_graficas.eps"

set autoscale
set multiplot layout 2,1 rowsfirst
set grid
set style data lines

#------------- Graf 1 ----------------
set title "Sine Function"
#unset label
set xlabel   "muestras"
set ylabel   "x(n)"
plot  "sin.dat"
unset xlabel
unset ylabel
unset title

#------------- Graf 2 ----------------
set title "Sine Func. with 4dB noise added"
# unset label
set xlabel   "k"
set ylabel   "y(n)"
plot  "sinNoise.dat"
unset xlabel
unset ylabel
unset title
#pause(3)
#unset multiplot

#
